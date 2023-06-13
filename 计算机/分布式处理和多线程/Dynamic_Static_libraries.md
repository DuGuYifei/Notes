# Dynamic_Static_libraries

[动态静态链接库](../%E7%BC%96%E8%AF%91%E5%99%A8/gcc/%E5%8A%A8%E6%80%81%E9%9D%99%E6%80%81%E9%93%BE%E6%8E%A5%E5%BA%93.md)

动态链接库指的是 .so 文件，静态链接库指的是 .a 文件。

动态链接库作用是 **减少程序体积**，静态链接库作用是 **减少程序运行时的开销**。 即动态链接库在编译时不会被链接到程序中，而是在程序运行时才被链接到程序中。 静态链接库在编译时就会被链接到程序中。

## 静态

```makefile
gcc -c file1.c file2.c -o file1.o file2.o
ar rcs libfile.a file1.o file2.o
gcc main.c -L. -lfile -o main
```

## 动态
```makefile
gcc -fPIC -c file1.c file2.c
gcc -shared -o libfile.so file1.o file2.o
gcc main.c -L. -lfile -o main
```