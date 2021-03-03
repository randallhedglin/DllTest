#include <iostream>
#include <string>

#include <WinSDKVer.h> // load flags
	#define NTDDI_VERSION NTDDI_WINBLUE
	#define _WIN32_WINNT  _WIN32_WINNT_WINBLUE
	#define WINVER        _WIN32_WINNT_WINBLUE
#include <sdkddkver.h> // apply flags

#define WIN32_LEAN_AND_MEAN // keep it light

#include <windows.h> // basic Windows components

#include "FlashRuntimeExtensions.h"

#define DEBUG_MSG(msg) { MessageDialog^ dialog = ref new MessageDialog(msg); dialog->ShowAsync(); }

#define DECL_LIB_FN_PROTOTYPE(fn) typedef FREObject (__cdecl *fn)(FREContext, void*, uint32_t, FREObject*)

typedef void (__cdecl *_WindowsANEExtensionInitializer)(void**, FREContextInitializer*, FREContextFinalizer*);
typedef void (__cdecl *_WindowsANEContextInitializer)(void*, const uint8_t*, FREContext, uint32_t*, const FRENamedFunction**);
typedef void (__cdecl *_WindowsANEContextFinalizer)(void*);

DECL_LIB_FN_PROTOTYPE(_addFullScreenButton);
DECL_LIB_FN_PROTOTYPE(_messageBox);
DECL_LIB_FN_PROTOTYPE(_testANE);
DECL_LIB_FN_PROTOTYPE(_toggleFullScreen);

int main()
{
	HMODULE hModule = NULL;

	std::cout << "Attempt #1: LoadLibraryEx(DONT_RESOLVE_DLL_REFERENCES)" << std::endl;
	std::cout << std::endl;

	hModule = LoadLibraryEx(TEXT("C:\\Users\\Randall Hedglin\\Documents\\Adobe Flash Builder\\WindowsANE\\build\\windows\\WindowsANE.dll"),
							NULL,
							DONT_RESOLVE_DLL_REFERENCES);
	
	std::cout << "err = " << GetLastError() << std::endl;
	std::cout << std::endl;

	std::cout << "hm  = " << hModule << std::endl;
	std::cout << std::endl;

	if(hModule)
	{
		_WindowsANEExtensionInitializer WindowsANEExtensionInitializer = (_WindowsANEExtensionInitializer) GetProcAddress(hModule, "WindowsANEExtensionInitializer");
		std::cout << "ei  = " << WindowsANEExtensionInitializer << std::endl;
		_WindowsANEContextInitializer WindowsANEContextInitializer = (_WindowsANEContextInitializer) GetProcAddress(hModule, "WindowsANEContextInitializer");
		std::cout << "ci  = " << WindowsANEContextInitializer << std::endl;
		_WindowsANEContextFinalizer WindowsANEContextFinalizer = (_WindowsANEContextFinalizer) GetProcAddress(hModule, "WindowsANEContextFinalizer");
		std::cout << "cf  = " << WindowsANEContextFinalizer << std::endl;
		_addFullScreenButton addFullScreenButton = (_addFullScreenButton) GetProcAddress(hModule, "addFullScreenButton");
		std::cout << "afs = " << addFullScreenButton << std::endl;
		_messageBox messageBox = (_messageBox) GetProcAddress(hModule, "messageBox");
		std::cout << "mb  = " << messageBox << std::endl;
		_testANE testANE = (_testANE) GetProcAddress(hModule, "testANE");
		std::cout << "ta  = " << testANE << std::endl;
		_toggleFullScreen toggleFullScreen = (_toggleFullScreen) GetProcAddress(hModule, "toggleFullScreen");
		std::cout << "tfs = " << toggleFullScreen << std::endl;
		std::cout << std::endl;

		FreeLibrary(hModule);
		hModule = NULL;
	}

	std::cout << "Attempt #2: LoadLibrary() only" << std::endl;
	std::cout << std::endl;

	hModule = LoadLibrary(TEXT("C:\\Users\\Randall Hedglin\\Documents\\Adobe Flash Builder\\WindowsANE\\build\\windows\\WindowsANE.dll"));
	
	std::cout << "err = " << GetLastError() << std::endl;
	std::cout << std::endl;

	std::cout << "hm  = " << hModule << std::endl;
	std::cout << std::endl;

	if(hModule)
	{
		_WindowsANEExtensionInitializer WindowsANEExtensionInitializer = (_WindowsANEExtensionInitializer) GetProcAddress(hModule, "WindowsANEExtensionInitializer");
		std::cout << "ei  = " << WindowsANEExtensionInitializer << std::endl;
		_WindowsANEContextInitializer WindowsANEContextInitializer = (_WindowsANEContextInitializer) GetProcAddress(hModule, "WindowsANEContextInitializer");
		std::cout << "ci  = " << WindowsANEContextInitializer << std::endl;
		_WindowsANEContextFinalizer WindowsANEContextFinalizer = (_WindowsANEContextFinalizer) GetProcAddress(hModule, "WindowsANEContextFinalizer");
		std::cout << "cf  = " << WindowsANEContextFinalizer << std::endl;
		_addFullScreenButton addFullScreenButton = (_addFullScreenButton) GetProcAddress(hModule, "addFullScreenButton");
		std::cout << "afs = " << addFullScreenButton << std::endl;
		_messageBox messageBox = (_messageBox) GetProcAddress(hModule, "messageBox");
		std::cout << "mb  = " << messageBox << std::endl;
		_testANE testANE = (_testANE) GetProcAddress(hModule, "testANE");
		std::cout << "ta  = " << testANE << std::endl;
		_toggleFullScreen toggleFullScreen = (_toggleFullScreen) GetProcAddress(hModule, "toggleFullScreen");
		std::cout << "tfs = " << toggleFullScreen << std::endl;
		std::cout << std::endl;

		if(WindowsANEExtensionInitializer)
		{
			void* pAppData;
			FREContextInitializer fnCtxInit;
			FREContextFinalizer fnCtxFinal;

			WindowsANEExtensionInitializer(&pAppData, &fnCtxInit, &fnCtxFinal);
			std::cout << "dll ci = " << fnCtxInit << std::endl;
			std::cout << "dll cf = " << fnCtxFinal << std::endl;
		}

		FreeLibrary(hModule);
		hModule = NULL;
	}

	Sleep(3600000); // 1 hour

	return(0);
}

