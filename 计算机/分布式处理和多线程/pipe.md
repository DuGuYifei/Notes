# pipe

```c
#include <unistd.h>
int pipe(int filedes[2]);

// filedes[0] 读端
// filedes[1] 写端

// 返回值：成功返回0，失败返回-1

// 读写管道
read(filedes[0], buf, len);
write(filedes[1], buf, len);
```