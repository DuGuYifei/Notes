# SNMP

SNMP（Simple Network Management Protocol）是一种简单网络管理协议，是一种应用层协议，用于管理网络设备，如路由器、交换机、服务器等。SNMP协议是一个基于UDP的协议，端口号为161。

SNMP协议由网络管理系统（NMS）和代理组成，NMS通过SNMP协议向代理发送管理命令，代理则返回相应的信息。

SNMP协议的主要功能包括：
1. 设备管理：可以通过SNMP协议对网络设备进行配置、管理、监控和维护，如获取设备的系统信息、监控设备的状态和性能、配置设备参数等。

2. 故障诊断：可以通过SNMP协议对网络设备进行故障诊断，如检测设备是否故障、定位故障原因等。

3. 性能优化：可以通过SNMP协议对网络设备进行性能优化，如检测网络瓶颈、调整网络参数等。


* SNMP GetResponse: a request send to device asking for the status of a speciiic object
* SNMP GetRequest: A reply to a request send to the device asking for the status of the object 