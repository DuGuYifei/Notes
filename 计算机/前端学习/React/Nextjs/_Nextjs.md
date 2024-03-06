# Nextjs

## Nextjs 介绍

Nextjs 是一个 React 框架，用于开发 SSR 应用。

## 模式

### app 模式

文件夹格式：
```
app
├── api
│   └── icon
│       └── route.js
├── page.js
├── pagename
│   └── [slug]
|       └── page.js
├── public
│   └── favicon.ico
```

public是用来存放静态资源的，比如图片、字体、favicon.ico等，也可以直接放html js 之类的东西。



### page 模式