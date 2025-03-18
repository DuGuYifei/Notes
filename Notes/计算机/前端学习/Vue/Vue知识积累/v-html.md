# v-html

* v-html指令的作用时：设置元素的 innerHTML
* 内容中有html结构会被解析为标签
* v-text指令无论内容是什么，只会解析为文本
* 解析文本使用v-text，需要解析html结构使用v-html


**当我们想要被渲染的东西以html的形式展示时**，就用到了这个指令
```javascript
<div id="app">
  <h1 v-html="url"></h1>
</div>
<script src="../js/vue.js"></script>
<script>
  const app = new Vue({
    el: '#app',
    data: {
      message: 'hello',
      url:'<a href="https://www.baidu.com">百度一下</a>'
    }
  })
</script>
```

![](2022-08-12-17-44-22.png)