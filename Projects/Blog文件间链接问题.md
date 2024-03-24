---
title: Blog文件间链接问题
date: 2022-08-13 21:34:41
tags:
- Blog
categories:
- Blog
description: 解决了文件间链接的问题
---

# Blog文件间链接问题

## 方法一 我不喜欢
不能
`[](ABC.md)`
只能
`[](../ABC)`



## 方法二
修改`\node_modules\hexo-renderer-marked\lib\renderer.js`里`link`函数：
```js
  link(href, title, text) {
    const { external_link, sanitizeUrl } = this.options;
    const { url: urlCfg } = this.hexo.config;

    if (sanitizeUrl) {
      if (href.startsWith('javascript:') || href.startsWith('vbscript:') || href.startsWith('data:')) {
        href = '';
      }
    }

    let out = '<a href="';

    // 开始修改
    try {
      let temp = encodeURL(href);
      if(temp.endsWith(".md")){
        temp = "../" + temp.substr(0, temp.length - 3);
      }
      out += temp;
      //out += encodeURL(href);
    } catch (e) {
      let temp = href;
      if(temp.endsWith(".md")){
        temp = "../" + temp.substr(0, temp.length - 3);
      }
      out += temp;

      //out += href;
    }
    //停止修改
    
    out += '"';
    以下省略...
```