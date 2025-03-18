# add-offer_remove-poll_element-peek

* 在容量已满的情况下，add() 方法会抛出IllegalStateException异常，offer() 方法只会返回 false 。
* remove方法和poll方法都是删除队列的头元素，remove方法在队列为空的情况下将抛异常，而poll方法将返回null；
* element和peek方法都是返回队列的头元素，但是不删除头元素，区别在与element方法在队列为空的情况下，将抛异常，而peek方法将返回null。