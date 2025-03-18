# Rest参数与Spread语法

在 JavaScript 中，很多内建函数都支持传入任意数量的参数。

例如：

* Math.max(arg1, arg2, ..., argN) —— 返回参数中的最大值。
* Object.assign(dest, src1, ..., srcN) —— 依次将属性从 src1..N 复制到 dest。

在本章中，我们将学习如何编写支持传入任意数量参数的函数，以及如何将数组作为参数传递给这类函数。

1. [Rest参数](#rest参数)
   1. [Rest 参数必须放到参数列表的末尾](#rest-参数必须放到参数列表的末尾)
2. [arguments 变量](#arguments-变量)
   1. [箭头函数没有 "arguments"](#箭头函数没有-arguments)
3. [Spread语法](#spread语法)
4. [复制 array/object](#复制-arrayobject)
5. [总结](#总结)

## Rest参数
在 JavaScript 中，无论函数是如何定义的，你都可以在调用它时传入任意数量的参数。

例如：
```js
function sum(a, b) {
  return a + b;
}

alert( sum(1, 2, 3, 4, 5) );
```

虽然这里这个函数不会因为传入过多的参数而报错。**但是，当然，只有前两个参数被求和了。**

我们可以在函数定义中**声明一个数组**来收集参数。语法是这样的：**...变量名**，这将会声明一个数组并指定其名称，其中存有**剩余的参数**。这三个点的语义就是“收集剩余的参数并存进指定数组中”。

例如，我们需要把所有的参数都放到数组 args 中：\]
```js
function sumAll(...args) { // 数组名为 args
  let sum = 0;

  for (let arg of args) sum += arg;

  return sum;
}

alert( sumAll(1) ); // 1
alert( sumAll(1, 2) ); // 3
alert( sumAll(1, 2, 3) ); // 6
```

我们也可以选择将第一个参数获取为变量，并将剩余的参数收集起来。

下面的例子把前两个参数获取为变量，并把剩余的参数收集到 titles 数组中：
```js
function showName(firstName, lastName, ...titles) {
  alert( firstName + ' ' + lastName ); // Julius Caesar

  // 剩余的参数被放入 titles 数组中
  // i.e. titles = ["Consul", "Imperator"]
  alert( titles[0] ); // Consul
  alert( titles[1] ); // Imperator
  alert( titles.length ); // 2
}

showName("Julius", "Caesar", "Consul", "Imperator");
```

### Rest 参数必须放到参数列表的末尾
Rest 参数会收集剩余的所有参数，因此下面这种用法没有意义，并且会导致错误：
```js
function f(arg1, ...rest, arg2) { // arg2 在 ...rest 后面？！
  // error
}
```

...rest 必须写在参数列表最后。

## arguments 变量
有一个名为 arguments 的特殊**类数组对象（它可以被迭代，因为支持 spread 语法）**可以在函数中被访问，该对象以参数在参数列表中的索引作为键，存储所有参数。

```js
function showName() {
  alert( arguments.length );
  alert( arguments[0] );
  alert( arguments[1] );

  // 它是可遍历的
  // for(let arg of arguments) alert(arg);
}

// 依次显示：2，Julius，Caesar
showName("Julius", "Caesar");

// 依次显示：1，Ilya，undefined（没有第二个参数）
showName("Ilya");
```

**缺点**是，尽管 arguments 是一个类数组，也是可迭代对象，但它终究不是数组。它不支持数组方法，因此我们不能调用 arguments.map(...) 等方法。

此外，它始终包含所有参数，我们不能像使用 rest 参数那样只截取参数的一部分。

因此，**当我们需要这些功能时，最好使用 rest 参数。**

### 箭头函数没有 "arguments"
如果我们在箭头函数中访问 arguments，访问到的 arguments 并不属于箭头函数，而是属于箭头函数外部的“普通”函数。

举个例子：
```js
function f() {
  let showArg = () => alert(arguments[0]);
  showArg();
}

f(1); // 1
```
我们已经知道，箭头函数没有自身的 this。现在我们知道了它们也没有特殊的 arguments 对象。

悟：其实就是箭头函数创建了一个新函数之前的参数不会传进去的，下面这样就行了
```js
function f() {
  let showArg = () => alert(arguments);
  showArg(arguments[1]);
}

f(1,2); // 2
```

## Spread语法

错误写法：
```js
let arr = [3, 5, 1];

alert( Math.max(arr) ); // NaN
```

Spread 语法 可以解决这个问题！它看起来和 rest 参数很像，也使用 ...，但是二者的用途完全相反。

当在**函数调用中**使用 **...arr** 时，它会**把可迭代对象 arr “展开”**到参数列表中。

```js
let arr = [3, 5, 1];

alert( Math.max(...arr) ); // 5（spread 语法把数组转换为参数列表）
```

**我们还可以通过这种方式传入多个可迭代对象：**

```js
let arr1 = [1, -2, 3, 4];
let arr2 = [8, 3, -8, 1];

alert( Math.max(...arr1, ...arr2) ); // 8
```

**我们还可以使用 spread 语法来合并数组：**

```js
let arr = [3, 5, 1];
let arr2 = [8, 9, 15];

let merged = [0, ...arr, 2, ...arr2];

alert(merged); // 0,3,5,1,2,8,9,15（0，然后是 arr，然后是 2，然后是 arr2）
```

**其实我们可以用 spread 语法这样操作任何可迭代对象。**

例如，在这儿我们使用 spread 语法将字符串转换为字符数组：

```js
let str = "Hello";

alert( [...str] ); // H,e,l,l,o
```

Spread 语法内部使用了迭代器来收集元素，与 for..of 的方式相同。

因此，对于一个字符串，for..of 会逐个返回该字符串中的字符，...str 也同理会得到 "H","e","l","l","o" 这样的结果。随后，字符列表被传递给数组初始化器 [...str]。

对于这个特定任务，我们还可以使用 **Array.from** 来实现，因为该方法会将一个可迭代对象（如字符串）转换为数组：

```js
let str = "Hello";

// Array.from 将可迭代对象转换为数组
alert( Array.from(str) ); // H,e,l,l,o
```

**不过 Array.from(obj) 和 [...obj] 存在一个细微的差别：**

* Array.from 适用于**类数组对象**也适用于**可迭代对象**。
* Spread 语法只适用于**可迭代对象**。

**因此，对于将一些“东西”转换为数组的任务，Array.from 往往更通用。**

## 复制 array/object
还记得我们 之前讲过的 Object.assign() 吗？

使用 spread 语法也可以做同样的事情（译注：也就是进行浅拷贝）。

```js
let arr = [1, 2, 3];

let arrCopy = [...arr]; // 将数组 spread 到参数列表中
                        // 然后将结果放到一个新数组

// 两个数组中的内容相同吗？
alert(JSON.stringify(arr) === JSON.stringify(arrCopy)); // true

// 两个数组相等吗？
alert(arr === arrCopy); // false（它们的引用是不同的）

// 修改我们初始的数组不会修改副本：
arr.push(4);
alert(arr); // 1, 2, 3, 4
alert(arrCopy); // 1, 2, 3
```

并且，也可以通过相同的方式来复制一个对象：

```js
let obj = { a: 1, b: 2, c: 3 };

let objCopy = { ...obj }; // 将对象 spread 到参数列表中
                          // 然后将结果返回到一个新对象

// 两个对象中的内容相同吗？
alert(JSON.stringify(obj) === JSON.stringify(objCopy)); // true

// 两个对象相等吗？
alert(obj === objCopy); // false (not same reference)

// 修改我们初始的对象不会修改副本：
obj.d = 4;
alert(JSON.stringify(obj)); // {"a":1,"b":2,"c":3,"d":4}
alert(JSON.stringify(objCopy)); // {"a":1,"b":2,"c":3}
```

这种方式比使用 let arrCopy = Object.assign([], arr) 复制数组，或使用 let objCopy = Object.assign({}, obj) 复制对象来说更为简便。**因此，只要情况允许，我们倾向于使用它**。

## 总结
当我们在代码中看到 "..." 时，它要么是 rest 参数，要么是 spread 语法。

有一个简单的方法可以区分它们：

若 ... 出现在函数参数列表的最后，那么它就是 rest 参数，它会把参数列表中剩余的参数收集到一个数组中。
若 ... 出现在函数调用或类似的表达式中，那它就是 spread 语法，它会把一个数组展开为列表。
使用场景：

Rest 参数用于创建可接受任意数量参数的函数。
Spread 语法用于将数组传递给通常需要含有许多参数的函数。
我们可以使用这两种语法轻松地互相转换列表与参数数组。

旧式的 arguments（类数组且可迭代的对象）也依然能够帮助我们获取函数调用中的所有参数。