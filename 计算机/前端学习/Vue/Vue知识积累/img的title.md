# img的title
```html
    <div id="app">
        <img v-bind:src="imgSrc">
        <br>
        <img :src="imgSrc" alt="" :title="imgTitle+'!!!'">
    </div>

    <script>
        var app = new Vue({
            el:"#app",
            data:{
                imgSrc:"http://127.0.0.1:5500//计算机/前端学习/Vue/Vue知识积累/2022-08-12-17-42-50.png",
                imgTitle:"嘿嘿"
            }
        })
    </script>
```

鼠标悬浮到图片上会有提示字出现，是title的内容