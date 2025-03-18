# stylesheet disabled

```css
QPushButton:disabled {
    background-color: #cccccc;  /* 灰色背景 */
    color: #666666;  /* 深灰色文字 */
}

QCheckBox::indicator:disabled {
    image: url(disabled.png);  /* 禁用状态的图片 */
    background-color: #cccccc;  /* 灰色背景，表示禁用 */
}

QTableWidget:disabled {
    background-color: #eeeeee;  /* 灰色背景 */
    color: gray;
}

QCheckBox::indicator:disabled {
    image: url(disabled.png);  /* 禁用状态的图片 */
    background-color: #cccccc;  /* 灰色背景，表示禁用 */
}
```