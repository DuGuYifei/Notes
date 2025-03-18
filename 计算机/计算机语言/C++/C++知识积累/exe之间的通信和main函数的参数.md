# exe之间的通信和main函数的参数

- 发送函数：
  ```cpp
  ss.append("\\Controller.exe ");
  std::string play = std::to_string((int)hFfplay);
  LPTSTR a = (LPTSTR)string2LPCWSTR(play);
  if (CreateProcess(s2ws(ss).c_str(), (LPTSTR)string2LPCWSTR(play), 0, 0, 0, 0, 0, 0, &si, &pi))
  {
  	CloseHandle(pi.hProcess);	CloseHandle(pi.hThread);
  }
  ```

- 接受函数：
  ```cpp
  int main(int argc, char* argv[])
  {
    hFfplay = (HWND)atoi(argv[0]);
  }
  ```
  1. `argc` 是参数个数，不需要输入
  2. `argv` 就是你在cmd里输入的 `-L -V` 之类的, 所以上面一样可以用`ShellExecuteA`来他代替`CreateProcess`
     ```cpp
     ShellExecuteA(NULL, "open",  //调用程序
     "D:\\Documents\\Visual Studio 2010\\Projects\\传参\\Debug\\接受参数.exe" 
     ,s.c_str(),NULL,SW_SHOW);
     system("pause");
     ```