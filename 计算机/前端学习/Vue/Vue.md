# Vue

## 选项式和组合式
组合式便于维护，适合大项目，但学习成本高。（所以我选组合式）

## 笔记目录
[B站教程笔记](B站教程笔记/_B站教程笔记.md)
[Vue 知识积累](Vue知识积累/_KnowledgeAccumulation_Vue.md)

## 环境安装
[HBuilder中vue使用ajax和axios](https://www.icode9.com/content-4-1259006.html)

### 运行依赖和开发依赖
如果你的项目是发布到npm的一个包，
那么这个包的package.json中的dependencies中的依赖是会被下载下来到这个包的node_modules文件夹中的（如果你的项目本身没有这个依赖），而devDependencies不会。

举个例子：
我发布了一个组件A，它有dependencies：lodash和devDependencies：moment。
那么，如果你的项目npm install 了组件A。
除非你的项目也依赖了lodash并且版本一致，那么项目的node_modules/A下会有一个node_modules，里面会有lodash。
而 moment，则无论如何也不会出现在你的项目中。

至于一般的项目，不管你是安装在dev还是dependencies中，安装的时候都会安装，打包的时候都会被打进去的，区分依赖只是为了让项目看起来更加清晰。

## 运行
[Vue3.2后台管理系统](https://www.bilibili.com/video/BV1pq4y1c7oy?p=4&spm_id_from=pageDriver&vd_source=6beebf17d5aa6fb3d9fb4b629d0b319a)
前6个视频讲解了如何配置环境
### local 和 network
local:本机
network:局域网

### npm run serve 不起作用
将package.json中script改为：
```json
  "scripts": {
    "dev": "vite",
    "build": "vite build",
    "serve": "vite serve"
  }
```
如果需要Network，就把dev改为 `vite --host`，并在vite.config.js中添加
```js
server:{
    host: '0.0.0.0',
}
```