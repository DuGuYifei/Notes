# @JoinColumn

1. @JoinColumn注释的是**保存表与表之间关系的字段**，它要标注在实体属性上。

2. 不设置name的值，则在默认情况下，name的取值遵循以下规则： **name=关联表的名称+“_”+ 关联表主键的字段名**

3. **双向**一对多关系
   1. 一是关系维护端（owner side），多是关系被维护端（inverse side）。
   2. **在关系被维护端需要通过@JoinColumn建立**外键列指向关系维护端的主键列。
   3. 即Animal是一，Pets是多，在Pets里建JoinColumn注释

4. **悟：它是怎么知道关联哪个表的**：
484傻，这不是由类型Animal吗
```Java
    @ManyToOne
    @JoinColumn(name = "animal")
    private Animal animal;
```
