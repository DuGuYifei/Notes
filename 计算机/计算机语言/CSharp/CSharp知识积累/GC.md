# GC

* 理论上，当托管内存不够时，GC就会运行，以便于获得更多的可分配对象。通常情况下，GC都是自动调用的，也可以GC.Collect()来实现手动调用。（尽量不要手动调用，会破坏原有GC策略，除非你明确知道内存在使过程中何时会产生大量垃圾）

* 不能够被GC回收的对象 ，是非托管的对象，例如文件流，数据库链接等。
非托管的对象如何实现回收呢？可以为类提供Dispose接口，或者使用using语句块。就可以释放非托管的对象。

* 如果想要自动释放非托管函数呢？
可以使用析构函数。当对象所在函数已经调用完毕，系统就会自动执行析构函数。
————————————————
版权声明：本文为CSDN博主「BluAky_12138」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/bluesky_12138/article/details/123055523