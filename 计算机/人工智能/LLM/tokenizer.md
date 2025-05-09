# tokenizer

## tokenizer, tokenize, ids, decode

`inputs = tokenizer(raw_inputs, padding=True, truncation=True, return_tensors="pt")`

* 参数pt是pytorch，直接可以返回torch.Tensor来方便送进模型

```python
from transformers import AutoTokenizer

tokenizer = AutoTokenizer.from_pretrained("distilbert-base-uncased-finetuned-sst-2-english")

sequence = "I've been waiting for a HuggingFace course my whole life."

print(tokenizer(sequence))

tokens = tokenizer.tokenize(sequence) # You can also use the __call__ function directly

print(tokens)

ids = tokenizer.convert_tokens_to_ids(tokens)

print(ids)

decoded_string = tokenizer.decode(ids)

print(decoded_string)

# {'input_ids': [101, 1045, 1005, 2310, 2042, 3403, 2005, 1037, 17662, 12172, 2607, 2026, 2878, 2166, 1012, 102], 'attention_mask': [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]}
# ['i', "'", 've', 'been', 'waiting', 'for', 'a', 'hugging', '##face', 'course', 'my', 'whole', 'life', '.']
# [1045, 1005, 2310, 2042, 3403, 2005, 1037, 17662, 12172, 2607, 2026, 2878, 2166, 1012]
# i've been waiting for a huggingface course my whole life.
```

| 语句                                      | 含义                                                    |
|-------------------------------------------|-------------------------------------------------------|
| `tokenizer(sequence)`                     | 完整调用，自动添加 `[CLS]` 和 `[SEP]`，适合直接喂模型     |
| `tokenizer.tokenize(sequence)`            | 拆分为 subword token（词或词的一部分）                    |
| `tokenizer.convert_tokens_to_ids(tokens)` | 把每个 token 转成对应的词表 ID                          |
| `[101]` 和 `[102]`                        | `[CLS]` 和 `[SEP]` 的 ID，是 BERT 系列模型需要的输入格式 |

## tokenizer 和 sentence pair

```python
tokenizer(text1, text2, ...)
```

两个句子作为一个样本（即句子对）

## padding和truncation

[padding truncate](padding-truncate.md)

## 问答训练

常规训练，比如训练对游戏的，需要将问答合并。

利用label来只掩盖回答部分

```python
instruction = "火焰魔龙在哪里？"
output = "火焰魔龙栖息在熔岩谷底部，每晚8点出现。"

prompt = f"### 用户：{instruction}\n\n### 助手："
full_text = prompt + output

# encode 全部文本
full = tokenizer(full_text, return_tensors="pt", padding="max_length", truncation=True, max_length=512)
input_ids = full["input_ids"][0]

# 分别 encode prompt（用来构造 label mask）
prompt_ids = tokenizer(prompt, return_tensors="pt")["input_ids"][0]

# 构造 label（只监督 output 部分）
labels = input_ids.clone()
labels[: len(prompt_ids)] = -100  # -100 表示忽略，不计算 loss
```
