# RingBuffer Disruptor 无锁队列

## 📌 Ring Buffer（环形缓冲区）

- 本质：固定大小的循环数组，头尾相接。
- 优点：
  - 高缓存命中率，避免内存频繁分配。
  - 适合单/多生产者、单/多消费者场景。
- 缺点：
  - 空间固定，超出需覆盖或丢弃。
  - 多线程访问需要同步策略（可用 CAS 实现无锁）。
- 应用场景：
  - 音视频流缓存
  - 网络收发缓冲
  - 多线程数据传递
- 指针设计：
  - write_index / read_index，通常通过模运算 `(index % size)` 实现循环。

## 📌 Disruptor（高性能并发框架）

- 来源：LMAX 开源，替代传统阻塞队列（BlockingQueue）。
- 内部结构：核心是 RingBuffer + Sequence 控制 + 无锁设计。
- 特点：
  - 单生产者/多消费者 或者 多生产者/多消费者。
  - 支持消费者拓扑结构（广播、依赖、流水线）。
  - 通过缓存行填充避免伪共享。
  - 极低延迟，高吞吐量。
- 使用方式：
  - 自定义 Event 对象（可复用）
  - 实现 EventHandler （**消费者（EventHandler）**注册在 Disruptor 上，Disruptor 内部调度这些消费者读取 RingBuffer 中的消息（通过 Sequence 控制谁读到哪个位置））。
  - 调用 publishEvent 发送数据（**生产者**调用 ringBuffer.publishEvent(...) 往 RingBuffer 写消息）
- 注意：
  - 需要预分配数据结构（池化）
  - 对 GC 敏感（JVM）

## 📌 无锁队列（Lock-Free Queue）

- 本质：基于 CAS 原子操作替代传统互斥锁实现线程安全。
- 常用算法：
  - Michael-Scott 队列（MSQueue） - 链表结构
  - RingBuffer-based Queue - 数组结构 + CAS
- 优点：
  - 高并发下性能优于加锁队列
  - 减少线程上下文切换
- 缺点：
  - 实现复杂（需要处理 ABA 问题、内存屏障等）
  - 不适合所有场景（如低并发、结构变动频繁）
- 应用场景：
  - 游戏引擎模块通信
  - 任务队列 / 消息队列
  - 网络线程与逻辑线程解耦

## 📌 技术关键词汇总（关键词索引）

- CAS（Compare And Swap）
- 内存屏障 / 内存可见性（Memory Barrier / Visibility）
- 伪共享（False Sharing）
- Producer / Consumer 模型
- Sequence 序号控制（Disruptor）
- 阻塞 vs 非阻塞（Blocking vs Non-Blocking）
- 单生产者/多消费者（SP/MC）
- 缓存行填充（Cache Line Padding）
- GC 压力（特别在 JVM 中）
- ABA 问题（Lock-Free 编程陷阱）

## 📌 实战建议

- 高频数据传输 & 实时性要求高 → RingBuffer / Disruptor
- 并发量大、逻辑复杂 → 无锁队列（链表结构）
- 稳定吞吐优先、线程模型清晰 → Disruptor
- 数据不大但消息量巨大 → RingBuffer（可复用对象）

## Disruptor vs 无锁队列（Lock-Free Queue）对比表格

| 对比点                       | **Disruptor**                                      | **无锁队列（Lock-Free Queue）**                        |
|------------------------------|----------------------------------------------------|--------------------------------------------------------|
| 顺序保证                     | ✅ 强顺序（Sequence 控制）                         | ❌ 无顺序或弱顺序（看实现）                            |
| 多消费者拓扑支持             | ✅ 支持广播、依赖链、流水线                        | ❌ 不支持拓扑，仅支持独立消费                         |
| 适用场景                     | 高频事件流、帧同步、模块依赖关系                  | 简单生产者-消费者、并发任务队列                       |
| 内存结构                     | 固定大小数组（RingBuffer）                        | 链表或动态数组                                         |
| 对象管理                     | 预分配对象（复用，低GC）                          | 每次 new（高GC，除非手动对象池）                      |
| GC 压力                     | 极低                                               | 中到高（依实现）                                       |
| 编程复杂度                   | 中等：需理解 Sequence、生命周期管理              | 中等：需理解 CAS、ABA 问题                             |
| 消息延迟                     | 纳秒级（极致性能）                                | 微秒级（具体看实现）                                   |
| 多生产者支持                 | ✅ 支持，使用 CAS 实现                            | ✅ 支持，MSQueue 等天然支持                            |
| 多消费者支持                 | ✅ 支持拓扑模型下的并发消费                       | ✅ 支持并发消费（逻辑需自己控制）                     |
| 扩展性                       | ❌ 固定大小 RingBuffer，不能动态扩容             | ✅ 动态扩容（链表结构可扩容）                         |
| 跨语言实现可行性             | 限 JVM（Java/Kotlin）为主                         | 任意语言（C++/Rust/Go/Java 等）                       |
| 使用复杂度                   | 中（需理解 Disruptor 架构）                       | 简单到中（MSQueue/自定义实现）                        |
| 实用场景示例                 | 游戏帧同步、日志流、行情处理流水线               | Actor 消息队列、异步任务池、模块数据解耦             |
