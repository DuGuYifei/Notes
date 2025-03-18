# 子元素margin-top会影响父元素解决办法

[子元素margin-top为何会影响父元素？_萤火虫塔莉的博客-CSDN博客](https://blog.csdn.net/sinat_27088253/article/details/52954688)

解决办法：

1. 父级或子元素使用浮动或者绝对定位absolute

浮动或绝对定位不参与margin的折叠

2. 父级overflow:hidden;

3. 父级设置padding（破坏非空白的折叠条件）

4. 父级设置border