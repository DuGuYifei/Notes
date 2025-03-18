# ref

## DOM元素
1. 废弃
  ```
  1）第1步：<input ref="item" type="text" /> ref后面跟一个字符串
  2）第2步：this.refs.item.value  获取输入框中的数据
  ```
2. 方式二
  ```
  ref后面跟上一个回调函数，回调函数的参数就是当前的DOM元素
  <input ref={(input)=>{
      this.xxx = input; // 当前的DOM元素挂载到当前组件对象的xxx属性上面的
  }} type="text" />
  获取DOM元素：this.input.value
  ```
3. 方式三
  ```
  1）this.ref1 = React.createRef(); // ref1是一个私有属性
  2）<input ref={this.ref1} type="text" />
  3）this.ref1.current.value  获取DOM元素中的内容
  ```


## 带value
ref() 将传入参数的值包装为一个带 .value 属性的 ref 对象：

```js
import { ref } from 'vue'

const count = ref(0)

console.log(count) // { value: 0 }
console.log(count.value) // 0

count.value++
console.log(count.value) // 1
```


一个包含对象类型值的 ref 可以响应式地替换整个对象：
```js
const objectRef = ref({ count: 0 })

// 这是响应式的替换
objectRef.value = { count: 1 }
```

ref 被传递给函数或是从一般对象上被解构时，不会丢失响应性：
```js
const obj = {
  foo: ref(1),
  bar: ref(2)
}

// 该函数接收一个 ref
// 需要通过 .value 取值
// 但它会保持响应性
callSomeFunction(obj.foo)

// 仍然是响应式的
const { foo, bar } = obj
```

简言之，ref() 让我们能创造一种对任意值的 “引用”，并能够在不丢失响应性的前提下传递这些引用。这个功能很重要，因为它经常用于将逻辑提取到 组合函数 中。