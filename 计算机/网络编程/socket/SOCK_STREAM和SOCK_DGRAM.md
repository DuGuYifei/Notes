# SOCK_STREAM和SOCK_DGRAM

## SOCK_STREAM

流式套接字，SOCK_STREAM是面向连接的，即TCP协议，数据传输前需要建立连接，传输完毕后需要断开连接。

## SOCK_DGRAM

数据报套接字，SOCK_DGRAM是无连接的，即UDP协议，数据传输不需要建立连接，传输完毕后也不需要断开连接。