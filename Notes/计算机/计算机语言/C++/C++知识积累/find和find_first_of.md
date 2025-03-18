# find和find_first_of

1. find 查找子串
2. find_first_of 查找和字串任意字符相等的第一个位置 (效率很高)

`words[j].find(words[i]) != string::npos`

* find会返回发现子字符串的index（从0开始）
* 如果没发现返回4294967295
* string::npos = 4294967295

[string的函数](string的函数.md)