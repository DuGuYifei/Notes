# scroll-snap自动滚动到合适位置

[css --- scroll-snap属性实现智能滚动_就叫小黄好了鸭的博客-CSDN博客_scroll-snap](https://blog.csdn.net/weixin_42365757/article/details/121704261)

scroller snap 目前支持scroll-snap-type和scroll-snap-align两个属性。

* scroll-snap-type用于容器，定义滚动的方向和类型。
* scroll-snap-align用于子元素，定义滚动停止后，子元素的对齐方式。

scroll-snap-type 的用法
* mandatory：比较好理解：当用户停止滚动的时候，会自动选择一个子元素的点。
* proximity：只有用户滚动到接近到足够的值的时候，才会选择一个子元素的点进行滚动。感觉有点难以理解。

举个例子来说：一个200px 宽的容器，内部有多个宽200px子元素横向滚动，设置子元素 scroll-snap-align: center;容器scroll-snap-type: x proximity;

## 放在body上无效，得放在html上