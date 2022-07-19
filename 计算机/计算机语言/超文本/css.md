# css

1. [overflow](#overflow)
2. [display:flex](#displayflex)
3. [float](#float)
4. [transition和animation](#transition和animation)
5. [margin, border, padding](#margin-border-padding)
6. [子元素选择器](#子元素选择器)
7. [ul偏右](#ul偏右)
8. [li图片不居中](#li图片不居中)
   
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