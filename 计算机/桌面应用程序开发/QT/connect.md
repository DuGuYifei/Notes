# connect

[信号和槽](信号和槽.md)

## 语法
* `connect(信号发送者，信号，信号接收者，槽)`
* `connect(按钮，被点击，窗口，关闭)`
* `connect(btn, &QPushButton::clicked, this, &Widget::close);`

点击按钮窗口关闭。

* 其他标准槽：showMiniMize, hide等 (文档Public Slots)
* 其他信号：pressed, released, toggled (文档Signals)
  * toggle:切到了某个标签

