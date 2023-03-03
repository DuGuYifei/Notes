# OpenAI

## max_tokens 和 temperature
max_tokens和temperature都是OpenAI GPT的API参数。

max_tokens参数指定生成的文本中最多允许出现的标记数量。一个标记通常对应于一个单词或标点符号。通过调整这个参数，您可以控制生成文本的长度。

temperature参数控制生成文本的随机性。具体而言，它控制从模型生成的文本的“多样性”或“创造性”。更高的温度会导致更加随机和创造性的生成文本，而更低的温度会导致更加确定性和精确的生成文本。在使用OpenAI GPT API生成文本时，通常建议在初始阶段尝试不同的温度值，以找到最适合您的应用程序的值。

## 模型和url

### Davinci Codex
* 文档：`https://platform.openai.com/docs/models/gpt-3-5`
* 最强大的代码：Davinci Codex，目前: `code-davinci-002` `max_tokens:4096`
* 最强大的自然语言：GPT3.5，目前: `gpt-3.5-turbo` `max_tokens:4000`
* 链接形式：`https://api.openai.com/v1/`几种url方式：
  * 补全：`/completions`  需要:`[model,prompt,max_tokens,temperature]`等
  * 聊天：`/chat/completions` 需要:`[model，messages]`
  * 编辑：`/edits` 需要`[model,input,instruction]`
  * 其他

Davinci Codex是一种用于编程的模型，可以将自然语言描述的编程任务转化为代码实现。它可以完成代码补全、代码生成等任务。相比于GPT-3，Davinci Codex对于编程语言的理解更加深入，并且有专门的API可以用于编程任务。

GPT-3是一种用于自然语言处理的模型，能够完成语言生成、语言理解、对话等多种任务。它是当前最先进的自然语言处理模型之一，拥有海量的训练数据和参数量。

## 报错时的结构

```JavaScript
error: {
  message: "This model's maximum context length is 4096 …ce the length of the messages or completion.", 
  type: 'invalid_request_error', 
  param: 'messages', 
  code: 'context_length_exceeded'
}
```
