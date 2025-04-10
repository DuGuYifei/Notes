# Git下载某个版本的某个文件夹

```cmd
# 克隆仓库（不拉内容）
git clone --filter=blob:none --no-checkout git@github.com:DuGuYifei/Notes.git
cd Notes

# 初始化 sparse-checkout
git sparse-checkout init --cone

# 设定要拉取的目录
git sparse-checkout set Projects

# 切换到指定 commit
git checkout eda47d946884d00dbe061f4684d01183b0ec6310
```