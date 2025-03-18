# Hello world

## Script标签
`<script>`标签可以将JavaScript插入到HTML文档的任何位置

## 标记(markup)
老标记
- `<script language=…>`
- `<script type=…> `
  - 现在type被用于JavaScript模块
- 老注释(其实就是html注释)
  ```html
    <script type="text/javascript"><!--balabala--></script>
  ```

## 外部脚本
单独的文件 通过src的attribute添加到html中
```html
<script src="/path/to/script.js"></script>
```
可以是路径，也可以是URL链接
```html
<script src="https://cdnjs.cloudflare.com/ajax/libs/lodash.js/4.17.11/lodash.js"></script>
```

**多个脚本用多个标签**
```html
<script src="/js/script1.js"></script>
<script src="/js/script2.js"></script>
```

- 使用独立文件的好处\
    使用独立文件的好处是浏览器会下载它，然后将它保存到浏览器的 缓存 中。\
    之后，其他页面想要相同的脚本就会从缓存中获取，而不是下载它。所以文件实际上只会下载一次。\
    这可以节省流量，并使得页面（加载）更快。

- 如果设置了 src 特性，script 标签内容将会被忽略。


