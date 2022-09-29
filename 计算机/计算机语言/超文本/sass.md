# sass
1. [什么是sass](#什么是sass)
2. [sass 和 scss](#sass-和-scss)
3. [安装](#安装)
4. [使用](#使用)
5. [@include和@mixin](#include和mixin)
6. [&](#)

## 什么是sass
sass是css的扩展语言。用来写css的。

解决css缺点：
- 选择器很长
- 有可能漏掉 - 选择不准确
- 有可能将顺序弄混 - 选择不到
- 权重不好区分

[https://www.runoob.com/sass/sass-install.html](https://www.runoob.com/sass/sass-install.html)

## sass 和 scss
sass和scss的区别

Sass 和 SCSS 其实是同一种东西，我们平时都称之为 Sass，两者之间不同之处有以下两点：

* 文件扩展名不同，Sass 是以“.sass”后缀为扩展名，而 SCSS 是以“.scss”后缀为扩展名

* 语法书写方式不同，Sass 是以严格的缩进式语法规则来书写，不带大括号({})和分号(;)，而 SCSS 的语法书写和我们的 CSS 语法书写方式非常类似。

## 安装
`npm install -g sass`

## 使用
npm 安装的 sass，安装完成后可以查看版本：
```bash
sass --version 
#1.22.12 compiled with dart2js 2.5.0 
```

1. 接下来我们创建一个 runoob-test.scss 文件，内容为：
```sass
/* 定义变量与值 */
$bgcolor: lightblue;
$textcolor: darkblue;
$fontsize: 18px;

/* 使用变量 */
body {
  background-color: $bgcolor;
  color: $textcolor;
  font-size: $fontsize;
}
```

2. **然后在命令行输入下面命令，即将 .scss 文件转化的 css 代码：**
```bash
sass runoob-test.scss 

#输出
@charset "UTF-8";
/* 定义变量与值 */
/* 使用变量 */
body {
  background-color: lightblue;
  color: darkblue;
  font-size: 18px;
}
```

3. **我们可以在后面再跟一个 .css 文件名，将代码保存到文件中：**
```bash
sass runoob-test.scss runoob-test.css
```

4. 这是会在当前目录下生成 runoob-test.css 文件，代码如下：
```css
@charset "UTF-8";
/* 定义变量与值 */
/* 使用变量 */
body {
  background-color: lightblue;
  color: darkblue;
  font-size: 18px;
}

/*# sourceMappingURL=runoob-test.css.map */
```

## @include和@mixin

mixin 创建模板，include使用

```css
.wrapper {
    display: flex;
    width: 100%;
    @include display(flex);
    @include flex-direction(column);
    @include align-items(center);
    @include justify-content(center);
    @include transition(all 2s linear);
}
```
案例：
[切角边框](css知识积累/切角边框和背景.md)

## &
这是sass的语法，代表上一级选择器
```scss
ul{

    margin-bottom: 20px;

    & >li {

        margin-bottom: 0;

    }

  }
```
解释成CSS代码如下
```css
ul{margin-bottom: 20px;}

ul > li {margin-bottom: 0;}
```