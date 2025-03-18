# C语言调用

## 调用方式

```go
package main

/*
#include <stdio.h>
#include <stdlib.h>
*/
import "C"

func main() {
    C.puts(C.CString("Hello, World\n"))
}
```

## 2. 通过cgo调用C++语言

```go
package main

/*
#include <iostream>
*/
import "C"

func main() {
    C.std::cout << "Hello, World" << C.std::endl
}
```

## 自定义代码

```go
package main

/*
#include <stdio.h>

void hello() {
    printf("Hello, World\n");
}
*/

import "C"

func main() {
    C.hello()
}
```

自己的文件

```go
package main

// #include "window_utils.h"
import "C"

func main() {
    C.FindWindow("Notepad")
}
```