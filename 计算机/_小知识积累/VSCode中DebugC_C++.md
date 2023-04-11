# VSCode中DebugC/C++

调试->GDB->gcc->更改task.json

[gcc -g](../编译器/gcc/-g.md)

```json
"args": [
    "-fdiagnostics-color=always",
    "-g",
    "*.c",
    "-o",
    "${fileDirname}\\${fileBasenameNoExtension}.exe"
],
```