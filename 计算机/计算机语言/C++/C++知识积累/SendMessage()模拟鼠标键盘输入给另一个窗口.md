# SendMessage()模拟鼠标键盘输入给另一个窗口

[GetAsyncKeyState()鼠标键盘输入](GetAsyncKeyState()鼠标键盘输入.md)

## SendMassage(目标窗口句柄，鼠标Down/Up(KeyDown/Up),鼠标0(VK_键),鼠标位置(第二个要按的键，组合键));
可能是错的：最后一个值为`0x10001`时意味着`EM_CHARFROMPOS`，它会返回屏幕坐标之外（65535, 65535）

最后一位：`0x00ab0001` or `0xC0ab0001`: `00`是按下，`C0`是抬起，`ab`用`MapVirtualKey(VK_键,0)`获得，跟VK值不一样的。注意`ab`是十六进制。`0001`是按一次。

开局让它最小化一下，是因为这样才可以传输后面的键盘，猜测原因就像4399打游戏得点一下让控制聚焦窗口。

- 用`short temp`是因为它会响应鼠标点击三次。（最后实验不用但配合sleep好像效果也不错）\
- GetCursor()   得到位置
- SetCursor()   不能省略
- MAKRLPARAM()  可以发送额外鼠标位置信息（应该没有也可以）
- 还要配合keyup完成一次点击，光keydown可能不够

  具体如下

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
