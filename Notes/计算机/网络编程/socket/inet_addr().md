# inet_addr()

```c
#include <arpa/inet.h>

inet_addr(const char *cp);

struct sockaddr_in server_addr;
server_addr.sin_family = AF_INET;
server_addr.sin_port = htons(8080);
server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
```
