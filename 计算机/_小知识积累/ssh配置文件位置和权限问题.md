# ssh配置文件位置和权限问题

## 位置问题

可以通过在`.ssh`文件夹下创建`config`文件来配置ssh的配置文件位置，并用include来放进其他位置的config，如下：

```shell
Include ~/.ssh/config.d/*
```

## 权限问题

因为windows里的文件权限不允许有authticated users，所以要把权限改为只有自己，如下：


1. 文件右键属性，安全，最下方的高级
2. 禁止继承
3. 添加一个用户->选择主体->名字就写自己电脑用户名，比如`yifei`会自动生产`电脑名\yifei`，然后确定