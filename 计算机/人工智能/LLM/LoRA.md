# LoRA

## LoraConfig

```python
lora_config = LoraConfig(
    task_type=TaskType.SEQ_CLS,
    r=16,  # Dimension of the low-rank matrices
    lora_alpha=16,  # Scaling factor for the weight matrices
    lora_dropout=0.1,  # Dropout probability of the LoRA layers
    bias="all",  # Train all bias parameters
)
```

| 参数        | 控制           | 建议默认值    |
| --------- | ------------ | -------- |
| `r`       | 插件能学多少维度的新信息 | 8 或 16   |
| `alpha`   | 插件输出被缩放多少    | 通常等于 `r` |
| `dropout` | 正则防止过拟合      | 0.05–0.1 |
| `bias`    | 是否也调整偏置      | `"none"` |

| r 值 | 表达能力   | 参数量  | 建议         |
| --- | ------ | ---- | ---------- |
| 1   | 极简线性偏移 | 最小   | 实验用        |
| 8   | 基础级别调整 | 较低   | 推荐起点       |
| 16  | 中等表达力  | 中等   | 精度优先       |
| 32+ | 强表达力   | 参数略多 | 对性能很敏感时可尝试 |

`LoRA 输出 = (B @ A) * (alpha / r)`

所以：alpha 越大，LoRA 的输出占比越大

| alpha / r      | 效果            |
| -------------- | ------------- |
| 很小（如 1.0）      | 插件很弱，主要靠原模型   |
| 适中（如 4.0\~8.0） | 插件与主模型力量平衡    |
| 很大（如 16.0）     | 插件主导模型行为（强干预） |

## 实例

```python
from datasets import load_dataset
from transformers import AutoTokenizer, DataCollatorWithPadding, AutoModelForSequenceClassification


raw_datasets = load_dataset("glue", "mrpc")
checkpoint = "bert-base-uncased"
tokenizer = AutoTokenizer.from_pretrained(checkpoint)

def tokenize_function(example):
    return tokenizer(example["sentence1"], example["sentence2"], truncation=True)

tokenized_datasets = raw_datasets.map(tokenize_function, batched=True)
data_collator = DataCollatorWithPadding(tokenizer=tokenizer)

model = AutoModelForSequenceClassification.from_pretrained(checkpoint, num_labels=2)
```

```python
def count_parameters(model):
    total_params = sum(p.numel() for p in model.parameters())
    trainable_params = sum(p.numel() for p in model.parameters() if p.requires_grad)
    return {'Total': total_params, 'Trainable': trainable_params}

def compute_metrics(eval_preds):
    metric = evaluate.load("glue", "mrpc")
    logits, labels = eval_preds
    predictions = np.argmax(logits, axis=-1)
    return metric.compute(predictions=predictions, references=labels)
```

```python
from peft import LoraConfig, TaskType, get_peft_model
from transformers import TrainingArguments, Trainer
import evaluate
import numpy as np


### YOUR CODE HERE ###

lora_config = LoraConfig(
    task_type=TaskType.SEQ_CLS,
    r=16,  # Dimension of the low-rank matrices
    lora_alpha=16,  # Scaling factor for the weight matrices
    lora_dropout=0.1,  # Dropout probability of the LoRA layers
    bias="all",  # Train all bias parameters
)

######################


# Count parameters before LoRA
before_lora_count = count_parameters(model)
print(f"Before LoRA:\n{before_lora_count}")

# Apply LoRA to the model
lora_model = get_peft_model(model, lora_config)

# Count parameters after LoRA
after_lora_count = count_parameters(lora_model)
print(f"After LoRA:\n{after_lora_count}")

### YOUR CODE HERE ###

trainer = Trainer(
    lora_model,  # Use the LoRA model here
    training_args,
    train_dataset=tokenized_datasets["train"],
    eval_dataset=tokenized_datasets["validation"],
    data_collator=data_collator,
    tokenizer=tokenizer,
    compute_metrics=compute_metrics
)

######################

trainer.train()
```