# TCP抓包实验

## TCP三次握手异常情况

### TCP第一次握手SYN丢包

拔掉服务器网线后，立刻在客户端执行curl命令

### TCP第二次握手SYN、ACK丢包

客户端加上防火墙设置，将来自服务端的数据全部丢弃

### TCP第三次握手ACK丢包

服务端加上对客户端ip的ack包的屏蔽防火墙

客户端两种处理：

+ 没有发送数据包，一直处于`ESTABLISHED`：**保活机制**
+ 发送了数据包，没有收到确认报文，超时重传，最后断开连接。



## TCP快速建立连接



## TCP重复确认和快速重传





## TCP流量控制

滑动窗口



## Nagle算法和延迟确认

Nagle——避免大量 TCP 小数据报文的传输



## 参考链接

[小林TCP实战抓包分析](https://xiaolincoding.com/network/3_tcp/tcp_tcpdump.html#%E6%98%BE%E5%BD%A2-%E4%B8%8D%E5%8F%AF%E8%A7%81-%E7%9A%84%E7%BD%91%E7%BB%9C%E5%8C%85)