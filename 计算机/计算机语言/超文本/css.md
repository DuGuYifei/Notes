# css

1. [overflow](#overflow)
2. [display:flex](#displayflex)
3. [float](#float)
4. [transition和animation](#transition和animation)
5. [margin, border, padding](#margin-border-padding)
6. [子元素选择器](#子元素选择器)
7. [ul偏右](#ul偏右)
8. [li图片不居中](#li图片不居中)
9. [井号，点，不加 选择器](#井号点不加-选择器)
10. [@规则](#规则)
   1. [常规规则](#常规规则)
   2. [嵌套规则](#嵌套规则)
      1. [@media](#media)
   
## overflow
内容溢出元素框时的布局设置

## display:flex
[浅谈CSS3中display属性的Flex布局 - 孙冠醇 - 博客园](https://www.cnblogs.com/sunwk/p/9049384.html)

## float
块靠哪里浮动，左/右

## transition和animation
transition只有两个关键帧，animation有多个
`transition: property duration timing-function delay;`

1. linear相同速度开始到结束
2. ease慢速开始变快慢速结束
3. ease-in慢速开始
4. ease-out慢速结束
5. ease-in-out
6. cubic-bezier(n,n,n,n)

## margin, border, padding
由外向里的三层

## 子元素选择器
father>child

## ul偏右
```css
#leftbar>ul{
	margin-left: 10%;
	margin-top: 50px;
	padding: 0;
}
```

## li图片不居中
```css
#leftbar>ul>li>img{
	vertical-align: bottom;
}
```

## 井号，点，不加 选择器
* `#`对应id
* `.`对应class
* 不加则对应标签

## @规则
[CSS @规则（详细）](http://c.biancheng.net/css3/at-rule.html)
在 CSS 中包含两种语法规则：
* 普通规则：由选择器、属性和值构成，在之前的学习中我们主要使用的就是这种规则；
* @规则：以@开头后面跟随一个关键字的形式构成，也被称为“AT规则”，根据使用方法的不同又可以分为：
  * “常规规则”
  * “嵌套规则”

### 常规规则
```
@[KEYWORD] (RULE);
```

### 嵌套规则
@规则后面需要跟随一个花括号{ }，其中包含了一些其它的规则声明
```
@[KEYWORD] {
    /* 嵌套语句 */
}
```
#### @media
@media 用来根据一个或多个媒体查询的结果来应用样式表的某一部分（**花括号中的样式信息**），使用 @media 您可以指定一组媒体查询和一个 CSS 样式块，**当且仅当媒体查询与正在使用的设备匹配时，指定的 CSS 样式才会应用于文档**。


*媒体查询是用于判断设备信息的一组条件，如设备的宽高值，宽高比，颜色，分辨率等，当条件匹配时，才会执行其内嵌套的样式信息。*


@media 可以放置在样式表中的任意位置，也可以放置于其它 @规则中，示例代码如下：
```css
@media all and (min-width: 1280px) {
    /* 宽度大于1280 */
}
@media
(-webkit-min-device-pixel-ratio: 1.5),
(min-resolution: 2dppx) {
    /* Retina屏幕 */
}
@media print {
    /* 打印 */
}
@media \0screen\,screen\9 {
    /* IE7,IE8 */
}
@media screen\9 {
    /* IE7*/
}
```