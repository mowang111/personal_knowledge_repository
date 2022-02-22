# 一、 实验介绍

#### 1.1 实验内容

本项目带领你学习用 C 语言实现 ping 命令。通过本项目中你可以更深入地理解 TCP/IP 协议，掌握 C 语言进行网络编程的技巧方法。

#### 1.2 知识点

- TCP/IP 协议介绍
- ping命令原理
- 套接字有关函数使用

#### 1.3 实验环境

- xfce 终端
- gcc 编译器

#### 1.4 适合人群

本课程涉及 C 基础，Linux 网络编程底层比较多，适合有一定基础，想了解网络编程，以及套接字原理的同学学习。

#### 1.5 代码获取

```
wget http://labfile.oss.aliyuncs.com/courses/305/ping.c
```

**请尽量按照实验步骤自己写出 C 语言程序，请确认文件保存在目录：“/home/shiyanlou/” 下。**

# 二、实验步骤

ping 命令是用来查看网络上另一个主机系统的网络连接是否正常的一个工具。这里我们用`192.168.42.3`这个 ip 做测试：

![1-2-1](https://doc.shiyanlou.com/document-uid100000labid939timestamp1488259421886.png)

由上面的执行结果可以看到，ping 命令执行后依次显示出

> - 被测试系统主机名和相应 IP 地址
> - 返回给当前主机的 ICMP 报文顺序号
> - ttl 生存时间和往返时间 rtt（单位是毫秒，即千分之一秒）

## 2.1 ping命令原理讲解

要真正了解 ping 命令实现原理，就要了解 ping 命令所使用到的 ICMP 协议：

> `ICMP` 是（Internet Control Message Protocol）Internet 控制报文协议；
>
> 它是 TCP/IP 协议族的一个子协议，用于在 IP 主机、路由器之间传递`控制消息`；
>
> ICMP是IP协议不可分割的一部分,ICMP是属于`网络层`的一个协议。

`控制消息`有

> - 目的不可达消息
> - 超时信息
> - 重定向消息
> - 时间戳请求和时间戳响应消息
> - 回显请求和回显应答消息。

ping 命令的机制是`回显请求`和`回显应答消息`。具体表现是向网络上的另一个主机系统发送 ICMP 报文，如果指定系统得到了报文，它将把报文一模一样地传回给发送者。

下面来看下`回显请求`和`回显应答`消息 ICMP 报文格式（它们的格式都一样）：

![1-2.1-1](https://doc.shiyanlou.com/userid18412labid939time1430195922881)

`类型`字段:

> 回显请求报文其中`类型`为 0，代码为 0。
>
> 回显应答报文其中`类型`为 8，代码为 0。

`校验和`字段：

> 包括数据在内的整个 ICMP 协议数据包的校验和，具体实现方法会在下面详细介绍。

`标识符`字段：

> 用于唯一标识 ICMP 报文，本项目使用程序的进程 id。因为如果同时在两个命令行终端执行 ping 命令的话，每个 ping 命令都会接收到所有的回显应答，所以需要根据标识符来判断回显应答是否应该接收。

`序号`字段：

> ICMP 报文的序号。

`数据`字段：

> 也就是报文，本项目中我们将发送报文的时间戳放入数据字段，这样当接收到该报文应答的时候可以取出发送时间戳，将接收应答的时间戳减去发送时间戳就是报文往返时间（rtt）。
>
> 提前预告一下，这里使用gettimeofday()API函数获取时间戳，详细介绍会在函数介绍部分说明。

> ```
> ICMP 报文 C 语言实现可以用下面的数据结构表示：
> struct icmp{
>         unsigned char   type;         // 类型
>         unsigned char   code;         // 代码
>         unsigned short  checksum;     // 校验和
>         unsigned short  id;            // 标识符
>         unsigned short  sequence;     // 序号
>         struct timeval  timestamp;    // 时间戳 
> };
> ```

unsigned char 正好一字节，也就是 8bit，unsigned short 二字节，也就是 16bit，unsigned int4 字节（32bit），不过上面没用到。其中 struct timeval 类型可能有人不清楚，不过没关系，函数部分说明。

- IP报文格式

系统发送ICMP报文时会将ICMP报文作为IP的数据，也就是放入IP报文格式的数据字段，IP报文格式如下图所示：

![1-2.1-2](https://doc.shiyanlou.com/userid18412labid939time1430196023379)

注意上面4位首部长度和16位总长度，4位首部长度不包括数据字段，并且单位是4字节。16位总长度包括数据字段，单位是1字节。

IP报文首部C语言实现可以用下面的数据结构表示：

> ```
> struct ip{
>     unsigned char version:4;       // 版本
>     unsigned char hlen:4;        // 首部长度
>     unsigned char tos;             // 服务类型
>     unsigned short len;         // 总长度
>     unsigned short id;            // 标识符
>     unsigned short offset;        // 标志和片偏移
>     unsigned char ttl;            // 生存时间
>     unsigned char protocol;     // 协议
>     unsigned short checksum;    // 校验和
>     struct in_addr ipsrc;        // 32位源ip地址
>     struct in_addr ipdst;       // 32位目的ip地址
> };
> ```

`struct in_addr`类型会函数介绍部分说明。注意ICMP协议是IP层的一个协议，这里有人可能不清楚为什么ICMP协议是IP层的。

> 这是因为ICMP报文在发送给报文接收方时可能要经过若干子网，会牵涉到路由选择等问题，所以ICMP报文需通过IP协议来发送，是IP层的。

## 2.2 地址信息表示

当我们编写网络应用程序时，必然要使用地址信息指定数据传输给网络上哪个主机，那么地址信息应该包含哪些呢？

> 1. 地址族，基于IPv4的地址族还是IPv6的地址族。
> 2. IP地址。
> 3. 端口号。

为了便于记录地址信息，系统定义了如下结构体：

> ```
> struct sockaddr_in{
>     sa_family_t        sin_family;     // 地址族
>     uint16_t        sin_port;        // 端口号
>     struct in_addr  sin_addr;          // 32位IP地址
>     char             sin_zero[8];    // 不使用
> };
> ```

其中`struct in_addr` 结构体定义如下：

> ```
> struct in_addr{
>     in_addr_t     s_addr;        // 32位IP地址
> };
> ```

`in_addr_t` 使用如下宏指令定义，也就是无符号整型32位。

> ```
> #define in_addr_t uint32_t
> ```

但实际上，还有一种结构体也可以表示地址信息，如下所示：

> ```
> struct sockaddr{
>     sa_family_t    sin_family;     // 地址族
>     char         sa_data[14]; // IP地址和端口
> };
> ```

成员`sa_data`保存的信息包含 IP 地址和端口号，剩余部分填充0。在网络编程中，常用的是 struct sockaddr_in 结构体，因为相对于 struct sockaddr 结构体，前者填充数据比较方便。

不过网络编程接口函数定义使用的是 struct sockaddr 结构体类型，这是由于最先使用的是 struct sockaddr 结构体，struct sockaddr_in 结构体是后来为了方便填充地址信息数据定义。这就出现矛盾了，不过也不用担心上面两个结构体之间是可以相互转换的。定义地址信息时使用 struct sockaddr_in 结构体，然后将该结构体类型转为 struct sockaddr 结构体类型传递给网络编程接口函数即可。

## 2.3 主机字节序与网络字节序

在不同 CPU 中，4字节整型数值1在内存空间的保存方式是不同的。

> 4字节整型数值1可用二进制表示如下：
>
> ```
> 00000000 00000000 00000000 00000001
> ```
>
> 而有些CPU则以倒序保存。
>
> ```
> 00000001 00000000 00000000 00000000
> ```

所以，如果发送主机与接收主机CPU字节序不一样则就会出现问题。引申上面的问题，这就涉及到CPU解析数据的方式，其方式有2种：

> 大端序（Big Endian）：高位字节存放到低位地址。
>
> 小端序（Little Endian）：高位字节存放到高位地址。

由于不同CPU字节序不一样，因此，在通过网络传输数据时约定统一方式，这种约定称为网络字节序（Network Byte Order），非常简单——统一为大端序。

所以，进行网络传输数据前，需要先把数据数组转化为大端序格式再进行网络传输。接收到网络数据后，需要转换本机字节序格式然后进行后续处理。不过，幸运地是这些工作不需要我们自己完成，系统会自动转换的。

我们唯一需要转换的是向struct sockaddr_in结构体变量填充IP地址和端口号数据的时候。当然，系统已经提供了一些函数，只需调用相应函数即可。

转换字节序的函数有：

> ```
> unsigned short htons(unsigned short);
> unsigned short ntohs(unsigned short);
> unsigned long  htonl(unsigned long);
> unsigned long  ntohl(unsigned long);
> ```

上面的函数非常简单，通过函数名就能知道它们的功能，htonl/htons 中的h代表主机（host）字节序，n代表网络（network）字节序，s指的是 short，l指的是 long（需要注意一下，linux 中 long 类型只占4个字节，跟int类型一样）。

下面通过简单的示例熟悉一下上面的函数，编写源代码文件 /home/shiyanlou/order.c：

> ```
> #include <stdio.h>
> #include <arpa/inet.h>
> 
> int main(void){
>     unsigned short hosts = 0x1234;
>     unsigned short nets;
>     unsigned long  hostl = 0x12345678;
>     unsigned long  netl; 
> 
>     nets = htons(hosts);
>     netl = htonl(hostl);
> 
>     printf("Host ordered short: %#x \n", hosts);
>     printf("Network ordered short: %#x \n", nets);
> 
>     printf("Host ordered long: %#lx \n", hostl);
>     printf("Network ordered long: %#lx \n", netl);
> 
>     return 0;
> }
> ```

程序运行结果如下：

![1-2.3-1](https://doc.shiyanlou.com/document-uid735639labid6387timestamp1528800766211.png)

从上面执行结果可以看出，主机字节序与网络字节序不一样，是小端序的。大家通过上面的程序也可以判断自己主机是大端序的还是小端序的。

> 多说一句，Intel 系列 CPU 采用的都是小端序标准。

## 2.4 函数介绍（一）

本章节介绍几个重要的函数及其作用

> - `gettimeofday()` 精确存入当前时间
> - `inet_addr()` 转换点分十进制-->32位整形
> - `inet_ntoa()` 转换32位整形-->点分十进制
> - `gethostbyname()` 通过域名得到IP

#### 2.4.1 `gettimeofday()` 函数

> ```
> #include <sys/time.h>
> int gettimeofday(struct timeval *tv, struct timezone *tz);
> ```

该函数的作用是把当前的时间放入 struct timeval 结构体中返回。注意：

> 1. 精确级别,微妙级别
> 2. 受系统时间修改影响
> 3. 返回的秒数是从1970年1月1日0时0分0秒开始

其参数 tv 是保存获取时间结果的结构体，参数 tz 用于保存时区结果。

结构体 timeval 的定义为：

> ```
> struct timeval
> {
>     long int tv_sec;      // 秒数
>     long int tv_usec;     // 微秒数
> }
> ```

结构体 timezone 的定义为：

> ```
> struct timezone
> {
>     int tz_minuteswest;/*格林威治时间往西方的时差*/
>     int tz_dsttime;    /*DST 时间的修正方式*/
> }
> ```

timezone 参数若不使用则传入0即可，本项目传入0。

下面通过计算程序运行时间的一个简单示例感受一下 gettimeofday 函数的使用，编写源代码文件 /home/shiyanlou/gettimeofday.c。

```
/**
 * 本程序实现计算程序运行时间
 */
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>

// 计算时间差，单位：ms
float timediff(struct timeval *begin, 
        struct timeval *end){
    int n;
    // 先计算两个时间点相差多少微秒
    n = ( end->tv_sec - begin->tv_sec ) * 1000000
        + ( end->tv_usec - begin->tv_usec );

    // 转化为毫秒返回
    return (float) (n / 1000);
}

int main(void){
    struct timeval begin, end;

    gettimeofday(&begin, 0);

    // 这里让程序挂起一秒
    printf("do something here...");
    sleep(1);

    gettimeofday(&end, 0);

    printf("running time : %fms\n", timediff(&begin, &end));

    return 0;
}
```

程序运行结果如下：

![1-2.4.1-1](https://doc.shiyanlou.com/document-uid735639labid6387timestamp1528800806293.png)

从上面执行结果可以看到，大约都运行了1秒钟时间。但有时候多1毫秒，有时候又恰好1秒。这是因为系统中运行的程序不只本程序一个，有时候恰好遇到内核进行进程切换需要时间。

#### 2.4.2 `inet_addr` 函数。

> ```
> #include <arpa/inet.h>
> in_addr_t inet_addr(const char *string);
> ```

该函数的作用是将用点分十进制字符串格式表示的IP地址转换成32位大端序整型。

成功时返回32位大端序整型数值，失败时返回 INADDR_NONE 。

下面通过一个简单的示例熟悉一下上面介绍的函数，编写源代码文件 /home/shiyanlou/inetaddr.c ：

```
#include <stdio.h>
#include <arpa/inet.h>

int main(void){
    char *addr1 = "1.2.3.4";
    char *addr2 = "192.168.1.1";

    in_addr_t data;

    data = inet_addr(addr1);
    printf(" %s -> %#lx \n", addr1, (long)data );

    data = inet_addr(addr2);
    printf(" %s -> %#lx \n", addr2, (long)data );

    return 0;
}
```

程序运行结果如下： ![1-2.4.2-1](https://doc.shiyanlou.com/document-uid735639labid6387timestamp1528800824915.png)

#### 2.4.3 `inet_ntoa` 函数。

> ```
> char * inet_ntoa(struct in_addr addr);
> ```

> 该函数的作用与 inet_addr 正好相反。将32位大端序整型格式IP地址转换为点分十进制格式。
>
> 成功时返回转换的字符串地址值，失败时返回-1。

同样下面也通过一个简单的示例熟悉一下inet_ntoa函数，编写源代码文件 /home/shiyanlou/inetntoa.c：

```
#include <stdio.h>
#include <arpa/inet.h>

int main(void){
    struct in_addr addr1, addr2;
    char * str1, * str2;

    addr1.s_addr  = htonl(0x1020304);
    addr2.s_addr  = htonl(0xc0a80101);

    str1 = inet_ntoa(addr1);
    str2 = inet_ntoa(addr2);

    printf("%#lx -> %s \n", (long)addr1.s_addr, str1);
    printf("%#lx -> %s \n", (long)addr2.s_addr, str2);

    return 0;
}
```

程序运行结果如下： ![1-2.4.3-1](https://doc.shiyanlou.com/document-uid735639labid6387timestamp1528800880576.png)

函数两次执行的结果怎么是一样的，其实这是 C 语言编程中常会出现的陷阱。

我们可以再看下上面函数的定义，注意该函数返回值类型为 char 指针类型，大家看出端倪了吗？

`inet_addr`函数在执行过程中，在内部会申请内存并保存结果字符串，然后返回内存地址。所以调用完该函数应该将字符串复制到其他内存空间。因为再次调用该函数时，之前保存的字符串很有可能被覆盖。知道了原因，大家可以动手修改上面的代码了。

> 首先定义一个接收缓冲区 `char buf[20];` ；
>
> 然后使用 `memcpy(buf, str1, sizeof(str))` 将 `inet_ntoa` 函数生成的字符串保存缓冲区。

记住，`memcpy` 函数在头文件 `#include <string.h>` 中声明的，需要加上这个头文件。这里就不贴完整代码了，修改后运行结果如下。 ![1-2.4.3-1](https://doc.shiyanlou.com/document-uid735639labid6387timestamp1528800893137.png)

## 2.5 函数介绍（二）

#### 2.5.1 `gethostbyname` 函数

> ```
> #include <netdb.h>
> struct hostent * gethostbyname(const char * hostname);
> ```

> 该函数的作用是根据域名获取IP地址。
>
> 成功时返回hostent结构体地址，失败时返回NULL指针。

struct hosten结构体定义如下：

> ```
> struct hostent{
>     char *          h_name;
>     char **     h_aliases;
>     char         h_addrtype;
>     char         h_length;
>     char **     h_addr_list;
> };
> ```

我们最关心的是 h_addr_list 成员，它保存的就是域名对应IP地址。由于一个域名对应的IP地址不止一个，所以h_addr_list成员是char **类型，相当于二维字符数组。

下面通过一张图来表示h_addr_list成员的参数，希望大家可以加深对hostent结构体的理解。 ![1-2.5.1-1](https://doc.shiyanlou.com/userid18412labid939time1430197955746)

同样下面通过一个简单的示例熟悉一下gethostbyname函数的用法，编写源代码文件 /home/shiyanlou/gethostbyname.c：

```
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>

int main(int argc, char *argv[]){
    int i;
    struct hostent *host;

    if(argc < 2){
        printf("Use : %s <hostname> \n", argv[0]);
        exit(1);
    }

    host = gethostbyname(argv[1]);

    for(i = 0; host->h_addr_list[i]; i++){
        printf("IP addr %d : %s \n", i+1,
                inet_ntoa(*(struct in_addr *)host->h_addr_list[i]));
    }

    return 0;
}
```

上面代码中，打印IP地址是出现了令人困惑的类型转换。

> `host->h_addr_list[i]`得到的是字符串指针，但该字符串指针实际指向的是`struct in_addr`结构体变量地址值。
>
> `(struct in_addr *)host->h_addr_list[i]`将字符串指针转换为`struct in_addr`结构体指针。
>
> 由于`inet_ntoa`参数类型是`struct in_addr`而不是`struct in_addr *`，所以用`*`运算符取出`struct in_addr`结构体的值。

程序运行结果如下：

![1-2.5.1-2](https://doc.shiyanlou.com/document-uid735639labid6387timestamp1528800907973.png)

注意：

> 如果获取某个网址的IP地址时提示失败。原因是实验楼对ip地址进行了限制，只能访问/etc/hosts文件中对应的ip地址和域名。

#### 2.5.2 `socket` 函数

> ```
> #include <sys/socket.h>
> int socket(int family, int type, int protocol);
> ```

> 成功时返回文件描述符，失败时返回-1。
>
> 该函数的作用是创建一个套接字。一般为了执行网络I/O，一个进程必须做的第一件事就是调用socket函数。

- 第一个参数family：指明套接字中使用的协议族信息。

常见值有： ![1-2.5.2-1](https://doc.shiyanlou.com/userid18412labid939time1430198146846)

- 第二个参数type：指明套接口类型，也即套接字的数据传输方式。

常见值有： ![1-2.5.3-2](https://doc.shiyanlou.com/userid18412labid939time1430198177422)

在常见的使用socket进行网络编程中，经常使用SOCK_STREAM和SOCK_DGRAM，也就是TCP和UDP编程。在本项目中，我们将使用SOCK_RAW（原始套接字）。

原始套接字的主要作用在三个方面：

> 1. 通过原始套接字发送/接收 ICMP 协议包
> 2. 接收发向本级的，但 TCP/IP 协议栈不能处理的IP包
> 3. 用来发送一些自己制定源地址特殊作用的IP包（自己写IP头）

ping 命令使用的就是 ICMP 协议，因此我们不能直接通过建立一个 SOCK_STREAM或SOCK_DGRAM 来发送协议包，只能自己构建 ICMP 包通过 SOCK_RAW 来发送。

- 第三个参数 protocol：指明协议类型。

常见值有： ![1-2.5.4-3](https://doc.shiyanlou.com/userid18412labid939time1430198232264)

参数 protocol 指明了所要接收的协议包。

> 如果指定了 IPPROTO_ICMP，则内核碰到ip头中 protocol 域和创建 socket 所使用参数 protocol 相同的 IP 包，就会交给我们创建的原始套接字来处理。

因此，一般来说，要想接收什么样的数据包，就应该在参数protocol里来指定相应的协议。当内核向我们创建的原始套接字交付数据包的时候，是包括整个IP头的，并且是已经重组好的IP包。如下所示： ![1-2.5.5-4](https://doc.shiyanlou.com/userid18412labid939time1430198267233)

这里的数据也就是前面所说的时间戳。

但是，当我们发送IP包的时候，却不用自己处理IP首部，IP首部由内核自己维护，首部中的协议字段被设置成调用 socket 函数时传递给它的第三个参数。

我们发送 IP 包时，发送数据时从 IP 首部的第一个字节开始的，所以只需要构造一个如下所示的数据缓冲区就可以了。 ![1-2.5.6-5](https://doc.shiyanlou.com/userid18412labid939time1430198299520)

如果想自己处理 IP 首部，则需要设置 IP_HDRINCL 的 socket 选项，如下所示：

> ```
> int flag = 1;
> setsocketopt(sockfd, IPPROTO_TO, IP_HDRINCL, &flag, sizeof(int));
> ```

此时，我们需要构造如下所示的数据缓冲区。

![1-2.5.7-6](https://doc.shiyanlou.com/userid18412labid939time1430198358322)

注意，我们自己填充 IP 首部时，也不是填充 IP 首部的所有字段，而是应该将 IP 首部的 id 字段设置为0，表示让内核来处理这个字段。同时，内核还会自动完成 IP 首部的校验和的计算并填充。

最后介绍发送和接收 IP 包的两个函数：recvfrom 和 sendto。

> ```
> #include <sys/socket.h>
> ssize_t recvfrom(int sockfd, void * buff, size_t nbytes, int flags, struct sockaddr * from, socklen_t * addrlen);
> 
> ssize_t sendto(int sockfd, const void * buff, size_t nbytes, int flags,const struct sockaddr * to, socklen_t addrlen);
> ```

> 成功时返回读写的字节数，失败时返回-1。
>
> sockfd参数：套接字描述符。
>
> buff参数：指向读入或写出缓冲区的指针。
>
> nbytes参数：读写字节数。
>
> flags参数：本项目中设置为0。
>
> recvfrom 的 from 参数指向一个将由该函数在返回时填写数据发送者的地址信息的结构体，而该结构体中填写的字节数则放在 addrlen 参数所指的整数中。
>
> sendto 的 to 参数指向一个含有数据报接收者的地址信息的结构体，其大小由addrlen参数指定。

#### 2.5.3 校验和算法

检验和算法在 TCP/IP 协议族中是比较常见的算法。IP、ICMP、UDP和TCP报文头部都有校验和字段，不过IP、TCP、UDP只针对首部计算校验和，而 ICMP 对首部和报文数据一起计算校验和。检验和算法可以分成两步来实现。

首先在发送端，有以下三步：

> 1. 把校验和字段置为0
> 2. 对需要校验的数据看成以16bit为单位的数字组成，依次进行二进制求和
> 3. 将上一步的求和结果取反，存入校验和字段

其次在接收端，也有相应的三步：

> 1. 对需要校验的数据看成以16bit为单位的数字组成，依次进行二进制求和，包括校验和字段
> 2. 将上一步的求和结果取反
> 3. 判断最终结果是否为0。如果为0，说明校验和正确。如果不为0，则协议栈会丢掉接收到的数据

从上可以看出，归根到底，校验和算法就是二进制反码求和。由于先取反后相加与先相加后取反，得到的结果是一样的，所以上面的步骤都是先求和后取反。

下面用C语言来实现校验和算法，代码如下：

> ```
> /**
>  * addr 指向需校验数据缓冲区的指针
>  * len  需校验数据的总长度（字节单位）
>  */
> unsigned short checkSum(unsigned short *addr, int len){
>     unsigned int sum = 0;  
>     while(len > 1){
>         sum += *addr++;
>         len -= 2;
>     }
>     
>     // 处理剩下的一个字节
>     if(len == 1){
>         sum += *(unsigned char *)addr;
>     }
> 
>     // 将32位的高16位与低16位相加
>     sum = (sum >> 16) + (sum & 0xffff);
>     sum += (sum >> 16);
> 
>     return (unsigned short) ~sum;
> }
> ```

代码分析如下：

> 上面的代码首先定义了一个32位无符号整型的变量sum，用来保存16bit二进制数字相加的结果，由于16bit相加可能会产生进位，所以这里使用32位变量来保存结果，其中高16bit保存的是相加产生的进位。
>
> 然后下面的 while 循环，对数据按16bit累加求和。
>
> 接下来的if语句判断是否还剩下8bit（一字节）。如果校验的数据为奇数个字节，会剩下最后一字节。把最后一个字节视为一个2字节数据的高字节，这个2字节数据的低字节为0，继续累加。
>
> 之后的两行代码作用是将 sum 高16bit的值加到低16bit上，即把累加中最高位的进位加到最低位上。（sum >> 16）将高16bit右移到低16bit，（sum & 0xffff）将高16bit全部置为0。注意，这两步都不会改变sum原来的值。
>
> 进行了两次相加可以保证 sum 高16bit都为0，没有进位了。
>
> 最后取反，并返回。

扩展：

> 为什么使用二进制反码求和，而不是原码或补码呢？
>
> 这是因为，使用反码计算校验和比较简单和快速。对于网络通信来说，最重要的就是效率和速度。

## 2.6 程序编写及测试

整个程序的流程图如下所示： ![1-2.6-1](https://doc.shiyanlou.com/userid18412labid939time1430198604615)

> 1. 首先创建原始套接字。
> 2. 封装 ICMP 报文，向目的IP地址发送 ICMP 报文，1秒后接收 ICM P响应报文，并打印 TTL，RTT。
> 3. 循环第二步N次，本项目设置为5。
> 4. 输出统计信息。

代码介绍到此结束，完成源代码文件编写 /home/shiyanlou/ping.c。

```
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <netdb.h>

#define ICMP_SIZE (sizeof(struct icmp))
#define ICMP_ECHO 0
#define ICMP_ECHOREPLY 0
#define BUF_SIZE 1024
#define NUM   5    // 发送报文次数

#define UCHAR  unsigned char
#define USHORT unsigned short
#define UINT   unsigned int 

/*请同学们参考 1.5 节的下载链接在这里补全代码，所用的代码和知识点在 2.1，2.2，2.3 2.4节已给出.*/
```

程序运行结果如下：

![1-2.6-2](https://doc.shiyanlou.com/document-uid735639labid6387timestamp1528801531843.png)

> 执行`./ping 192.168.42.3` 提示 socket() error 错误，也就是调用 socket 函数的时候出现了错误。
>
> 这是因为我们创建的是原始套接字，原始套接字必须有 root 权限才能创建，所以我们可以加 sudo 执行。

执行成功了！

# 三、实验总结

通过本节的实验实现了 C 语言编写 ping 命令，以及如何获取系统时间，大端序，小端序，原始套接字的编程，校验和算法。