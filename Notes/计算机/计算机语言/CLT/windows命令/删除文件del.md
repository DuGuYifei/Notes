# 删除文件del


```
C:\Users\Administrator>del /?
删除一个或数个文件。

DEL [/P] [/F] [/S] [/Q] [/A[[:]attributes]] names
ERASE [/P] [/F] [/S] [/Q] [/A[[:]attributes]] names

  names         指定一个或多个文件或者目录列表。
                通配符可用来删除多个文件。
                如果指定了一个目录，该目录中的所
                有文件都会被删除。

  /P            删除每一个文件之前提示确认。
  /F            强制删除只读文件。
  /S            删除所有子目录中的指定的文件。
  /Q            安静模式。删除全局通配符时，不要求确认
  /A            根据属性选择要删除的文件
  属性           R  只读文件                    S  系统文件
                H  隐藏文件                    A  存档文件
                I  无内容索引文件               L  重分析点
                -  表示“否”的前缀

如果命令扩展被启用，DEL 和 ERASE 更改如下:

/S 开关的显示句法会颠倒，即只显示已经
删除的文件，而不显示找不到的文件。
```
[cmd删除文件命令del/erase和删除目录命令rmdir/rd - Macrored - 博客园](https://www.cnblogs.com/macrored/p/11415741.html)

```cmd
del /S *.log
```