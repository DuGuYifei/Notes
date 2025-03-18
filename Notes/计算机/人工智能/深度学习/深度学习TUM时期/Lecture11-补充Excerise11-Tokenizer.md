# Tokenizer

## BPE

Byte Pair Encoding，字节对编码，是一种用于文本数据压缩和分词的算法。最初，它是一种简单的数据压缩方法，但在自然语言处理（NLP）领域，它被改进并广泛用于生成词汇表，以应对词汇量庞大的问题。

后来在OpenAI的GPT模型中用于分词。它仍然是一种在许多Transformer模型（如GPT、GPT-2、RoBERTa、BART和DeBERTa）中广泛使用的基础技术。

现在的

### 基本原理

迭代地合并最频繁的字符对（或子词对），直到达到预定的词汇表大小。通过这种方式，它可以有效地减少词汇表的大小，并且能够处理未见过的词汇（OOV, Out-Of-Vocabulary）问题。

1. 初始化：将所有词拆分为单字符的序列。例如，词“lower”会被分解为 l o w e r。
2. 计算频率： 统计所有字符对（相邻字符）的出现频率。
3. 合并最频繁对： 找到出现频率最高的字符对，并将其合并为一个新的符号。例如，如果“l o”是最频繁的字符对，就将其合并为一个新符号“lo”。
4. 更新文本和重复： 用合并后的新符号更新文本，然后重复步骤2和步骤3，直到达到预定的词汇表大小。

### 优点
* 处理未见过的词汇： BPE生成的子词可以组合成新词，减少了未见词的问题。
* 词汇表压缩： 通过合并高频字符对，BPE可以生成一个较小且高效的词汇表。
* 语言独立性： BPE不依赖于特定语言的词法规则，因此可以应用于多种语言。

### 示例

假设我们有以下文本序列：“low”, “lowest”, “newer”, “wider”。
* 初始分割：l o w, l o w e s t, n e w e r, w i d e r
* 合并最频繁对：“l o” -> “lo”
  * 结果：lo w, lo w e s t, n e w e r, w i d e r
* 下一次合并：“e r” -> “er”
  * 结果：lo w, lo w e s t, n e w er, w i d er
* 下一次合并: “lo w” -> “low” (**新组合"lo"被认为一个整体**)
  * 结果：low, low e s t, n e w er, w i d er

通过反复合并这些最频繁的字符对，最终可以得到一个优化后的词汇表。

### 局限性

* 合并策略依赖于训练数据： 生成的子词依赖于训练数据，如果训练数据与实际应用场景差异较大，效果可能会受到影响。
* 没有语义信息： BPE基于字符频率合并，对词的语义信息没有考虑。

### 代码使用

#### 使用tokenizer模型

这里使用了预训练的tokenizer，可以直接使用。

```bash
pip install tokenizer
```

```python
from tokenizers import Tokenizer

file_path = os.path.join(pretrained_model_path, 'pretrained_tokenizer')
tokenizer = Tokenizer.from_file(file_path)

sentence = "Hi, Introduction to Deep Learning is class IN2346!"
encodings = tokenizer.encode(sentence)
tokens = encodings.tokens
print(tokens)

# Output: ['<[EOS]>', 'H', 'i', ',', 'ĠIn', 't', 'rodu', 'ction', 'Ġto', 'ĠDe', 'ep', 'ĠL', 'ear', 'ning', 'Ġis', 'Ġclass', 'ĠI', 'N', '2', '3', '4', '6', '!', '<[EOS]>']
```

Note: The character Ġ is used to mark the location of whitespaces.

```python
token_ids = encodings.ids
print(token_ids)
# [0, 29, 57, 6, 362, 68, 2272, 547, 132, 750, 1444, 253, 587, 4966, 143, 5741, 175, 35, 11, 12, 13, 15, 1, 0]

tokenizer.decode(token_ids)
# 'Hi, Introduction to Deep Learning is class IN2346!'
```

#### 训练 - 原理

