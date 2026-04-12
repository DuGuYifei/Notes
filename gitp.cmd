(
git stash push -u
git pull
git stash pop
git add .
git commit -m "%date% %time:~0,8%"
git push origin master
)
