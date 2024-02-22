# 一、实验介绍

#### 1.1 实验简介

`ls` 命令用来显示目标列表，在 Linux 中是使用率较高的命令。`ls` 的命令很简单，正确快捷的使用 `ls` 的自带参数能够帮我们我们更加轻松的完成所需要做的事情。本课程从讲解 `ls` 命令用法到原理，从原理到实现，更加深入理解文件，命令内部所发生的事情

常用参数：

> `-l`：以长格式显示目录下的内容列表。输出的信息从左到右依次包括文件名，文件类型、权限模式、硬连接数、所有者、组、文件大小和文件的最后修改时间等;
> `-a`：显示所有档案及目录；
> `-r`：以文件名反序排列并输出目录内容列表；
> `-t`：用文件和目录的更改时间排序；
> `-R`：递归处理，将指定目录下的所有文件及子目录一并处理；
> `-r`：以文件名反序排列并输出目录内容列表；

常用参数组合：

> `ls -rtl` ：非常实用，反向按时间排序，通常我们需要查看一个目录下面最近修改的文件，在面临很多文件的时候，可以用这条命令很快的将最近修改的文件列在前面几行
> `ls --full-time`：非常实用，在写一些shell脚本的时候需要获取文件被更新的时间，可以用`ls`的列出完整的日期与时间，获取时间细微的变化

更多请参考: http://man.linuxde.net/ls

#### 1.2 知识点

- Linux 下的 `ls` 实现原理
- C 语言基础
- 文件，目录结构体（dirent 和 stat）
- `readdir` 系统函数调用
- `opendir` 系统函数调用

#### 1.3 实验环境

- Xfce 终端
- GCC
- Gedit

#### 1.4 适合人群

本课程适合有 C 语言基础，理解 Linux 系统中 `ls` 命令的实现过程和相关知识，做一些有趣的事情。

#### 1.5 代码获取

你可以通过下面命令将本课程里的所有源代码下载到实验楼环境中，作为参照对比进行学习。

```bash
wget http://labfile.oss.aliyuncs.com/courses/439/source_code.zip
unzip source_code.zip
```

**请尽量按照实验步骤自己写出 C 语言程序，请确认文件保存在目录：“/home/shiyanlou/source_code/” 下。**

# 二、实验步骤

在 Unix/Linux 的文件系统中，所有东西的储存形式都是文件（一切皆文件的理念）。这样的话，在磁盘上的这一棵目录树上，每一个节点只有两种情况，要么是文件，要么是目录。
不像 Winodws 那样有驱动器，分区之类。这样的目录结构让 `ls` 的实现变得简单和容易理解。

