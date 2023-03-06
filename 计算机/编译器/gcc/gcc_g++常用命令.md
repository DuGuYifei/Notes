# gcc_g++常用命令


## 快捷
```bash
gcc *.c
```

## 基础
* `-E` 选项可以只进行预处理，不生成可执行程序。
* `-S` 选项可以只进行预处理和编译，不进行汇编和链接。
* `-c` 选项可以只进行预处理、编译和汇编，不进行链接。
* `-o` 选项可以指定输出文件的名称。链接多个目标文件。
* `-l` 链接，包括动态库，静态库
  * 数学库的文件名是 `libm.a` 或 `libm.so`，所以链接时用 `-lm`。C++标准库的文件名是 `libstdc++.a` 或 `libstdc++.so`，所以链接时用 `-lstdc++`。
  * `-L` 指库目录
    * `-L.`当前目录
    * `-L/home/user/lib`
    * PATH变量下的不需要
  * 可以省略：
    * `gcc -o my_program my_program.c /usr/lib/libm.a`
    * `gcc -o my_program my_program.c -lm`
    * `gcc -o my_program my_program.c -L/usr/lib/ -lm`

```bash
# 1.2.可以跳过，直接生成 object 文件
# 1.预处理，生成预编译文件（i.文件）：
    gcc –E hello.c –o hello.i
# 2.编译，生成汇编代码（.s文件）：
    gcc –S hello.i –o hello.s
# 3.汇编，生成目标文件（.o文件）：
    gcc –c hello.s –o hello.o
# 4.生成可执行文件(可以链接多个文件或-l库)：
    gcc hello.o –o hello
    gcc main.o b.o c.o -o main
    gcc main.o b.o c.o -o main -lm -lstdc++ (-L.)
```

```bash
g++ –E hello.c –o hello.i
g++ –S hello.i –o hello.s
g++ –c hello.s –o hello.o
g++ hello.o –o hello
g++ main.o b.o c.o -o main
g++ main.o b.o c.o -o main -lm -lstdc++
```