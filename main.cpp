#include <Windows.h>
#include <iostream>
#include <thread>

int main()
{
	DWORD localplayer = 0x04C88E8;
	DWORD flags = 0x350;
	DWORD forcejump = 0x4F5D24;
	DWORD gameModule;
	gameModule = (DWORD)GetModuleHandle("client.dll");
	localplayer = *(DWORD*)(gameModule + localplayer);

	MessageBox(0, "Loading gamemodule + localplayer", "Loading gamemodule + localplayer", MB_OK); //best debug method

	if (localplayer == NULL) //sort of broken since starting a new game will cause the bhop not to work
		while (localplayer == NULL)
			  localplayer = *(DWORD*)(gameModule + localplayer);
		
	while (!GetAsyncKeyState(VK_END)) //to lazy to free lib and exit thread
	{
		byte flag = *(BYTE*)(localplayer + flags);

		if (GetAsyncKeyState(VK_SPACE) && flag & (1 << 0)) //do not switch! 
		{			
		  *(DWORD*)(gameModule + forcejump) = 6;		
		}
	}
}

//dll injecto!
BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH) {

		DisableThreadLibraryCalls(hModule);
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)main, NULL, NULL, NULL);
		MessageBox(0, "Injected Succesfully", "Injected Succesfully", MB_OK);
	
	}
	return TRUE;
}
