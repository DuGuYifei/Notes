# 环境搭建anaconda
不再推荐，我不喜欢anaconda，我觉得venv就挺好的。

## Anaconda
• NVDIA
	○ 显卡版本
	○ 英伟达官网下载驱动
	○ win+r nvidia smi
• Anaconda
	○ 下载anaconda
	○ add PATH
• Pytorch
	○ win+r （conda env list 查看环境）
	○ 创建 conda create -n pyrotchtest python=3.8
	○ 激活 conda activate pytorchtest
	○ 换清华源下载资源
	○ 打开pytorch官网复制下载链接
• paddle
	○ win+r
	○ 创建 conda create -n paddletest python=3.8
	○ 激活 conda activate paddletest
	○ 打开paddle官网复制下载链接

### 创建环境到指定文件夹
```bash
conda create  -p /opt/environment/.conda/envs/env_name  python=2.7
//或者：
conda create --prefix=D:\envs\py1.2 python=3.7
```

### 显示已安装的包
```bash
pip list
```

### 更改python版本
```bash
conda install python=3.5
```

### 显示所有环境
```bash
conda env list
```

### 删除环境
```bash
conda remove -n pyrotchtest --all
conda remove -p E:/Produce/AIEnvironment/pyrotchtest --all
```

### 复制（+删除=重命名）
```bash
conda create -p E:/Produce/AIEnvironment/yolo5_pytorch --clone E:/Produce/AIEnvironment/yolo
```

## pytorch 和 cuda，cudnn
可以直接下带cuda的pytorch，只要显卡支持（在NVIDIA控制面板-帮助-系统信息-组件里就可以看见，balabalaba cuda balabala）。pytorch现在下载好自带了cuda cudnn 的功能。

## 数据标注软件
标注软件：labelImg
pip install labelimg -I http://pypi.tuna.tsinghua.edu.cn/simple

按w标注
选择VOC模式的文件存储

	•  VOC2007
		○ Annotation
		○ JPEGImages
		
打开：cmd
```bash
labelImg
```

## openCV 在 c++
[opencv](../机器视觉/opencv/c++中添加opencv.md)

## onnx 在 c++
直接按document使用命令行就行了（NuGet包管理器）

## pytorch 在 c++
和openCV类似
1. 包含目录
```
E:\Download\pytorch\libtorch\include
E:\Download\pytorch\libtorch\include\torch\csrc\api\include
```
1. 库目录
```
E:\Download\pytorch\libtorch\lib
```
1. 链接器 输入
```
asmjit.lib
c10.lib
c10_cuda.lib
caffe2_nvrtc.lib
clog.lib
cpuinfo.lib
dnnl.lib
fbgemm.lib
kineto.lib
libprotobuf.lib
libprotobuf-lite.lib
libprotoc.lib
pthreadpool.lib
torch.lib
torch_cpu.lib
torch_cuda.lib
torch_cuda_cpp.lib
torch_cuda_cu.lib
XNNPACK.lib
```
