(
git stash push -u
git pull
git stash pop
git add .
git commit --amend --no-edit
git push origin master -f
)
