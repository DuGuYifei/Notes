# export-default

不管export default有没有在module里命名，import ABC from module 时，ABC就是default的名字，

比如

export default的是一个**箭头函数**并**返回一个函数**，那么ABC可以直接当函数使用
```JavaScript
ABC(param1, param2);
```