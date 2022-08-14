---
title: Blog首页文章不要全展开问题
date: 2022-08-14 1:20:14
tags:
- Blog
categories:
- Blog 
description: 
---

# Blog首页文章不要全展开问题
将next主题的config里的`excerpt_description: true`设置为true

然后在开头添加description即可
```
title: ***
description: ***
```

也可以在文章中加入
```js
<!--more-->
```
将文章截断显示

