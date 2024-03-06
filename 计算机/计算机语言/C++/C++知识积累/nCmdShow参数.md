# nCmdShow参数

[ShowWindow function (winuser.h) - Win32 apps](https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-showwindow)

| Value              | Meaning                                                                                                                                                                                                                    |
| ------------------ | -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| SW_HIDE            |
| 0                  | Hides the window and activates another window.                                                                                                                                                                             |
| SW_SHOWNORMAL      |
| SW_NORMAL          |
| 1                  | Activates and displays a window. If the window is minimized or maximized, the system restores it to its original size and position. An application should specify this flag when displaying the window for the first time. |
| SW_SHOWMINIMIZED   |
| 2                  | Activates the window and displays it as a minimized window.                                                                                                                                                                |
| SW_SHOWMAXIMIZED   |
| SW_MAXIMIZE        |
| 3                  | Activates the window and displays it as a maximized window.                                                                                                                                                                |
| SW_SHOWNOACTIVATE  |
| 4                  | Displays a window in its most recent size and position. This value is similar to SW_SHOWNORMAL, except that the window is not activated.                                                                                   |
| SW_SHOW            |
| 5                  | Activates the window and displays it in its current size and position.                                                                                                                                                     |
| SW_MINIMIZE        |
| 6                  | Minimizes the specified window and activates the next top-level window in the Z order.                                                                                                                                     |
| SW_SHOWMINNOACTIVE |
| 7                  | Displays the window as a minimized window. This value is similar to SW_SHOWMINIMIZED, except the window is not activated.                                                                                                  |
| SW_SHOWNA          |
| 8                  | Displays the window in its current size and position. This value is similar to SW_SHOW, except that the window is not activated.                                                                                           |
| SW_RESTORE         |
| 9                  | Activates and displays the window. If the window is minimized or maximized, the system restores it to its original size and position. An application should specify this flag when restoring a minimized window.           |
| SW_SHOWDEFAULT     |
| 10                 | Sets the show state based on the SW_ value specified in the STARTUPINFO structure passed to the CreateProcess function by the program that started the application.                                                        |
| SW_FORCEMINIMIZE   |
| 11                 | Minimizes a window, even if the thread that owns the window is not responding. This flag should only be used when minimizing windows from a different thread.                                                              |