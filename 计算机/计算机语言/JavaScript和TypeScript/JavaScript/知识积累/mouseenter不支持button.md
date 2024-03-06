# mouseenter不支持button

```html
    <h2 @monseenter="changeFood">{{food}}</h2>
    <input type="button" value="鼠标进入" v-on:monseenter="doIt">
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

button进入是没有反应的

h2进入就有反应