# 得到和设置鼠标位置GetCursor_SetCursor

[SendMessage()模拟鼠标键盘输入给另一个文件](SendMessage()模拟鼠标键盘输入给另一个窗口.md)

POINT 点类

```cpp
#include <windows.h>
//#include <WinUser.h>
POINT lpPoint;
GetCursorPos(&lpPoint);
SetCursorPos(lpPoint.x, lpPoint.y);
```