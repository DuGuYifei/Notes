#
# @lc app=leetcode.cn id=194 lang=bash
#
# [194] 转置文件
#
# https://leetcode-cn.com/problems/transpose-file/description/
#
# shell
# Medium (34.74%)
# Likes:    69
# Dislikes: 0
# Total Accepted:    14.1K
# Total Submissions: 40.8K
# Testcase Example:  'a'
#
# 给定一个文件 file.txt，转置它的内容。
#
# 你可以假设每行列数相同，并且每个字段由 ' ' 分隔。
#
#
#
# 示例：
#
# 假设 file.txt 文件内容如下：
#
#
# name age
# alice 21
# ryan 30
#
#
# 应当输出：
#
#
# name alice ryan
# age 21 30
#
#
#

# @lc code=start
# Read from the file file.txt and print its transposed content to stdout.
awk '{
        for (i=1;i<=NF;i++){
            if (NR==1){
                res[i]=$i
            }
            else{
                res[i]=res[i]" "$i
            }
        }
    }END{
        for(j=1;j<=NF;j++){
            print res[j]
        }
    }' file.txt
# @lc code=end
