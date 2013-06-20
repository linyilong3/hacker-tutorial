#include "OpenProcess.h"


HANDLE OpenProcessByID( const DWORD id )
{
	return OpenProcess(PROCESS_ALL_ACCESS,FALSE,id);
}

HANDLE OpenProcessByProcessName( const char *name )
{
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0); 
	if (hSnapshot == INVALID_HANDLE_VALUE)
	{
		CloseHandle(hSnapshot);
		return INVALID_HANDLE_VALUE;
	}

	PROCESSENTRY32 pe32;
	DWORD id = 0;
	pe32.dwSize = sizeof(PROCESSENTRY32);
	if ( !Process32First(hSnapshot,&pe32) )
	{
		CloseHandle(hSnapshot);
		return INVALID_HANDLE_VALUE;
	}

	while ( 1 )
	{
		pe32.dwSize = sizeof(PROCESSENTRY32);
		if (Process32Next(hSnapshot,&pe32) == FALSE)
			break;

		if ( strcmp(pe32.szExeFile,name)==0 )
		{
			return OpenProcessByID(pe32.th32ProcessID);
		}
	}

	CloseHandle(hSnapshot);

	return INVALID_HANDLE_VALUE;
}

HANDLE OpenProcessByWindowName( const char *name )
{
	HWND hWnd = FindWindow(NULL,name);

	if (hWnd != NULL)
	{
		DWORD ThreadID = -1;
		DWORD ProcessID = -1;
		ThreadID = GetWindowThreadProcessId(hWnd,&ProcessID);

		return OpenProcessByID(ProcessID);
	}
	return INVALID_HANDLE_VALUE;

}

DWORD GetProcessID( const char *name )
{
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0); 
	if (hSnapshot == INVALID_HANDLE_VALUE)
	{
		CloseHandle(hSnapshot);
		return -1;
	}

	PROCESSENTRY32 pe32;
	DWORD id = 0;
	pe32.dwSize = sizeof(PROCESSENTRY32);
	if ( !Process32First(hSnapshot,&pe32) )
	{
		CloseHandle(hSnapshot);
		return -1;
	}

	while ( 1 )
	{
		pe32.dwSize = sizeof(PROCESSENTRY32);
		if (Process32Next(hSnapshot,&pe32) == FALSE)
			break;

		if ( strcmp(pe32.szExeFile,name)==0 )
		{
			return (pe32.th32ProcessID);
		}
	}

	CloseHandle(hSnapshot);

	return -1;
}

