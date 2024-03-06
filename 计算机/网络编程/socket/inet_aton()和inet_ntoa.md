# inet_aton()和inet_ntoa

```c
//头文件
#include<arpa/inet.h>
//函数：把字符串形式的“192.168.1.123”转为网络能识别的格式 。
int inet_aton(const char* straddr,struct in_addr *addrp); 
//函数：把网络格式的ip地址转为字符串形式。
char* inet_ntoa(struct in_addr inaddr); 
```