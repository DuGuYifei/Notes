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


## v-on补充
* 传递自定义参数
  * 事件绑定的方法携程函数调用的形式，可以传入自定义参数
  * 定义方法是需要定义形参来接收传入的实参
* 事件修饰符
  * 事件的后面跟上`.`修饰符可以对事件进行限制
  * .enter可以限制触发的案件为回车
  * 事件修饰符有多种 https://v2.cn.vuejs.org/v2/api/#v-on

```html
    <div id="app">
        <input type="button" value="点击" @click="doI(666,'abc')">
        <input type="text" @keyup.enter="doI(1,2)">
    </div>
    <!-- 开发环境版本，包含了有帮助的命令行警告 -->
    <script src="https://cdn.jsdelivr.net/npm/vue/dist/vue.js"></script>
    <script>
        var app = new Vue({
            el:"#app",
            methods:{
                doI(p1,p2){
                    alert(p1 + p2);
                }
            }
        })
    </script>
```
