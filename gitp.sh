git add .
WEEKDAY=$(date '+%a')
case $WEEKDAY in
  Mon) CN_WEEKDAY="周一";;
  Tue) CN_WEEKDAY="周二";;
  Wed) CN_WEEKDAY="周三";;
  Thu) CN_WEEKDAY="周四";;
  Fri) CN_WEEKDAY="周五";;
  Sat) CN_WEEKDAY="周六";;
  Sun) CN_WEEKDAY="周日";;
esac
git commit -m "$(date '+%Y/%m/%d') $CN_WEEKDAY $(date '+%H:%M:%S')"
git push origin master