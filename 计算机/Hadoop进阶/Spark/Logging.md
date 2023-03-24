# Logging

## 例子

```python
import logging
logging.basicConfig(stream=sts.stdout, level=logging.INFO,
					format='%(asctime)s - %(levelname)s - %(message)s')
logging.info("Hello %s", "world")
logging.debug("Hello, take %d", 2)

# 2020-05-20 15:59:00,000 - INFO - Hello world
```
第二个不输出是因为第二个在Debug level，需要`level=logging.DEBUG`才能输出。

## Debugging lazy evaluation

* lazy evaluation
* distributed execution

```python	
import logging
logging.basicConfig(stream=sts.stdout, level=logging.INFO,
					format='%(asctime)s - %(levelname)s - %(message)s')

logging.info("No action here")
logging.debug("df has %d rows", df.count())
```
df.count()还是会执行

## 各种输出
debug,info,warn,error,critical

## basiConfig
1. stream参数用于指定日志输出流的目的地。默认情况下，输出流是sys.stderr，即输出到控制台上。当指定了stream参数时，日志信息就会输出到该参数所指定的流中。在你的例子中，stream=sts.stdout，这意味着日志信息将输出到sts模块中的stdout流中。
2. level参数用于指定日志记录的等级。logging模块支持的日志等级有以下几个（按从高到低的顺序）：
* CRITICAL: 严重错误
* ERROR: 一般错误
* WARNING: 警告信息
* INFO: 一般信息
* DEBUG: 调试信息
* NOTSET: 没有设置任何等级，即所有日志信息都记录下来
3. format参数用于指定日志记录的输出格式。format参数的格式是一个字符串，其中可以包含各种格式化标记，用于表示日志信息中的不同部分。常用的格式标记包括：
* %(asctime)s: 输出日志时间，格式为YYYY-MM-DD HH:MM:SS
* %(levelname)s: 输出日志等级，如INFO、WARNING、ERROR等
* %(message)s: 输出日志信息