# exit

exit() 是一个函数调用，它会立即终止程序的执行，并将控制权返回给操作系统。exit() 函数不会返回到它被调用的那个函数，而是直接返回到操作系统。在 exit() 函数被调用之前，程序可以执行一些清理工作，例如关闭文件、释放内存等。

exit() 函数的原型如下：

```c
#include <stdlib.h>

void exit(int status);

exit(EXIT_FAILURE);
```