```python
words = ["hug", "pug", "pun", "bun", "hugs"]

base_vocabulary = create_alphabet_from_list(words)
print(base_vocabulary)
# ['b', 'g', 'h', 'n', 'p', 's', 'u']

word_freq = {"hug": 10, "pug": 5, "pun": 12, "bun": 4, "hugs": 5}

splits = create_splits(word_freq.keys())
print('Words split into characters: {}'.format(splits))
# Words split into characters: {'hug': ['h', 'u', 'g'], 'pug': ['p', 'u', 'g'], 'pun': ['p', 'u', 'n'], 'bun': ['b', 'u', 'n'], 'hugs': ['h', 'u', 'g', 's']}

pair_freq = compute_pair_freq(word_freq, splits)

print('Pair frequencies in corpus: {}'.format(dict(pair_freq)))
# Pair frequencies in corpus: {('h', 'u'): 15, ('u', 'g'): 20, ('p', 'u'): 17, ('u', 'n'): 16, ('b', 'u'): 4, ('g', 's'): 5}

best_pair = compute_best_pair(pair_freq)

print("The best pair is: {}".format(best_pair))
# The best pair is: ('u', 'g')

merges = {}
splits = merge_pair(word_freq, *best_pair, splits)
merges[best_pair] = best_pair[0] + best_pair[1]
base_vocabulary.append(best_pair[0] + best_pair[1])

print('The new splits are: {}'.format(splits))
print('New vocabulary: {}'.format(base_vocabulary))
print('Dictionary with all merges: {}'.format(merges))
# The new splits are: {'hug': ['h', 'ug'], 'pug': ['p', 'ug'], 'pun': ['p', 'u', 'n'], 'bun': ['b', 'u', 'n'], 'hugs': ['h', 'ug', 's']}
# New vocabulary: ['b', 'g', 'h', 'n', 'p', 's', 'u', 'ug']
# Dictionary with all merges: {('u', 'g'): 'ug'}

pair_freq = compute_pair_freq(word_freq, splits)
best_pair = compute_best_pair(pair_freq)

print('Pair frequencies in corpus: {}'.format(dict(pair_freq)))
print("The best pair is: {}".format(best_pair))
# Pair frequencies in corpus: {('h', 'ug'): 15, ('p', 'ug'): 5, ('p', 'u'): 12, ('u', 'n'): 16, ('b', 'u'): 4, ('ug', 's'): 5}
# The best pair is: ('u', 'n')

splits = merge_pair(word_freq, *best_pair, splits)
merges[best_pair] = best_pair[0] + best_pair[1]
base_vocabulary.append(best_pair[0] + best_pair[1])

print('The new splits are: {}'.format(splits))
print('New vocabulary: {}'.format(base_vocabulary))
print('Dictionary with all merges: {}'.format(merges))
# The new splits are: {'hug': ['h', 'ug'], 'pug': ['p', 'ug'], 'pun': ['p', 'un'], 'bun': ['b', 'un'], 'hugs': ['h', 'ug', 's']}
# New vocabulary: ['b', 'g', 'h', 'n', 'p', 's', 'u', 'ug', 'un']
# Dictionary with all merges: {('u', 'g'): 'ug', ('u', 'n'): 'un'}
```

我们继续这样做，直到达到所需的词汇量。

#### 训练 - 代码库

```python
from tokenizers import Tokenizer
from tokenizers.models import BPE
from tokenizers import trainers
from tokenizers.pre_tokenizers import ByteLevel, Digits, Sequence, Punctuation

tokenizer = Tokenizer(BPE())

vacab_size = 300
eos_token = "<[EOS]>" # End of sentence token，比如有时候还会有BOS token (Begin of sentence token), PAD token (Padding token)
# special tokens 参数就是把自定义的token组合作为一个整体，防止被拆分
tokenizer.train_from_iterator(words, vocab_size=vocab_size, special_tokens=[eos_token])

pre_tokenizer = Sequence([ByteLevel(add_prefix_space=False), Digits(individual_digits=True), Punctuation()]) 

output = pre_tokenizer.pre_tokenize_str(sentence)
print(output)
# [('Hi', (0, 2)), (',', (2, 3)), ('ĠIntroduction', (3, 16)), ('Ġto', (16, 19)), ('ĠDeep', (19, 24)), ('ĠLearning', (24, 33)), ('Ġis', (33, 36)), ('Ġclass', (36, 42)), ('ĠIN', (42, 45)), ('2', (45, 46)), ('3', (46, 47)), ('4', (47, 48)), ('6', (48, 49)), ('!', (49, 50))]

tokenizer.pre_tokenizer = pre_tokenizer
```

