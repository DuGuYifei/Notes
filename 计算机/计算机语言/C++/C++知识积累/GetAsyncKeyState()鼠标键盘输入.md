# GetAsyncKeyState()鼠标键盘输入

[SendMessage()模拟鼠标键盘输入给另一个窗口](SendMessage()模拟鼠标键盘输入给另一个窗口.md)

- 用`short temp`是因为它会响应三次。

- GetCursor得到位置
- SetCursor不能省略

```cpp
    #include <windows.h>
    //#include <WinUser.h>
	POINT lpPoint;
	GetCursorPos(&lpPoint);
	bool ctrl = false, shift = false, lMouseButton = false, rMouseButton = false, space = false, enter = false, escape = false, up = false, left = false, right = false, down = false;//按下为true
	while (true)
	{
		//为了能够与下面达成组合键，ctrl和shift在上面
		if (GetAsyncKeyState(VK_SHIFT) & 0x8000)
		{
			if (!shift)
			{
				SendMessage(hFfplay, WM_KEYDOWN, VK_SHIFT, 0x002A0001);
				shift = true;
			}
		}
		else
		{
			if (shift)
			{
				SendMessage(hFfplay, WM_KEYUP, VK_SHIFT, 0xC02A0001);
				shift = false;
			}
		}

		if (GetAsyncKeyState(VK_CONTROL) & 0x8000)
		{
			if (!ctrl)
			{
				SendMessage(hFfplay, WM_KEYDOWN, VK_CONTROL, 0x001D0001);
				ctrl = true;
			}
		}
		else
		{
			if (ctrl)
			{
				SendMessage(hFfplay, WM_KEYUP, VK_CONTROL, 0xC01D0001);
				ctrl = false;
			}
		}

		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		{
			GetCursorPos(&lpPoint);
			if (lMouseButton)
			{
				SendMessage(hFfplay, WM_LBUTTONDOWN, 0, MAKELPARAM(lpPoint.x, lpPoint.y));
			}
			else if (!lMouseButton && InWorkArea(lpPoint))
			{
				lMouseButton = true;
				SendMessage(hFfplay, WM_LBUTTONDOWN, 0, MAKELPARAM(lpPoint.x, lpPoint.y));
				//std::cout << lpPoint.x << " " << lpPoint.y << std::endl;
			}
		}
		else
		{
			if (lMouseButton)
			{
				SendMessage(hFfplay, WM_LBUTTONUP, 0, MAKELPARAM(lpPoint.x, lpPoint.y));
				lMouseButton = false;
			}
		}

		//必须ctrl+右键
		if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
		{
			GetCursorPos(&lpPoint);
			if (rMouseButton)
			{
				SendMessage(hFfplay, WM_RBUTTONDOWN, 0, MAKELPARAM(lpPoint.x, lpPoint.y));
			}
			else if (ctrl && !rMouseButton && InWorkArea(lpPoint))
			{
				rMouseButton = true;
			}
		}
		else
		{
			if (rMouseButton)
			{
				GetCursorPos(&lpPoint);
				SendMessage(hFfplay, WM_RBUTTONUP, 0, MAKELPARAM(lpPoint.x, lpPoint.y));
				rMouseButton = false;
			}
		}

		if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		{
			if (!space)
			{
				SendMessage(hFfplay, WM_KEYDOWN, VK_SPACE, 0x00390001);
				space = true;
			}
		}
		else
		{
			if (space)
			{
				SendMessage(hFfplay, WM_KEYUP, VK_SPACE, 0xC0390001);
				space = false;
			}
		}

		if (GetAsyncKeyState(VK_UP) & 0x8000)
		{
			if (!up)
			{
				//SendMessage(hFfplay, WM_NCACTIVATE, 1, -1);
				PostMessage(hFfplay, WM_KEYDOWN, VK_UP, 0x000D0001);
				up = true;
			}
		}
		else
		{
			if (up)
			{
				PostMessage(hFfplay, WM_KEYUP, VK_UP, 0xC00D0001);
				up = false;
			}
		}


		if ((GetAsyncKeyState(VK_DOWN) & 0x8000) && !down)
		{
			PostMessage(hFfplay, WM_KEYDOWN, VK_DOWN, 0x000D0001);
			down = true;
		}
		if (!(GetAsyncKeyState(VK_DOWN) & 0x8000) && down)
		{
			PostMessage(hFfplay, WM_KEYUP, VK_DOWN, 0xC00D0001);
			down = false;
		}

		if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		{
			if (!left)
			{
				PostMessage(hFfplay, WM_KEYDOWN, VK_LEFT, 0x000D0001);
				left = true;
			}
		}
		else
		{
			if (left)
			{
				PostMessage(hFfplay, WM_KEYUP, VK_LEFT, 0xC00D0001);
				left = false;
			}
		}


		if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		{
			if (!right)
			{
				PostMessage(hFfplay, WM_KEYDOWN, VK_RIGHT, 0x000D0001);
				right = true;
			}
		}
		else
		{
			if (right)
			{
				PostMessage(hFfplay, WM_KEYUP, VK_RIGHT, 0xC00D0001);
				right = false;
			}
		}


		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
		{
			if (!escape)
			{
				SendMessage(hFfplay, WM_KEYDOWN, VK_ESCAPE, 0x00010001);
				escape = true;
			}
		}
		else
		{
			if (escape)
			{
				SendMessage(hFfplay, WM_KEYUP, VK_ESCAPE, 0xC0010001);
				escape = false;
			}
		}

		if (GetAsyncKeyState(VK_RETURN) & 0x8000)
		{
			if (!enter)
			{
				PostMessage(hFfplay, WM_KEYDOWN, VK_RETURN, 0x000D0001);
				enter = true;
			}
		}
		else
		{
			if (enter)
			{
				PostMessage(hFfplay, WM_KEYUP, VK_RETURN, 0xC00D0001);
				enter = false;
			}
		}

		Sleep(30);
	}
  ```