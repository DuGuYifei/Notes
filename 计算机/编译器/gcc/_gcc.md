# gcc

## 跟MinGW的关系
GCC（GNU Compiler Collection）是一个广泛使用的编译器套件，包括多种编程语言的编译器，例如 C、C++、Objective-C、Fortran、Ada、Go 等。它是自由软件，可以在多种操作系统平台上使用。

MinGW（Minimalist GNU for Windows）是在 Windows 平台上使用 GCC 的一个项目。它提供了一个开发环境，包括 GCC 编译器和相关的开发工具，使得在 Windows 上编译和运行基于 GCC 的程序更加方便。

因此，可以说 GCC 不是 MinGW，但 MinGW 是使用 GCC 的一个项目。在 MinGW 中，使用的是 GCC 编译器及其相关工具，但也可以使用其他编译器，例如 Clang。

## g++
`g++` is equivalent to `gcc -xc++ -lstdc++ -shared-libgcc`

## 命令
1. [gcc_g++常用命令](gcc_g++常用命令.md)
2. [-g](-g.md)
3. [-Wall](-Wall.md)
4. [-fPIC](-fPIC.md)
5. [-shared](-shared.md)
6. [动态静态链接库](动态静态链接库.md)