# @Column

1. name

    定义了被标注字段在数据库表中所对应字段的名称；

    [字段带下划线findBy问题](字段带下划线findBy问题.md)

2. unique

    表示该字段是否为唯一标识，默认为false。如果表中有一个字段需要唯一标识，则既可以使用该标记，也可以使用@Table标记中的@UniqueConstraint。

3. nullable
   
    表示该字段是否可以为null值，默认为true。

4. insertable
   
    表示在使用“INSERT”脚本插入数据时，是否需要插入该字段的值。

5. updatable
    
    表示在使用“UPDATE”脚本插入数据时，是否需要更新该字段的值。insertable和updatable属性一般多用于只读的属性，例如主键和外键等。这些字段的值通常是自动生成的。

6. columnDefinition（大多数情况，几乎不用）
    
    表示创建表时，该字段创建的SQL语句，一般用于通过Entity生成表定义时使用。（也就是说，如果DB中表已经建好，该属性没有必要使用。）

7. table
    
    表示当映射多个表时，指定表的表中的字段。默认值为主表的表名。

8. length
    
    表示字段的长度，当字段的类型为varchar时，该属性才有效，默认为255个字符。

9. precision和scale

    precision属性和scale属性表示精度，当字段类型为double时，precision表示数值的总长度，scale表示小数点所占的位数。