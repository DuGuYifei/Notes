# alert、prompt和confirm

## alert

弹出**模态窗**。

## prompt

```javascript
result = prompt(title, [default]);
```

浏览器会显示一个带有文本消息的模态窗口，还有input框和确定/取消按钮。

`title`
显示给用户的文本

`defualt`
可选的第二个参数，指定input框的初始值

`[]`表示该参数是可选的

输入结果会放进result，如果按esc退出，则result为null

## confirm

```javascript
result = confirm(question);
```

confirm函数显示一个带有question以及确定和取消两个按钮的模态窗口。

点击确定返回`true`，点击取消返回`false`。

