# 计算机更新卡在logo界面不更新解决办法

任务管理器->服务->随机地方右键->打开服务 会弹出服务窗口

打开以下服务:(不知道是否全部需要，但我都打开了，于是成功了)
1. Windows Update
2. Windows Modules Installer 
3. Windows Installer (该任务打开后好像还是会自动关，所以我打开后不关闭该服务窗口直接点的更新并重启)

额外：
1. 更新完后我关闭了联想电脑管家里启动项的：Windows更新服务启动任务。
2. 联想电脑管家里启动项的windows安装服务打不开的，所以不用管。