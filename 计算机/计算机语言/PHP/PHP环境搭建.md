# PHP环境搭建

## windows
1. 下载php
2. 解压目录
3. 配置环境变量
4. 复制一份`php.ini-development` or `php.ini-production`并重命名为`php.ini`
5. 对于需要添加的ext，就将php.ini的`;extern=ext`前面的分号去掉
6. 下载vscode的扩展[php(https://marketplace.visualstudio.com/items?itemName=DEVSENSE.phptools-vscode)](https://marketplace.visualstudio.com/items?itemName=DEVSENSE.phptools-vscode)
7. 直接在vscode中运行php文件即可，debug选择built-in web server
8. 可以配置自己想要的端口，并且这个server可以把同目录的`html`和`js`也自动放到该端口。