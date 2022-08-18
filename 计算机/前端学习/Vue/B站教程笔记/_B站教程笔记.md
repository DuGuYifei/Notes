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
* 在线地址，联网使用
`<script src="https://unpkg.com/axios/dist/axios.min.js"></script>`

* get方法
  `axios.get(地址?key=value&key2=values).then(functioon(response){},function(err){})`
* post方法
  `axios.post(地址,{key:value,key2:value2}).then(function(response){},function(err){})

