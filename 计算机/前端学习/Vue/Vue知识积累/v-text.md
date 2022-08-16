# v-test

* 设置标签的文本值（textcontent）

* 默认写法会替换全部内容，使用**插值表达式{{}}**可以替换指定内容

* 内部支持写表达式

```html
    <div id="app">
        <h2 v-text="message+'!'">深圳</h2>
        <h2 v-text="info+'!'">深圳</h2>
        <h2>{{ message +'!'}}深圳</h2>
    </div>
```

```html
    <script src="https://cdn.jsdelivr.net/npm/vue/dist/vue.js"></script>
    <script>
        var app = new Vue({
            el:"#app",
            data:{
                message:"黑马程序员!!!",
                info:"前端与移动教研部"
            }
        })
    </script>
```

注意“深圳”并没有显示，被**替换**了