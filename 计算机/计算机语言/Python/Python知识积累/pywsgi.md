# pywsgi

web server gateway interface

直接使用flask时候
```
WARNING: This is a development server. Do not use it in a production deployment. Use a production
```

使用wsgi
```
from app import app
from gevent import pywsgi


if __name__ == '__main__':
    server = pywsgi.WSGIServer(('127.0.0.1', 8000), app)
    server.serve_forever()
```