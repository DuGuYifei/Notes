# Jade的基本程序关系

1. JADE 定义了Agent class 作为其他Agent 的父类， 其他Agent均继承自Agent class。 
2. Agent class 中
   1. 定义了setup 方法，用于初始化Agent；
   2. 定义了takeDown 方法，用于结束Agent 的运行；
   3. 定义了doDelete 方法，用于终止Agent；
   4. 定义了Behaviour 类以及addBehaviour 方法用于添加Agent 任务。 
3. 为了保证Agent 的分布式计算和协作机制，JADE 构建行为池(Behaviour Pool)来存储所有添加的Behaviour，这些Behaviour 呈队列排列，按照进入行为池的顺序依次被调用。
   1. Behaviour 方法被调用时，首先执行Action 方法，
   2. 然后判断Done 函数返回的布尔值， 如果为真则将Behaviour 移出行为池，继续下一个Behaviour 的执行。 
   3. JADE提供了这样一个基类，其他Agent 所需要做的是重载setup，action，done，takeDown 这几个方法来实现特定的功能模块。