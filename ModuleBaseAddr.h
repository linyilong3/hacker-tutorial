#pragma once
#include <Windows.h>
DWORD GetBaseAddr(const char *process_name);

DWORD GetBaseAddrByEnumProcess(const char *process_name);