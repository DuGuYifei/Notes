import os
from pathlib import Path

config = {
    "IgnoreFile": [
        "gitp.cmd", "gitp.sh", "gitpf.cmd", "_sidebar.md", "README.md", ".gitignore"
    ],
    "IgnoreDir": [
        ".git",
        "_attachments",
        "MyGameDesign",
        "images",
        "vue学习用案例模板",
    ],
    "IgnoreDirNameContain": [
    ]
}

def generate_sidebar(base_dir):
    base_dir = Path(base_dir)

    def recurse_folder(current_path, level=0):
        sidebar_content = []
        # 获取所有文件和文件夹，除去忽略的文件和文件夹
        items = [item for item in current_path.iterdir() if item.name not in config['IgnoreFile'] and not any(dir_name in item.parts for dir_name in config['IgnoreDir'])]
        items.sort(key=lambda x: (x.is_file(), x.name.lower()))  # 文件夹优先，然后按字母顺序

        for item in items:
            # 检查是否需要跳过包含特定文本的文件夹
            if item.is_dir() and any(ignored in item.name for ignored in config['IgnoreDirNameContain']):
                continue

            prefix = '    ' * level if level > 0 else ''  # 最外层没有缩进，子层级缩进
            if item.is_dir():
                # 文件夹名（不创建链接）
                folder_name = f"{item.name}/"
                sidebar_content.append(f"{prefix}- {folder_name}")
                # 递归遍历文件夹
                child_content = recurse_folder(item, level + 1)
                sidebar_content.extend(child_content)
            else:
                # 添加文件链接
                link_name = item.name
                path_link = item.relative_to(current_path).as_posix()
                sidebar_content.append(f"{prefix}- [{link_name}]({path_link})")

        # 写入_sidebar.md到当前文件夹
        sidebar_path = current_path / '_sidebar.md'
        with open(sidebar_path, 'w', encoding='utf-8') as f:
            f.write('\n'.join(sidebar_content))

        # 重新打开文件，对每行去掉第一行前面的空格数
        print(f"Generate sidebar for {current_path}")
        space_count_in_first_line = 0
        with open(sidebar_path, 'r', encoding='utf-8') as f:
            lines = f.readlines()
            space_count_in_first_line = len(lines[0]) - len(lines[0].lstrip())
        with open(sidebar_path, 'w', encoding='utf-8') as f:
            for line in lines:
                f.write(line[space_count_in_first_line:])

        # 在第一行添加返回上一级目录
        if level > 0:
            with open(sidebar_path, 'r', encoding='utf-8') as f:
                content = f.read()
            with open(sidebar_path, 'w', encoding='utf-8') as f:
                f.write(f"- [返回上级目录](../)\n\n")
                f.write(content)
        
        return sidebar_content

    recurse_folder(base_dir)

# 设置基本目录
base_directory = '.'  # 使用当前目录
generate_sidebar(base_directory)

print(f"Sidebar generated for each directory in {base_directory}")
