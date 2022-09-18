# backgroundPosition在center时

当设置为center时，其backgroundPositionX = backgroundPositionY = "50%"

用于验证的代码：

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

[获取元素css样式_backgroundPosition](../../JavaScript和TypeScript/JavaScript/知识积累/获取元素css样式_backgroundPosition.md)