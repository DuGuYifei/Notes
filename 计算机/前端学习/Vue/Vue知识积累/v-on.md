# v-on

* 为元素绑定事件
* 时间名不需要写on
* 指令可以简写为@
* 绑定的方法定义在methods属性中
* 方法内部通过this关键字可以访问定义在data中的数据

```html
    <div id="app">
        <input type="button" value="v-on指令" v-on:click="doIt">
        <input type="button" value="v-on简写" @click="doIt">
        <input type="button" value="双击事件" v-on:dblclick="doIt">
        <input type="button" value="双击简写" @dblclick="doIt">
        <h2 @click="changeFood">{{food}}</h2>
        <h2 @monseenter="changeFood">{{food}}</h2>
        <!--<input type="button" value="鼠标进入" v-on:monseenter="doIt">-->
    </div>
```

```html
    <script>
        var app = new Vue({
            el:"#app",
            data:{
                food:"西兰花炒蛋"
            },
            methods: {
                doIt:function(){
                    alert("做IT");
               },
               changeFood:function(){
                    //console.log(this.food);
                    this.food += "好好吃";
               }
            },
        })
    </script>
```

