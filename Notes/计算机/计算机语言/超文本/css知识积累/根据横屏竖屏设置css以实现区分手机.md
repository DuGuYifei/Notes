# 根据横屏竖屏设置css以实现区分手机

```css
<style type="text/css">
/*定义竖屏 css*/
@media screen and (orientation:portrait) {
	.portrait { display:block; background-color:#FFCC00; }
	.landscape { display:none; }
}
/*定义横屏 css*/
@media screen and (orientation:landscape) {
	.portrait { display:none; }
	.landscape { display:block; background-color:#FFCC00; }
}
</style>
```