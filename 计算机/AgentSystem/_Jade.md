# Jade

1. [Java Agent 概述](#java-agent-概述)
   1. [Java Agent 的作用](#java-agent-的作用)
2. [教程](#教程)
3. [命令行创建](#命令行创建)
4. [发送消息的交互界面](#发送消息的交互界面)
   1. [Lab1](#lab1)
   2. [Lab2](#lab2)
5. [Java 代码创建](#java-代码创建)

## Java Agent 概述
Java Agent 本质上是 JDK 提供的一个工具。

在 JDK1.5 之后，可以使用 Java Agent 技术构建一个独立于应用程序的代理程序（即Agent）。

可以用来协助监测、运行甚至替换其他JVM上的程序。使用它可以实现虚拟机级别的 AOP 功能，比如字节码注入。

### Java Agent 的作用
我们可以通过 Java Agent 的类加载拦截功能，修改某个类所对应的字节码二进制数组，并利用这个修改过后的二进制数组完成接下来的类加载。

JavaAgent 是运行在 main 方法之前的拦截器，它内定的方法名叫 premain ，也就是说先执行 premain 方法然后再执行 main 方法。

## 教程
[jade的中文资料_fire1175的博客-CSDN博客_jade createrequestmsg](https://blog.csdn.net/fire1175/article/details/1584164)

## 命令行创建
Main Container
```cmd
java -cp jade.jar jade.Boot -host 127.0.0.1 -port 5656 -local-host 127.0.0.1 -local-port 5656 -gui
```

Federate Container
```cmd
java -cp jade.jar jade.Boot -host 127.0.0.1 -port 5656 -container
```

## 发送消息的交互界面
创建 dummy agent

### Lab1
使用以下命令启动单个容器：
```
java -cp lib/jade.jar jade.Boot
```

jade.Boot 类是主要的 JADE 类，它包括运行单个容器的 main () 方法。 可以使用以下可选参数配置容器启动：
| 命令            | 作用                                                      |
| --------------- | --------------------------------------------------------- |
| -container      | - 创建联合容器的实例，                                    |
| -host           | - 启动主容器的主机的名称。                                |
| -local-host     | - 将启动容器的主机名称，                                  |
| -port           | - 启动主容器的端口号，                                    |
| -local-port     | - 启动容器的端口号，                                      |
| -gui            | - 启动 RMA 代理（远程管理代理），允许对平台进行图形管理， |
| -name           | - 设置平台名称，在启动主容器时使用，                      |
| -container-name | - 设置正在启动的容器的名称。                              |

在两台机器上运行两个容器示例：
主容器：
```cmd
java -cp lib/jade.jar jade.Boot -host des01.eti.pg.gda.pl -port 5656 -local-host des01.eti.pg.gda.pl -local-port 5656
```
联合容器：(faderal container)
```cmd
java -cp lib/jade.jar jade.Boot -host des01.eti.pg.gda.pl -port 5656 -local-host des02.eti.pg.gda.pl -local-port 4646 -container
```
要测试组装环境的正确性，可以使用 DummyAgent 代理。 它是 JADE 库中提供的用于环境测试的现成代理。 可以使用 RMA 代理来运行它。 为此，请选择将在其上启动代理的目标容器，然后选择 DummyAgent 图标（带有显示语言的帽子中的代理）。  RMA 代理允许您在任何容器上创建代理，也可以在另一台物理机器上创建代理。
DummyAgent 代理允许您创建任何消息并将其发送给驻留在平台上的任何代理。 请注意，代理 ID 的格式为 agent_name @platform_name，其中默认（除非另有设置）平台名称为 main_container_address: main_container_port / JADE。 仅指定代理名称不足以正确地将消息传递给它。 在正确配置环境的情况下，驻留在所有容器上的代理之间的通信应该是可能的。

任务： 
1. 展示位于同一容器中的两个代理之间的通信， 
2. 展示位于同一物理机器上三个不同容器中的三个代理之间的通信， 
3. 展示位于四个/六个不同容器中的四/六个代理之间的通信两个/三个具有相同操作系统的不同物理机器，成对/三个执行任务，
4. 演示居住在四个/六个不同容器中的四个/六个代理的通信两个/三个具有不同操作系统的不同物理机器，任务是成对/三个进行。
   
注意： 
* 每个任务都需要为平台、所有容器和代理设置自己的名称。

### Lab2
该任务的目的是编译分布式多代理环境并将基础架构级别的安全性引入其中。 接下来，您应该测试驻留在不同容器中的代理之间的通信。
在环境的基本配置中，一个容器始终充当主容器，其他容器作为联合容器加入。 这种配置创建了一个集中的星型拓扑基础设施，所有联合容器都依赖于主容器。 任何联合容器的故障只会导致驻留在平台上的代理从平台上移除，并且只要主容器运行，整个平台就会继续运行。 为了防止这种情况，可以引入备份主容器，与主容器一起形成环形拓扑。 如果当前作为主容器的容器发生故障，其他容器将检测到它并选择一个新的主容器来负责管理平台。 联合容器可以连接到主容器或任何备份容器以加入平台。
默认情况下，代理之间的通信不受任何保护，很容易被窃听。 为了防止消息被环境外的元素读取，您可以在容器级别进行加密通信。 为此，每个容器都可以配备一组密钥，用于加密通信。请注意，加密不是代理的责任（其代码和内容可能在通过网络迁移期间被截获），而是它当前所在的容器。
通信安全仅保护交换的消息。 仍然任何容器都可以加入该平台。 为了防止这种情况，您可以配备一组受信任的公钥。 这将允许您根据其私钥识别新容器。 如果一个新容器向自己展示了一个不受信任的密钥，它将不会被允许进入平台。

jade.Boot 类是主要的 JADE 类，它包括运行单个容器的 main () 方法。 可以使用以下可选参数配置容器启动：
| 命令            | 作用                                                      |
| --------------- | --------------------------------------------------------- |
| -container      | - 创建联合容器的实例，                                    |
| -host           | - 启动主容器的主机的名称。                                |
| -local-host     | - 将启动容器的主机名称，                                  |
| -port           | - 启动主容器的端口号，                                    |
| -local-port     | - 启动容器的端口号，                                      |
| -gui            | - 启动 RMA 代理（远程管理代理），允许对平台进行图形管理， |
| -name           | - 设置平台名称，在启动主容器时使用，                      |
| -container-name | - 设置正在启动的容器的名称。                              |
| -nomtp          | - 禁用容器之间的默认通信方法，                            |
| -icps           | - 定义容器之间的通信方法，                                |
| -services       | - 在平台上启动附加服务，                                  |
| -backupmain     | - 将容器作为备份主容器启动。                              |

1. 主容器：
```cmd
java -cp lib/jade.jar jade.Boot ^ 
-host des01.eti.pg.gda.pl -port 5656 ^
-local-host des01.eti.pg.gda.pl -local-host 5656 ^
-services ^
jade.core.replication.MainReplicationService ^;^
jade.core.replication.AddressNotificationService
```

2. 备用容器：
```cmd
java -cp lib/jade.jar jade.Boot ^ 
-host des01.eti.pg.gda.pl -port 5656 ^
-local-host des02.eti.pg.gda.pl -local-host 4646 -backupmain ^
-services ^
jade.core.replication.MainReplicationService ^;^
jade.core.replication.AddressNotificationService
```

3. 联合容器：
```cmd
java -cp lib/jade.jar jade.Boot ^ 
-host des01.eti.pg.gda.pl -port 5656 ^
-local-host des03.eti.pg.gda.pl -local-host 4646 -container ^
-services ^
jade.core.replication.AddressNotificationService
```

注意：在 Linux 上运行环境时，在主容器上调用 ctrl + c 被认为是有效的程序终止并禁用整个平台。 建议使用带参数 9 的 kill 命令。

在容器之间使用加密（无需身份验证）不需要生成特殊密钥，只需适当启动平台即可。 禁用标准通信方法并将其替换为使用加密 (JICPSPeer) 的方法。 下面显示了一个启动示例。

1. 主容器：
```cmd
java -cp lib/jade.jar jade.Boot ^
-host des01.eti.pg.gda.pl -port 5656 ^
-local-host des01.eti.pg.gda.pl -local-port 5656 ^
-nomtp -icps jade.imtp.leap.JICP.JICPSPeer
```

2. 联合容器：
```cmd
java -cp lib/jade.jar jade.Boot ^
-host des01.eti.pg.gda.pl -port 5656 ^
-local-host des02.eti.pg.gda.pl -local-port 4646 -container ^
-nomtp -icps jade.imtp.leap.JICP.JICPSPeer
```

在正确启动的情况下，主容器的日志应包含以下信息：
```
INFO: JICP Secure Peer acticated. (auth=false, ta=jicp://des01.eti.pg.gda.pl:5656)
```

使用容器的加密和认证需要使用生成的密钥和密钥容器。 每个平台容器都必须配备一组将在消息加密过程中使用的密钥。 此外，为了确保其他容器的身份验证，容器必须具有构成平台的其他容器的可信密钥容器。
下面是一些使用 JRE 中包含的 keytool 工具的命令。

1. 为它们生成一对密钥和一个容器： 
```cmd
keytool -genkeypair -keystore des01.jks -alias des01 -keyalg rsa
keytool -genkeypair -keystore des02.jks -alias des02 -keyalg rsa
```

2. 导出公钥：
```cmd
keytool -export -keystore des01.jks -alias des01 -file des01.cer
keytool -export -keystore des02.jks -alias des02 -file des02.cer
```

3. 将公钥导入到可信密钥容器中：
```cmd
keytool -import -file des01.cer -alias des01 -keystore des02-ca.jks
keytool -import -file des02.cer -alias des02 -keystore des01-ca.jks
```

以下是运行具有加密和身份验证的环境的示例。

* keyStore 存储自身的公钥和私钥
* trustStore 存储对方的公钥

1. 主容器
```cmd
java -Djavax.net.ssl.keyStore=des01.jks ^
-Djavax.net.ssl.keyStorePassword=changeit ^
-Djavax.net.ssl.trustStore=des01-ca.jks ^
-cp lib/jade.jar jade.Boot ^
-host des01.eti.pg.gda.pl -port 5656 ^
-local-host des01.eti.pg.gda.pl -local-port 5656 ^
-nomtp ^
-icps jade.imtp.leap.JICP.JICPSPeer
```

```cmd
java -Djavax.net.ssl.keyStore=des01.jks ^
-Djavax.net.ssl.keyStorePassword=123456 ^
-Djavax.net.ssl.trustStore=des01-ca.jks ^
-Djavax.net.ssl.trustStorePassword=123456 ^
-cp jade.jar jade.Boot ^
-host 127.0.0.1 -port 5656 ^
-local-host 127.0.0.1 -local-port 5656 ^
-nomtp ^
-icps jade.imtp.leap.JICP.JICPSPeer ^
-gui
```


2. 联合容器
```cmd
java ^
-Djavax.net.ssl.keyStore=des02.jks ^
-Djavax.net.ssl.keyStorePassword=changeit ^
-Djavax.net.ssl.trustStore=des02-ca.jks ^
-cp lib/jade.jar jade.Boot ^
-host des01.eti.pg.gda.pl ^
-port 5656 ^
-local-host des02.eti.pg.gda.pl ^
-local-port 4646 ^
-container ^
-nomtp ^
-icps jade.imtp.leap.JICP.JICPSPeer
```

```cmd
java ^
-Djavax.net.ssl.keyStore=des02.jks ^
-Djavax.net.ssl.keyStorePassword=123456 ^
-Djavax.net.ssl.trustStore=des02-ca.jks ^
-Djavax.net.ssl.trustStorePassword=123456 ^
-cp jade.jar jade.Boot ^
-host 127.0.0.1 ^
-port 5656 ^
-local-host 127.0.0.1 ^
-local-port 4646 ^
-container ^
-nomtp ^
-icps jade.imtp.leap.JICP.JICPSPeer
```

在正确启动的情况下，主容器的日志应包含以下信息：
```
INFO: JICP Secure Peer activated. (auth=true, ta=jicp://des01.eti.pg.gda.pl:5656)
```

任务： 
1. 展示一个正确配置和启动的平台，在两个/三个容器之间进行加密（日志、代理之间的通信）， 
2. 展示一个正确配置和运行的平台，在两个/三个容器之间进行加密和授权（日志、代理之间的通信）， 
3. 在一个主容器、两个/三个备用容器和一个/两个联合（搅动主容器+日志）构建的星型拓扑中展示一个正确配置和运行的平台， 
4. 在一个由一个主容器构建的星型拓扑中展示一个正确配置和运行的平台一个主容器，两个/三个备份和一个/两个联合容器之间启用加密和授权（日志，代理之间的通信，搅动主容器+日志）。

成对/三人一组进行的任务。

**plus:**
以同样的方式运行下一个关联的容器
联合容器启动：
```cmd
java ^
-Djavax.net.ssl.keyStore=keystore1 ^
-Djavax.net.ssl.keyStorePassword=123456 ^
-Djavax.net.ssl.trustStore=truststore1 ^
-cp jade.jar jade.Boot ^
-host 127.0.0.1 ^
-port 5500 ^
-container ^
-nomtp ^
-icps jam.imtp.leap.JICP.JICPSPeer ^
-container-name jam-container1 
```


## Java 代码创建

* jade.core实现系统的核心.它包含必须被应用程序员继承的Agent类
  * jade.core.behaviours子包还包含一个Behaviour类层次结构.行为实现了一个Agent的任务或意图.它们是逻辑活动单元,并且可以以不同的方式组合,以获取不同的执行方式,当然,它们是可以并行执行的.应用程序员定义Agent的操作,编写行为以及Agent的执行路径.
* jade.lang.acl子包用于依照FIPA标准规定处理Agent通讯语言(ACL).
* jade.content包包含了一组类用于支持用户定义的概念和语言.
* jade.domain包包含了所有那些由FIPA标准定义的,描述Agent管理实体的JAVA类,特别是AMS (Agent Management Services) 和 DF(Directory Facilitator) Agent,它们提供生命周期服务和白黄页服务.
  * 子包jade.domain.FIPAAgentManagement包含了FIPA Agent管理的概念和描述其概念的类.
  * 子包jade.domain.JADEAgentManagement则包含了JADE对Agent管理的扩展(例如,对消息的探测以及控制Agent的生命周期).
  * 子包jade.domain.introspection包含了用于描述在JADE工具和JADE内核之间沟通领域的概念.
  * 子包jade.domain.mobility包含了描述移动通信的概念.
* Jade.gui包含了一组一般的类,用于建立用户图形界面,用来显示和编辑Agent标识符,Agent描述,ACL消息……
* jade.mtp包包含了一个JAVA接口.为了容易用JADE框架集成,每个消息传送协议必须利用这个接口,它还包含了一组这些协议的执行.
* jade.proto包包含了建模标准交互协议的类(如:fipa-request, fipa-query, fipa-contract-net, fipa-subscribe和其他一些被FIPA定义的类),同时也包含了帮助应用程序员建立自定义的协议的类.

`[我的github网址](还没定)`

1. [AID](AID.md)