在操作系统和编程中，`uint8_t`, `uint16_t`, `uint32_t`, 和 `uint64_t` 这些类型的出现，主要是为了解决数据类型在不同平台上的一致性问题。不同平台（如32位和64位操作系统）的基本整数类型（如 `int` 和 `long`）可能有不同的大小。为了确保跨平台代码的一致性和可移植性，标准库提供了这些明确大小的类型。

## uint8_t / uint16_t / uint32_t / uint64_t 是什么

这些类型是标准整数类型的别名，它们确保无论在哪个平台上，其表示的整数大小都是一致的。这些类型是通过 `typedef` 在 C 语言中定义的。例如，`uint8_t` 保证是一个无符号的8位（1字节）整数。

## uint8_t / uint16_t / uint32_t / uint64_t  占用几个字节

- `uint8_t`：占用 1 个字节，表示 8 位无符号整数。
- `uint16_t`：占用 2 个字节，表示 16 位无符号整数。
- `uint32_t`：占用 4 个字节，表示 32 位无符号整数。
- `uint64_t`：占用 8 个字节，表示 64 位无符号整数。

## 类型定义

C99标准的C语言硬件为我们定义了这些类型。 按照posix标准，一般整形对应的`*_t`类型，
具体定义在：`/usr/include/stdint.h`    ISO C99: 7.18 Integer types <stdint.h>
```c
/* Unsigned.  */  

typedef unsigned char           uint8_t;  

typedef unsigned short int      uint16_t;  

#ifndef __uint32_t_defined  

typedef unsigned int            uint32_t;  

# define __uint32_t_defined  

#endif  

#if __WORDSIZE == 64  

typedef unsigned long int       uint64_t;  

#else  

__extension__  

typedef unsigned long long int  uint64_t;  

#endif
```