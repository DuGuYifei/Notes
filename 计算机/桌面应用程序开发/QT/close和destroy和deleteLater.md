# close和destroy和deleteLater

* close 关闭，但是短时间还存在内存中
* destroy 立刻摧毁，并发送信号（参数）
* deleteLater 进入循环立刻停止并delete，正在循环就回到循环时停止，若循环已结束，则原主将一直不被删除。
