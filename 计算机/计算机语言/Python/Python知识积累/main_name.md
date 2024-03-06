# main_name

```python
if __name__ == '__main__':
	app.run(host='localhost', port=8080, debug=True)
```

原理：

1. 当前文件作为主程序运行时，`__name__`的值为`__main__`，所以`if`条件成立，执行`app.run()`；
