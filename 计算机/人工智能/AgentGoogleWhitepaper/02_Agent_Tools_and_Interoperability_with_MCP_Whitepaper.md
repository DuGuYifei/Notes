# Agent Tools & Interoperability with MCP 白皮书

# 导言：模型、工具和智能体

模型上下文协议（Model Context Protocol, MCP）于2024年推出，作为简化工具与模型集成过程并解决其中一些技术和安全挑战的方式。

# Tools and tool calling

工具和工具调用

## 我们所说的“工具”是什么意思？

在现代人工智能世界中，工具是一个函数或程序，LLM（大型语言模型）应用可以利用它来完成模型能力之外的任务。广义上讲，工具分为两大类：它们允许模型**知晓某事**或**执行某事**。

## 工具的类型

在人工智能系统中，工具的定义就像非人工智能程序中的函数一样。至少，这包括一个清晰的名称、参数以及一个解释其目的和如何使用的自然语言描述。工具的三种主要类型是函数工具（Function Tools）、内置工具（Built-in Tools）和智能体工具（Agent Tools）。

### 函数工具（Function Tools）

所有支持函数调用的模型都允许开发者定义模型可以按需调用的外部函数。工具的定义应提供模型如何使用该工具的基本细节，这些细节作为请求上下文的一部分提供给模型。在像Google ADK这样的Python框架中，传递给模型的定义是从工具代码中的Python文档字符串（docstring）中提取的，如下例所示。

这个例子展示了一个为[Google ADK](https://google.github.io/adk-docs/)定义的工具，它调用一个外部函数来改变灯光的亮度。set_light_values 函数被传入一个 ToolContext 对象（Google ADK框架的一部分），以提供有关请求上下文的更多细节。

Snippet 1: Definition for set_light_values tool
```python
def set_light_values(
    brightness: int
    color_temp: str
    context: ToolContext) -> dict(str, int | str):
    """This tool sets the brightness and color temperature of the room lights in the user's current location.
    Args:
        brightness: Light level from 0 to 100. Zero is off and 100 is full
    color_temp: Color temperature of the light fixture, which can be
    brightness
        `daylight`, `cool' or 'warm`.
        context: A ToolContext object used to retrieve the user's location. Returns:
    A dictionary containing the set brightness and color temperature.
    user_room_id = context.state['room_id']
    # This is an imaginary room lighting control API
    room = light_system.get_room(user_room_id)
    response = room.set_lights (brightness, color_temp) return {"tool_response": response}
```

### 内置工具 (Built-in tools)

一些基础模型提供了利用内置工具的能力，这些工具的定义以隐式方式或在模型服务的幕后提供给模型。例如，Google的Gemini API提供了几种内置工具：**Google搜索增强 (Grounding with Google Search)**、**代码执行 (Code Execution)**、**URL上下文 (URL Context)** 和 **计算机使用 (Computer Use)**。

Snippet 2: Calling url_context tool
```python
from google import genai
from google.genai.types import (
    Tool
    GenerateContentConfig
    HttpOptions
    UrlContext
)
client = genai.Client(http_options=HttpOptions(api_version="v1")
model_id = "gemini-2.5-flash"
url_context_tool = Tool(
    url_context = UrlContext
)
url1 =
"https://www.foodnetwork.com/recipes/ina-garten/perfect-roast-chicken-recipe-19 40592"
url2 = "https://www.allrecipes.com/recipe/70679/simple-whole-roasted-chicken/"
response = client.models.generate_content(
    model=model_id
    contents=("Compare the ingredients and cooking times from
f"the recipes at {url1} and {url2}")
    config=GenerateContentConfig(
        tools=[url_context_tool]
        response_modalities=["TEXT"]
    )
)
for each in response.candidates[0].content.parts:
    print(each.text)
# For verification, you can inspect the metadata to see which URLs the model retrieved
print(response.candidates[0].url_context_metadata)
```

### Agent 工具 (Agent Tools)

