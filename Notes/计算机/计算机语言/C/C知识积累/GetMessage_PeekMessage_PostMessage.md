# GetMessage_PeekMessage_PostMessage

## GetMessage
作用是从消息队列中取出一条消息，如果没有消息，就会阻塞，直到有消息为止。

```c
BOOL GetMessage(
  LPMSG lpMsg,
  HWND  hWnd,
  UINT  wMsgFilterMin,
  UINT  wMsgFilterMax
);
```

- `lpMsg`: 指向一个MSG结构体的指针，用来存储消息
- `hWnd`: 指定窗口句柄，如果为NULL，就是所有窗口
- `wMsgFilterMin`: 指定消息过滤器的最小值
- `wMsgFilterMax`: 指定消息过滤器的最大值

过滤器都设置为0，就是所有消息都会被处理。

## PeekMessage

作用是从消息队列中取出一条消息，如果没有消息，就会返回0。

```c
BOOL PeekMessage(
  LPMSG lpMsg,
  HWND  hWnd,
  UINT  wMsgFilterMin,
  UINT  wMsgFilterMax,
  UINT  wRemoveMsg
);
```

- `lpMsg`: 指向一个MSG结构体的指针，用来存储消息
- `hWnd`: 指定窗口句柄，如果为NULL，就是所有窗口
- `wMsgFilterMin`: 指定消息过滤器的最小值
- `wMsgFilterMax`: 指定消息过滤器的最大值
- `wRemoveMsg`: 指定是否删除消息

## PostMessage

作用是向消息队列中添加一条消息。

```c
BOOL PostMessage(
  HWND   hWnd,
  UINT   Msg,
  WPARAM wParam,
  LPARAM lParam
);
```
