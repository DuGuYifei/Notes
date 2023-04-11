# Global和剪切板Clipboard

* `GlobalAlloc`分配内存
* `GlobalLock`锁定内存，返回指向内存的指针
* `GlobalUnlock`解锁内存
* `GlobalFree`释放内存 - 必须在解锁内存后
* `OpenClipboard`打开剪切板，打开期间，其他程序不能访问剪切板
* `CloseClipboard`关闭剪切板
* `EmptyClipboard`清空剪切板
* `SetClipboardData`设置剪切板数据 - 必须在清空剪切板后
* `GetClipboardData`获取剪切板数据
* `IsClipboardFormatAvailable`判断剪切板数据是否是指定格式
* `SetClipboardViewer`设置剪切板观察者
* `ChangeClipboardChain`更改剪切板观察者链
* `WM_DRAWCLIPBOARD`剪切板内容改变时发送的消息

```c
#include <Windows.h>
#include <stdio.h>
#include <ctype.h>

HANDLE hClip, hNewClip;
char *buffer, *newBuffer;
BOOL isChange = FALSE;

BOOL IsBankCardNumber(char *str)
{
    int len = strlen(str);
    if (len < 12 || len > 19)
    {
        return 0;
    }
    for (int i = len - 1; i >= 0; i--)
    {
        if (!isdigit(str[i]))
        {
            return 0;
        }
    }
    return 1;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_CREATE:
        SetClipboardViewer(hwnd);
        printf("Clipboard viewer added.\n");
        break;

    case WM_DESTROY:
        ChangeClipboardChain(hwnd, hwnd);
        PostQuitMessage(0);
        break;

    case WM_DRAWCLIPBOARD:
        printf("Clipboard changed.\n");
        if (!OpenClipboard(NULL))
        {
            printf("Unable to open clipboard.\n");
            break;
        }
        // If data is pure text
        if (!IsClipboardFormatAvailable(CF_TEXT))
        {
            CloseClipboard();
            Sleep(100);
            break;
        }
        hClip = GetClipboardData(CF_TEXT);
        if (!hClip)
        {
            printf("Unable to get clipboard data.\n");
            CloseClipboard();
            break;
        }
        buffer = (char *)GlobalLock(hClip);
        if (!buffer)
        {
            printf("Unable to lock clipboard.\n");
            CloseClipboard();
            break;
        }

        if (IsBankCardNumber(buffer))
        {
            strcpy(buffer, "Don't copy bank card number");
            hNewClip = GlobalAlloc(GMEM_MOVEABLE, strlen(buffer) + 1);
            newBuffer = (char *)GlobalLock(hNewClip);
            strcpy(newBuffer, buffer);
            GlobalUnlock(hNewClip);
            isChange = TRUE;
        }
        GlobalUnlock(hClip);
        if (isChange)
        {
            printf("%s\n", newBuffer);
            EmptyClipboard();
            SetClipboardData(CF_TEXT, hNewClip);
            GlobalFree(hClip);
            isChange = FALSE;
        }
        if (!CloseClipboard())
        {
            printf("Unable to close clipboard.\n");
            return 1;
        }
        break;

    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

int main()
{
    WNDCLASS wc = {0};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = "Lab5";
    RegisterClass(&wc);

    // create a virtual window to receive messages
    HWND hwnd = CreateWindow("Lab5", "Clipboard Viewer", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 640, 480, NULL, NULL, GetModuleHandle(NULL), NULL);
    printf("window created.\n");
    if (!hwnd)
    {
        printf("Unable to create window.\n");
        return 1;
    }

    MSG msg;
    while (1)
    {
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
        {
            break;
        }

        if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return 0;
}
```


```c
#include <Windows.h>
#include <stdio.h>
#include <ctype.h>

BOOL IsBankCardNumber(char *str)
{
    int len = strlen(str);
    if (len < 12 || len > 19)
    {
        return 0;
    }
    for (int i = len - 1; i >= 0; i--)
    {
        if (!isdigit(str[i]))
        {
            return 0;
        }
    }
    return 1;
}

int main()
{
    HANDLE hClip, hNewClip;
    char *buffer, *newBuffer;
    BOOL isChange = FALSE;
    while (1)
    {
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
        {
            break;
        }
        if (!OpenClipboard(NULL))
        {
            printf("Unable to open clipboard.\n");
            return 1;
        }
        // If data is pure text
        if (!IsClipboardFormatAvailable(CF_TEXT))
        {
            Sleep(100);
            continue;
        }
        hClip = GetClipboardData(CF_TEXT);
        if (!hClip)
        {
            printf("Unable to get clipboard data.\n");
            CloseClipboard();
            return 1;
        }
        buffer = (char *)GlobalLock(hClip);
        if (!buffer)
        {
            printf("Unable to lock clipboard.\n");
            CloseClipboard();
            return 1;
        }

        if (IsBankCardNumber(buffer))
        {
            strcpy(buffer, "Don't copy bank card number");
            hNewClip = GlobalAlloc(GMEM_MOVEABLE, strlen(buffer) + 1);
            newBuffer = (char *)GlobalLock(hNewClip);
            strcpy(newBuffer, buffer);
            GlobalUnlock(hNewClip);
            isChange = TRUE;
        }
        GlobalUnlock(hClip);
        if (isChange)
        {
            printf("%s\n", newBuffer);
            EmptyClipboard();
            SetClipboardData(CF_TEXT, hNewClip);
            GlobalFree(hClip);
            isChange = FALSE;
        }
        if (!CloseClipboard())
        {
            printf("Unable to close clipboard.\n");
            return 1;
        }
        Sleep(100);
    }
    return 0;
}
```