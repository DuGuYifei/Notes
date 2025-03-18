# ab

## 参数
1. -n选项用于指定总共要执行的请求数量
2. -c选项用于指定并发请求数量。

## header
```bash
ab -n 100 -c 10 -H "Authorization: Bearer YOUR_TOKEN" http://example.com/
```

## cookie
```bash
ab -n 100 -c 10 -C "token=YOUR_TOKEN" http://example.com/
```

## post/put
```bash
ab -n 100 -c 10 -p data.txt -T "application/json" http://example.com/post-endpoint
# 使用post模拟put，不自带put
ab -n <请求数量> -c <并发数> -T <Content-Type> -p <数据文件> -m <HTTP 方法> <URL> 
```