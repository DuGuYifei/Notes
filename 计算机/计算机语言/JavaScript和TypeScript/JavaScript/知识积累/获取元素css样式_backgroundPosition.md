# 获取元素css样式_backgroundPosition

```js
function getStyle( obj , attr ){
    if ( window.getComputedStyle ) {
        return getComputedStyle( obj , null )[attr];
    }else{
        return obj.currentStyle[attr];
    }
}

let box=document.getElementById('profile');
alert(getStyle(box, 'background-position'));
```

修改：
```js
let back = document.getElementById('back');
back.style.backgroundPositionX = x+"px";
back.style.backgroundPositionY = y+"px";
```