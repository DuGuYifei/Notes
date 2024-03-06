# configparser

## 1. 读取配置文件

```config.ini
[FREE_USER]
username = xxx
email = xxx
ip = xxxxx

[LIMIT]
translation = 3

[FILE]
home_path = xxxx
```

```python
import configparser

config = configparser.ConfigParser()
config.read('config.ini', encoding='utf-8')

file_home_path = config['FILE']['home_path']
```