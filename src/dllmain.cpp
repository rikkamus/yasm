#include <algorithm>
#include <filesystem>
#include <fstream>
#include <queue>

#define NOMINMAX
#include "sdk/inc/enums.h"
#include "sdk/inc/main.h"
#include "sdk/inc/natives.h"

#include "config.h"
#include "speed.h"
#include "text.h"

static const float ALPHA_ADJUSTMENT_SPEED = 765.0f;

static HMODULE module;

static float lastSpeedMps = 0.0f;
static float alpha = 0.0f;

static Config config;
static std::string configLoadErrorMessage = "";

static bool playerInVehicleLastFrame = false;

static void loadConfig() {
    configLoadErrorMessage = "";

    std::vector<wchar_t> buffer = std::vector<wchar_t>(MAX_PATH, L'\0');
    DWORD length;

    while ((length = GetModuleFileName(module, buffer.data(), (DWORD) buffer.size())) >= buffer.size()) {
        buffer.resize(buffer.size() * 2, L'\0');
    }

    if (length == 0) {
        configLoadErrorMessage = "Could not get module file name.";
        return;
    }

    std::filesystem::path filePath = std::filesystem::path(std::wstring(buffer.data()));
    filePath.replace_extension("ini");

    std::ifstream stream = std::ifstream(filePath);
    if (!stream.is_open()) {
        configLoadErrorMessage = "Could not find config file.";
        return;
    }

    try {
        config.load(stream);
    } catch (const ConfigParseException &e) {
        configLoadErrorMessage = e.what();
        return;
    }

    if (stream.bad() || !stream.eof()) {
        configLoadErrorMessage = "Failed to parse config file.";
    }
}

static void renderSpeedometer() {
    const std::string displayString = formatSpeed(config.formatString, lastSpeedMps);

    TextStyle style = TextStyle();
    style.font = config.font;
    style.alpha = (int) alpha;
    style.scale = config.scale;

    renderText(displayString, config.anchor, config.offsetX, config.offsetY, style);
}

static void displayErrorNotification(const std::string &title, const std::string &message) {
    UI::_SET_NOTIFICATION_TEXT_ENTRY((char*) "STRING");
    UI::_ADD_TEXT_COMPONENT_STRING((char*) message.c_str());
    UI::_SET_NOTIFICATION_MESSAGE((char*) "CHAR_MP_FM_CONTACT", (char*) "CHAR_MP_FM_CONTACT", FALSE, 2, (char*) "Yet Another Speedometer Mod", (char*) title.c_str());
    UI::_DRAW_NOTIFICATION(TRUE, TRUE);
}

static void tick() {
    const Player player = PLAYER::PLAYER_ID();
    const Ped playerPed = PLAYER::PLAYER_PED_ID();

    if (!ENTITY::DOES_ENTITY_EXIST(playerPed)) {
        alpha = 0.0f;
        playerInVehicleLastFrame = false;
        return;
    }

    if (config.hideVehicleName) UI::HIDE_HUD_COMPONENT_THIS_FRAME(6);

    const bool playerInVehicle = PED::IS_PED_IN_ANY_VEHICLE(playerPed, FALSE);
    const bool playerInVehicleAndPhoneHidden = playerInVehicle && (!config.hideWhenUsingPhone || !PED::IS_PED_RUNNING_MOBILE_PHONE_TASK(playerPed));

    if (!PLAYER::IS_PLAYER_CONTROL_ON(player) || ENTITY::IS_ENTITY_DEAD(playerPed) || PLAYER::IS_PLAYER_BEING_ARRESTED(player, TRUE)) {
        alpha = playerInVehicleAndPhoneHidden ? 255.0f : 0.0f;
        playerInVehicleLastFrame = playerInVehicle;
        return;
    }

    if (playerInVehicle && !playerInVehicleLastFrame && !configLoadErrorMessage.empty()) {
        displayErrorNotification("~r~Config Load Error", configLoadErrorMessage);
    }

    playerInVehicleLastFrame = playerInVehicle;

    if (playerInVehicleAndPhoneHidden) {
        lastSpeedMps = getPedVehicleSpeedMps(playerPed);
        alpha = std::min(alpha + ALPHA_ADJUSTMENT_SPEED * GAMEPLAY::GET_FRAME_TIME(), config.opacity * 255.0f);
    } else {
        alpha = std::max(alpha - ALPHA_ADJUSTMENT_SPEED * GAMEPLAY::GET_FRAME_TIME(), 0.0f);
    }

    renderSpeedometer();
}

static void scriptMain() {
    loadConfig();

    while (true) {
        tick();
        scriptWait(0);
    }
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    switch (ul_reason_for_call) {
        case DLL_PROCESS_ATTACH:
            module = hModule;
            scriptRegister(hModule, scriptMain);
            break;
        case DLL_PROCESS_DETACH:
            scriptUnregister(hModule);
            break;
    }

    return TRUE;
}
