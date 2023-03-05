# GOPATH和GOMODULE

当你开启 GoModules 模式时，你就无需将你的 go 项目放到 $GOPATH/src 目录下了，其实在新版 Go 的默认情况下，你就可以把项目随意放置了。接下来就看下怎么用 mod。

```bash
go env -w GO111MODULE=on
```
* auto： 自动模式，当项目下存在 go.mod 文件时，就启用 GoModules 模式；
* on： 开启模块支持，编译时会忽略 GOPATH 和 vendor 文件夹，只根据 go.mod下载依赖；
* off： 关闭模块支持，使用 GOPATH 模式。

```bash
go mod download    # 下载依赖的module到本地cache（默认为$GOPATH/pkg/mod目录）
go mod edit        # 编辑go.mod文件
go mod graph       # 打印模块依赖图
go mod init        # 初始化当前文件夹, 创建go.mod文件
go mod tidy        # 增加缺少的module，删除无用的module
go mod vendor      # 将依赖复制到vendor下
go mod verify      # 校验依赖
go mod why         # 解释为什么需要依赖
```

