# 原生js获取css伪类元素并设置属性

[原生js获取css伪类元素并设置属性_blankliu404的博客-CSDN博客_js获取伪类元素](https://blog.csdn.net/L333333333/article/details/101619111)

## 设置或更改伪类的属性
```JavaScript
<script type="text/javascript">
	function loading() {
		document.styleSheets[0].addRule('button::after','animation-name:load;animation-duration: 3s;animation-iteration-count: infinite;')
	}
</script>
```

## 获取伪类元素并取值（如果你只是单纯的取值，请看这里）
```JavaScript
<script type="text/javascript">
	var buttonObj = document.querySelector('button')
	var buttonAfterStyle = getComputedStyle(buttonObj,':after')
	//第一种方法
	alert('buttonAfterStyle.getPropertyValue("width") result: ' + buttonAfterStyle.getPropertyValue('width'))
	//第二种方法
	alert('buttonAfterStyle.width result: ' + buttonAfterStyle.width)
</script>

```

## 案例让图片跟随鼠标移动
```js
let headBack = document.getElementById('profile');
let x = -1,y = -1;
let len = document.styleSheets[0].rules.length;
document.styleSheets[0].addRule('#profile::before','background-position-x: center')
headBack.onmouseenter = function(event){
    x = event.clientX;
    y = event.clientY;
}
headBack.onmousemove = function(event){
	let newX = event.clientX;
	let newY = event.clientY;
	document.styleSheets[0].removeRule(len)
	document.styleSheets[0].addRule('#profile::before','background-position-x:' + (50 - (x - newX)/50) + '%;background-position-y:' + (50 - (y - newY)/50 +"%") + '%;');
}
headBack.onmouseleave = function(event){
	headBack.style = 'transition:background-position 0.2s 0s linear; background-position: center;';
}
```