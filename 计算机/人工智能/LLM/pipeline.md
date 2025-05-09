# pipeline

## 语法

pipeline接受多个参数，
- task：任务名称
- model：模型名称

### task

| 任务类型                             | 描述              | 示例输出                         |
| -------------------------------- | --------------- | ---------------------------- |
| `"sentiment-analysis"`           | 情感分类            | `label: POSITIVE / NEGATIVE` |
| `"text-classification"`          | 文本分类（更通用）       | 标签 + 分数                      |
| `"text-generation"`              | 文本生成            | 生成字符串                        |
| `"question-answering"`           | 问答              | `start`, `end`, `answer`     |
| `"translation"`                  | 翻译              | 翻译后的文本                       |
| `"summarization"`                | 摘要              | 概括后的文本                       |
| `"ner"`                          | 命名实体识别          | 实体、类型、位置                     |
| `"fill-mask"`                    | 掩码预测（如 BERT）    | `[MASK]` 替换预测                |
| `"zero-shot-classification"`     | 零样本文本分类         | 自定义标签分类                      |
| `"image-classification"`         | 图像分类（配图像模型）     | 标签                           |
| `"automatic-speech-recognition"` | 语音转文本           | 文本字符串                        |
| `"conversational"`               | 对话生成（Chat-like） | 回复内容                         |


## 例子

```python
from transformers import pipeline

checkpoint = "distilbert-base-uncased-finetuned-sst-2-english"
classifier = pipeline("sentiment-analysis", checkpoint)
classifier(["I've been waiting for a HuggingFace course my whole life.", "I hate this so much!"])

# classifier(["I've been waiting for a HuggingFace course my whole life.", 
#             "I hate this so much!"])
```

```python
generator = pipeline("text-generation")
generator(
    "In this course, we will teach you how to",
    max_length=30,
    num_return_sequences=2,
)

# [{'generated_text': 'In this course, we will teach you how to set up and use a basic command line tool. You will learn the basics of using a terminal,'},
#  {'generated_text': 'In this course, we will teach you how to make your own light bulb and LED lighting in no time. How to build your own lights or accessories'}]
```

```python
checkpoint = "bert-base-uncased"
unmasker = pipeline("fill-mask", checkpoint)
unmasker("This course will teach you all about [MASK] models.", top_k=2)

# [{'score': 0.33661210536956787,
#   'token': 2535,
#   'token_str': 'role',
#   'sequence': 'this course will teach you all about role models.'},
#  {'score': 0.0837174504995346,
#   'token': 2449,
#   'token_str': 'business',
#   'sequence': 'this course will teach you all about business models.'}]
```