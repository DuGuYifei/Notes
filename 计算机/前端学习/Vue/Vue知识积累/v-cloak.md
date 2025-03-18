# v-cloak


**当网络较慢，网页还在加载 Vue.js ，而导致 Vue 来不及渲染，这时页面就会显示出 Vue 源代码。我们可以使用 v-cloak 指令来解决这一问题。**

```javascript
<style>
  [v-cloak]{
    display: none;
  }
</style>
<div id="app" v-cloak>{{message}}</div>
<script src="../js/vue.js"></script>
<script>
  /*延迟1s*/
  setTimeout(function (){
    const app = new Vue({
      el: '#app',
      data: {
        message: 'hello'
      }
    })
  },1000)
</script>
```