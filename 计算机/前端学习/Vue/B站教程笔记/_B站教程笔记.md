# B站教程笔记

[Getting Title at 45:34](http://[视频地址]

[官方文档](https://cn.vuejs.org)

## Vue基础

### Vue简介
1. JS框架
2. 简化Dom操作
3. 响应式数据驱动
 
### 第一个Vue程序
1. 导入开发版本的Vue.js
2. 创建Vue实例对象，设置el属性和data属性
3. 使用简介的模板语法把数据渲染到页面上

### el挂载点
1. Vue实例的作用范围
   Vue会管理el选项命中的元素及其内部的后代元素
2. 是否可以使用其他选择器
   id，class，标签都可以，但建议ID选择器
3. 是否可以设置其他dom元素
   不能挂在<html>和<body>

### data 数据对象
Vue中的数据定义在data中

## 本地应用-介绍
Vue指令：
* v-text
* v-html
* v-on
* v-show
* v-if
* v-bind
* v-for
* v-model
  
### v-text指令
[v-text](../Vue知识积累/v-text.md)

### v-html
[v-html](../Vue知识积累/v-html.md)

### v-on
[v-on]

### 计数器

[计数器](vue学习用案例模板/计数器.html)
* 创建vue示例时：el（挂载点），data（数据），methods（方法）
* v-on指令的作用时绑定事件，简写为@
* 通过this关键字获取data中的数据
* v-text指令作用是设置文本值，作用等同于{{}}
* v-html指令作用时设置元素的innerHTML

### v-show
[v-show](../Vue知识积累/v-show.md)

### v-if
[v-if](../Vue知识积累/v-if.md)

### v-bind
[v-bind](../Vue知识积累/v-bind.md)

### 图片切换
[图片切换](vue学习用案例模板/图片切换.html)

* 列表数据使用数组保存
* v-bind指令可以设置元素属性，比如src
* v-show和v-if都可以切换元素的显示状态，频繁切换用v-show

### v-for
[v-for](../Vue知识积累/v-for.md)

### v-on 补充
[v-on](../Vue知识积累/v-on.md)

### v-model
[v-model](../Vue知识积累/v-model.md)

### 记事本
* 新增
  * 生成列表结构  （v-for数组）
  * 获取用户输入  （v-model）
  * 回车，新增数据（v-on，.enter 添加数据）
* 删除
  * v-on
  * splice 索引
* 痛剂
  * v-text
  * 基于数据的开发方式
* 清空
  * v-on
  * 基于数据的开发方式
* 隐藏
  * v-show/v-if
  * 数组非空

* v-for  列表结构可以通过v-for指令结合数据生成
* v-on   结合事件修饰符可以对事件进行限制，比如.enter
* v-on   在绑定事件时可以传递自定义参数
* v-model可以快速地设置和获取表单元素的值
* 基于数据的开发方式
  * 早期是基于dom，每次获得dom元素再进行开发
  * 现在要先想到数据再开发

## 网络应用
* axios
* axios + vue

### axios 网络请求库
* axios必须先导入才能使用：在线地址，联网使用
`<script src="https://unpkg.com/axios/dist/axios.min.js"></script>`

* get方法发送对应请求
  `axios.get(地址?key=value&key2=values).then(functioon(response){},function(err){})`
* post方法发送对应请求
  `axios.post(地址,{key:value,key2:value2}).then(function(response){},function(err){})

* then方法种的回调函数会在请求成功或失败时触发

* 通过回调函数的形参可以获取相应内容或错误信息

传送门：https://github.com/axios/axios

```html
<body>
    <input type="button" value="get请求" class="get">
    <input type="button" value="post请求" class="post">
    <!-- 官网提供的 axios 在线地址 -->
    <script src="https://unpkg.com/axios/dist/axios.min.js"></script>
    <script>
        /*
            接口1:随机笑话
            请求地址:https://autumnfish.cn/api/joke/list
            请求方法:get
            请求参数:num(笑话条数,数字)
            响应内容:随机笑话
        */
        document.querySelector(".get").onclick = function(){
            //axios.get("https://autumnfish.cn/api/joke/list?num=6")
            axios.get("https://autumnfish.cn/api/joke/list?num=3")
            //axios.get("https://autumnfish.cn/api/joke/list1234?num=3")
            .then(function(response){
                console.log(response);
            },function(err){
                console.log(err);
            })
        }

        /*
             接口2:用户注册
             请求地址:https://autumnfish.cn/api/user/reg
             请求方法:post
             请求参数:username(用户名,字符串)
             响应内容:注册成功或失败
         */
        document.querySelector(".post").onclick = function(){
            axios.post("https://autumnfish.cn/api/user/reg", 
            //axios.post("https://autumnfish.cn/api/user/reg123", 
            {username:"西兰花"})
            .then(function(response){
                console.log(response);
            },function(err){
                console.log(err);
            })
        }
    </script>
</body>
```

### axios+vue
[axios+vue](../Vue知识积累/axios+vue.md)


### 查天气
[查天气](vue学习用案例模板/查天气/查天气.html)

1. 回车查询
   1. 按下回车（v-on .enter）
   2. 查询数据（axios 接口 v-model）
   3. 渲染数据（v-for 数组 that)
   4. 重点
      1. 应用逻辑代码建议和页面分离，使用单独的js文件编写
      2. 服务器返回的数据比较复杂时，获取的时候就需要注意层级结构·
2. 点击查询
   1. 点击城市（v-on 自定义参数）
   2. 查询数据（this.方法())
   3. 渲染数据（this.方法())
   4. 重点
      1. 自定义参数可以让代码的复用性更高
      2. methods中定义的方法内部，可以通过this关键字点出其他的方法
   

### 音乐播放器
1. 歌曲搜索
   1. 按下回车（v-on .enter）
   2. 查询数据（axios 接口 v-model）
   3. 渲染数据（v-for 数组 that）
2. 歌曲播放
3. 歌曲封面
4. 歌曲评论
5. 播放动画
6. mv播放