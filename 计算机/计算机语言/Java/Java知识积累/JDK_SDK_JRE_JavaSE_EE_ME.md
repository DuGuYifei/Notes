# JDK_SDK_JRE_JavaSE_EE_ME

## JDK
JDK是`Java Development Kit`的缩写，是Java开发环境的核心组件之一。它是一个用于开发Java应用程序的软件开发工具包，包含了Java编译器、Java虚拟机（JVM）、Java类库、Java调试器等。

**包含JRE**

## SDK
SDK（Software Development Kit），Java ME需要安装Java ME SDK（Software Development Kit），可以从Oracle官网下载和安装最新版本的Java ME SDK。

## JRE

JRE是Java Runtime Environment的缩写，是Java运行时环境，它是用于运行Java程序的组件之一。

JRE包含了Java虚拟机（JVM）和Java类库，可以让用户运行Java应用程序和小程序（applet），而不需要进行任何的编译工作。当用户安装JRE时，就可以在计算机上运行Java程序，而不必安装任何其他开发工具或库。

JRE只包含了Java运行时所需的组件，不包括Java编译器和其他开发工具。如果需要开发Java程序，则需要安装Java开发工具包（JDK），其中**包含了JRE**和Java开发所需的工具。

## JavaSE_EE_ME

Java平台包括三个主要版本：Java SE（`Java Standard Edition`）、Java EE（`Java Enterprise Edition`）和Java ME（`Java Micro Edition`）。它们各自定位于不同的应用场景。

Java SE是标准版Java平台，它主要用于桌面应用程序、嵌入式系统、移动设备和Web应用程序等。Java SE包含了Java语言本身的基本功能和标准类库。

Java EE是针对企业级应用程序开发的扩展平台，它提供了一系列的API和规范，帮助开发人员构建分布式、可伸缩、安全、高性能的企业级应用程序。

Java ME是专门针对嵌入式设备和移动设备开发的平台，它提供了一些小型的API和规范，使得开发人员能够在资源受限的环境中开发Java应用程序。

总之，Java平台包括Java SE、Java EE和Java ME三个版本，它们各自针对不同的应用场景，为开发人员提供了不同的工具和功能支持。

**Java EE，ME 都是建立在 SE 基础上的**

### Java EE 
安装Java EE开发环境：Java EE需要在支持Java EE规范的应用服务器上运行。可以使用开源的应用服务器如**Apache Tomcat、Jetty、WildFly**或者商用的应用服务器如WebLogic、WebSphere等。另外，还需要安装Java EE的开发工具，如Eclipse、IntelliJ IDEA等。

编写Java EE代码：编写Java EE代码，包括**Servlet、JavaServer Pages（JSP）、JavaServer Faces（JSF）、Enterprise JavaBeans（EJB）、Java Persistence API（JPA）等组件**。使用Java EE API和规范来实现业务逻辑和数据访问等功能。