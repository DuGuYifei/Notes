# @Size

限制长度
```Java
    @Column(length = 512)
    @Size(min = 3, max = 512)
    private String data;
```

