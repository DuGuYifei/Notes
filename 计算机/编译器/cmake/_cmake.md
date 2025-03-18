# cmake

```
# Require a specific CMake version, here 3.20 for C++23 support
cmake_minimum_required(VERSION 3.20)
# Set project name, required for every project
project(hello2)
# We use C++23, basically adds -std=c++23 to compiler flags
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Compile executable hello2 from hello2.cpp
add_executable(hello2 hello2.cpp)
```

```sh
$ mkdir build; cd build # create separate build directory
$ cmake ..
$ cmake --build .
$ ./hello2
```

- add_executable(myprogram a.cpp b.cpp)

  定义一个可执行文件，该可执行文件由源文件 a.cpp 和 b.cpp 构建。

- add_compile_options(-Wall -Wextra)

  添加 -Wall 和 -Wextra 到编译标志。

- set(CMAKE_CXX_COMPILER clang++)

  设置 C++ 编译器为 clang++。

- set(CMAKE_BUILD_TYPE Debug)

  设置“构建类型”为 Debug（其他值：Release、RelWithDebInfo）；影响优化和调试信息。

可以在命令行调用 CMake 时设置变量：

cmake .. -DCMAKE_BUILD_TYPE=RelWithDebInfo