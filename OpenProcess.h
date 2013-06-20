#pragma once
#include <Windows.h>
#include <TlHelp32.h>

HANDLE OpenProcessByID(const DWORD id);

HANDLE OpenProcessByProcessName(const char *name);

HANDLE OpenProcessByWindowName(const char *name);

DWORD GetProcessID(const char *name);

