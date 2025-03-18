# powershell编码问题

```powershell
[Console]::OutputEncoding = [Text.UTF8Encoding]::UTF8
```
添加到
```powershell
notepad $PROFILE
```