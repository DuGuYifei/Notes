# VLAN_IEEE802_1

## Intro
IEEE 802.1Q is a standard describing the operation of virtual LANs (VLANs) built in a frame  transport environment. It is designed to use a single physical link to transmit information from  several networks while maintaining their differentiation. Data transmitted within one virtual  network is not visible to other networks using the same physical link. The IEEE 802.1Q name is  also used to denote the encapsulation protocol used in the implementation of this mechanism  in Ethernet.

Managed devices (e.g. switches) that operate in accordance with 802.1Q standard, use special  frame marking (tagging). This is not additional encapsulation, but only attaching information  to which virtual network the frame belongs to. For Ethernet frames the tagging consists in  insertion of additional **4 bytes** between the **source MAC address** and the **EtherType field**. This  is referred to as **TPID (Tag Protocol Identifier)**. The **first 2** additional bytes are a tag and always  have the value `0x8100`, which makes it possible **identifying the frame as 802.1Q tagged**. The  **remaining 2** bytes called **TCI (Tag Control Information)** contain the following information:

**TPID = 0x8100 + TCI = 2 bytes + 2 bytes = 4 bytes**

1. PCP 字段——一个**三位**字段，用于指示**帧优先级**。 该字段的用法在 IEEE 802.1p 标准中定义。
2. CFI（规范格式指示符 Canonical Format Indicator）字段 - **一位**标识符，指示 LAN 是使用哪种技术创建的。 使用端口以外技术的帧将被丢弃。
3. VLAN ID (VID) - 指定帧属于哪个可视网络的 **12 位**字段。 **零值**表示该帧不属于任何虚拟网络，**值一**通常用于桥接，**值 0xFFF** 保留用于其他目的。其他 4093 值可用于标识单个 VLAN。

Frames belonging to embedded virtual networks are not modified while they are being transmitted on the common link. One of these networks is always “Native type”, which is commonly  referred to as a "Management VLAN”. 

## Port
Network ports can operate in two modes: **access** and **trunk**
1. The first mode allows assignment to **only one virtual network**. Frames coming out of an access  port are **not tagged** with 802.1Q tags. 
2. 为了通过单个链路在设备之间**发送来自不同网络的帧**，需要在该链路上启用不同虚拟网络内的帧传输。 为此，使用了 **VLAN 中继(trunk)**。 使用中继（即跨越多个交换机的虚拟网络）在单个网络内的通信是通过使用 **VLAN ID** 标记网络帧的技术实现的。 在 Cisco 设备上，端口名称由三部分组成。 例如：

FastEther net0/
1. FastEthernet - name of the port type, in this case it is Ethernet with speed 100Mbps
2. 0 - group number
3. 1 - interface number

## 题

1. 如果远程配置端口移动到不同的虚拟 LAN，则： 
- [x] 与交换机的通信将丢失 
- [ ] 只有本地控制台会修复此错误
- [ ] 只有远程控制台会修复此错误 
- [ ] 从管理的角度来看，什么都不会发生

2. 某些端口属于虚拟网络 10（禁用标记）。 交换机已获悉站点在此网络上的位置。 如果站 A 发送一个地址为站 B 的帧，则： 
- [x] 该帧将只发送到站 B 的端口 
- [ ] 该帧将被发送到网络 10 的所有端口，除了站点 A 所在的端口
- [ ] 该帧将被发送到网络 10 的所有端口，除了站 B 所在的端口
- [ ] 该帧将被丢弃

3. 属于虚拟网络不能通过以下方式实现：
- [x] 以太网帧前导元素
- [ ] 发件人的MAC地址
- [ ] 网络层协议类型
- [ ] IEEE 802.1Q 标签

4. 添加到帧的标签会导致：
- [x] 不支持标记帧的计算机将拒绝这样的帧
- [ ] 帧缩短
- [ ] 带宽使用效率低于时隙 (TDM)
- [ ] 如果帧在一个链路上发送，则在 VLAN 之间混合帧 

5. 基于 MAC 地址的从属关系导致：
- [x] **将一个端口上的多个站点归属于不同虚拟网络的可能性**
- [ ] 所有附属方法中最快的帧切换
- [ ] 将交换机端口分配给**一个虚拟**本地网络的可能性
- [ ] 广播域精确划分的可能性

6. 一台交换机上的两个端口属于不同的VLAN，并且都禁用了它们的标签。 将电缆连接到这些端口将导致：
- [x] 这些虚拟网络的**连接**，尽管它们的 ID 不同
- [ ] 不同标识符导致的网络分离
- [ ] 网络环路，如果没有消除网络环路的机制
- [ ] 在任何情况下都在网络中循环

7. 您的计算机有一个仅处理未标记帧的网络堆栈。 要将其移动到新的虚拟网络（编号 10），您需要：
- [x] 将端口添加到**虚拟网络** 10 并将其配置为**本机**
- [ ] 只需将端口添加到没有标签的网络 10
- [ ] 只需将网络 10 设置为该端口的本地网络
- [ ] 您需要重新配置您的计算机以发送带有标签的帧

8. 虚拟局域网不适用于：
- [x] 为员工提供通过 Internet 对公司网络的远程访问
- [ ] 广播域划分
- [ ] 增加本地网络的安全性
- [ ] 站点的逻辑分组

9. 具有典型网络堆栈（例如 Windows）的计算机连接到属于虚拟网络 100 并在此端口上启用标记的交换机端口将无法与同一 VLAN 中的其他计算机通信，因为：
- [x] **接收**，但错误解释带有标签的帧并且**无法发送**它们
- [ ] 它只是不接收标记帧
- [ ] 此端口未接收来自同一 VLAN 的其他端口的流量
- [ ] 它只是不能发送带有标签的帧

10. 在交换机端口上接收到没有标记的帧。 它最多可以访问多少个虚拟网络：
- [x] 1
- [ ] 255
- [ ] 4095
- [ ] 0

11. 两个交换机相互连接并从虚拟网络 1 传输未标记的帧。要从网络 2 额外发送帧还需要做什么：
- [x] 您需要在**启用**标记的情况下添加将交换机连接到网络 2 的端口
- [ ] 您需要在禁用标记的情况下添加将交换机连接到网络 2 的端口
- [ ] 无法将端口配置为同时从两个网络传输帧
- [ ] 您需要从交换机中完全删除网络 1

12. MAC地址的长度为:
- [x] 6 字节 
- [ ] 64 位 
- [ ] 48 字节 
- [ ] 64 字节

13. 在以太网帧中，标记紧接在以下位置之后添加：
- [x] 发件人的MAC地址
- [ ] 帧序言
- [ ] 协议标识符
- [ ] 收件人的MAC地址

14. 添加与 802.1Q 标准兼容的标签允许您：
- [x] 将虚拟局域网的区域扩展到单个设备之外。 更重要的是，许多厂商的设备只要支持相同的标准，例如IEEE 802.1Q，就可以相互协作。
- [ ] 基于网络层协议类型的站点隶属关系
- [ ] 基于 IP 地址的站点隶属关系
- [ ] 根据 MA​​C 地址向 VLAN 发送站分配表