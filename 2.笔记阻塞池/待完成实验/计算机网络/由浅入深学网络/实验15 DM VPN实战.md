## 一、实验介绍

DM VPN 是在古老但是又被广泛应用的 IPSec VPN 上做的升级。而本章节依然只会简单的介绍 DMVPN 的产生，以及使用的范围，最后一个小实验体验该功能，其中会遇到一些以前没有提到的概念不会深入的讲解，因为涉及的方面过广，期待进阶的课程来专门的讲解。

### 1.1 实验涉及的知识点

- GRE 介绍
- DMVPN 的简介
- DMVPN 的简单工作流程
- DMVPN 的配置

## 二、GRE 介绍

在上一节实验中我们使用了 IPSec 的功能对数据进行了加密后进行传输，而加密后的数据报文是无法进行广播域组播，在我们配置的时候就会发现我们建立的是一个一对一的通信，也就是单播，所以这样是无法通过其广播加密的数据报文。

而我们的 RIP 与 OSPF 这样的动态路由协议就是通过广播与组播来发送报文动态学习、更新路由表。

这样便使得虽然我们建立了与远程网络的连接，但是远程网络中若是有多个网段或者说是我们还与另外的分布建立了连接，而分布与分布在没有专门建立线路时是无法通信。

尤其为了在某些网络协议的数据报文能够在另一个网络层协议中进行传输便出现了 GRE（Generic Routing Encapsulation，通用路由封装），简单来说就是在发送一个数据包的情况下却相当于两个平行的 IP 数据包在发送一般，GRE 是 Tunnel 隧道技术中的一种，所谓的隧道技术就是在公共网络的正常线路下隐藏着一条逻辑上的直达专线。

隧道嘛，就是在地底下看不见，摸不着，但却暗中运行着。

GRE 隧道技术是一个虚拟的点到点的连接，为封装的数据报文提供了一条传输通路，GRE 隧道的两端 分别对数据报进行封装及解封装。

在大概知道了 GRE 的概念之后我们便来了解一下 GRE 的使用场景：

- 与一般的 VPN 相同，建立单一协议的隧道，连接两个远端的局域网，使其相互通信
- 扩大了距离矢量类型的协议的工作范围，例如 RIP 有十五跳的限制，但是通过隧道的传输，从本地出口到远端的入口这里只算做一跳
- 与 IPSec 的结合使用，GRE 只是实现了两段的连接以及多个协议的承载，但是数据却没有经过安全的加密，而与 IPSec 的结合使用便可弥补这样的缺陷

同样 GRE 的使用只是在设备商建的配置几条命令即可。

## 四、 DMVPN 的简介

在上节实验中讲到的 IPSec 隧道，利用其在 Internet 上进行安全的数据传输是大部分公司总部与分支通讯 的主要解决方案。

在上个使用中我们讨论的是一个总部与一个分布的连接情况，但是若是随着规模的不断扩大就会有越来越多的分支机构。

这样多站点、大范围的连接就会设计到拓扑。在帧中继中我们讨论有三种拓扑结构：

- 星型（hub and spoke）：一个总部多个分部，所有的分布都直连总部。
- 全网型（full mesh）：所有的节点都没有总部与分部的区分，所有的站点都两辆相连。
- 部分连接（partial Mesh）：也就是部分的节点相互连接在一起，但是没有所有都两两连接这么夸张。

大多数情况下为了节约成本都会采用星型结构来部署网络，而使用星型的结构来部署 IPSec 的隧道通信，而这样所带来的问题有：

- 随着分部的不断增加，那么总部需要一个一个的去建立连接，而连接的建立需要 IKE 的 policy 集与 IPSec 的 transfer set 集，这样会使得这两个集越来越多，这样在管理、维护起来非常的麻烦，并且配置十分的繁复。
- 若是分部与分部之间需要通信，若是没有 GRE 来广播动态路由协议便无法做到之间的相互通信在不使用 partial mesh 或者 full mesh 的情况下。
- 即使通过了 GRE 实现了两个分部的通信，那也需要总部在中间转发，这样会造成两次加密解密的过程，这样的过程效率不高并且还浪费系统的资源
- 没有自适应的能力

对于这样种种的缺陷，DMVPN 便孕育而生了。

DMVPN 使得隧道之间的连接更加的灵活，扩展性更强，并且对于分布添加的时候不用修改总部的配置，从而 sa 与各种集合不会变多，并且 DMVPN 有自适应的能力使得两个分部在通过总部学习到相关的消息之后会自动相互建立连接。

这就是为什么会使用 DMVPN 的原因，同时也是 DMVPN 使用的场景。

而 DMVPN 完成这样的一些功能需要依靠这样的协议：

