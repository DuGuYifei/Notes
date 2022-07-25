# c++中添加opencv

[C++项目中引用OpenCV库 / C++调用摄像头](https://www.bilibili.com/read/cv15980459)
1. C++ 项目 -> 属性 -> vc++目录
2. 包含目录 -> 新增
   ![](2022-07-24-11-30-58.png)
3. 库目录 -> 新增
   ![](2022-07-24-11-31-44.png)
4. 链接器 -> 输入 -> 附加依赖项 -> 编辑
   ![](2022-07-24-11-32-32.png)

   有d的lib文件是Debug版本的文件库，填入即可
5. 将.dll文件复制到C:\Windows\System32 **这步我暂时没做，在robomaster风车能量靶识别中**

在CV15 -> bin 中找到所有.dll文件复制到C:\Windows\System32中即可


这时候重启c++就行opencv库应该已经引用好了
