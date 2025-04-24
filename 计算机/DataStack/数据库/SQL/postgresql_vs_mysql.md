# postgresql

维度 | MySQL | PostgreSQL
---|---|---
🧱 数据库类型 | 传统关系型（略偏工程） | 高级关系型（偏学术、规范）
🧠 事务一致性 | 普通（默认 REPEATABLE READ） | 严格（默认 READ COMMITTED）
🧩 JSON支持 | 基本可用 | 强大（几乎像文档数据库）
🔍 全文搜索 | 有（但功能一般） | 内建 tsvector 非常强
🚦 外键/约束支持 | 有，但用得少 | 全支持，写得规范
🔧 可扩展性 | 稍弱（插件机制差） | 强（支持自定义类型/函数）
🚀 性能表现 | 读写高并发下稳定 | 写密集型、分析型更强
📚 社区/资料 | 极其丰富，教程多 | 稍少，但近年来迅速增长
❤️ 大厂使用 | Facebook, Twitter（早期）, Shopify | Instagram, Reddit, Discord, Timescale


用户画像 | 推荐数据库
---|---
刚上手 web 开发、部署在云上、熟悉 LAMP/LEMP | ✅ MySQL
需要复杂查询、GIS、全文搜索、或者 JSON 数据处理 | ✅ PostgreSQL
想要以后做分析、机器学习、时序数据库 | ✅ PostgreSQL
做 CRM、电商、博客、论坛 | ✅ MySQL
用 Python / Django / Rust / Elixir 开发 | ✅ PostgreSQL（生态更匹配）
用 PHP / Laravel / WordPress | ✅ MySQL（天然支持）