- MGRE（Multipoint GRE）：多点的 GRE 协议
- NHRP（Next Hop Resolution Protocol）：下一跳解析协议，此协议类似于 ARP 与逆向 ARP（RARP），区别在于 ARP 是 IP 与 MAC 地址的映射，RARP 是 IP 与 DLCI 的映射，而 NHRP 是 公网 IP 地址与 Tunnel 隧道 IP 地址的映射关系，
- Dynamic Routing Protocol：与之前所讨论的动态路由协议相同，没有动态路由协议是学习不到分部。
- IPsec VPN：用于数据的加密，可以结合使用可以不用。

这便是 DMVPN 的大体框架

## 五、 DMVPN 的简单工作流程

NHRP 的工作类似类似于 C/S 模式，也就是客户端/服务器模式，同样也是因为这样的运作模式使得不用过多的去配置我们的中心 Hub 的出口路由。

所谓的客户端/服务器模式是指的所有的 spoke 分部在建立通道的时候都必须与 Server 端的 Hub 中心路由注册信息，让中心的路由记录下我的公网地址与隧道地址的映射关系，这样之后才能建立隧道关系。

所以 DMVPN 的大致工作流程：

- 分部站点的设备会根据设置的中心路由的公网 IP 地址找到中心节点的路由；
- 然后通过已配置在设备的认证信息，还有公网 IP 地址与 Tunnel 隧道地址的对应关系尝试与中心路由建立连接。协商之后成功建立连接。
- 此时若是分部与分部之间相互联系需要通过中心的站点也就是我们的 Hub（这个 Hub 是星型拓扑结构的 Hub，不是集线器的 Hub） 节点的路由转发；
- 分部1 与分部2 连接，路由跳数是2，中心节点会优化，使之尝试分布之间的连接，从而不用通过 Hub 节点进行中转。
- 分部1 通过中心节点获取到分部2 的相关信息，然后尝试连接，由此分部1 与2 之间可以之间联系而不用通过中心节点了。

这便是 DMVPN 的一种情况的、简单的工作流程。

## 六、 DMVPN 的配置

我们通过这样一个实验来体验 DMVPN 所带来的效果，以及加上对 DMVPN 的一个印象

- 实验目的：配置实现 DMVPN
- 实验材料：三台路由器与一台交换机
- 实验方法：
  - 拖动三台路由器与一台交换机（三台路由器分别作为一个中心与两个分部的出口路由，交换机作为中继）
  - 配置路由器名字与连接线路
  - 配置路由器的端口地址
  - 配置 DMVPN
  - 验证 DMVPN

1.首先按照惯例，利用我们的终端打开 GNS3 模拟器，然后拖出上述要求的设备，做出这样的拓扑结构：

