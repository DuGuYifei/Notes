# CreateProcess()创建进程

```c#
BOOL CreateProcessA(
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
);
```

- 第一项可以写到第二项
- 第一项是你的程序完整路径或相对路径
- 第二项是传递的参数（跟其C#唤醒不一样，传递的参数从0开始，c#或c++调试时，第一个参数是程序路径）
- 第二个参数开头要空格
- 6个0
- 确认打开和查找主窗口
  ```c++
  	LPTSTR p = (LPTSTR)stringToLPCWSTR(parameter);
	STARTUPINFO si{ 0 };
	PROCESS_INFORMATION pi{ 0 };
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));
	if (CreateProcess(program, p, 0, 0, 0, 0, 0, 0, &si, &pi))
	{
		ProcessWindow procwin;
		procwin.dwProcessId = pi.dwProcessId;
		procwin.hwndWindow = NULL;

		// 查找主窗口，找到了说明打开了，不然有可能在加载中需要等待
		while (EnumWindows(EnumWindowCallBack, (LPARAM)&procwin))
		{
			Sleep(1000);
		}

		CloseHandle(pi.hProcess);	CloseHandle(pi.hThread);

		HWND hwnd = procwin.hwndWindow;
    }
    ```