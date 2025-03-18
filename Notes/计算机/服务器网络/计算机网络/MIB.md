# MIB

MIB（Management Information Base）是指管理信息库，是[SNMP](SNMP.md)（Simple Network Management Protocol）协议中的一个概念。它是一种用于存储网络设备、服务器、路由器、交换机等网络设备的管理信息的数据库，是SNMP协议的核心组成部分之一。

MIB主要用于定义SNMP代理的管理信息，通过SNMP协议向NMS（Network Management System）提供管理信息，包括设备的状态、性能、配置等。MIB可以用一个树状结构表示，其中每个节点代表一个对象，每个对象都有一个唯一的标识符OID（Object Identifier），用于在SNMP协议中唯一标识一个对象。

MIB分为两种类型：

1. 标准MIB：由SNMP标准组织（如IETF、ITU-T）定义，包括了通用的网络设备、系统、应用程序等信息。

2. 私有MIB：由厂商自行定义的MIB，用于存储特定设备的管理信息，包括特定设备的状态、性能、配置等信息。

MIB是SNMP协议中的一个重要概念，可以为网络管理提供大量的管理信息，通过SNMP协议提供给NMS使用。

