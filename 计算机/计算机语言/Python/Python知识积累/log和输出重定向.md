# log和输出重定向

## log
### logging

```python
import logging
from logging.handlers import TimedRotatingFileHandler
from qt_redirector import QTextEditHandler
import sys


logger = logging.getLogger()
logger.setLevel(logging.DEBUG)
formatter = logging.Formatter('%(asctime)s - %(levelname)s - %(message)s')


def add_file_handler():
    file_handler = TimedRotatingFileHandler("头条发布.log", when='midnight', backupCount=7, encoding='utf-8', interval=1)
    file_handler.setFormatter(formatter)
    file_handler.setLevel(logging.DEBUG)
    logger.addHandler(file_handler)


def add_console_handler():
    console_handler = logging.StreamHandler()
    console_handler.setFormatter(formatter)
    console_handler.setLevel(logging.DEBUG)
    logger.addHandler(console_handler)


def add_qt_handler(text_edit):
    log_handler = QTextEditHandler(text_edit)
    log_handler.setLevel(logging.INFO)
    logger.addHandler(log_handler)


def add_exception_hook():
    def handle_exception(exc_type, exc_value, traceback):
        logger.error("Uncaught exception", exc_info=(exc_type, exc_value, traceback))
    sys.excepthook = handle_exception
```

### 将错误堆栈用log输出

#### sys.excepthook

```python
import sys
import logging

# 配置日志
logging.basicConfig(level=logging.DEBUG, filename='app.log', filemode='w',
                    format='%(asctime)s - %(levelname)s - %(message)s')

def add_exception_hook():
    def handle_exception(exc_type, exc_value, traceback):
        logger.error("Uncaught exception", exc_info=(exc_type, exc_value, traceback))
    sys.excepthook = handle_exception
```


#### logger.exception()和logger.error()

`logger.error()`和`logger.exception()`都可以输出错误堆栈，但是`logger.exception()`会输出错误堆栈，而`logger.error()`只会输出错误信息。但是error可以通过参数`exc_info=True`来输出错误堆栈。

```python
import logging

# 配置日志系统
logging.basicConfig(level=logging.DEBUG, filename='app.log', filemode='w',
                    format='%(asctime)s - %(levelname)s - %(message)s')

logger = logging.getLogger()

try:
    # 产生一个异常
    1 / 0
except ZeroDivisionError:
    # 使用 logger.exception() 记录异常和堆栈信息
    logger.exception("An error occurred")
```

```python
try:
    1 / 0
except ZeroDivisionError:
    # 使用 logger.error() 并设置 exc_info=True 记录异常和堆栈信息
    logger.error("An error occurred", exc_info=True)
```


## 控制台输出重定向

### tkinter

```python
class ConsoleDirector:
    def __init__(self, text_widget):
        self.text_widget = text_widget
        self.text_widget.see(tk.END)

    def write(self, message):
        self.text_widget.insert(tk.END, message)
        self.text_widget.see(tk.END)

sys.stdout = ConsoleDirector(self.text_box)
sys.stderr = ConsoleDirector(self.text_box)
```

### QT

```python
from PySide6.QtWidgets import QTextEdit


class ConsoleDirector:
    def __init__(self, text_edit: QTextEdit):
        self.text_widget = text_edit
        self.text_widget.ensureCursorVisible()

    def write(self, message):
        self.text_widget.append(message)
        self.text_widget.ensureCursorVisible()

    def flush(self):
        # 由于 sys.stdout 是文件类对象，flush 是必须实现的方法
        pass

sys.stdout = ConsoleDirector(self.text_edit)
sys.stderr = ConsoleDirector(self.text_edit)
```


## log输出重定向

### QT

```python
import logging
from PySide6.QtWidgets import QTextEdit


class QTextEditHandler(logging.Handler):
    def __init__(self, text_edit: QTextEdit):
        super().__init__()
        self.text_edit = text_edit

    def emit(self, record):
        # 格式化日志记录
        msg = self.format(record)
        # 将日志消息插入到 QTextEdit 中
        self.text_edit.append(msg)
        # 确保光标可见
        self.text_edit.ensureCursorVisible()
```

```python
def log_redirect(self):
    log_handler = QTextEditHandler(self.window.ui.textEdit)
    log_handler.setLevel(logging.INFO)
    logger.addHandler(log_handler)
```