# test和选择-跳过

1. 选择
```bash
mvn test -Dmaven.main.skip=true -Dtest=com.example.app.*
```

2. 跳过
```bash
mvn test -Dtest=!com.example.service.TestService.*
mvn test -Dtest=!com.example.service.TestService#testMethod1
```

遇到问题可能的解决办法：
1. 在`*`前面加上转移符号变为`\*`，`!`不用
2. 用引号将`=`后的内容包裹
3. linux用`/`代替`.`在路径上

