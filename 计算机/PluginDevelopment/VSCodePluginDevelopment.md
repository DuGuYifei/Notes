# vscode 插件开发
1. [教程](#教程)
2. [安装开发工具包](#安装开发工具包)
3. [创建项目](#创建项目)
4. [进入项目](#进入项目)
5. [.vscode/lanuch.json](#vscodelanuchjson)
6. [切换开发人员工具](#切换开发人员工具)
7. [API](#api)
   1. [editor](#editor)
      1. [selection](#selection)
   2. [window](#window)
8. [打包](#打包)
   1. [注意包否则可能命令找不到](#注意包否则可能命令找不到)
9. [发布](#发布)
10. [配置](#配置)
    1. [编辑器菜单栏图标](#编辑器菜单栏图标)
    2. [总案例](#总案例)

## 教程
[VS Code 开发不完全入门 - 掘金](https://juejin.cn/post/7169040468880130078)

## 安装开发工具包
`npm install -g yo generator-code`

## 创建项目
进入要进行开发的文件夹\
`E:`

开始新建项目\
`yo code`

进行一系列基础设置\
其中`New extension`有两种语言选择：
- [TypeScript](../计算机语言/JavaScript和TypeScript/TypeScript/TypeScript.md)
- [JavaScript](../计算机语言/JavaScript和TypeScript/JavaScript/JavaScript.md)

## 进入项目
```shell
cd 项目名
code .
```

## .vscode/lanuch.json
```json
args: ["--disable-extensions"]
```
可以帮助你打开一个没有任何扩展的工作区

## 切换开发人员工具
会有类似f12的工具，方便看


## API
### editor

#### selection
`editor.selection.`
* active - 选中的内容
* replace - 替换
* end - 选中内容结束位置

### window
* ``vscode.window.showErrorMessage(`出现了错误：${error.message}`);``
* `vscode.window.showInformationMessage();`
* `const outputChannel = vscode.window.createOutputChannel('My Extension');`
  * `outputChannel.appendLine('My Extension is activated.');`

## 打包
```
npm install -g @vscode/vsce
vsce publish
```

### 注意包否则可能命令找不到
package.json中如果你有类似fetch必须运行时候使用的包，要加入
```
  "dependencies":{
    "node-fetch": "^2.6.9"
  },
```

## 发布
[Publishing Extensions](https://code.visualstudio.com/api/working-with-extensions/publishing-extension)

## 配置

### 编辑器菜单栏图标
其实是command图标
```json
"commands": [
	{
		"command": "extension.demo.testMenuShow",
		"title": "这个菜单仅在JS文件中出现",
		"icon": {
			"light": "./images/tool-light.svg",
			"dark": "./images/tool-light.svg"
		}
	}
]
```

### 总案例
```json
{
    // 插件的名字，应全部小写，不能有空格
    "name": "ks-stark",
    // 插件的友好显示名称，用于显示在应用市场，支持中文
    "displayName": "ks-stark",
    // 描述
    "description": "埋点管理平台插件",
    // 关键字，用于应用市场搜索
    "keywords": ["vscode", "stark"],
    // 版本号
    "version": "1.0.0",
    // 发布者，如果要发布到应用市场的话，这个名字必须与发布者一致
    "publisher": "ks-stark",
    // 表示插件最低支持的vscode版本
    "engines": {
        "vscode": "^1.27.0"
    },
    // 插件应用市场分类，可选值： [Programming Languages, Snippets, Linters, Themes, Debuggers, Formatters, Keymaps, SCM Providers, Other, Extension Packs, Language Packs]
    "categories": ["Other"],
    // 插件图标，至少128x128像素
    "icon": "https://s2-10710.kwimgs.com/kos/nlav10710/ks-stack/images/icon.png",
    // 扩展的激活事件数组，可以被哪些事件激活扩展
    "activationEvents": ["onCommand:extension.sayHello"],
    // 插件的主入口
    "main": "./src/extension",
    // 贡献点，整个插件最重要最多的配置项
    "contributes": {
        // 插件配置项
        "configuration": {
            // 配置项标题，会显示在vscode的设置页
            "title": "ks-track",
            // 配置的选项
            "properties": {
                "ks-track.appName": {
                    "type": "string",
                    "default": "KUAISHOU",
                    "scope": "application",
                    "description": "埋点列表的产品英文名"
                },
                "ks-track.codePlatformList": {
                    "type": "string",
                    "default": "H5",
                    "scope": "application",
                    "description": "样例代码所使用的的平台",
                    "enum": ["PC_WEB", "ANDROID_PHONE", "IPHONE", "H5"] // 枚举
                },
                "ks-track.defaultListType": {
                    "type": "string",
                    "default": "group",
                    "scope": "application",
                    "description": "默认加载埋点方式(group,list)",
                    "enum": ["group", "list"]
                },
                "ks-track.completionKey": {
                    "type": "string",
                    "default": "log",
                    "scope": "application",
                    "description": "触发自动完成的关键词"
                }
            }
        },
        // 命令
        "commands": [
            {
                "command": "extension.sayHello",
                "title": "Hello World"
            }
        ],
        // 快捷键绑定
        "keybindings": [
            {
                "command": "extension.sayHello",
                "key": "ctrl+f10",
                "mac": "cmd+f10",
                "when": "editorTextFocus"
            }
        ],
        // 菜单
        "menus": {
            // 编辑器右键菜单
            "editor/context": [
                {
                    // 表示只有编辑器具有焦点时才会在菜单中出现
                    "when": "editorFocus",
                    "command": "extension.sayHello",
                    // navigation是一个永远置顶的分组，后面的@6是人工进行组内排序
                    "group": "navigation@6"
                },
                {
                    "when": "editorFocus",
                    "command": "extension.demo.getCurrentFilePath",
                    "group": "navigation@5"
                },
                {
                    // 只有编辑器具有焦点，并且打开的是JS文件才会出现
                    "when": "editorFocus && resourceLangId == javascript",
                    "command": "extension.demo.testMenuShow",
                    "group": "z_commands"
                },
                {
                    "command": "extension.demo.openWebview",
                    "group": "navigation"
                }
            ],
            // 编辑器右上角图标，不配置图片就显示文字
            "editor/title": [
                {
                    "when": "editorFocus && resourceLangId == javascript",
                    "command": "extension.demo.testMenuShow",
                    "group": "navigation"
                }
            ],
            // 编辑器标题右键菜单
            "editor/title/context": [
                {
                    "when": "resourceLangId == javascript",
                    "command": "extension.demo.testMenuShow",
                    "group": "navigation"
                }
            ],
            // 资源管理器右键菜单
            "explorer/context": [
                {
                    "command": "extension.demo.getCurrentFilePath",
                    "group": "navigation"
                },
                {
                    "command": "extension.demo.openWebview",
                    "group": "navigation"
                }
            ]
        },
        // 代码片段
        "snippets": [
            {
                "language": "javascript",
                "path": "./snippets/javascript.json"
            },
            {
                "language": "html",
                "path": "./snippets/html.json"
            }
        ],
        // 自定义新的activitybar图标，也就是左侧栏的入口图标
        "viewsContainers": {
            "activitybar": [
                {
                    "id": "ks-track",
                    "title": "埋点管理",
                    "icon": "https://s2-10710.kwimgs.com/kos/nlav10710/ks-stack/images/track-logo.png"
                }
            ]
        },
        // 自定义侧边栏内view的实现
        "views": {
            // 和 viewsContainers 的id对应
            "ks-track": [
                {
                    "id": "track.start",
                    "name": "已开发"
                },
                {
                    "id": "track.noStart",
                    "name": "未开发"
                }
            ]
        },
        // 定义对于view的欢迎页，view 与 views 中的id对应
        "viewsWelcome": [
            {
                "view": "track.start",
                "contents": "当前未登录或登录失败，请点击登录按钮登录。\n 点击[使用教程](https://component.corp.kuaishou.com/docs/weblogger/views/tools/vscode.html)了解更多信息\n[登录](command:track.cmd.login)",
                "when": "store-login-status == nologin"
            },
            {
                "view": "track.start",
                "contents": "数据正在加载中，请等待...",
                "when": "store-login-status == logining"
            }
        ],
        // 图标主题
        "iconThemes": [
            {
                "id": "testIconTheme",
                "label": "测试图标主题",
                "path": "./theme/icon-theme.json"
            }
        ]
    },
    // 同 npm scripts
    "scripts": {},
    // 开发依赖
    "devDependencies": {}
}

作者：aitexiaoy
链接：https://juejin.cn/post/7169040468880130078
来源：稀土掘金
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```