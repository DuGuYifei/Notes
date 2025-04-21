# RAG

---

## 1. RAG 简介

**RAG（Retrieval-Augmented Generation）** 是一种结合了信息检索（Retrieval）与生成模型（如 GPT）的方法，提升了大语言模型在处理知识密集型任务时的能力。

### 1.1 传统 LLM 的问题
- 固定参数限制了知识量
- 无法动态更新外部信息
- 回答可能基于过时或错误知识

### 1.2 RAG 的优势
- 动态检索知识库信息
- 增强上下文准确性
- 减少幻觉（hallucination）

---

## 2. RAG 架构组成

RAG 通常包含两个主要模块：

### 2.1 检索器（Retriever）
- 功能：从外部知识库中检索相关文档/片段
- 技术实现：向量检索（如 FAISS）、BM25 等
- 输入：用户查询（Query）
- 输出：Top-k 个相关文档（Docs）

### 2.2 生成器（Generator）
- 功能：基于检索到的文档生成答案
- 技术实现：预训练语言模型（如 GPT、T5、LLaMA）
- 输入：Query + Retrieved Docs
- 输出：最终的自然语言回答

> 有些实现中，Retriever 和 Generator 可进行端到端训练（如 Facebook 的原始RAG）

---

## 3. RAG 工作流程

1. 用户输入 Query  
2. Retriever 从知识库中找出相关文档（转为向量后用向量相似度匹配）  
3. Generator 将 Query 和文档拼接作为上下文，生成回答  
4. 返回答案  

可视化流程：
```
User Query → Retriever → Relevant Docs → Generator → Answer
```

---

## 4. 实现工具

### 4.1 向量数据库
- FAISS、Weaviate、Milvus、Pinecone、Chroma

### 4.2 Embedding 模型
- OpenAI Ada、BGE、E5、sentence-transformers

### 4.3 生成模型
- GPT-3/4、LLaMA、Mistral、T5 等

### 4.4 开发框架
- LangChain
- LlamaIndex
- Haystack

---

## 5. 常见挑战

- 检索质量影响生成质量
- 多文档融合困难
- 长文本截断问题（token 限制）
- 检索文档冗余或不相关会引入噪音
- 延迟较高（检索+生成过程）

---

## 6. 优化策略

- 精调 Embedding 模型提升匹配度
- Rerank（重排序）阶段提高结果质量
- 多阶段检索（粗-精）
- 使用摘要压缩 Retrieved Docs
- 引入记忆机制或缓存

---

## 7. 应用场景

- 企业内部知识问答
- 法律/医疗/金融领域问答
- 聊天机器人
- 文档搜索与摘要
- 辅助写作与代码生成

---

## 8. 延伸与发展

- **Hybrid RAG**：结合稀疏（BM25）和密集（向量）检索
- **Multi-hop RAG**：支持多跳推理
- **Agent + RAG**：智能体执行多步任务时引入 RAG 提升上下文感知
- **Streaming RAG**：实时数据检索与回答

---

## 9. OpenAI RAG 案例分析

### 9.1 OpenAI Embedding 是 RAG 吗？

不是。

#### 9.1.1 Embedding 是什么？
- OpenAI 的 `text-embedding-3-small` 等模型能将一段文字转换为一个向量（表示其语义）
- 这个向量可用于语义搜索、分类、聚类等任务
- 属于 RAG 的**检索部分的第一步**

#### 9.1.2 为什么 Embedding ≠ RAG？
- RAG 是一个完整流程：Embedding + 检索 + 生成
- Embedding 只是把文本变成向量，**没有检索、没有生成**

---

### 9.2 OpenAI 提供 RAG 吗？

❌ 没有一体化的 RAG 产品，但有所有组件：

| 功能          | 是否提供 | 用途说明 |
|---------------|----------|----------|
| Embedding API | ✅ 提供  | 把文本变成向量 |
| GPT API       | ✅ 提供  | 文本生成部分 |
| 检索工具      | ❌ 不提供 | 需用第三方工具，如 FAISS、Chroma |
| 文档上传      | ✅ 有    | 可以作为轻量检索+问答场景的方案（ChatGPT Custom GPT）|

---

### 9.3 RAG 实现流程梳理

#### 9.3.1 离线构建知识库
- 文档预处理：分段、切片
- 生成 embedding：调用 OpenAI Embedding API
- 存储向量及原文：
  - 向量数据库如：FAISS、Chroma、Pinecone、Weaviate

#### 9.3.2 在线检索+生成
- 用户提问 → 生成向量
- 在向量库中搜索最相似的 Top-k 结果
- 取出原始文本 → 拼接 prompt
- 发给 GPT 生成答案

---

### 9.4 向量数据库结构解析

虽然不是关系型数据库，但逻辑结构类似一张表：

| ID（Key） | 向量（Vector） | 原文（Document） | 元数据（Metadata） |
|-----------|----------------|------------------|---------------------|
| chunk_001 | [0.23, 0.45...]| "这是文档段落"   | {"source": "xx.pdf"}|

#### 9.4.1 常见数据库对比

| 库名      | 是否存文本 | 是否存元数据 | 是否支持相似度检索 | 是否托管 |
|-----------|------------|--------------|---------------------|----------|
| FAISS     | ❌ 向量 + 索引（文本要自己配）| ❌ | ✅ | ❌ |
| Chroma    | ✅ 文本字段 | ✅            | ✅ | ❌（本地优先）|
| Pinecone  | ✅ 支持     | ✅            | ✅ | ✅（云托管）|
| Weaviate  | ✅ 支持     | ✅            | ✅ | ✅ |

---

### 9.5 向量检索方式说明

RAG 中不是使用 QKV 检索（Transformer 内部结构），而是**语义向量之间的相似度搜索**：

- 常用距离指标：
  - 余弦相似度（cosine similarity）
  - 内积（dot product）
  - 欧几里得距离（euclidean）

---

### 9.6 RAG 完整流程图

```
[原始文档] 
   ↓ 切片
[段落们] 
   ↓ Embedding API
[向量 + 原文] 
   ↓ 存入向量数据库
——————————————
      ↓ 用户提问
   [问题] → 向量 → 相似搜索
      ↓ Top-k 文档
   [拼接 prompt → GPT]
      ↓ 回答
```
