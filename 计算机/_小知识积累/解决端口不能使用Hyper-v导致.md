# 解决端口不能使用Hyper-v导致

[Windows 下显示端口占用，却查不到占用进程_lylhw13_的博客-CSDN博客_端口被占用但是查不到](https://blog.csdn.net/m0_47696151/article/details/117785566)

发现端口被占用，首先使用
```cmd
> netstat -aon | find "1080"
或
> netstat -aon | grep "1080"
```

但是有些情况下面，显示端口占用，但是却查不到占用的进程。
原因是 Windows 会保留一些端口，这些端口刚好处于被保留的序列里。

```cmd
C:\> netsh interface ipv4 show excludedportrange protocol=tcp

Protocol tcp Port Exclusion Ranges

Start Port    End Port
----------    --------
      1031        1130
      1131        1230
      1561        1660
      2663        2762
      2763        2862
      2863        2962
      5357        5357
     50000       50099     *
     55500       55599
 
* - Administered port exclusions.
```

windows 保留这些端口的可能的原因：

* 因为发现病毒活动而被微软屏蔽
* 安装过windows update以后，保留的端口发生变化
* 开启了 Hyper-V 特性

**三种解决办法：**

1. 换用其他端口
2. 关闭 Hyper-V 特性
3. 将这些端口设置为 Administered port exclusions
    ```cmd
    netsh int ipv4 add excludedportrange protocol=tcp startport=1099 numberofports=1099
    ```