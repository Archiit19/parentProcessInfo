// processPPID.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "processPPID.h"




TCHAR* processPPID::GetParentProcessPathandName( TCHAR* strPath, DWORD cchSize)
{
	fnNtQueryInformationProcess aNtQueryInformationProcess;
	HMODULE hModNtDll = GetModuleHandle(_T("Ntdll.dll"));

	if (!hModNtDll)
		return nullptr;

	aNtQueryInformationProcess = (fnNtQueryInformationProcess) GetProcAddress(hModNtDll, "NtQueryInformationProcess");
	
	HANDLE currProc = GetCurrentProcess();
	
	PROCESS_BASIC_INFORMATION pbi;
	NTSTATUS status = aNtQueryInformationProcess(	currProc,
													0,
													&pbi,
													sizeof(pbi),
													NULL );
	if (status < 0)
		return nullptr;

	HANDLE parentProc = OpenProcess(	PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,
										FALSE,
										pbi.ParentProcessId	);
	if (parentProc == NULL)
		return nullptr;

	
	DWORD dwSize = GetModuleFileNameEx(parentProc,
						NULL,
						strPath, 
						cchSize);
	

	CloseHandle(parentProc); parentProc = NULL;

	if (dwSize == 0 || dwSize >= cchSize)
		return nullptr;

	TCHAR * exeName = _tcsrchr(strPath, _T('\\'));
	return exeName+1;

}



int main()
{
	TCHAR strParentPath[MAX_PATH] = {};
	processPPID procPPIDObj;
	TCHAR *strExeName = procPPIDObj.GetParentProcessPathandName( strParentPath, _countof(strParentPath));
	
	if (strExeName != nullptr)
	{
		
	}
	printf("\nPath of executing Parent Process : %ls", strParentPath);
	printf("\nName of executing Parent Process : %ls", strExeName);

	getchar();
	return 0;
}

