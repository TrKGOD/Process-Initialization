#include <windows.h>
#include <stdio.h>
#include <psapi.h>

int main() {

	/*BOOL CreateProcessA(
  [in, optional]      LPCSTR                lpApplicationName,
  [in, out, optional] LPSTR                 lpCommandLine,
  [in, optional]      LPSECURITY_ATTRIBUTES lpProcessAttributes,
  [in, optional]      LPSECURITY_ATTRIBUTES lpThreadAttributes,
  [in]                BOOL                  bInheritHandles,
  [in]                DWORD                 dwCreationFlags,
  [in, optional]      LPVOID                lpEnvironment,
  [in, optional]      LPCSTR                lpCurrentDirectory,
  [in]                LPSTARTUPINFOA        lpStartupInfo,
  [out]               LPPROCESS_INFORMATION lpProcessInformation
);*/
	
	STARTUPINFO si = { 0 };
	PROCESS_INFORMATION pi = { 0 };

	if (!CreateProcessW(L"C:\\Windows\\System32\\calc.exe",
		NULL,
		NULL,
		NULL,
		FALSE,
		0,
		NULL,
		NULL,
		&si,
		&pi
	)) {

		printf("Operation Failed, error: %ld", GetLastError());
		return 0;
	}
	
	DWORD PID = pi.dwProcessId;
	DWORD TID = pi.dwThreadId;
	HANDLE hThread = pi.hThread;
	HANDLE hProcess = pi.hProcess;

	printf("got handle to process\n");
	printf("process started! pid: %ld\n", PID);
	printf("\tpid: %ld, handle: 0x%x\n", PID, hProcess);
	printf("\ttid: %ld, handle: 0x%x\n\r", TID, hThread);

	WaitForSingleObject(hProcess, INFINITE);
	printf("Done");

	CloseHandle(hThread);
	CloseHandle(hProcess);
	return 0;

}
