#include <string>
using namespace std;
/*
 * @lc app=leetcode.cn id=71 lang=cpp
 *
 * [71] 简化路径
 */

// @lc code=start
class Solution
{
public:
    string simplifyPath(string path)
    {
        string newPath = "";
        for (int i = 0; i < path.length(); i++)
        {
            if (path[i] == '/' && path[i + 1] == '/')
                continue;
            if (path[i] == '/')
            {
                newPath.append("/");
                if (newPath.size() > 1 && newPath[newPath.size() - 2] == '/')
                    newPath.pop_back();
            }
            else if (path[i] == '.' && path[i - 1] == '/')
            {
                if (path[i + 1] == '/' || path[i + 1] == '\0')
                {
                    i++;
                    continue;
                }
                if (path[i + 1] == '.' && (path[i + 2] == '/' || path[i + 2] == '\0'))

                {
                    if (newPath.size() != 1)
                    {
                        newPath.pop_back();
                        for (int j = newPath.size() - 1; newPath[j] != '/'; j--)
                        {
                            newPath.pop_back();
                        }
                    }
                    i += 2;
                    continue;
                }

                while (path[i] != '/' && path[i] != '\0')
                {
                    newPath.append(1, path[i]);
                    i++;
                }
                i--;
                continue;
            }
            else if (path[i] == '\0' && newPath[newPath.length() - 1] == '/')
                newPath.pop_back();
            else
                newPath.append(1, path[i]);
        }

        if (newPath == "")
            newPath.append(1, '/');
        else if (newPath[newPath.length() - 1] == '/' && newPath.length() != 1)
        {
            newPath.pop_back();
        }

        return newPath;
    }
};
// @lc code=end
