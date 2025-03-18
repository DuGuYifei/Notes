# v-bind


* 设置元素的属性(e.g.:src,title,class)
* `v-bind:属性名=表达式`
* 简写省略v-bind，只保留`:属性名`
* 需要动态的增删class建议使用对象的方式，如案例中那样，用对象的方式来决定class是否存在。**案例中active是style的名字，即`.active`**


```html
    <div id="app">
        <img v-bind:src="imgSrc">
        <br>
        <img :src="imgSrc" alt="" :title="imgTitle+'!!!'" :class="isActive?'active':''" @click="toggleActive">
        <br>
        <img :src="imgSrc" alt="" :title="imgTitle+'!!!'" :class="{active:isActive}" @click="toggleActive">
    </div>
```

```html
    <script src="https://cdn.jsdelivr.net/npm/vue/dist/vue.js"></script>
    <script>
        var app = new Vue({
            el:"#app",
            data:{
                imgSrc:"http://127.0.0.1:5500//计算机/前端学习/Vue/Vue知识积累/2022-08-12-17-42-50.png",
                imgTitle:"嘿嘿",
                isActive:false
            },
            methods:{
                toggleActive(){
                    this.isActive = !this.isActive;
                }
            }
        })
    </script>
```
