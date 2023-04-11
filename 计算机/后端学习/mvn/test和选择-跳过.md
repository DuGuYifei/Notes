# test和选择-跳过

1. 选择
```bash
mvn test -Dmaven.main.skip=true -Dtest=com.example.app
```

2. 跳过
```bash
mvn test -Dtest=!com.example.service.TestService
mvn test -Dtest=!com.example.service.TestService#testMethod1
```

