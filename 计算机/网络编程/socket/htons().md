# htons

htons 是一个用于将主机字节序转换为网络字节序（Big-Endian）的函数。其中 h 代表主机字节序（Host Byte Order），n 代表网络字节序（Network Byte Order），s 代表 short 类型（16 位）。

在不同的计算机体系结构中，字节序可能会有所不同，例如 x86 架构的计算机使用的是小端序（Little-Endian），而网络传输一般采用的是大端序（Big-Endian）。因此，在进行网络通信时，需要将主机字节序转换为网络字节序，以保证通信的正确性。

**htons 函数的作用就是将 short 类型的参数从主机字节序转换为网络字节序。如果当前计算机采用的是小端序（Little-Endian），则 htons 函数会将参数的高字节（Most Significant Byte，MSB）放到低地址处，低字节（Least Significant Byte，LSB）放到高地址处，以得到网络字节序。如果当前计算机采用的是大端序（Big-Endian），则 htons 函数不会做任何操作。**