import os
import shutil
from pathlib import Path

def move_and_update_images(base_dir):
    # 遍历当前目录及子目录
    for current_dir, dirs, files in os.walk(base_dir):
        # 直接修改遍历中的 dirs 列表，以跳过 _attachments 文件夹
        if '_attachments' in dirs:
            dirs.remove('_attachments')
        if '.git' in dirs:
            dirs.remove('.git')

        for file in files:
            # 检查文件是否是图片格式
            if file.lower().endswith(('.png', '.jpg', '.jpeg', '.gif', '.webp', '.bmp', '.tiff', '.svg')):
                file_path = Path(current_dir) / file
                # 确定 _attachments/old 目录
                target_dir = Path(current_dir) / '_attachments/old'
                target_dir.mkdir(parents=True, exist_ok=True)
                # 移动图片
                new_path = target_dir / file
                shutil.move(str(file_path), str(new_path))
                # 更新同目录下的 Markdown 文件中的链接
                update_links(current_dir, file)

def update_links(dir_path, old_filename):
    # 收集当前目录下的所有 Markdown 文件
    markdown_files = list(Path(dir_path).glob('*.md'))

    for md_file in markdown_files:
        # 读取 Markdown 文件内容
        with open(md_file, 'r', encoding='utf-8') as file:
            content = file.read()
        
        # 构造新的链接路径
        new_file_link = f'_attachments/old/{old_filename}'
        # 更新链接
        new_content = content.replace(old_filename, new_file_link)
        
        # 写回文件
        with open(md_file, 'w', encoding='utf-8') as file:
            file.write(new_content)

# 设置基本目录
base_directory = Path('.')  # 使用当前目录
move_and_update_images(base_directory)
