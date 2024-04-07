`size_t`类型是一个无符号整型，由`typedef`定义而来。
在C标准头文件`<stddef.h>`中实际定义
```c
#define __SIZE_TYPE__ long unsigned int 
typedef __SIZE_TYPE__ size_t;
```
> 代码清单：<stddef.h> 中的 size_t

在我个人的机器上，size_t的真面目即：long unsigned int。

查阅相关文档后了解到，`size_t`的含义是_size type_，是一种**计数类型**。取值范围与机器架构与操作系统相关。32 位机器一般是`unsigned int`，占 4 字节；而 64 位机器一般是`unsigned long`，占 8 字节。

`size_t`类型常被用作计数用途，例如：`sizeof`运算符得到对象所占的字节数；字符串函数`strlen`返回字符串的长度等等，其返回值都为`size_t`类型。

`size_t`类型隐含着**本机理论所能容纳建立最大对象的字节数大小**的含义，因此常被用于数组索引、内存管理函数中。

最初设计`size_t`类型初衷，是为了程序的跨平台兼容性考虑。

## `size_t`小陷阱
在 Google 搜索的时候，还发现了一个非常有趣的案例。

```
#include <stdio.h>
#include <string.h>

int main(void) {
    int i = -1;
    if (i < strlen("hello")) {
        printf("Hello, World\n");
    } else {
        printf("Hello, ziheng\n");
    }
    return 0;
}
```

> 代码清单：`size_t` 陷阱

```
$ gcc test.c && ./a.out
Hello, ziheng
```

> 代码清单：`size_t` 程序执行结果

上述代码编译执行后，程序打印出了`else`分支语句`Hello, ziheng`，这似乎与预想的有些不同。

实际上，这段代码的`if`条件比较中触发了 C 语言**隐式自动类型转换**机制，`size_t`实际类型为`unsigned long int`，而带符号整型变量`i`与`size_t`比较时会被类型提升自动转换为无符号整型`unsigned int`，数值`-1`转化无符号整型数是`4294967295`，远大于字符串长度`5`。

**带符号数和无符号数之间的运算操作，请一定小心。**

## 参考资料
+ ziheng's Blog: https://zihengcat.github.io/2017/06/02/c-learning-notes-understanding-size_t/
- 官方文档: [http://en.cppreference.com/w/c/types/size_t](http://en.cppreference.com/w/c/types/size_t)
- `size_t`小陷阱案例: [http://demon.tw/programming/c-size_t-pitfall.html](http://demon.tw/programming/c-size_t-pitfall.html)