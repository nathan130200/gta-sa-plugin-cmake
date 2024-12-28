#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include "plugin_sa.h"

BOOL WINAPI DllMain(HINSTANCE, INT reason, LPVOID)
{

	switch (reason) {
	case DLL_PROCESS_ATTACH:
		// entrypoint
		return 1;

	default:
		return 0;
	}
}
