# 其他特殊ip地址

1. loopback address：127.0.0.1	
该地址定义为机器上运行的软件环回接口的地址。 该地址未分配给任何硬件接口，也未连接到网络。 它主要用于在未连接网络的机器上测试IP软件，而不管网络接口或其驱动程序是否正常工作。 它也可以在本地机器上用作接口地址，无论硬件接口的当前状态如何，该接口地址始终处于活动状态并且可由软件访问。 例如，可以使用此地址来寻址客户端软件引用与同一台机器上的漫游服务器，而无需使用外部主机 IP 地址。 IP 协议规范要求此地址以及整个网络 127.0.0.0/8 永远不应分配给外部机器接口。 如果发生这种情况，这些地址将被任何接收如此寻址的数据包的主机或路由器丢弃。 请注意，此地址违反了 IP 地址唯一标识主机的规则，因为 IP 网络上的所有主机都使用相同的环回接口地址。

2. 0.0.0.0
除了在遗留软件中将其用作本地网络广播地址外，某些路由协议还将其视为捕获地址或默认路由。

3. 不可路由地址：
	1. 10.0.0.0/8：包括所有以 10 开头的 IP 地址。
	2. 172.16.0.0/12：包括所有以 172.16 至 172.31 开头的 IP 地址。
	3. 192.168.0.0/16：包括所有以 192.168 开头的 IP 地址。