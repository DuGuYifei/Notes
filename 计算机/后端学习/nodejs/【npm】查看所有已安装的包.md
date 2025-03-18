# 【npm】查看所有已安装的包

全局和项目查看
```bash
npm ls -g
npm ls
```

加上层级控制显示深度
```bash
npm ls -g --depth 0
```

如果只想显示生产环境依赖的包
如果只想显示开发环境依赖的包
```bash
npm ls --depth 0 --prod
npm ls --depth 0 --dev
```

