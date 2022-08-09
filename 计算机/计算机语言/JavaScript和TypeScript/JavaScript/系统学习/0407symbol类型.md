# 0407symbol类型

只有两种原始类型可以用作对象属性键：
* 字符串类型
* symbol类型

否则，如果使用另一种类型，例如数字，它会被**自动转换为字符串**
所以 `obj[1]` 与 `obj["1"]` 相同，而 `obj[true]` 与 `obj["true"]` 相同。

## symbol
symbol值表示唯一的标识符

可以使用Symbol()来创建
```javascript
let id = Symbol();
// id 是描述为 "id" 的 symbol （描述名或symbol名）
let id = Symbol("id"); 
```

symbol保证是唯一的，即使我们创建了许多具有相同描述的symbol

```javascript
let id1 = Symbol("id");
let id2 = Symbol("id");

alert(id1 == id2); // false
```

### 注意symbol不能自动转换为字符串

JavaScript 中的大多数值都支持字符串的隐式转换。例如，我们可以 alert 任何值，都可以生效。symbol 比较特殊，它不会被自动转换。


```javascript
let id = Symbol("id");
alert(id); // 类型错误：无法将 symbol 值转换为字符串。

alert(id.toString()); // 输出：Symbol(id)

alert(id.description); // 输出：id
```

## 隐藏属性
symbol 允许我们创建对象的“隐藏”属性，**代码的任何其他部分都不能意外访问或重写这些属性**。

例如，如果我们使用的是属于第三方代码的 user 对象，我们想要给它们添加一些标识符。

**使用 Symbol("id") 作为键，比起用字符串 "id" 来有什么好处呢？**

由于 user 对象属于另一个代码库，所以向它们添加字段是不安全的，因为我们可能会影响代码库中的其他预定义行为。但 symbol 属性不会被意外访问到。第三方代码不会知道新定义的 symbol，因此将 symbol 添加到 user 对象是安全的。


```javascript
let user = { // 属于另一个代码
  name: "John"
};

let id = Symbol("id");

user[id] = 1;

alert( user[id] ); // 我们可以使用 symbol 作为键来访问数据
```


另外，假设另一个脚本希望在 user 中有自己的标识符，以实现自己的目的。

那么，**该脚本可以创建自己的 Symbol("id")**


但是如果用**字符串**：

```javascript
let user = { name: "John" };

// 我们的脚本使用了 "id" 属性。
user.id = "Our id value";

// ……另一个脚本也想将 "id" 用于它的目的……

user.id = "Their id value"
// 砰！无意中被另一个脚本重写了 id！
```

## 对象字面量中的使用方法
如果我们要在对象字面量 {...} 中使用 symbol，则需要使用方括号把它括起来。

就像这样：

```javascript
let id = Symbol("id");

let user = {
  name: "John",
  [id]: 123 // 而不是 "id"：123
};
```
这是因为我们需要变量 id 的值作为键，而不是字符串 “id”。**


## symbol在for...in中会被跳过
symbol 属性不参与 for..in 循环。

例如：
```javascript
let id = Symbol("id");
let user = {
  name: "John",
  age: 30,
  [id]: 123
};

for (let key in user) alert(key); // name, age（没有 symbol）

// 使用 symbol 任务直接访问
alert("Direct: " + user[id]); // Direct: 123
```

## Object.key和assign
`Object.keys(user)` 也**会忽略**它们。这是一般“隐藏符号属性”原则的一部分。如果另一个脚本或库遍历我们的对象，它不会意外地访问到符号属性。

相反，`Object.assign` **会同时复制字符串和 symbol 属性：**

```javascript
let id = Symbol("id");
let user = {
  [id]: 123
};

let clone = Object.assign({}, user);

alert( clone[id] ); // 123
```

## 全局symbol
正如我们所看到的，通常所有的 symbol 都是不同的，即使它们有相同的名字。但有时我们想要名字相同的 symbol 具有相同的实体。例如，应用程序的不同部分想要访问的 symbol "id" 指的是完全相同的属性。

为了实现这一点，这里有一个 **全局 symbol 注册表**。我们可以在其中创建 symbol 并在稍后访问它们，它可以确保每次访问相同名字的 symbol 时，返回的都是相同的 symbol。


### Symbol.for(key)
要从注册表中读取（**不存在则创建**）symbol，请使用 `Symbol.for(key)`。

该调用会检查全局注册表，如果有一个描述为 key 的 symbol，则返回该 symbol，否则将创建一个新 symbol（`Symbol(key)`），并通过给定的 key 将其存储在注册表中。

```javascript
// 从全局注册表中读取
let id = Symbol.for("id"); // 如果该 symbol 不存在，则创建它

// 再次读取（可能是在代码中的另一个位置）
let idAgain = Symbol.for("id");

// 相同的 symbol
alert( id === idAgain ); // true
```
### Symbol.keyFor
对于全局 symbol，
`Symbol.for(key)` 按名字返回一个 symbol。
相反，通过**全局 symbol** 返回一个名字，我们可以使用 `Symbol.keyFor(sym)：`

```javascript
// 通过 name 获取 symbol
let sym = Symbol.for("name");
let sym2 = Symbol.for("id");

// 通过 symbol 获取 name
alert( Symbol.keyFor(sym) ); // name
alert( Symbol.keyFor(sym2) ); // id
```

如果 symbol 不是全局的，它将无法找到它并返回 undefined。

```javascript
let globalSymbol = Symbol.for("name");
let localSymbol = Symbol("name");

alert( Symbol.keyFor(globalSymbol) ); // name，全局 symbol
alert( Symbol.keyFor(localSymbol) ); // undefined，非全局

alert( localSymbol.description ); // name
```

## 系统symbol
* Symbol.hasInstance
* Symbol.isConcatSpreadable
* Symbol.iterator
* Symbol.toPrimitive
* ……等等。

例如，Symbol.toPrimitive 允许我们将对象描述为原始值转换。我们很快就会看到它的使用。

当我们研究相应的语言特征时，我们对其他的 symbol 也会慢慢熟悉起来。

avaScript 使用了许多系统 symbol，这些 symbol 可以作为 Symbol.* 访问。我们可以使用它们来改变一些内建行为。例如，在本教程的后面部分，我们将使用 Symbol.iterator 来进行 迭代 操作，使用 Symbol.toPrimitive 来设置 对象原始值的转换 等等。