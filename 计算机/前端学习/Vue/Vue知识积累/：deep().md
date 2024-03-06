# ：deep()

处于 **scoped** 样式中的选择器如果想要做更“深度”的选择，也即：**影响到子组件**，可以使用 :deep() 这个伪类：

```css
<style scoped>
.a :deep(.b) {
  /* ... */
}
</style>
```

上面的代码会被编译成：
```css
.a[data-v-f3f3eg9] .b {
  /* ... */
}
```