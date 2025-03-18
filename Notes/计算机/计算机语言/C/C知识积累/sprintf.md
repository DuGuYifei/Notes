# sprintf

## 作用

将格式化的数据写入某个字符串中

## 1. 用法

```c
int sprintf(char *str, const char *format, ...);
```

## 2. 例子

```c
#include <stdio.h>
#include <string.h>

int main()
{
	char str[100];
	int i = 65;
	float f = 123.456;
	sprintf(str, "Integer: %d, float: %f", i, f);
	printf("String: %s\n", str);
	printf("Length: %d\n", strlen(str));
	return 0;
}
```

## 3. 输出

```
String: Integer: 65, float: 123.456001
Length: 27
```

