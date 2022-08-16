# html

1. [html5标记](#html5标记)
2. [head](#head)
   1. [base](#base)
   2. [link](#link)
   3. [style](#style)
   4. [meta](#meta)
3. [div和span的区别](#div和span的区别)
4. [button和input type button区别](#button和input-type-button区别)
5. [img](#img)
   1. [title属性](#title属性)

## html5标记
<!DOCTYPE html>

## head
### base
`<base>` 标签描述了基本的链接地址/链接目标，该标签作为HTML文档中所有的链接标签的默认链接:

```html
<head>
<base href="http://www.runoob.com/images/" target="_blank">
</head>
```

### link
`<link>` 标签定义了文档与外部资源之间的关系。

`<link>` 标签通常用于链接到样式表:

```html
<head>
<link rel="stylesheet" type="text/css" href="mystyle.css">
</head>
```

### style
`<style>` 标签定义了HTML文档的样式文件引用地址.

在`<style>` 元素中你也可以直接添加样式来渲染 HTML 文档:

```html
<head>
<style type="text/css">
body {background-color:yellow}
p {color:blue}
</style>
</head>
```

### meta
HTML `<meta>` 元素
meta标签描述了一些基本的元数据。

`<meta>` 标签提供了元数据.元数据也不显示在页面上，但会被浏览器解析。

META 元素通常用于指定网页的描述，关键词，文件的最后修改时间，作者，和其他元数据。

元数据可以使用于浏览器（如何显示内容或重新加载页面），搜索引擎（关键词），或其他Web服务。

`<meta>` 一般放置于 `<head>` 区域

## div和span的区别
div和span的区别是：
* div标签是块级元素，每个div标签都会从新行开始显示，占据一行；div标签内可以添加其他的标签元素（行内元素、块级元素都行）。
* span标签是行内元素，会在一行显示；span标签内只能添加行内元素的标签或文本。

## button和input type button区别
[https://www.jianshu.com/p/14f18aad2d2f](https://www.jianshu.com/p/14f18aad2d2f)

* 差别1
button 默认和 type="submit" 一样，点击后会自动提交，但是最好还是写上type属性
button type="button", 按了什么都没有，要自己绑定click函数之类的

input type="button" 跟 button type="button" 差不多，都需要自定义

* 差别2
button 有 `<button>****</button>` 闭合标签
input 只有 `<input>` 但是可以属性 `value=`

## img
### title属性
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