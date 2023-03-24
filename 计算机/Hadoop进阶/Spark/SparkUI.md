# SparkUI

## Use the Spark UI inspect execution
* **Spark Task** is a unit of execution that runs on a single cpu
* **Spark Stage** a group of tasks that perform the same computation in parallel, each task typically running on a different subset of data
* **Spark Job** is a computation triggered by an action, sliced into one or more stages.

## Jobs tab
![](2023-03-23-18-53-52.png)

![](2023-03-23-18-54-12.png)

## Stage tab
![](2023-03-23-18-56-46.png)

比如一个sqlquery用到了多个stage，就会在这里显示出多个stage。

## Storage tab
![](2023-03-23-18-54-24.png)

Shows where data partitions exist
* in memory
* or on disk
* across the cluster
* at a snapshot in time

## SQL tab
![](2023-03-23-18-55-03.png)