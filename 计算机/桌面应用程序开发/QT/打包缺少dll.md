# 打包缺少dll

1. 缺少qt，使用命令`windeployqt.exe`打包或补全
2. 缺少其他dll，是`mingw492_32\bin`目录下的dll，复制到exe目录下即可，大概是这个名字，版本号可能不一样，不是你自己的mingw，是qt安装一体包时候带的