# docsify

## 介绍

Docsify 是一个基于 JavaScript 的文档生成工具，可以将 Markdown 文件转换为一个漂亮的、可导航的文档网站。它不需要构建过程，直接在浏览器中运行，非常适合快速创建和维护文档。

## 运行

```sh
npx docsify serve ./docs
```
npx是npm 5.2.0引入的一个命令，可以直接运行在node_modules/.bin目录下的包，而不需要全局安装。

```sh
npm install -g docsify-cli
docsify init ./docs
docsify serve ./docs
# docsify serve ./docs --port 3000
```