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