---
title: IO多路复用是阻塞的还是非阻塞的，同步还是异步
date: {{ date }}
top: false
cover: false
password:
toc: true
mathjax: true
summary:
tags: [网络编程] 
categories: []
---

整理自[](https://github.com/CyC2018/CS-Notes/issues/194)

# IO多路复用是阻塞的还是非阻塞的，同步还是异步

所有I/O多路复用都是同步的，涵盖select/poll。

阻塞/非阻塞是相对于同步I/O来说的，与异步I/O无关。

## 关于Select

在使用`int select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout)`函数时，可以设置timeval决定该系统调用是否阻塞。

## 关于Poll

在使用`int poll(struct pollfd *fds, nfds_t nfds, int timeout)`函数获取信息时，可以通过指定timeout值来决定是否阻塞（当timeout<0时，会无限期阻塞；当timeout=0时，会立即返回）。

## 关于Epoll:

在使用`epoll_wait(int epfd, struct epoll_event *events, int maxevents, int timeout)`函数来获取是否有发生变化/事件的文件描述符时，可以通过指定timeout来指定该调用是否阻塞（当timeout=-1时，会无限期阻塞；当timeout=0时，会立即返回）。



关于Epoll是否同步：

**当前是否有发生变化的文件描述符需要通过epoll_wait显示地进行查询，因此不是异步。**