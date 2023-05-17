# Runtime


每个Java应用程序都有一个Runtime类的单个实例，允许应用程序与应用程序运行的环境进行交互。当前runtime可以从getRuntime方法获得。

应用程序不能创建自己的这个类的实例。

它包含了一些有用的方法，如exec，gc，exit，获得内存使用情况等。