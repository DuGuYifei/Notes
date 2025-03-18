# 箭头函数return与大括号省略问题

// 当箭头函数的函数体只有一个 `return` 语句时，可以省略 `return` 关键字和方法体的花括号
```js
elements.map(element => element.length); // [8, 6, 7, 9]
```