![1-dmvpn-topo.png](https://doc.shiyanlou.com/document-uid113508labid2232timestamp1478237394826.png)

2.配置各个端口的 IP 地址：

```
## Router-center code for interface

Router-center#conf t

Router-center(config)#int e0/0

Router-center(config-if)#ip add 1.1.1.3 255.255.255.0

Router-center(config-if)#no sh

Router-center(config-if)#exit

Router-center(config)#int lo 0

Router-center(config-if)#ip add 10.3.3.1 255.255.255.0

Router-center(config-if)#no sh

Router-center(config-if)#exit

#配置隧道接口 IP 地址

Router-center(config)#int tunnel 10

Router-center(config-if)#ip add 192.168.1.3 255.255.255.0

Router-center(config-if)#no sh

## Router-spoke1 code for interface

Router-spoke1#conf t

Router-spoke1(config)#int e0/0

Router-spoke1(config-if)#ip add 1.1.1.1 255.255.255.0

Router-spoke1(config-if)#no sh

Router-spoke1(config-if)#exit

Router-spoke1(config)#int  lo 0

Router-spoke1(config-if)#ip add 10.3.1.1 255.255.255.0

Router-spoke1(config-if)#no sh 

Router-spoke1(config-if)#exit

Router-spoke1(config)#int tunnel 10

Router-spoke1(config-if)#ip add 192.168.1.1 255.255.255.0

Router-spoke1(config-if)#no sh

## Router-spoke2 code for interface

Router-spoke2#conf t

Router-spoke2(config)#int e0/0

Router-spoke2(config-if)#ip add 1.1.1.2 255.255.255.0

Router-spoke2(config-if)#no sh

Router-spoke2(config-if)#exit

Router-spoke2(config)#int  lo 0

Router-spoke2(config-if)#ip add 10.3.2.1 255.255.255.0

Router-spoke2(config-if)#no sh 

Router-spoke2(config-if)#exit

Router-spoke2(config)#int tunnel 10

Router-spoke2(config-if)#ip add 192.168.1.2 255.255.255.0

Router-spoke2(config-if)#no sh
```

3.配置隧道接口的相关策略：

```
## Router-center for tunnel

#在 tunnel 的端口中配置源端口，也就是它将借用那个端口发送数据
Router-center(config-if)#tunnel source e0/0

#设置模式为多点 GRE ，只有这样 tunnel 端口才可以发送动态路由信息
Router-center(config-if)#tunnel mode gre multipoint

#配置 nhrp 所在的网络编号，同一个 ID 下的 Tunnel 才能相互通信
Router-center(config-if)#ip nhrp network-id 10

#配置 nhrp 的认证密钥
Router-center(config-if)#ip nhrp authentication shiyan

#配置 nhrp 动态接受组播映射
Router-center(config-if)#ip nhrp map multicast dynamic

#配置 ospf 的网络可以组播或广播，否则 ospf 将永远卡在 extart 的状态
Router-center(config-if)#ip ospf net point-to-multipoint

#开启 nhrp 重写，这样可以优化路由，但是目前只发现对 eigrp 有效果
Router-center(config-if)#ip nhrp redirect

Router-center(config-if)#exit

## Router-spoke1 for tunnel

# 配置与 hub 的差不多只有端口映射部分有差别

Router-spoke1(config-if)#tunnel source e0/0

Router-spoke1(config-if)#tunnel mode gre multipoint

Router-spoke1(config-if)#ip nhrp network-id 10

Router-spoke1(config-if)#ip nhrp authentication shiyan

#spoke 需要手动映射组播到 hub，以便后续的spoke和hub之间建立动态路由协议邻居
Router-spoke1(config-if)#ip nhrp map multicast 1.1.1.3

#spoke 需要静态配置 hub 地址映射
Router-spoke1(config-if)#ip nhrp map 192.168.1.3 1.1.1.3

#配置 nhrp server 地址，spoke 启动以后会到服务器注册自己虚拟隧道地址的映射
Router-spoke1(config-if)#ip nhrp nhs 192.168.1.3

Router-spoke1(config-if)#ip ospf net point-to-multipoint

Router-spoke1(config-if)#exit

Router-spoke1(config)#


## Router-spoke2 for tunnel

##与 spoke1 的配置完全一样

Router-spoke2(config-if)#tunnel source e0/0

Router-spoke2(config-if)#tunnel mode gre multipoint

Router-spoke2(config-if)#ip nhrp network-id 10

Router-spoke2(config-if)#ip nhrp authentication shiyan

Router-spoke2(config-if)#ip nhrp map multicast 1.1.1.3

Router-spoke2(config-if)#ip nhrp map 192.168.1.3 1.1.1.3 

Router-spoke2(config-if)#ip nhrp nhs 192.168.1.3

Router-spoke2(config-if)#ip ospf net point-to-multipoint

Router-spoke2(config-if)#ip nhrp shortcut

Router-spoke2(config-if)#exit
```

做好这样的准备工作之后我们便配置动态路由，不然私网内部的网络之间无法通信：

```
##Router-center config code for routing

Router-center(config)#router ospf 100

Router-center(config-router)#network 192.168.1.0 0.0.0.255 area 0

Router-center(config-router)#network 10.3.3.0 0.0.0.255 area 0

Router-center(config-router)#

##Router-spoke1 config code for routing

Router-spoke1(config)#router ospf 100

Router-spoke1(config-router)#network 192.168.1.0 0.0.0.255 area 0

Router-spoke1(config-router)#network 10.3.1.0 0.0.0.255 area 0

##Router-spoke2 config code for routing

Router-spoke2(config)#router ospf 100

Router-spoke2(config-router)#network 192.168.1.0 0.0.0.255 area 0

Router-spoke2(config-router)#network 10.3.2.0 0.0.0.255 area 0

Router-spoke2(config-router)#
```

4.验证隧道的建立与通信：

如此我们便配置好了动态路由与隧道接口，我们可以通过 `show ip route` 来查看，我们的 `10.3.0.0` 网段的学习来源：

![2-dmvpn-show-ip-route.png](https://doc.shiyanlou.com/document-uid113508labid2232timestamp1478240660149.png)

同时我们也能通过 spoke1 去 ping 通 spoke2 的所有地址，这些地址都是通过 Tunnel 端口学到的：

![3-dmvpn-ping-test](https://doc.shiyanlou.com/document-uid113508labid2232timestamp1478240790098.png)

还可以通过 nhrp 协议开查看：

![3-dmvpn-show-nhrp.png](https://doc.shiyanlou.com/document-uid113508labid2232timestamp1478241093931.png)

同样我们还可以通过 wireshark 抓包查看数据包中是否有使用 nhrp 协议来通信。

DMVPN 更多的时候是与 IPSec 结合使用，同时还会用到 GRE，但是这两个协议我们都没有细讲所以这里就不再继续深入了。

## 实验总结

通过本章节的学习我们大致了解了一下 DMVPN 的作用，也小小的体验了一下，可能现在你还是晕乎乎的，没关系，留个印象，以后再深入学习的时候会轻松许多。