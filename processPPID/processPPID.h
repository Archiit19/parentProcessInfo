#pragma once

#include "stdafx.h"
#include <Windows.h>
#include <Psapi.h>



class processPPID
{
	typedef struct _PROCESS_BASIC_INFORMATION {
	LONG ExitStatus;
	PVOID PebBaseAddress;
	ULONG_PTR AffinityMask;
	LONG BasePriority;
	ULONG_PTR UniqueProcessId;
	ULONG_PTR ParentProcessId;
	} PROCESS_BASIC_INFORMATION;

	typedef NTSTATUS(NTAPI *fnNtQueryInformationProcess)(
	HANDLE ProcessHandle,
	INT ProcessInformationClass,
	PVOID ProcessInformation,
	ULONG ProcessInformationLength,
	PULONG ReturnLength
	);

	public:
		TCHAR* GetParentProcessPathandName(TCHAR* strPath, DWORD cchSize);
};