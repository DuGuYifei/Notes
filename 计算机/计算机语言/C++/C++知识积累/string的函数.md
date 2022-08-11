# string的函数 

## string.substr(start, size)
string.substr(start)

## str.append()

其中`str.append(size,char)`注意`size和char`的顺序

## str.c_str()
[将string转为char* str.c_str()](string转为constchar星指针c_str().md)

## str.find(s)
[find和find_first_of](find和find_first_of.md)

`words[j].find(words[i]) != string::npos`

* find会返回发现子字符串的index（从0开始）
* 如果没发现返回4294967295
* string::npos = 4294967295

## find_first_of
[find和find_first_of](find和find_first_of.md)

## str.rfind(s)

## accumulate
[accumulate](accumulate.md)