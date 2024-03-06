# system()和ShellExecuteA()和WinExec()直接cmd命令

- `system`是`C语言`自带API
- `ShellExecuteA`是`Win32`的API


```cpp
system("taskkill /f /IM ffplay.exe");
```

```cpp
     ShellExecuteA(NULL, "open",  //调用程序
     "D:\\Documents\\Visual Studio 2010\\Projects\\传参\\Debug\\接受参数.exe" ,
     s.c_str(),NULL,SW_SHOW);
     system("pause");
```


隐藏控制台，比system好看
```cpp
WinExec("taskkill /f /IM Controller.exe", SW_HIDE);
```