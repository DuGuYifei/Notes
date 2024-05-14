# 自我初识shader

## shader是什么

[【游戏开发基础知识】什么是Shader?](https://www.bilibili.com/video/BV1qZ4y1q7pm)

1. PBR(Physically Based Rendering) 物理渲染 像现实世界一样渲染
2. Toon Shader 卡通渲染 用于卡通风格游戏

本质上都是用shader来实现的

1. shader和OpenGL以及DirectX的关系
   1. OpenGL和DirectX是图形API
   2. shader是在图形API中运行的程序
   3. shader的代码会被编译成GPU可以运行的代码
   4. shader需要图形API来运行，而OpenGL和DirectX就是这样的图形API
2. shader在Unity和UE里实际应用写的代码是shader吗
   1. Unity shaderlab
      1. ShaderLab 不是一种传统意义上的着色语言，而是 Unity 用于定义和组织 shaders 的一种语法和框架。它用来设置 shader 的属性、传递参数和定义 shader 的结构，实际的着色运算则是通过内嵌的 HLSL 或 GLSL 代码来完成的。ShaderLab 主要负责 shader 的“包装”，定义如何将数据输入到这些着色程序中，以及如何组合多个 pass（渲染阶段）。
      2. ShaderLab 结构：包括属性声明、子着色器和 pass 声明等。每个 pass 内部可以包含实际的 HLSL 或 GLSL 代码。
      3. 语法：ShaderLab 的语法主要用于描述 shader 的配置和组织结构，而不直接参与具体的图形渲染计算。
   2. UE HLSL 是
      1. HLSL 和 GLSL 是两种着色语言，它们是 shader 的核心部分，用于实现具体的图形渲染计算。HLSL 是 DirectX 中的着色语言，GLSL 则是 OpenGL 中的着色语言。

## shader基本结构

1. shader的基本结构
   1. shader的基本结构包括：shader的类型、shader的名称、shader的属性、shader的子着色器和pass
      1. shader的类型：shader的类型包括：顶点着色器、片元着色器、几何着色器、计算着色器、外壳着色器和域着色器
      2. shader的名称：shader的名称是shader的唯一标识符，用于在程序中引用shader
      3. shader的属性：shader的属性是shader的输入参数，用于传递数据到shader中
      4. shader的子着色器：shader的子着色器是shader的渲染阶段，用于定义shader的渲染过程
      5. shader的pass：shader的pass是shader的渲染通道，用于定义shader的渲染方式
2. 一般编写shader需要写vertex shader和fragment shader
   1. vertex shader：顶点着色器，用于处理顶点的位置和属性
   2. fragment shader：片元着色器，用于处理像素的颜色和属性
   3. 一般情况下，vertex shader和fragment shader是成对出现的，用于处理顶点和像素的渲染过程
   4. 除了vertex shader和fragment shader之外，还有其他类型的shader，如几何着色器、计算着色器、外壳着色器和域着色器等，他们在比如几何着色器用于处理几何图元的渲染过程，计算着色器用于处理通用计算过程，外壳着色器用于处理曲面细分过程，域着色器用于处理曲面细分过程等

## 从编写到被执行
1. 编写shader
2. 用其他应用程序比如c++写的程序，调用opengl的api来编译
3. 链接多个着色器(opengl api)
4. 加载到gpu(opengl api)
5. GPU执行shader程序

举个基本的理解例子：vertex shader里有in (attribute),out (varying),uniform (uniform)三种变量，in是输入，out是输出，uniform是全局变量。而in的值，是程序通过比如opengl的api - glVertexAttribPointer来传入的，uniform的值是通过glUniform传入的，out的值是vertex shader传给fragment shader的。