![1-2-1](https://doc.shiyanlou.com/document-uid100000labid1456timestamp1446609390458.png)

## 2.1 ls 原理

输入 `ls` ，输出一个文件名的列表，它大致是这样工作的：

![1-2.1-1](https://doc.shiyanlou.com/document-uid100000labid1456timestamp1446609788102.png)

> - 打开一个目录
> - 从入口开始读取
>   - 展示文件
> - 关闭目录

然后我们看，可以用哪些函数，实现对于目录的操作

> ```c
> opendir //打开一个目录，成功则返回DIR*型态的目录流，打开失败则返回NULL
> readdir //读取目录 readdir 返回一个指向目录的当前记录的指针，记录的类是 struct dirent 这个结构定义 /usr/include/dirent.h
> closedir //关闭目录
> ```

## 2.2 ls 的实现

首先来看一看目录的结构体（位于 /usr/include/x86_64-linux-gnu/bits/dirent.h）。查看目录的结构体定义，看看计算机理解的“目录”是什么样子的。

> ```c
> struct dirent {
>        ino_t          d_ino;         /* inode number */
>        off_t          d_off;         /* offset to the next dirent */
>        unsigned short d_reclen;      /* length of this record */
>        unsigned char  d_type;        /* type of file; not supportedby all file system types */
>        char           d_name[256];   /* filename */
> };
> ```

我们需要的就是 d_name，也就是目录的名字。 **编写源程序 ls1.c：**

```c
/*这里关于main函数的参数，ac包括程序本身的参数个数，av是参数名*/
/*************************************************************************
    > File Name: ls1.c
    > Author: 
    > Mail: 
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<dirent.h>

void do_ls(char[]);

main(int ac, char *av[])
{
    if(ac==1)
    do_ls(".");
    else
    while(--ac){
        printf("%s:\n",*++av);
        do_ls(*av);
    }
}

void do_ls(char dirname[])
{
/*请同学们参考 1.5 节的下载链接在这里补全代码，所用的代码和知识点在 2.2 节已给出.*/
}
```

编译后运行结果如下：

![1-2.2-1](https://doc.shiyanlou.com/document-uid735639labid1456timestamp1528267929138.png)

## 2.3 ls -l 的实现

#### 2.3.1 查看文件属性

那么，如果我们需要更多的信息呢？如果获取文件的属性呢？磁盘上的文件有很多属性，如文件大小，文件素有这的 ID 等。 我们先来学习一下文件的结构体 :

> 关于目录中文件的属性等信息使用 `struct stat` 结构体来描述的，其结构的定义如下：（位于 /usr/include/x86_64-linux-gnu/bits/stat.h）
>
> > ```c
> > /*由于这个结构体比较大，我们选取比较关键的几个结构讲解,同学们可以用locate找到这个stat.h文件进行查看  
> > 该结构体提供了关于文件(或者设备)的如下重要信息：*/
> > struct stat
> > {
> >     __dev_t st_dev;                 /* Device. */
> >     __mode_t  st_mode;              /* 文件类型和许可权限 */
> >     __nlink_t st_nlink;             /* 文件链接数 */
> >     __uid_t   st_uid;               /* 文件属主id */
> >     __gid_t   st_gid;               /* 文件属主所在组的id*/
> >     __dev_t   st_rdev;              /* 文件的字节数*/
> >     unsigned short int __pad2;      /* 用于填充对齐 */
> >     __blkcnt_t  st_blocks;          /* 文件所占的块数 */
> > 
> >     struct timespec st_atim;        /* 文件最后访问时间 (access time) */
> >     struct timespec st_mtim;        /* 文件最后修改时间 (modification time)*/
> >     struct timespec st_ctim;        /* 文件属性/状态最后改变的时间 (change status time) */
> >     
> >     ...
> > }
> > ```

如果需要得到文件属性，进程可以定义一个 struct stat，然后调用 stat，告诉内核把文件属性放到这个结构中。 stat 把文件 fname 的信息复制到指针 bufp 所指的结构中。

**编写源程序 fileinfo.c：**

```c
/*************************************************************************
    > File Name: fileinfo.c
    > Author: 
    > Mail: 
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>

int main(int argc,char *argv[])
{
    struct stat info;

    if(argc>1)
        if(stat(argv[1],&info)!=-1){
            show_stat_info(argv[1],&info);
            return 0;
        }
    else
        perror(argv[1]);     /*report stat() error*/
    
    return 1;
}

show_stat_info(char * fname,struct stat *buf)
{
/*请同学们参考 1.5 节的下载链接在这里补全代码，所用的代码和知识点在 2.3.1 节已给出.*/
}
```

编译后运行结果如下：

![1-2.3.1-1](https://doc.shiyanlou.com/document-uid735639labid1456timestamp1528267980092.png)

XXX 作为参数，直接输入你需要查看文件属性的文件名

#### 2.3.2 查看用户权限

经过上面的练习，我们似乎明白了 `ls -l` 的工作原理，这里还有我们发现了一个比较重要的地方

```
-rw-rw-r--
```

这个是 Linux 下对于不同用户的权限展示，分别是用户，用户组，所有组在 stat 结构体中，也就是用 mode 这个字段进行存储的

> 它是一个 16 位的二进制数，前 4 位用作文件类型，1 代表具有某个属性，0 代表没有；
>
> 接下来的3位分为 user-ID，set-group-ID 位和 sticky 位，最后9位是许可权限，分三组，每组 3 位；
>
> 这里使用了`掩码`的技术来划分，就跟ip中的子网掩码一样比如把2进制的 100000110110100 分成 1,000,000,110,110,110。 从而得到8进制的 100664。

对2 进制进行位与操作，这也是我们所说的解码。代码如下（判断目录）

> ```c
> if((info.st_mode&0170000)==0040000)
>     printf("this is a directory");
> ```

用宏定义去代替以上代码：

> ```c
> #define S_ISFIFO(m)  (((m)&(0170000))==(0040000))
> #define S_ISDIR(m)  (((m)&(0170000))==(0020000))
> #define S_ISCHR(m)  (((m)&(0170000))==(0060000))
> #define S_ISBLK(m)  (((m)&(0170000))==(0100000))
> ```

> ```c
> if(S_ISDIR(info.st_mode))
>     printf("this is a directory");
> ```

#### 2.3.3 编写 ls2.c

有关于 uid_to_name 和 gid_to_name 这个两个函数的实现简单调用了 pwd.h 的函数，可以先查看结构体然后编写，学习方法与上面相同：

**编写源程序 ls2.c：**

```c
#include<stdio.h>
#include<sys/types.h>
#include<dirent.h>
#include<sys/stat.h>

void do_ls(char[]);
void dostat(char *);
void show_file_info(char *,struct stat *);
void mode_to_letters(int ,char[]);
char * uid_to_name(uid_t);
char * gid_to_name(gid_t);

main(int argc,char *argv[])
{
    if(argc==1)
        do_ls(".");
    else
    while(--argc){
        printf("%s:\n",*++argv);
        do_ls;
    }
}

/*请同学们参考 1.5 节的下载链接在这里补全代码，所用的代码和知识点在 2.3 节已给出.*/
```

如果加 -l 参数，那么会分栏显示出，每个文件的详细信息，每一行都代表了一个文件和它的属性。编译后运行结果如下：

![1-2.3.3-1](https://doc.shiyanlou.com/document-uid735639labid1456timestamp1528268016942.png)

# 三、实验总结

本课程由浅入深的讲解了 `ls` 的实现过程，先讲了最基本的 `ls`，然后加入查看文件属性功能，再加入了权限展示的功能，学习了 C 语言对于系统函数的调用。一个 `ls` 命令看起来很简单，其实是很复杂的。在平时使用的过程的中觉得很方便，甚至感觉不到内部的运转，是因为 Linux 的结构和设计比较巧妙，多学甚意。

#### 参考资料

[《UNIX环境高级编程》](https://book.douban.com/subject/1788421/)

