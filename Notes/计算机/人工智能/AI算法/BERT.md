# BERT

## 介绍
[什么是 BERT？【知多少](https://www.bilibili.com/video/BV11N41197nq/)
让机器理解语言。BERT源于Transformer，相当于将Encoder部分单独拿出来(Decoder被GPT来代替了)。它将语言理解建模放到合适的向量位置里。

1. 有遮挡训练
2. 判断句子是否相连
3. 可以将其与其他不同的任务模型结合起来，bert理解语言其他模型做输出层，比如文本分类添加分类器，阅读理解添加全链接层。
4. 然后就有了[GPT](GPT.md)