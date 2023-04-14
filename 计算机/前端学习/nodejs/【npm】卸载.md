# 【npm】卸载

## 卸载
```bash
npm uninstall xxxx
npm uninstall --save xxxx
```

如果你将安装的包作为 "devDependency"（也就是通过 --save-dev 参数保存的），那么 --save 无法将其从 package.json 文件中删除。所以必须通过 --save-dev 参数可以将其卸载。

即
```bash
npm install xxx --save
```