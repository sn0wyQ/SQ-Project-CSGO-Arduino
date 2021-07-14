#include "SDK/Entity/LocalPlayer/local_player.h"
#include "SDK/Entity/entity.h"
#include "SDK/EntityList/entity_list.h"

#include "Arduino/arduino.h"
#include "Arrays/arrays.h"
#include "Global/global.h"
#include "Memory/memory.h"
#include "Timer/timer.h"
#include "Utils/utils.h"
#include "dump.h"

void CheckArduinoOutput() {
  char output;
  if (Arduino::ReadByte(&output)) {
    switch (output) {
      case ER_UNKNOWN_CMD: {
        Utils::Log("[ARDUINO] Internal Error: unknown command");
        break;
      }

      default: {
        Utils::Log("[ARDUINO] Error: Output \"%\" can not be recognized as "
                   "a command", output);
        break;
      }
    }
  }
}

void BunnyHop(const LocalPlayer& local_player) {
  if (!Utils::IsHeld(Global::bhop_button)) {
    return;
  }

  if (local_player.IsInAir()) {
    return;
  }

  Arduino::SendCommand(CMD_JUMP);
}

void TriggerBot(const LocalPlayer& local_player,
                const EntityList& entity_list) {
  // TODO(sn0wyQ): return if trigger bot is not active

  int target_entity_index = local_player.GetCrosshairId();
  if (!EntityList::CanBeEntity(target_entity_index)) {
    return;
  }

  Entity target_entity = entity_list.GetEntity(target_entity_index);
  if (!target_entity.IsAlive()
      || target_entity.GetTeam() == local_player.GetTeam()) {
    return;
  }

  // TODO(sn0wyQ): add Arduino::SendCommand(CMD_SHOOT);
}

void Loop(const Module& client) {
  CheckArduinoOutput();

  LocalPlayer local_player(client);
  if (!local_player.IsAlive()) {
    return;
  }

  BunnyHop(local_player);

  EntityList entity_list(client);

  TriggerBot(local_player, entity_list);
}

int main() {
  Utils::Log(">>> SQ Project for Arduino | CS:GO Edition | v0.0.1 <<<\n");

  Utils::Log("[ARDUINO] Trying to find Arduino Leonardo...");
  Timer finding_arduino_timer;
  bool found_arduino = false;
  while (finding_arduino_timer.GetElapsedS() < 30.f
         && !found_arduino) {
    char com_port[256] = R"(\\.\)";
    found_arduino = Arduino::GetDevice("Arduino Leonardo", com_port);
    if (found_arduino) {
      Arduino::Connect(com_port);
    }
  }
  if (!found_arduino) {
    Utils::Log("[ARDUINO] Error: Failed finding Arduino Leonardo after %s",
               finding_arduino_timer.GetElapsedS());
    return 0;
  }

  Utils::Log("[MEMORY] Trying to attach to CS:GO process...");
  Timer attaching_to_process_timer;
  bool is_attached_to_process = false;
  while (attaching_to_process_timer.GetElapsedS() < 30.f
         && !is_attached_to_process) {
    is_attached_to_process = Memory::Attach("csgo.exe", PROCESS_ALL_ACCESS);
  }
  if (!is_attached_to_process) {
    Utils::Log("[MEMORY] Error: Failed attaching to CS:GO process after %s",
               attaching_to_process_timer.GetElapsedS());
    return 0;
  }
  Module client = Memory::GetModule("client.dll");
  Utils::Log("[MEMORY] Successfully attached to CS:GO process:");
  Utils::Log("\tBase: %\n\tSize: %\n", client.base, client.size);

  Utils::GetKey(&Global::bhop_button, "Bunny Hop");

  while (true) {
    Loop(client);
    Sleep(1);
  }

  Memory::Detach();

  return 0;
}
