# MapReduce流程


1. 任务提交阶段（Job Submission）：创建一个 MapReduce 作业并将其提交给 Hadoop 集群。
   
2. 任务准备阶段（Job Preparation）：任务提交后，Hadoop 集群会进行一系列的准备工作，包括文件分发、作业本地化、环境配置等。
3. Mapper 阶段（Map）：
   1. setup()：初始化 Mapper 阶段的工作，执行一次。
   2. map()：读取输入的键值对，进行处理，产生中间键值对。
   
4. Combiner 阶段（Combiner，可选）：
   1. combine()：对 Mapper 阶段输出的中间结果进行合并和优化，减少数据传输和磁盘 I/O 操作，提高性能。

5. Shuffle 阶段（Shuffle and Sort）：
   1. Hadoop 框架自动处理，无需程序员干预。
   2. Shuffle可以将来自相同key的value合并

6. Reducer 阶段（Reduce）：
   1. setup()：初始化 Reducer 阶段的工作，执行一次。
   2. reduce()：读取中间键值对，进行处理，输出最终结果。
   3. cleanup()：清理 Reducer 阶段的工作，执行一次。

7. 任务完成阶段（Job Completion）：
   1. Hadoop 框架自动处理，进行一些清理工作，例如关闭文件、释放内存等，以保证任务正常结束。

其中，任务提交阶段、任务准备阶段和任务完成阶段通常由 Hadoop 框架自动处理，setup()、map()、reduce() 和 cleanup() 阶段则需要根据程序逻辑进行实现。Shuffle 和 Sort 阶段由 Hadoop 框架自动处理，无需程序员干预。

[setup_clenup_run_context](setup_clenup_run_context.md)
[map和reduce执行次数](map和reduce执行次数.md)： 这里解释了map后将value根据key合并