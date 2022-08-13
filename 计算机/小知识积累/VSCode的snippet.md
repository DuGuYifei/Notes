# VSCode的snippet

## file->preference->UserSnippets
```JSON
{
	// Place your snippets for html here. Each snippet is defined under a snippet name and has a prefix, body and 
	// description. The prefix is what is used to trigger the snippet and the body will be expanded and inserted. Possible variables are:
	// $1, $2 for tab stops, $0 for the final cursor position, and ${1:label}, ${2:another} for placeholders. Placeholders with the 
	// same ids are connected.
	// Example:
	// "Print to console": {
	// 	"prefix": "log",
	// 	"body": [
	// 		"console.log('$1');",
	// 		"$2"
	// 	],
	// 	"description": "Log output to console"
  // }
  
  /* ------------上面内容都是VSCode默认内容可以删除----------- */
  /* ------------下面是我们定义的html模板内容----------- */
  "html template": {
    "prefix": "h", // 使用模板的快捷键
    "body": [  //模板的内容都定义在body中
      "<!DOCTYPE html>",
      "<html lang=\"en\">",
      "<head>",
        "\t<meta charset=\"UTF-8\">",
        "\t<title>Title</title>",
      "</head>",
      "<body>",
      "\t $0",  //$0 鼠标停留的位置
      "</body>",
      "</html>"
    ],
    "description": "html 简单模板"  //模板的描述
  }
}
```


## 设置settings.json
对于markdown:
```json
    "[markdown]": {
        "editor.quickSuggestions": {
            "other": true,
            "comments": true,
            "strings": true
        },
        "editor.acceptSuggestionOnEnter": "on"
    }   
```