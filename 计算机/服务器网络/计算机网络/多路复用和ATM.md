# 多路复用和ATM

Every computer that sends the data must have a unique identifier. Such an identifier is usually called an  address. In some network technologies, the address indicates a specific machine, while in others  indicates the point of attachment to the network, which is commonly called the interface. As a result, a  single machine on a network that has several interfaces can have several IP addresses, one for each of  these interfaces. Interfaces are usually physically distinguishable connections (i.e. the sockets to which  the network cable is connected), but they can also be logical connections that have one common  physical connection. You may also come across another solution called **interface multiplexing**, which is used in the **ATM network**. The ATM logical host division are several groups that allows every single  group to be treated as a separate logical network even though all the hosts are attached to one physical  network. The equipment connected to this type of physical network can simultaneously belong to  several logical networks thanks to establishing several logical connections, each with its own IP address.
Machines that have multiple addresses are referred to as **multi-homed**. All routers are multihomed by  definition, as they transport packets between several networks. However, not all machines are referred  to as multi-homed routers, e.g. one machine can have several connections to the network and perform  the function of a file server shared by several different networks without routing information between  these networks.

每台发送数据的计算机都必须有一个唯一的标识符。 这种标识符通常称为地址。 在某些网络技术中，地址表示特定的机器，而在其他网络技术中，地址表示网络的连接点，通常称为接口。 因此，具有多个接口的网络上的一台机器可以有多个 IP 地址，每个接口一个。 接口通常是物理上可区分的连接（即网线所连接的插座），但它们也可以是具有一个公共物理连接的逻辑连接。 您可能还会遇到另一种称为接口多路复用的解决方案，它用于 ATM 网络。 ATM 逻辑主机划分为多个组，允许将每个单独的组视为一个单独的逻辑网络，即使所有主机都连接到一个物理网络。 由于建立了多个逻辑连接，每个逻辑连接都有自己的 IP 地址，因此连接到此类物理网络的设备可以同时属于多个逻辑网络。
具有多个地址的机器称为多宿主。 根据定义，所有路由器都是多宿主的，因为它们在多个网络之间传输数据包。 但是，并非所有机器都称为多宿主路由器，例如 一台机器可以有多个网络连接，并执行由多个不同网络共享的文件服务器的功能，而无需在这些网络之间路由信息。

## Interface Multiplexing
接口复用（Interface Multiplexing）是指在一个网络连接（如TCP连接）上同时发送多个不同的数据流或服务请求，并且在接收端将它们分离和处理的技术。

在计算机网络中，接口复用通常是通过多路复用器（Multiplexer）来实现的。多路复用器可以同时处理多个数据流，并且可以将它们分离成单独的数据流发送到目标应用程序中。这样，就可以在一个连接上同时进行多个应用程序的通信，提高了网络的利用率。

常见的接口复用技术包括HTTP/2协议中的流（Stream）技术、SSH协议中的通道（Channel）技术等。这些技术可以将多个数据流或请求打包在一个连接中，从而减少了连接的数量和维护成本，并且可以提高通信的效率和可靠性。

## ATM网络
ATM（Asynchronous Transfer Mode，异步传输模式）网络是一种基于分组交换技术的高速广域网络，它是在20世纪80年代末和90年代初开发出来的。

ATM网络通过将数据分成固定大小的小数据包（也称为“单元”或“细胞”），在网络中进行传输和路由。每个细胞都有5个字节的头部和48个字节的有效数据，可以在不同的网络层（如物理层、数据链路层、网络层等）之间进行传输。

ATM网络的优点包括高速、低延迟、可靠性高、适合多媒体应用等。它的设计初衷是为了支持各种类型的通信服务，包括语音、视频、数据等。ATM网络可以提供丰富的服务质量保证机制（如带宽保障、拥塞控制、优先级调度等），可以满足不同应用的需求。

然而，随着互联网的发展和IP技术的成熟，ATM网络逐渐被IP网络所取代。尽管ATM网络在一些特定场景下仍然得到广泛应用，但其在商业领域的影响已经相对较小。