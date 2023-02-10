# memmove和memcpy

memmove和memcpy的差别就是memmove函数处理的源内存块和目标内存块是可以重叠的。 如果**源空间和目标空间出现重叠**，就得使用memmove函数处理。

| 函数                       | 结果                     |
| -------------------------- | ------------------------ |
| `memmove(arr + 3, arr, 5)` | `abcdefgh` -> `abcabcde` |
| `memcpy(arr + 3, arr, 5)`  | `abcdefgh` -> `abcabcab` |