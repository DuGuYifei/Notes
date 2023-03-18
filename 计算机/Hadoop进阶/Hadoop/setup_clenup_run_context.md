# setup_clenup_run_context
1. setup()，此方法被MapReduce框架仅且执行一次，在执行Map任务前，进行相关变量或者资源的集中初始化工作。若是将资源初始化工作放在方法map()中，导致Mapper任务在解析每一行输入时都会进行资源初始化工作，导致重复，程序运行效率不高！
2. Mapper或Reducer运行
3. cleanup(),此方法被MapReduce框架仅且执行一次，在执行完毕Map任务后，进行相关变量或资源的释放工作。若是将释放资源工作放入方法map()中，也会导致Mapper任务在解析、处理每一行文本后释放资源，而且在下一行文本解析前还要重复初始化，导致反复重复，程序运行效率不高！
4. run 程序启动运行
5. Context 是MapReduce任务运行的一个上下文，包含了整个任务的全部信息
   1. context作为了map和reduce执行中各个函数的一个桥梁，这个设计和java web中的session对象、application对象很相似

注：建议资源初始化及释放工作，分别放入方法setup()和cleanup()中进行

2.执行顺序
setup---->Mapper或Reducer----->cleanup
| |
run