# 1107微任务(Microtask)

promise 的处理程序 .then、.catch 和 .finally 都是异步的。

即便一个 promise 立即被 resolve，.then、.catch 和 .finally 下面 的代码也会在这些处理程序之前被执行。

示例代码如下：
```js
let promise = Promise.resolve();

promise.then(() => alert("promise done!"));

alert("code finished"); // 这个 alert 先显示
```

**如果你运行它，你会首先看到 code finished，然后才是 promise done。**

这很奇怪，因为这个 promise 肯定是一开始就完成的。

为什么 .then 会在之后才被触发？这是怎么回事？

## 微任务队列（Microtask queue）
如 规范 中所述：

* 队**列（queue）是先进先出的：首先进入队列的任务会首先运行。**
* **只有在 JavaScript 引擎中没有其它任务在运行时，才开始执行任务队列中的任务。**

如果执行顺序对我们很重要该怎么办？我们怎么才能让 code finished 在 promise done 之后出现呢？

```js
Promise.resolve()
  .then(() => alert("promise done!"))
  .then(() => alert("code finished"));
```

## 未处理的 rejection
还记得 使用 promise 进行错误处理 一章中的 unhandledrejection 事件吗？

**如果一个 promise 的 error 未被在微任务队列的末尾进行处理，则会出现“未处理的 rejection”。**

正常来说，如果我们预期可能会发生错误，我们会在 promise 链上添加 .catch 来处理 error：
```js
let promise = Promise.reject(new Error("Promise Failed!"));
promise.catch(err => alert('caught'));

// 不会运行：error 已经被处理
window.addEventListener('unhandledrejection', event => alert(event.reason));
```

但是如果我们忘记添加 .catch，那么，微任务队列清空后，JavaScript 引擎会触发下面这事件：
```js
let promise = Promise.reject(new Error("Promise Failed!"));

// Promise Failed!
window.addEventListener('unhandledrejection', event => alert(event.reason));
```

如果我们迟一点再处理这个 error 会怎样？例如：
```js
let promise = Promise.reject(new Error("Promise Failed!"));
setTimeout(() => promise.catch(err => alert('caught')), 1000);

// Error: Promise Failed!
window.addEventListener('unhandledrejection', event => alert(event.reason));
```

**现在，如果我们运行上面这段代码，我们会先看到 Promise Failed!，然后才是 caught。**

如果我们并不了解微任务队列，我们可能会想：“为什么 unhandledrejection 处理程序会运行？我们已经捕获（catch）并处理了 error！”

但是现在我们知道了，当微任务队列中的任务都完成时，才会生成 unhandledrejection：引擎会检查 promise，如果 promise 中的任意一个出现 “rejected” 状态，unhandledrejection 事件就会被触发。

在上面这个例子中，被添加到 setTimeout 中的 .catch 也会被触发。只是会在 unhandledrejection 事件出现之后才会被触发，所以它并没有改变什么（没有发挥作用）。

## 总结

Promise 处理始终是异步的，因为所有 promise 行为都会通过内部的 “promise jobs” 队列，也被称为“微任务队列”（V8 术语）。

因此，.then/catch/finally 处理程序总是在当前代码完成后才会被调用。

如果我们需要确保一段代码在 .then/catch/finally 之后被执行，我们可以将它添加到链式调用的 .then 中。

在大多数 JavaScript 引擎中（包括浏览器和 Node.js），微任务（microtask）的概念与“事件循环（event loop）”和“宏任务（macrotasks）”紧密相关。由于这些概念跟 promise 没有直接关系，所以我们将在本教程另外一部分的 事件循环：微任务和宏任务 一章中对它们进行介绍。

## 个人记录
```js
let promise = new Promise(function(resolve, reject) {
    resolve("done!");
    alert(100);
});

promise.then(
  result => alert(result), 
  error => alert(error) 
);
alert(1000);
```
显示顺序：100   1000    done


```js
let promise = new Promise(function(resolve, reject) {
  setTimeout(() => 
  {
    resolve("done!");
    alert(100)
  }, 1000);
});


promise.then(
  result => alert(result), 
  error => alert(error) 
);
alert(1000);
```
显示顺序：1000 100 done
