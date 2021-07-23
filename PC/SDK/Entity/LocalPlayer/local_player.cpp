#include "local_player.h"

LocalPlayer::LocalPlayer(const Module& client, const DWORD client_state)
  : AbstractLocalPlayer(
      Memory::Read<DWORD>(client.base + Signatures::dwLocalPlayer)),
    client_address_(client.base),
    client_state_(client_state) {}

int LocalPlayer::GetCrosshairId() const {
  return Memory::Read<int>(this->GetAddress() + NetVars::m_iCrosshairId);
}

Vector LocalPlayer::GetLocalViewAngle() const {
  return Memory::Read<Vector>(
      client_state_ + Signatures::dwClientState_ViewAngles);
}

std::pair<Vector, float> LocalPlayer::GetAimAngleDiffAndDistance(
    const EntityList& entity_list, int bone, float max_fov) const {
  float best_fov = 360.f;
  Vector angle_diff(0, 0, 0);
  float dist = 0.f;

  Vector view_angle = this->GetLocalViewAngle();
  NormalizeAngles(view_angle);

  const Team local_player_team = this->GetTeam();

  for (int target_id = 1; target_id <= 64; ++target_id) {
    Entity target = entity_list.GetEntity(target_id);
    if (!target.GetAddress()) {
      continue;
    }

    if (!target.IsAlive()) {
      continue;
    }

    if (target.GetTeam() == Team::kNone
        || target.GetTeam() == Team::kSpectator
        || target.GetTeam() == local_player_team) {
      continue;
    }

    if (target.IsDormant()) {
      continue;
    }

    Vector angle_to_target = this->GetAngleToTarget(target, bone);
    float fov = GetFov(view_angle.ToQAngle(), angle_to_target.ToQAngle());
    if (fov < best_fov && fov <= max_fov) {
      best_fov = fov;

      angle_diff = angle_to_target - view_angle;
      NormalizeAngles(angle_diff);

      dist = this->GetPos().DistTo(target.GetPos());
    }
  }

  return std::make_pair(angle_diff, dist);
}

Vector LocalPlayer::GetAngleToTarget(const Entity& target, int bone) const {
  const Vector cur_view = this->GetView();
  const Vector aim_view = target.GetBonePos(bone);

  Vector dst = CalcAngle(cur_view, aim_view).ToVector();
  NormalizeAngles(dst);

  return dst;
}

float LocalPlayer::GetSensitivity() const {
  DWORD ptr = client_address_ + Signatures::dwSensitivityPtr;
  auto sensitivity =
      Memory::Read<DWORD>(client_address_ + Signatures::dwSensitivity);
  sensitivity ^= ptr;
  return *reinterpret_cast<float*>(&sensitivity);
}
