# 现代模式，"use strict"

让代码按“现代”方式进行

## 位置及注意点
放在开头
放在函数体的开头

注：
1. 只能放开头，不然不启用
2. 开始了就没有办法取消

## 浏览器控制台
默认并不开启，可以用`shift+enter`通过输入多行来开启
```Javascript
'use strict'; <Shift+Enter 换行>
//  ...你的代码
<按下 Enter 以运行>
```
旧的浏览器，可能只能放在容器里了
```JavaScript
(function() {
  'use strict';

  // ...你的代码...
})()
```

## 什么时候使用
因此，目前我们欢迎将 

"use strict"; 
'use strict';

写在脚本的顶部。

稍后，当你的代码全都写在了 class 和 module 中时，你则可以将 "use strict"; 这行代码省略掉。

**现代 JavaScript 支持 “classes” 和 “modules” —— 高级语言结构（本教程后续章节会讲到），它们会自动启用 use strict。因此，如果我们使用它们，则无需添加 "use strict" 指令。**