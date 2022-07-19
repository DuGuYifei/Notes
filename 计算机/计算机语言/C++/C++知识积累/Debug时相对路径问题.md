# Debug时相对路径问题
`./`在debug时候起始路径从`vcproj/vcprojx`的文件开始，所以要

`../Debug/`

但是最后直接点击`exe`文件时，改回`./`