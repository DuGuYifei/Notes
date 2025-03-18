# vscode和wsl配置cpp环境

1. 安装wsl
    ```cmd
    wsl --install
    ```
2. 安装ubuntu/fedora等
3. 使用`code .`自动安装vscode
4. 在vscode的wsl中安装:`c/c++`,`code runner`。
5. 在fedora中
    ```bash
    dnf install -y clang llvm clang-tools-extra cmake git gtest-devel libasan libubsan python3-lit diffutils && dnf clean all
    ```