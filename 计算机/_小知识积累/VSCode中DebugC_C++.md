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

这里是运行。debug用gdb时候[gdb vscode](../编译器/gdb/_gdb.md)