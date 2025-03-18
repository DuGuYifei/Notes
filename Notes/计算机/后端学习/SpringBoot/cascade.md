# @OneToMany的cascade
默认没有级联

1. CascadeType.REMOVE
Cascade remove operation，级联删除操作。
删除当前实体时，与它有映射关系的实体也会跟着被删除
**没有这一句删除One边的api会返回500**
2. CascadeType.MERGE
Cascade merge operation，级联更新（合并）操作。
当orderDetail中的数据改变，会相应地更新order中的数据。
3. CascadeType.DETACH
Cascade detach operation，级联脱管/游离操作。
如果你要删除一个实体，但是它有外键无法删除，你就需要这个级联权限了。它会撤销所有相关的外键关联。
4. CascadeType.REFRESH
Cascade refresh operation，级联刷新操作。
假设场景 有一个订单,订单里面关联了许多商品,这个订单可以被很多人操作,那么这个时候A对此订单和关联的商品进行了修改,与此同时,B也进行了相同的操作,但是B先一步比A保存了数据,那么当A保存数据的时候,就需要先刷新订单信息及关联的商品信息后,再将订单及商品保存
5. CascadeType.ALL
Cascade all operations，清晰明确，拥有以上所有级联操作权限。

### REMOVE 和 DETACH 区别
REMOVE 实体的行
DETACH 删除整个实体