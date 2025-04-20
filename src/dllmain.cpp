#include "sdk/inc/main.h"

void scriptMain() {

}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    switch (ul_reason_for_call) {
        case DLL_PROCESS_ATTACH:
            scriptRegister(hModule, scriptMain);
            break;
        case DLL_PROCESS_DETACH:
            scriptUnregister(hModule);
            break;
    }

    return TRUE;
}
