# itoa和iota

## iota
数组赋值
[iota生成顺序递增序列](iota生成顺序递增序列.md)

## itoa
整数转字符串
```cpp
/* itoa example */
#include <stdio.h>
#include <stdlib.h>

int main ()
{
  int i;
  char buffer [33];
  printf ("Enter a number: ");
  scanf ("%d",&i);
  itoa (i,buffer,10);
  printf ("decimal: %s\n",buffer);
  itoa (i,buffer,16);
  printf ("hexadecimal: %s\n",buffer);
  itoa (i,buffer,2);
  printf ("binary: %s\n",buffer);
  return 0;
}


//output
Enter a number: 1750
decimal: 1750
hexadecimal: 6d6
binary: 11011010110
```