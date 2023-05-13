# 配置spark_conf_get

1. 配置选项：
Spark具有许多可用的配置设置，可以控制安装的各个方面。可以修改这些配置以最好地满足群集的特定需求。配置设置可以在配置文件、通过Spark Web界面和在运行时代码中进行修改。本课程的测试群集只能通过命令行访问，所以我们将使用最后一种选项。要读取配置设置，使用配置名称作为参数调用spark.conf.get()函数。要写入配置设置，使用配置名称和实际值作为函数参数调用`spark.conf.set()`函数。

2. 群集类型：
Spark的部署可以根据用户的确切需求而有所不同。部署的一个重要组成部分是群集管理机制。Spark集群可以是以下几种类型：单节点群集，在单个系统（物理机器/虚拟机/容器）上部署所有组件。独立群集，具有专用机器作为驱动程序和工作节点。托管群集，意味着群集组件由第三方群集管理器（如YARN、Mesos或Kubernetes）处理。在本课程中，我们使用的是单节点群集。生产环境可能会有很大的差异，但是我们将讨论独立群集，因为这些概念适用于所有管理类型。

3. Driver（驱动程序）：
如果你还记得的话，每个Spark集群都有一个驱动程序。驱动程序负责处理以下几个任务：将任务分配给群集中的各个节点/进程。驱动程序监控所有进程和任务的状态，并处理任何任务重试。驱动程序还负责 consolodating（汇总）来自群集中其他进程的结果。驱动程序处理对共享数据的访问，并验证每个工作节点是否具有必要的资源（代码、数据等）。鉴于驱动程序的重要性，通常值得增加节点的规格，以与其他系统相比增加内存。建议将内存加倍，这对任务监控和数据汇总任务非常有用。与Spark的所有系统一样，快速的本地存储对于在理想的设置中运行Spark非常有用。

4. Worker（工作节点）：
Spark工作节点负责运行驱动程序分配的任务，并将结果传输回驱动程序。理想情况下，工作节点具有完成给定任务所需的所有代码、数据和访问所需的资源的副本。如果其中任何一项不可用，工作节点必须暂停以获取资源。在调整群集大小时，有几个建议：根据任务的类型，更多的工作节点通常比更大的节点更好。


## 获取一些配置信息
```python
# Name of the Spark application instance
app_name = spark.conf.get('spark.app.name')

# Driver TCP port
driver_tcp_port = spark.conf.get('spark.driver.port')

# Number of join partitions
num_partitions = spark.conf.get('spark.sql.shuffle.partitions')

# Show the results
print("Name: %s" % app_name)
print("Driver TCP port: %s" % driver_tcp_port)
print("Number of partitions: %s" % num_partitions)
```

## 修改配置信息
```python
# Store the number of partitions in variable
before = departures_df.rdd.getNumPartitions()

# Configure Spark to use 500 partitions
spark.conf.set('spark.sql.shuffle.partitions', 500)

# Recreate the DataFrame using the departures data file
departures_df = spark.read.csv('departures.txt.gz').distinct()

# Print the number of partitions for each instance
print("Partition count before change: %d" % before)
print("Partition count after change: %d" % departures_df.rdd.getNumPartitions())
```