pre_tokenizer 是在文本分词过程中用于预处理文本的一种工具。它在正式分词之前对输入文本进行初步的拆分和处理。通过预处理，pre_tokenizer 可以将文本分成更小的单位，如单词、标点符号、数字等，以便后续的分词器（如BPE）进行更精确和高效的分词。

```python
files = [os.path.join(dataset_path, 'europarlOpusDatasets', 'corpus_english.txt'),
         os.path.join(dataset_path, 'europarlOpusDatasets', 'corpus_german.txt')]
tokenizer.train(files, trainer)
```

好了，训练已经完成，我们要做的最后一件事是定义输出模板。我们希望每个标记序列都以序列结束标记开始和结束。
* 以 EOS 标记开始和结束序列，可以帮助模型更好地理解文本的边界，从而更准确地进行序列预测和生成。
* 在实际应用中，可能会遇到一些特殊情况，例如空序列或包含特殊标记的序列。通过在序列两端添加 EOS 标记，可以确保模型在这些特殊情况下仍能正确处理输入和输出。
* 对于生成任务（如机器翻译、文本生成等），在序列开始和结束添加 EOS 标记，可以为模型提供额外的上下文信息，帮助模型更好地理解输入和生成更连贯的输出。

而且在加载数据的时候，因为为了确保所有项目长度相同，就会序列填充，在句子末尾添加特殊标记，直到所有句子一样长。

```python
from tokenizers.processors import TemplateProcessing

tokenizer.post_processor = TemplateProcessing(
    single=eos_token + " $0 " + eos_token,
    pair=None,
    special_tokens=[
        (eos_token, tokenizer.token_to_id(eos_token))
    ],
)
```

#### 使用

```python
output = tokenizer.encode(sentence)
print(output.tokens)
# ['<[EOS]>', 'H', 'i', ',', 'ĠI', 'n', 't', 'ro', 'd', 'u', 'ct', 'ion', 'Ġto', 'ĠD', 'e', 'e', 'p', 'ĠL', 'e', 'ar', 'n', 'ing', 'Ġis', 'Ġc', 'l', 'as', 's', 'ĠI', 'N', '2', '3', '4', '6', '!', '<[EOS]>']

print(output.ids)
# [0, 29, 57, 6, 175, 62, 68, 148, 52, 69, 192, 112, 132, 236, 53, 53, 64, 253, 53, 115, 62, 140, 143, 127, 60, 118, 67, 175, 35, 11, 12, 13, 15, 1, 0]
```

decode错误示例 - 没有配置deocoder
```python
tokenizer.decode(output.ids)
# 'H i , ĠI n t ro d u ct ion Ġto ĠD e e p ĠL e ar n ing Ġis Ġc l as s ĠI N 2 3 4 6 !'
```

配置decoder
* ByteLevel: 替换所有空格为特殊字符Ġ并拆分句子。
* Digits: 将所有数字序列拆分为单个数字。这样我们就不会浪费任何词汇在经常出现的数字上。
* Punctuation: 在标点处拆分序列。

```python
from tokenizers.decoders import ByteLevel
tokenizer.decoder = ByteLevel()

tokenizer.decode(output.ids)
# 'Hi, Introduction to Deep Learning is class IN2346!'
```

#### 保存

```python
file_path = os.path.join(model_path, "custom_tokenizer")
tokenizer.save(file_path)
```

#### 配合transformers库加载使用

```bash
pip install tokenizer
```

```python
from transformers import PreTrainedTokenizerFast

tokenizer_fast = PreTrainedTokenizerFast(
    tokenizer_file=file_path,
    # tokenizer_object=tokenizer, # This also works!
    eos_token=eos_token,
    pad_token=eos_token
)

output = tokenizer_fast.encode(sentence)
print(output)
# [0, 29, 57, 6, 175, 62, 68, 148, 52, 69, 192, 112, 132, 236, 53, 53, 64, 253, 53, 115, 62, 140, 143, 127, 60, 118, 67, 175, 35, 11, 12, 13, 15, 1, 0]

tokenizer_fast.decode(output, skip_special_tokens=True)
# 'Hi, Introduction to Deep Learning is class IN2346!'
```