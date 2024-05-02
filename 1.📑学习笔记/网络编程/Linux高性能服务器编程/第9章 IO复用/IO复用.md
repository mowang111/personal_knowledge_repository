---
title: IO复用
date: {{ date }}
top: false
cover: false
password:
toc: true
mathjax: true
summary:
tags: [Linux高性能服务器编程] 
categories: []

---



+ 客户端程序要同时处理多个socket
+ 客户端程序要同时处理用户输入和网络连接
+ TCP服务器要同时处理监听socket和连接socket
+ 服务器要同时监听多个端口，或处理多种服务

I/O复用虽然能同时监听多个文件描述符，但是其本身是阻塞的。如果要实现并发，只能使用多进程或多线程。

Linux下实现I/O复用的系统调用主要是select、poll和epoll。

# select

在一段指定时间内，监听用户感兴趣的文件描述符上的可读、可写和异常等事件。

```C++
#include <sys/select.h>
int select( int nfds, fd_set* readfds, fd_set* writefds, fd_set* exceptfds, struct timeval* timeout );
```

nfds通常被设置为select监听的所有文件描述符中的最大值+1，因为文件描述符是从0开始计数的。

fd_set结构体中仅包含一个整型数组，该数组的每个元素的每一位（bit）标记一个文件描述符。fd_set能容纳的文件描述符数量由FD_SETSIZE指定，这就限制了select能同时处理的文件描述符的总量。

```c++
#incldue <sys/select.h>
FD_ZERO( fd_set* fdset);
FD_SET( int fd, fd_set* fdset ); //添加描述符fd
FD_CLR( int fd, fd_set* fdset );
int FD_ISSET( int fd, fd_set* fdset );
```

timeout参数用来设置select函数超时时间

# poll

poll系统调用和select类似，也是在指定时间内轮询一定数量的文件描述符，以测试其中是否有就绪者。

```c++
#include <poll.h>
int poll( struct pollfd* fds, nfds_t nfds, int timeout );
```

fds参数是一个pollfd结构类型的数组，它指定所有我们感兴趣的文件描述符上发生的可读、可写和异常等事件。

```c++
sturct pollfd
{
	int fd; //文件描述符
	short evens; //注册的事件，一系列事件按位或
	short revents;//实际发生的事件，由内核填充
}
```

nfds参数指定被监听事件集合fds的大小

```c++
typedef unsigned long int nfds_t;
```

timeout参数指定poll的超时值，单位是毫秒，timeout为-1时，poll将永远阻塞，直到某个事件发生；timeout为0时，poll调用立即返回。

# epoll

## 内核事件表

epoll是Linux特有的I/O复用函数，epoll用一组函数来完成任务，而不是单个函数。另外，epoll将用户关心的文件描述符上的事件放在内核里的一个事件表中，从而无需像select和poll那样每次调用都重复传入文件描述符集或事件集。但epoll需要一个额外的文件描述符，来标识内核中的这个事件表。这个文件描述符使用epoll_create函数来创建。
```c
#include <sys/epoll.h>
int epoll_create( int size )
```

下面函数用来操作epoll内核事件表：
```c++
#include <sys/epoll.h>
int epoll_ctl(int epfd, int op, int fd,struct epoll_event* event)
```
fd是要操作的文件描述符，op时指定操作类型：
+ EPOLL_CTL_ADD
+ EPOLL_CTL_MOD
+ EPOLL_CTL_DEL
event指定事件
```c++
struct epoll_event
{
	__unit32_t events;
	epoll_data_t data;
}
```
## epoll_wait函数

```c++
#include <sys/epoll.h>
int epoll_wait( int epfd, struct epoll_event* events, int maxevents, int timeout );
```

## LT和ET模式

epoll对文件描述符的操作有两种模式：LT(Level Trigger,电平触发)模式和ET(Edge Triggger,边沿触发)模式。
对于采用LT工作模式的文件描述符，当epoll_wait监测到其上有事件发生并将事件通知到应用程序后，应用程序可以不立即处理该事件，当应用程序下次调用epoll_wait时，epoll_wait还会再次相应通告该事件，直到该事件被处理。
对于采用ET工作模式的文件描述符，应用程序则必须立即处理该事件，因为后续的epoll_wait调用将不再通知这一事件。

## EPOLLONESHOT 事件

一个socket连接在任意时刻都只被一个线程处理
> 注意：监听文件描述符不能注册为EPOLLONESHOT事件，否则应用程序只能处理一个客户连接



![image.png](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/20230115151114.png)
