# setup

setup() 钩子是在组件中使用 `组合式 API` 的入口，通常只在以下情况下使用：

1. 需要在非单文件组件中使用组合式 API 时。
2. 需要在基于选项式 API 的组件中集成基于组合式 API 的代码时。

其他情况下，都应优先使用 `<script setup>` 语法。

## 基本使用
我们可以使用响应式 API 来声明响应式的状态，**在 setup() 函数中返回的对象会暴露给模板和组件实例。其它的选项也可以通过组件实例来获取 setup() 暴露的属性**：
```js
<script>
import { ref } from 'vue'

export default {
  setup() {
    const count = ref(0)

    // 返回值会暴露给模板和其他的选项式 API 钩子
    return {
      count
    }
  },

  mounted() {
    console.log(this.count) // 0
  }
}
</script>

<template>
  <button @click="count++">{{ count }}</button>
</template>
```