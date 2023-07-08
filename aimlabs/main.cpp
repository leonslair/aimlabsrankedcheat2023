#include <iostream>
#include <vector>
#include <Windows.h>
#include <TlHelp32.h>
#include "proc.h"

uintptr_t getAddr(HANDLE pHandle, uintptr_t modBase, std::vector<unsigned int> offsets)
{
	uintptr_t addr{ modBase };

	for (int i{ 0 }; i < offsets.size(); ++i)
	{
		ReadProcessMemory(pHandle, (LPVOID)addr, &addr, sizeof(addr), nullptr);
		addr += offsets[i];
	}
	return addr;
}

int main()
{
	DWORD pID{ proc::getPID(L"AimLab_tb.exe") };

	uintptr_t modBase{ (proc::modBase(pID, L"GameAssembly.dll") + 0x03D18BD0) };

	HANDLE pHandle{ OpenProcess(PROCESS_ALL_ACCESS, FALSE, pID) };

	std::cout << std::hex << modBase;

	uintptr_t countPtr{ getAddr(pHandle, modBase, {0xB8, 0x178, 0xB0, 0x18}) };

	float newVal{ 169696999.0f };

	WriteProcessMemory(pHandle, (LPVOID)countPtr, &newVal, sizeof(newVal), nullptr);

	CloseHandle(pHandle);

	std::cin.get();

	return 0;
}
