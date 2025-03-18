# 构建工具功能：Vite-glob导入或者webpack-require.context

## webpack的 require.context()
require.context(directory,useSubdirectories,regExp)

1. directory:表示检索的目录
2. useSubdirectories：表示是否检索子文件夹
3. regExp:匹配文件的正则表达式,一般是文件名

例如 require.context("@/views/components",false,/.vue$/)

## vite的 import.meta.glob()
**动态导入**

## vite的 import.meta.globEager()
从功能上来看，它与glob()函数几乎完全一样。但是这中**导入是静态**的，它将在你调用该函数时直接引入所有的模块。