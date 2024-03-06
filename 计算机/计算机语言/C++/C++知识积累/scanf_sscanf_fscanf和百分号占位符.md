# scanf_sscanf_fscanf和百分号占位符

## scanf fscanf sscanf
scanf 从控制台输入 
fscanf 从文件输入
sscanf 从指定字符串输入

1. 常用的总结如下：
（1）%[0-9]表示只读入’0’到’9’之间的字符

（2）%[a-zA-Z]表示只读入字母

（3）%[^a-z]就表示读入小写字母之外的字符。 ^表示除XXX之外。

（4）"%n[^=]" 读入"="号前的至多n 个字符

（5）在符号前面加^，比如 “%[^：]” 就是除了冒号其他字符都可以输入，唯独忽略冒号，可输入的字符是除去冒号的字符集补集。
'-'是范围连接符，当然也可以直接列出需要读入的字符。
2. 其他

%c 一个单一的字符
%d 一个十进制整数
%i 一个整数
%e, %f, %g 一个浮点数
%o 一个八进制数
%s 一个字符串
%x 一个十六进制数
%p 一个指针
%n 一个等于读取字符数量的整数
%u 一个无符号整数
%[] 一个字符集
%% 一个精度符号

```cpp
public:
    vector<int> exclusiveTime(int n, vector<string>& logs) {
        stack<pair<int, int>> run;
        for(auto& i : logs)
        {
            int idx, timestamp;
            char type[6];
            sscanf(i.c_str(), "%d:%[^:]:%d", &idx, type, &timestamp);
        }
    }
```

