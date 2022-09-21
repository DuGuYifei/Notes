# sass
1. [什么是sass](#什么是sass)
2. [安装](#安装)
3. [使用](#使用)
4. [@include和@mixin](#include和mixin)

## 什么是sass
sass是css的扩展语言。用来写css的。

解决css缺点：
- 选择器很长
- 有可能漏掉 - 选择不准确
- 有可能将顺序弄混 - 选择不到
- 权重不好区分

[https://www.runoob.com/sass/sass-install.html](https://www.runoob.com/sass/sass-install.html)

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