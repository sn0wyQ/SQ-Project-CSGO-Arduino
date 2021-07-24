#include "SDK/Entity/LocalPlayer/local_player.h"
#include "SDK/EntityList/entity_list.h"

#include "Arduino/arduino.h"
#include "Arrays/arrays.h"
#include "Features/aim_bot.h"
#include "Features/bunny_hop.h"
#include "Features/trigger_bot.h"
#include "Global/global.h"
#include "Memory/memory.h"
#include "Timer/timer.h"
#include "Utils/utils.h"
#include "dump.h"

void Loop(const Module& client, const Module& engine) {
  Arduino::CheckArduinoOutput();

  auto client_state =
      Memory::Read<DWORD>(engine.base + Signatures::dwClientState);
  LocalPlayer local_player(client, client_state);
  if (!local_player.IsAlive()) {
    return;
  }

  BunnyHop(local_player);

  EntityList entity_list(client);

  TriggerBot(local_player, entity_list);

  AimBot(local_player, entity_list);
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
  Module engine = Memory::GetModule("engine.dll");
  Utils::Log("[MEMORY] Successfully attached to CS:GO process:");
  Utils::Log("\tClient base: %\n\tClient size: %", client.base, client.size);
  Utils::Log("\tEngine base: %\n\tEngine size: %\n", engine.base, engine.size);

  Utils::GetKey(&Global::bhop_button, "Bunny Hop");
  Utils::GetKey(&Global::trigger_bot_button, "Trigger Bot");
  Utils::GetKey(&Global::aim_bot_button, "Aim Bot");

  Utils::Log("Cheat started successfully!\n");

  while (true) {
    Loop(client, engine);
  }

  Memory::Detach();
  system("pause");

  return 0;
}
