import os
from pathlib import Path

def find_images(base_dir):
    # 支持的图片格式列表
    image_extensions = ('.png', '.jpg', '.jpeg', '.gif', '.webp', '.bmp', '.tiff', '.svg')
    images_found = []

    # 遍历根目录及其所有子目录
    for root, dirs, files in os.walk(base_dir):
        # 从目录列表中移除 '_attachments'，避免进入这些目录
        dirs[:] = [d for d in dirs if '_attachments' not in d]

        # 检查每个文件是否是图片
        for file in files:
            if file.lower().endswith(image_extensions):
                images_found.append(Path(root) / file)

    return images_found

# 设置基本目录
base_directory = Path('/path/to/your/directory')  # 修改为你的目录路径
images = find_images(base_directory)

# 打印找到的图片文件
for image in images:
    print(image)
