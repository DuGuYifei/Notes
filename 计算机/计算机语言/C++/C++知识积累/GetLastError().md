# GetLastError()

[WinError.h (0-499)  (系统错误)  - Win32 apps](https://docs.microsoft.com/zh-cn/windows/win32/debug/system-error-codes--0-499-?redirectedfrom=MSDN)

```c++
if(!CreateProcess())
{
    printf(GetLastError());
}
```

| 错误码 | 错误       |
| ------ | --------- |
| 3      | 找不到路径 |
| 123    | 路径不正确 |