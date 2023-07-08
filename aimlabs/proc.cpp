#include "proc.h"

DWORD proc::getPID(const wchar_t* procName)
{
	HANDLE pHandle{ CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0) };

	if (pHandle != INVALID_HANDLE_VALUE)
	{
		PROCESSENTRY32 pEntry;

		pEntry.dwSize = sizeof(PROCESSENTRY32);

		if (Process32First(pHandle, &pEntry))
		{
			do
			{
				if (!_wcsicmp(pEntry.szExeFile, procName))
				{
					DWORD pid{ pEntry.th32ProcessID };
					CloseHandle(pHandle);
					return pid;
				}
			} while (Process32Next(pHandle, &pEntry));
		}
	}
	return 0;
}

uintptr_t proc::modBase(DWORD pid, const wchar_t* modName)
{
	HANDLE pHandle{ CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, pid) };

	if (pHandle != INVALID_HANDLE_VALUE)
	{
		MODULEENTRY32 mEntry;

		mEntry.dwSize = sizeof(MODULEENTRY32);

		if (Module32First(pHandle, &mEntry))
		{
			do
			{
				if (!_wcsicmp(mEntry.szModule, modName))
				{
					uintptr_t modBase{ (uintptr_t)mEntry.modBaseAddr };
					CloseHandle(pHandle);
					return modBase;
				}
			} while (Module32Next(pHandle, &mEntry));
		}
	}
	return 0;
}