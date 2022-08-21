# 0608调度：setTimeout和setInterval

有时我们并不想立即执行一个函数，而是等待特定一段时间之后再执行。这就是所谓的“计划调用（scheduling a call）”。

目前有两种方式可以实现：

* **setTimeout 允许我们将函数推迟到一段时间间隔之后再执行。**
* **setInterval 允许我们重复运行一个函数，从一段时间间隔之后开始运行，之后以该时间间隔连续重复运行该函数。**

***这两个方法并不在 JavaScript 的规范中。***但是大多数运行环境都有内建的调度程序，并且提供了这些方法。目前来讲，所有浏览器以及 Node.js 都支持这两个方法。

## setTimeout

```
let timerId = setTimeout(func|code, [delay], [arg1], [arg2], ...)
```

参数说明：

1. func|code
想要执行的函数或代码字符串。 一般传入的都是函数。由于某些历史原因，支持传入代码字符串，但是不建议这样做。
2. delay
执行前的延时，以毫秒为单位（1000 毫秒 = 1 秒），默认值是 0；
3. arg1，arg2…
要传入被执行函数（或代码字符串）的参数列表（IE9 以下不支持）

例如，在下面这个示例中，sayHi() 方法会在 1 秒后执行：
```js
function sayHi() {
  alert('Hello');
}

setTimeout(sayHi, 1000);
```

**带参数的情况：**
```js
function sayHi(phrase, who) {
  alert( phrase + ', ' + who );
}

setTimeout(sayHi, 1000, "Hello", "John"); // Hello, John
```

如果第一个参数位传入的是**字符串**，JavaScript 会自动为其创建一个函数。

所以这么写也是可以的：
```js
setTimeout("alert('Hello')", 1000);
```

但是，**不建议使用字符串，我们可以使用箭头函数**代替它们，如下所示：
```js
setTimeout(() => alert('Hello'), 1000);
```
### 传入一个函数，但不要执行它
新手开发者有时候会误将一对括号 () 加在函数后面：
```js
// 错的！
setTimeout(sayHi(), 1000);
```
这样不行，因为 setTimeout 期望得到一个对函数的引用。而**这里的 sayHi() 很明显是在执行函数**，所以实际上传入 setTimeout 的是 **函数的执行结果**。在这个例子中，sayHi() 的执行结果是 **undefined（也就是说函数没有返回任何结果）**，所以实际上什么也没有调度。

### 用 clearTimeout 来取消调度
setTimeout 在调用时会**返回一个“定时器标识符（timer identifier）”**，在我们的例子中是 timerId，我们可以**使用它来取消执行**。

```js
let timerId = setTimeout(...);
clearTimeout(timerId);
```