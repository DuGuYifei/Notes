# 【npm】npm全局安装和局部(本地)安装

[【npm】npm 全局安装 和 局部(本地)安装_Eva3288的博客-CSDN博客](https://blog.csdn.net/Eva3288/article/details/104131735?spm=1001.2101.3001.6661.1&utm_medium=distribute.pc_relevant_t0.none-task-blog-2%7Edefault%7ECTRLIST%7ERate-1-104131735-blog-79861404.t5_refersearch_landing&depth_1-utm_source=distribute.pc_relevant_t0.none-task-blog-2%7Edefault%7ECTRLIST%7ERate-1-104131735-blog-79861404.t5_refersearch_landing&utm_relevant_index=1)

| |全局安装|	局部(本地)安装
:-:|:-|:-
命令	|npm install webpack -g	|npm install --save-dev webpcak
安装位置|	一般在 Node安装目录下的node_modules文件夹中：\Users\用户名\AppData\Roaming\ 目录下\npm\node_modules	|项目的node_modules文件夹中
建议	|工具类建议全局安装	|项目中的包用本地
优点	|只安装一次就行	|1、据node团队介绍，本地安装包对于项目的加载会更快; 2、本地安装可以让每个项目拥有独立的包，不受全局包的影响，方便项目的移动、复制、打包等，保证不同版本包之间的相互依赖，这些优点是全局安装难以做到的。
缺点	|1、包的更新不好管理 2、不能支持全局多版本	|1、每次新项目都要本地安装所依赖的包，安装包时间相对较长，一来是包太大导致下载慢；二是浪费了硬盘空间，
