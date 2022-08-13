---
title: Blog图片显示问题
date: 2022-08-13 23:37:00
tags:
- Blog
categories:
- Blog
description: 图片的markdown链接会使图片无效的修复方法
---

## markdown语法用于hexo

1. 将config里：`post_asset_folder: true` 设置位`true`

2. 再次`hexo new "ABC"` 时会自动创建ABC同名文件夹，将图片放入其中

3. 使用语法`![](ABC/xxx.png)`即可
