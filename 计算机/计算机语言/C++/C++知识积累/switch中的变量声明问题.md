# switch中的变量声明问题
swith中不能直接声明变量的赋值只能:
1. 分开：
    ```cpp
    class Solution
    {
    public:
        int calPoints(vector<string> &ops)
        {
            int ans = 0;
            vector<int> points;
            for (string& op:ops)
            {
                switch (op[0])
                {
                case '+':
                    int n;
                    n = points.size();
                    int temp;
                    temp = points[n - 1] + points[n - 2];
                    points.push_back(temp);
                    ans += temp;
                    break;
                case 'D':
                    temp  = 2 * points[points.size() - 1];
                    points.push_back(temp);
                    ans += temp;
                    break;
                case 'C':
                    ans -= points[points.size() - 1];
                    points.pop_back();
                    break;
                default:
                    temp = stoi(op);
                    points.push_back(temp);
                    ans += temp;
                    break;
                }
            }
            return ans;
        }
    };
    ```
2. 用大括号，形成新的作用域
    ```cpp
    class Solution
    {
    public:
        int calPoints(vector<string> &ops)
        {
            int ans = 0;
            vector<int> points;
            for (string& op:ops)
            {
                switch (op[0])
                {
                case '+':
                    {
                        int n = points.size();
                        int temp = points[n - 1] + points[n - 2];
                        points.push_back(temp);
                        ans += temp;
                        break;
                    }
                case 'D':
                    {
                        int temp = 2 * points[points.size() - 1];
                        points.push_back(temp);
                        ans += temp;
                        break;
                    }
                case 'C':
                    ans -= points[points.size() - 1];
                    points.pop_back();
                    break;
                default:
                    {
                        int temp = stoi(op);
                        points.push_back(temp);
                        ans += temp;
                        break;
                    }
                }
            }
            return ans;
        }
    };
    ```