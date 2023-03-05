# os.OpenFile

```go
file, err := os.OpenFile("example.txt", os.O_CREATE|os.O_WRONLY, 0600)
if err != nil {
    log.Fatal(err)
}
defer file.Close()
```

* os.FileMode(0600)：只读写权限
* os.FileMode(0644)：所有用户都有读权限，文件所有者还有写权限
* os.FileMode(0755)：所有用户都有读、写和执行权限，文件所有者还有删除权限