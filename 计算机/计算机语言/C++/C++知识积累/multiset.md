# multiset

## 介绍
* 底层:红黑树
* 有序
* 不去重
* multiset的查找的时间复杂度是`Olog2N`
* multiset的底层存储的是`<value, value>`的键值对

## erase
会删除所有比较函数相同的元素

### c.erase(elem)

删除与elem相等的所有元素，返回被移除的元素个数。

### c.erase(pos)

移除迭代器pos所指位置元素，无返回值。

### c.erase(beg,end)

移除区间[beg,end)所有元素，无返回值。


