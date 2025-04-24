# postgresql-docker快速部署

```yaml
version: '3.9'

services:
  postgres:
    container_name: quirkset-postgres
    image: postgres:16
    restart: always
    environment:
      POSTGRES_USER: quirkset
      POSTGRES_PASSWORD: quirkset
      POSTGRES_DB: quirkset
    ports:
      - "5432:5432"
    volumes:
      - ./pgdata:/var/lib/postgresql/data
      - ./init:/docker-entrypoint-initdb.d
    shm_size: 256mb
```

其中：
- `pgdata`：持久化数据
- `init`：初始化脚本，里面有一个`init.sql`文件
- `shm_size`：设置共享内存大小，避免`out of shared memory`错误
  