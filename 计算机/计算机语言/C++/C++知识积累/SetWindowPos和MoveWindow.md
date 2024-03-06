# SetWindowPos和MoveWindow

都是按父窗口位置，但是SetWindowPos好像对屏幕数适配有问题，待测试

1. `SetWindowPos(hwnd,left,right,width,height,特殊信息)`

   [SetWindowPos function (winuser.h) - Win32 apps](https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-setwindowpos)

   return bool

2. `MoveWindow(hwnd,left,right,width,height,bool repaint)`
   
   [MoveWindow function (winuser.h) - Win32 apps](https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-movewindow)

   return bool

3. `std::cout<<GetLastError()`
   
   查看错误代码

   错误代码：[Tutorial - Debug system error codes - Win32 apps](https://docs.microsoft.com/en-us/windows/win32/debug/system-error-codes)