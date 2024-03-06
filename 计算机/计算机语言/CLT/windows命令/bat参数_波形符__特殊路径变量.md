# 获取路径

```bash
set TARGET='%~dp0WallpaperEngineStart.exe'
set SHORTCUT='%USERPROFILE%\AppData\Roaming\Microsoft\Windows\Start Menu\Programs\Startup\WallpaperEngineStart.lnk'
set PWS=powershell.exe -ExecutionPolicy Bypass -NoLogo -NonInteractive -NoProfile

%PWS% -Command "$ws=New-Object -ComObject WScript.Shell;$s=$ws.CreateShortcut(%SHORTCUT%); $S.TargetPath=%TARGET%; $S.Save()"
```

1. %n包含用于调用文件的参数：%0是 bat 文件本身的路径，%1是后面的第一个参数，%2是第二个等等。
2. ~d是驱动器，~p是路径（不含驱动器），~n是文件名。它们可以组合，~dp驱动器+路径也是如此。
3. %~dp0因此在 bat 中非常有用：它是执行 bat 文件所在的文件夹。
4. ~t是时间戳，~z是大小
5. %USERPROFILE% user文件夹路径
6. %PATH% 系统环境path变量

波形符用法[Command-line reference A-Z](https://learn.microsoft.com/en-us/previous-versions/windows/it-pro/windows-xp/bb490890(v=technet.10)?redirectedfrom=MSDN)