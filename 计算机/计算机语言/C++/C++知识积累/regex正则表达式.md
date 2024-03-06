# regex正则表达式

- leetcoode(正则表达式 存储到vector)
  [力扣](https://leetcode-cn.com/problems/complex-number-multiplication/solution/fu-shu-cheng-fa-by-leetcode-solution-163i/)
  ```cpp
    class Solution {
    public:
        string complexNumberMultiply(string num1, string num2) {
            regex re("\\+|i"); 
            vector<string> complex1(sregex_token_iterator(num1.begin(), num1.end(), re, -1), std::sregex_token_iterator());
            vector<string> complex2(sregex_token_iterator(num2.begin(), num2.end(), re, -1), std::sregex_token_iterator());
            int real1 = stoi(complex1[0]);
            int imag1 = stoi(complex1[1]);
            int real2 = stoi(complex2[0]);
            int imag2 = stoi(complex2[1]);
            return to_string(real1 * real2 - imag1 * imag2) + "+" + to_string(real1 * imag2 + imag1 * real2) + "i";
        }
    };
  ```

- [C++11 正则表达式——实例1 - KingsLanding - 博客园](https://www.cnblogs.com/zhuyp1015/archive/2012/04/08/2438215.html)
    这里对is_email_valid()函数中的正则表达式做一个简短的说明，如果对于正则表示不是很清楚的同学就能很容易理解了。
     const std::regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+"); 首先注意‘()’表示将正则表达式分成子表达式，每个‘()’之间的内容表示一个子表达式；‘\’是一个转义字符，‘\\’表示扔掉第二个‘\’的转义特性，‘\w+’表示匹配一个或多个单词，‘+’表示重复一次或者多次，因此第一个子表达式的意思就是匹配一个或者多个单词；接着看第二个子表达式，‘|’表示选择，出现‘.’或者‘_’，后面的‘?’表示该子表示出现一次或者零次，因此第二个子表示表示‘.’或‘_’出现不出现都匹配。第三个子表达式表示出现一个单词，‘*’表示任意个字符。后面的子表示根据已经介绍的内容，已经可以容易理解，就不再赘述。通过对正则表达式匹配模式串的分析，可以容易理解运行结果。

所以第一个leetcode例子中其实是

`\\+|i` 转义第二个`\`在字符串中，然后转义`+`在正则表达式中，`|`选择是否有虚部。

