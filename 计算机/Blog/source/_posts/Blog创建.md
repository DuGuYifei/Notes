---
title: 用Hexo和Github制作Blog
date: 2022-08-13 19:06:37
categories:
- Blog
tags: 
- Blog
- Hexo
- Github
description: 如何使用hexo创建blog，并连接上github，以及一些简单的设置：搜索功能，链接样式，新主题，增加tags和categories
---

1. [参考文献](#参考文献)
2. [创建并第一次运行](#创建并第一次运行)
3. [创建新blog](#创建新blog)
4. [github.io](#githubio)
   1. [不一定是github.io仓库](#不一定是githubio仓库)
5. [主题修改](#主题修改)
   1. [添加搜索功能](#添加搜索功能)
6. [修改文章内链接文本样式](#修改文章内链接文本样式)
7. [添加tags和categories](#添加tags和categories)

# Blog创建

## 参考文献
[CSDN博客_github hexo](https://blog.csdn.net/sywdebug/article/details/113942047?fbclid=IwAR3CZC9vs8qEObbcHqdRKS4vsWZvNt39yiAOetyvj8hdPv3aKkRKcNFsqRg)


## 创建并第一次运行
```bash
# npm install hexo-cli -g
hexo init blog
cd blog
hexo server   # hexo s
```

## 创建新blog
```bash
hexo new "My New Post"
```

# Github
## github.io
下载插件到根目录
```bash
npm install hexo-deployer-git --save
```

用编辑器打开目录中的 _config.yml 文件
先上面的 url 和 root 补充完整，不然会没有 css 样式和 js 脚本
![](Blog创建/2022-08-13-16-18-27.png)

**关于root的深入理解 以及 解决自定义url后出现的无法加载资源问题**
如果是靠 liuyifei.tech/blog 连接就不会出问题，如果单独设置了一个CNAME连接比如'blog.liuyifei.tech'，并将root设置为 `/blog` 那么发送请求就变成了 blog.liuyifei.tech/blog/ 就不对了，
我们需要**blog.liuyifei.tech**，所以这时候只需要将root设置为`../`即可。
暂时放弃子域名链接，由于hexo的结构经过长时间维护已经很混乱，对于不同的url解读代码太过分散，修改太浪费精力了，以后有时间自己写。


也可以加上 branch:[自定义分支名称] 和 massage:[自定义提交消息]  
![](Blog创建/2022-08-13-16-18-35.png)

保存后执行 hexo generate 更新本地代码或执行hexo clean删除本地代码
执行 hexo deploy 生成本地代码并推送到 github 库

```bash
hexo clean # 清除已生成文件及缓存
hexo generate # 生成静态页面，简写做hexo g
hexo deploy #推送到github库，简写做hexo d
hexo server # 启动本地WEB服务器，简写做hexo s
```

### 不一定是github.io仓库
github只要是`gh-pages`的branch都可以同过`github.io/project`来访问，所以可以看上图中的deploy的url并不是io仓库

# Blog定制
## 主题修改

git clone 主题到themes下即可

比如`next`主题
```
git clone https://github.com/next-theme/hexo-theme-next.git themes/next
```

下载后config里的参数可以参考最上面的链接，但其实config里都有详细注释

### 添加搜索功能

下载：`npm install hexo-generator-searchdb --save`

修改主题config
```
local_search:
  enable: true
  trigger: auto
  top_n_per_article: 1
  unescape: false
  preload: false
```

写进根目录config
```
# Search
search:
  path: search.xml
  field: post
  format: html
  limit: 10000
```


## 修改文章内链接文本样式
在 /themes/next/source/css/_common/components/post/index.styl 内添加以下代码即可

```css
// 文章内链接文本样式
.post-body p a{
  color: #0593d3;
  border-bottom: none;
  border-bottom: 1px solid #0593d3;
  &:hover {
    color: #fc6423;
    border-bottom: none;
    border-bottom: 1px solid #fc6423;
  }
}
```

## 添加tags和categories
```bash
hexo new page categories
hexo new page tags
```

在生成的两个新文件夹source/tags和source/categories下，将自动生成地index.md的开头修改为
```md
---
title: categories
date: 2022-08-13 19:49:11
type: "categories"
---

和

---
title: tags
date: 2022-08-13 19:44:52
type: "tags"
---

```

然后在写博客时添加
```md
---
title: Hello World
categories:
- Blog
tags:
- Blog
---
```
即可

另外，需要在next的config文件里将tags和categories取消注释
```md
menu:
  home: / || fa fa-home
  #about: /about/ || fa fa-user
  tags: /tags/ || fa fa-tags
  categories: /categories/ || fa fa-th
  archives: /archives/ || fa fa-archive
  #schedule: /schedule/ || fa fa-calendar
  #sitemap: /sitemap.xml || fa fa-sitemap
  #commonweal: /404/ || fa fa-heartbeat
```
