# 打开另一个cmd并执行命令

`start cmd`

* `/K` 执行命令后不关闭

* `/C` 执行命令后关闭

`start cmd /K "yarn start:back" &&  yarn start`

```cmd
start cmd /C _main.cmd
timeout /T 5
start cmd /C _backup1.cmd
timeout /T 5
start cmd /C _backup2.cmd
timeout /T 5
start cmd /C _federal1.cmd
timeout /T 5
start cmd /C _federal2.cmd
```