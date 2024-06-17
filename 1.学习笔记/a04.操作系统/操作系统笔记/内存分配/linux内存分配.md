---
title: Linux内存分配
date: {{ date }}
top: false
cover: false
password:
toc: true
mathjax: true
summary:
tags: 
- 操作系统
- 内存管理
categories: [操作系统]
---



本文引用自[小林malloc是如何分配内存的](https://xiaolincoding.com/os/3_memory/malloc.html#linux-%E8%BF%9B%E7%A8%8B%E7%9A%84%E5%86%85%E5%AD%98%E5%88%86%E5%B8%83%E9%95%BF%E4%BB%80%E4%B9%88%E6%A0%B7)

# Linux内存分配

## Linux进程的内存分布

Linux操作系统中，虚拟地址空间内部分为内核空间和用户空间两部分。

![image-20230322201744530](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20230322201744530.png)

每个虚拟内存中的内核地址，其实关联的是相同的物理地址

![image-20230322201837525](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20230322201837525.png)

以32位系统为例，用户空间从低到高分别是6种不同的内存段

![image-20230322201932059](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20230322201932059.png)

+ 代码段，包括二进制可执行代码
+ 数据段，包括已初始化的静态常量和全局变量
+ BSS段，包括未初始化的静态变量和全局变量
+ 堆段，包括动态分配的内存，从低地址开始向上增长
+ 文件映射段，包括动态库、共享内存等，从低地址开始向上增长（跟硬件和内核版本有关）
+ 栈段，包括局部变量和函数调用的上下文等。栈的大小是固定的，一般是8MB。系统也提供参数自定义大小。

在这6个内存段中，堆和文件映射段的内存是动态分配的。比如，使用C标准库的`malloc()`或者`mmap()`，就可以分别在堆和文件映射段动态分配内存。



## malloc是如何分配内存的？

malloc不是系统调用，而是C库中的函数

其有两种方式向操作系统申请堆内存

+ 方式一：通过brk()系统调用从堆分配内存
+ 方式二：通过mmap()系统调用从文件映射区域分配内存

方式一，通过brk()函数将堆顶指针向高地址移动，获得新的内存空间。

![image-20230322203217619](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20230322203217619.png)

方式二，通过mmap()系统调用中【私有匿名映射】的方式，在文件映射区分配一块内存。

![image-20230322203323290](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20230322203323290.png)

malloc()源码中默认定义了一个阈值：

+ 如果用户分配的内存小于128KB，则通过brk()申请内存；
+ 如果用户分配的内存大于128KB，则通过mmap()申请内存。

注意，不同的glibc版本定义的阈值也不相同



## malloc()分配的是物理内存吗？

不是的，malloc()分配的是虚拟内存。

如果分配后的虚拟内存没有被访问的话，虚拟内存是不会映射到物理内存的，这样就不会占用物理内存了。

只有在访问已分配的虚拟地址空间的时候，操作系统通过查找页表，发现虚拟内存对应的页没有在物理内存中，就会触发缺页中断，然后操作系统会建立虚拟内存和物理内存之间的映射关系。



## malloc(1)会分配多大的虚拟内存？

malloc()在分配内存的时候，会预分配更大的空间作为内存池

具体预分配多大的内存，跟malloc使用的内存管理器有关，以malloc默认的内存管理器（Ptmalloc2）来分析。

```c
#include <stdio.h>
#include <malloc.h>

int main(){
    printf("使用cat /proc/%d/maps查看内存分配\n", getpid());
    
    //申请1字节的内存
    void *addr = malloc(1);
    printf("此1字节的内存起始地址：%x\n", addr);
    printf("使用cat /proc/%d/maps查看内存分配\n", getpid());
    
    //将程序阻塞，当输入任意字符是才往下执行
    getchar();
    
    //释放内存
    free(addr);
    printf("释放了1字节的内存，但heap堆并不会释放\n");
    getchar();
    return 0;
}
```

![image-20230322213656213](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20230322213656213.png)

![image-20230322213643726](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20230322213643726.png)

堆分配的地址从73c000-75d000（这里的单位是字节），这个范围大小是132KB，也就说明了malloc(1)实际上预分配了132KB字节的内存。

## free释放内存，会归还给操作系统吗？

并没有，这是因为与其把这1字节归还给操作系统，不如先缓存进malloc的内存池里。

如果malloc通过mmap方式申请内存，free释放内存后就会归还给操作系统

```c
#include <stdio.h>
#include <malloc.h>

int main(){
    printf("使用cat /proc/%d/maps查看内存分配\n", getpid());
    
    //申请1字节的内存
    void *addr = malloc(128*1024);
    printf("此1字节的内存起始地址：%x\n", addr);
    printf("使用cat /proc/%d/maps查看内存分配\n", getpid());
    
    //将程序阻塞，当输入任意字符是才往下执行
    getchar();
    
    //释放内存
    free(addr);
    printf("释放了128字节的内存，内存也归还给了操作系统\n");
    getchar();
    return 0;
}
```



## 为什么不全部使用mmap来分配内存？

频繁通过mmap分配内存的话，不仅每次都会发生运行态的切换，还会发生缺页中断（在第一次访问虚拟内存后），这样会导致CPU消耗大

为了改进这两个问题，malloc通过brk()系统调用在堆空间申请内存的时候，由于堆空间是连续的，所以直接预分配更大的内存来作为内存池，当内存释放的时候，就缓存在内存池中。

等下次在申请内存的时候，就直接从内存池中取出对应的内存块就行，而且可能这个内存块的虚拟地址与物理地址的映射关系还存在，这样不仅减少了系统调用，也减少了缺页中断的次数，大大降低了CPU的消耗。



## 为什么不全部使用brk来分配？

![image-20230322221933468](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20230322221933468.png)

如果全部使用brk，系统频繁地malloc和free，内存不会归还给系统，堆内会产生大量不可用的碎片，导致”内存泄漏“，这种”泄漏“现象是使用valgrind无法检测出来的。

## free()函数只传入一个内存地址，如何知道释放多大的内存？

签名malloc 返回给用户态的内存起始地址比进程的堆空间起始地址多了 16 字节，这16 字节就是保存了该内存块的描述信息，比如有该内存块的大小。

![image-20230322222032300](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20230322222032300.png)

这样当执行 free() 函数时，free 会对传入进来的内存地址向左偏移 16 字节，然后从这个 16 字节的分析出当前的内存块的大小，自然就知道要释放多大的内存了。