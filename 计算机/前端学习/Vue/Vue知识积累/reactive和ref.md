# reactive和ref

reactive与ref区别
1、 从定义数据方面：

ref通常用来定义基本类型数据
reactive用来定义：对象（或者数组）类型数据
ref也可以用来定义对象或者数组类型的数据，内部会通过reactive转为代理对象

2、从原理方面：
ref通过Object.defineProperty()的get和set实现数据代理。
reactive使用Proxy实现数据代理，并且通过Reflect操作源对象内部的数据。

3、从使用方面：
ref操作数据需要.value，template模板中不需要。
reactive都不需要,value
————————————————
版权声明：本文为CSDN博主「一路向阳~负责的男人」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/weixin_43416349/article/details/120360330