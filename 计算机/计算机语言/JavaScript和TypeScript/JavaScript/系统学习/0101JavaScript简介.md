# 0101JavaScript简介
1. [什么是JavaScript](#什么是javascript)
2. [JavaScript能做什么](#javascript能做什么)
3. [JavaScript不能做什么](#javascript不能做什么)
4. [JavaScript的上层语言](#javascript的上层语言)


## 什么是JavaScript
1. 它是**脚本**语言。
   
   它的脚本以纯文本的形式提供和执行，它们不需要特殊的准备或编译即可运行。

2. JavaScript引擎
   - V8 —— Chrome、Opera和Edge
   - SpiderMonkey —— FireFox
   - 其他
     - Chaka —— IE
     - Nitro、SquirrelFish —— Safari

3. 应用最广泛的浏览器语言，与HTML/CSS完全集成，具有独特的地位。
  
## JavaScript能做什么
“安全的”编程语言，不提供内存和CPU底层访问。

能力取决于运行的环境。e.g. Node.js支持允许JavaScript读取/写入任意文件，执行网络请求等函数。

浏览器中的JavaScript：
- 网页操作
- 用户交互
- Web服务器相关的事情

e.g.
- 在网页中添加新的 HTML，修改网页已有内容和网页的样式。
- 响应用户的行为，响应鼠标的点击，指针的移动，按键的按动。
- 向远程服务器发送网络请求，下载和上传文件（所谓的 AJAX 和 COMET 技术）。
- 获取或设置 cookie，向访问者提出问题或发送消息。
- 记住客户端的数据（“本地存储”）

## JavaScript不能做什么
- 不能读，写，执行，赋值，执行硬盘上的文件。没有直接访问操作系统的功能。
- 不同标签页/窗口直接**通常**互不了解（同源策略）
- 轻松与当前页面所在服务器进行通信，但是从其他网站/域的服务器中接受数据的能力被削弱了。（如果在浏览器环境外，例如服务器上，使用JavaScript则不存在此类限制）（现代浏览器还允许安装可能会要求扩展权限的插件/扩展）

## JavaScript的上层语言
先转换为JavaScript
- CoffeeScript
- TypeScript
- Flow
- Dart
- Brython
- Kotlin