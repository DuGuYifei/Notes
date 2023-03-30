# oh-my-posh

## WSL

```bash
eval "$(oh-my-posh init bash --config ~/.poshthemes/wopian.omp.json)"

echo 'eval "$(oh-my-posh init bash --config ~/.poshthemes/M365Princess.omp.json)"' >> ~/.bashrc
```

注意wsl要有自己的git命令，不能用git.exe代替，否则会感知不到git仓库

## PowerShell

```powershell
notepad $PROFILE
```

## CLINK
https://blog.csdn.net/qq_21689457/article/details/129345662

```lua
load(io.popen('oh-my-posh init cmd --config C:\\Users\\NUT\\AppData\\Local\\Programs\\oh-my-posh\\themes\\robbyrussell.omp.json'):read("*a"))()
```

### autorun

```cmd
clink autorun install oh-my-posh.lua
```

autorun install 注册表
autorun set 当前有效

### 以下抛弃：

不是安装的版本，而是下载的版本时，没有cmd自启动，可以手动添加：

https://blog.csdn.net/weixin_33913377/article/details/86186020

跟随cmd自动启动clink
clink的安装程序带有“Autorun when cmd.exe starts"选项，但如果你不想使用安装程序，又想要在启动cmd时自动启动clink，可以按如下办法:

1. 打开注册表编辑器，找到（或者新建）HKEY_CURRENT_USER\Software\Microsoft\Command Processor
2. 在该键下新建一个字符串项，名为AutoRun
3. 将AutoRun的值设置为一个bat文件的路径，比如d:\cmdstart.cmd
4. 编辑d:\cmdstart.cmd，里面写一句 d:\tools\clink /inject （当然你也可以再添加其他命令

## Vscode
terminal会不显示一些东西，所以字体推荐：'MesloLGS Nerd Font Mono'