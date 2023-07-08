#pragma once
#include <Windows.h>
#include <TlHelp32.h>

namespace proc
{
	DWORD getPID(const wchar_t* procName);

	uintptr_t modBase(DWORD pid, const wchar_t* modName);
}