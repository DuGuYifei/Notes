# padding truncate

## 原理

### padding

因为想要batch，所以长度得一样

```python
batched_ids = [
    [200, 200, 200],
    [200, 200, tokenizer.pad_token_id],
]
```

然后attention mask

```python
# This prediction
sentence_1_ids = [[200, 200, 200]]
sentence_2_ids = [[200, 200]]

# will be different from this one
batched_ids = [
    [200, 200, 200],
    [200, 200, tokenizer.pad_token_id],
]

# so we add the attention masks
attention_mask = [
    [1, 1, 1],
    [1, 1, 0],
]

outputs = model(torch.tensor(batched_ids), attention_mask=torch.tensor(attention_mask))

print(outputs.logits)

# tensor([[-0.1630, -0.0376],
        # [ 0.0316, -0.1406]], grad_fn=<AddmmBackward0>)
```

### truncation

标准 Transformer 具有其可处理的最大序列长度，当被要求处理更长的序列时会崩溃。早期模型的最大序列长度通常为 512 或 1024 个 token。此问题有两种解决方案：(1) 使用支持更长序列长度的模型；(2) 截断序列。


## 真实使用

真实使用肯定是有api的

### tokenizer的参数

```python
from transformers import AutoTokenizer

checkpoint = "distilbert-base-uncased-finetuned-sst-2-english"
tokenizer = AutoTokenizer.from_pretrained(checkpoint)

sequences = ["I've been waiting for a HuggingFace course my whole life.", "So have I!"]

# Will pad the sequences up to the maximum sequence length
model_inputs = tokenizer(sequences, padding="longest")

# Will pad the sequences up to the model max length
# (512 for BERT or DistilBERT)
model_inputs = tokenizer(sequences, padding="max_length")

# Will pad the sequences up to the specified max length
model_inputs = tokenizer(sequences, padding="max_length", max_length=8)

# Will truncate the sequences that are longer than the model max length
# (512 for BERT or DistilBERT)
model_inputs = tokenizer(sequences, truncation=True)

# Will truncate the sequences that are longer than the specified max length
model_inputs = tokenizer(sequences, max_length=8, truncation=True)
```

### 自动 padding 的组件 DataCollatorWithPadding

```python
from transformers import DataCollatorWithPadding

data_collator = DataCollatorWithPadding(tokenizer=tokenizer)

from transformers import AutoModelForSequenceClassification
from transformers import TrainingArguments, Trainer

model = AutoModelForSequenceClassification.from_pretrained(checkpoint, num_labels=2)

training_args = TrainingArguments("test-trainer", report_to=[]) #hyperparams for the training

print(training_args)

trainer = Trainer(
    model,
    training_args,
    train_dataset=tokenized_datasets["train"],
    eval_dataset=tokenized_datasets["validation"],
    data_collator=data_collator,
    tokenizer=tokenizer,
)

trainer.train()
```