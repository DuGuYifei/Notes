import os
from pathlib import Path
from urllib.parse import quote

from catalog_ignore import IGNORE_FILES, IGNORE_DIRS


def format_entry_name(full_path: Path) -> str:
    """Show markdown files without extension; keep extension for downloadable files."""
    if full_path.suffix.lower() in {".md", ".markdown"}:
        return full_path.stem
    return full_path.name

def generate_sidebar(path, visible_root):
    ignore_files = IGNORE_FILES
    ignore_dirs = IGNORE_DIRS

    entries = []
    for entry in sorted(os.listdir(path), key=lambda s: (0 if s.startswith('_') else 1, s)):
        full_path = Path(path) / entry
        if entry in ignore_files or any(part in ignore_dirs for part in full_path.parts):
            continue

        if full_path.is_dir():
            # 递归子目录时，visible_root 变为子目录的路径
            # join visible_root and entry
            temp_visible_root = visible_root / entry
            subdir_entries = generate_sidebar(full_path, temp_visible_root)
            if subdir_entries:
                entries.append(f"- {entry}")
                entries.extend([f"    {line.replace('](', f']({entry}/')}" for line in subdir_entries])

        # elif full_path.suffix == ".md":
        else:
            # 相对于 visible_root 计算路径
            rel_path = full_path.relative_to(visible_root).as_posix()
            print(rel_path)
            rel_path = quote(rel_path, safe="/")
            entry_name = format_entry_name(full_path)
            entries.append(f"- [{entry_name}]({rel_path})")

    if entries:
        sidebar_path = Path(path) / "_sidebar.md"
        with open(sidebar_path, "w", encoding="utf-8") as f:
            # 添加返回上级目录, 即 visible_root
            if visible_root != base_path:
                f.write(f"- [返回上级目录](../_sidebar.md)\n")
            f.write("\n".join(entries))

    return entries

# 起始路径
base_path = Path(".")
# 调用时，把当前目录作为 base_path，同时 visible_root 也设置为 base_path
generate_sidebar(base_path, base_path)

# 下载 "https://raw.githubusercontent.com/DuGuYifei/DuGuYifei/main/README.md" 到当前目录 覆盖
os.system("curl -o README.md https://raw.githubusercontent.com/DuGuYifei/DuGuYifei/main/README.md")
