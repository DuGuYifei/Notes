# 苹果设备不支持background-attachment的fixed

曲线救国，使用伪类：
```css
body::before {
    content: '';
    position: fixed;
    z-index: -1;
    top: 0;
    right: 0;
    bottom: 0;
    left: 0;
    background: url('../img/bg.png') no-repeat center top/100%;
    background-size: cover;
}
```

```JavaScript
headBack.onmousemove = function(event){
	let newX = event.clientX;
	let newY = event.clientY;
	document.styleSheets[0].removeRule(len)
	document.styleSheets[0].addRule('#profile::before','background-position-x:' + (50 - (x - newX)/50) + '%;background-position-y:' + (50 - (y - newY)/50 +"%") + '%;');
}
```