## 一、实验介绍

上节实验我们认识到了 RIP 动态路由协议的原理以及配置的方法与注意事项，但 RIP 协议更多的用于中小型网络，在中大型网络中我们更多的使用 OSPF 的动态路由协议，本实验将粗略的带领大家认识 OSPF，以及简单的配置。

### 1.1 实验涉及的知识点

- OSPF 的简介
- OSPF 的工作流程
- OSPF 的基本配置

![OSPF.png](https://doc.shiyanlou.com/document-uid113508labid2226timestamp1477562489593.png)

## 二、 OSPF 的简介

OSPF （Open Shortest Path First）名为开放式最短路径优先，该协议同属于动态路由协议，动态路由协议相较于静态路由的优势便不在多说，OSPF 协议同样可以让网络中的设备自己学习整个网络的路由信息，不用手工的去维护。同时不受跳数的闲置，有较快的收敛时间。OSPF 已经发布了三个版本，Version 2 对 Version 1 做了一定的优化，Version 2 适用于 IPv4，Version 3 适用于 IPv6。

从功能的简述上看似乎与 RIP 并没有多大的区别，那么 OSPF 存在的价值在何处呢？

首先 OSPF 使用的是算法基于链路状态的 Dijkstra's algorithm，用于计算最短路径树，以 Cost 开销作为链路的度量值，脱离了基于 Bellman-Ford 距离矢量算法的传统路由协议，也就是 RIP 所使用的算法，以跳数值来作为度量值。

由于 OSPF 是使用的基于链路状态的算法，所以他并没有跳数的限制。而 RIP 是使用的距离矢量算法，所以在使用的时候有跳数的限制，不能超过 15 跳。即使像 EIGRP （增强型内部网关协议）这样混合型路由协议同时对跳数、链路状态作为参考也有对跳数的限制，不能超过 200 跳。

同时 OSPF 支持变长子网掩码的使用，支持路由的汇聚功能。而在 RIP 中在 Version 2 版本才支持。

OSPF 的收敛速度比 RIP 的快许多。OSPF 在初次建立之时可以短短几秒钟便完成网络的稳定，当然我们不能以这样简单的量化时间去衡量一个路由协议的好坏，毕竟在收敛时间受很多情况的影响，网络的初步建立、网络从故障中恢复等等情况。但是根据大量的实践情况与实例证明可以得出在相同的情况下 OSPF 的收敛时间是 RIP 所不可比的。

OSPF 能够非常快速的适应网络的变化，在网络变化时也是采取的出发更新，并且在更新只是只发送更新网络的数据内容，而不像 RIP 会将整张路由表都发送过去，同时定期更新的频次很低，相较于 RIP 的 30s 发送一次节约了很多的带宽。

OSPF 支持认证功能，而 RIP 到了 Version2 才有此功能，提供了明文，MD5 加密，不开启的技术支持。

OSPF 还拥有比 RIP 更多的 IOS 工具库可以使用。

所以我们可以得出这样的结论：

| OSPF                              | RIP                              |
| --------------------------------- | -------------------------------- |
| 基于链路状态的算法                | 基于距离矢量的算法               |
| 不受跳数的限制                    | 受限于跳数                       |
| 工作于 AS 之内，适用于中大型网络  | 工作于 AS 之内，适用于中小型网络 |
| 基于无类网络设计，支持 VLSM、CIDR | Version 2 才支持                 |
| 收敛速度快                        | 收敛速度慢                       |
| 更新频次低，节省带宽              | 更新频次高，带宽消耗大           |
| 支持认证功能                      | Vesion 2 才支持                  |

这边是 OSPF 与 RIP 的简单对比。

同时我们从上述的对比中也看到了 OSPF 更适用于 中大型的网络中，因为他没有跳数的限制，收敛速度也快。

虽然 OSPF 的结构、理论上看起来似乎有些复杂，但是配置命令上确并不复杂，主要的功能配置几乎与 RIP 的命令相差不大。

- 开启 OSPF 进程
- 发布网段，包含网段与反掩码以及所属区域

## 三、 OSPF 的工作流程

OSPF 经过这样的过程来使得路由的链路状态来达到收敛的状态：

1.首先建立邻接关系。

只有建立好了邻接关系才能在后期做到信息共享，扩充路由表中的信息。

（1）设备在启动 OSPF 进程之后会向所有的开启支持 OSPF 端口发送 Hello 包，以确定他们的链路上是否存在邻居。此时链路的状态从 Down State 转变为 Attempt State。

（2）对端路由器在接收到 Hello 数据包之后，检查其中的字段，若是 Neighbor 中并没有包含自己的 Router ID，此时链路的状态从 Attempt 转变为 Init State，并把对方的 Router ID、Area ID、优先级、子网掩码、Hello 包时间间隔等等一些配置信息记录下来.同时将自己的信息放入 Hello 包中发送给源路由。

（3）在源路由收到对端路由的 Hello 包之后，在 Neighbor 字段中发现自己的 Router ID 便知道刚刚对端路由已经收到自己 Hello 包，就像消息确认一般。此时链路的状态从 Init State 转变成 Two-ways State。在消息确认中两台路由器的 Hello 间隔、Dead 间隔、网络类型这些参数必须一致，若是一致两台路由器便建立好了邻居关系。

进入改状态的路由便可开始 DR（Designated Router 指派路由，负责使用该变化信息更新其他路由的主设备）的选举了，同时 Hello 报文是周期性的发送，用于实时告知邻居状态，若是在一段时间内没有收到 Hello 数据包，或者 Hello 数据包中无自己的 Router ID，链路的状态会从 Two-ways State 回退到 Init State

（4）建立好邻居关系之后便创建邻居表来记录邻居关系，同时开始 DR 与 BDR（Backup Designated Router）的选举，根据他们的优先级、Router ID 来选举。DR 的选举也标志着链路的状态从 Two-ways State 转变成 Exstart State。选举的完成也标志这该状态的结束。

虽然 DR 的选举完成，也就标志着第一阶段的邻居建立关系的协商结束了。

> 注意：邻居关系与邻接关系是不同的。（DR 路由器会在下文详解）

- 邻居关系（neighbor）：任意两台启用了 OSPF 的路由器，相互的 Hello 数据包协商，在信息匹配之后都能够形成邻居关系。
- 邻接关系（Adjacency）：启用了 OSPF 的路由器与 DR 或者 BDR 形成的关系叫做邻接关系邻居之间需要同步链路状态数据库，那么它们之间需要建立邻接关系。建立了邻接关系的路由器，那么它们的链路状态数据库一定是同步的。 在广播型链路中需要通过选举来确定 DR 与 BDR，然后形成邻接关系。而在点到点的链路中，直接形成邻接关系不会选举。

2.交换链路状态通告，数据同步

每台运行着 OSPF 的路由器都会维持一个链路状态数据库。在建立了邻接关系之后，路由器会相互发送链路状态通告（LSA，Link state Advertisement），通过 DBD 数据包（Database Description，有时也称为 DD）描述自己所知道的直连链路的状态、开销等等的信息；通过 LSR 数据包（Link state Request）请求邻接路由发送链路状态更新包，LSU 数据包（Link state update：链路状态更新数据包）用于回应 LSR 而发送的更新数据包，在收到了 LSU 数据包之后会向对方发送 LSAck 数据包（Link state Acknowledgment）用于确认对方所发送的 LSU 数据包。

路由器在收到 LSA 后会以通过 `224.0.0.5` 的组播地址泛洪到邻居路由上。收到 LSA 的邻接路由立即将 LSA 泛洪到其他直接连接的邻居，直到区域中的所有路由器收到所有 LSA。

当该区域中所有的路由设备的链路状态数据库都同步完成，链路会经历 Exchange State --> Loading State --> Full State 这样的三个状态。

3.路由的生成

一旦路由器收到所有 LSA 并建立好了其本机的链路状态数据库，也就代表这它拥有了所有的路由器及其状态的信息。

OSPF 会根据收到的 LSA 信息构建出拓扑表（LSDB），由此数据库负责维护网络的拓扑信息。

此时的 OSPF 就会使用 Dijkstra 算法，也就是 SPF 最短路劲优先算法，创建一个 SPF 树。（在交换机环路的实验中我们便讨论了树形结构才不会导致环路的产生，所以会生成一颗树）

每个路由器都有自己生成的一棵树，都是以自己为根节点生成的一棵树，也就代表都是站在自己的角度，根据每条链路的带宽来算出到达每个节点的最短路径。最后将计算得出的每条最短路劲插入路由表中。

这样路由器根据路由表中提供的信息，能够将数据从最佳的接口转发出去。

这便是 OSPF 相互通信，并最终建立自己的路由表的整个过程。

![ospf-state-change](https://doc.shiyanlou.com/document-uid113508labid2213timestamp1477551264838.png) （此图来自于[上午八点的博客]（http://blog.sina.com.cn/s/blog_57305f200100pgzh.html））

在整个过程中我们可以得到 OSFP 一共会建立三张表，使用五种数据包，链路有八种状态的变化。

- 三张表：邻居表、拓扑表、路由表

| 名字   | 作用                                                         |
| ------ | ------------------------------------------------------------ |
| 邻居表 | 记录所有已知邻居的数据库                                     |
| 拓扑表 | 记录了同区域中中所有路由器以及相关链路的信息                 |
| 路由表 | 记录路由信息，也叫转发数据库（forwarding database），由 SPF 计算得出 |

- 五种数据包：

  | 名字     | 作用                                                     |
  | -------- | -------------------------------------------------------- |
  | Hello 包 | 与邻居建立关系，并且维护这个关系，使用组播地址 224.0.0.5 |
  | DBD 包   | 描述本地链路状态                                         |
  | LSR 包   | 请求相邻路由器发送其数据库中链路状态的具体条目           |
  | LSU 包   | 向邻居发送链路状态的条目及信息                           |
  | LSAck 包 | 向被请求方确认收到数据包                                 |

- 八种状态：Down state、Init State、Attempt State（部分讲解中没有这个状态）、Two-ways State、Exstart State、Exchange State、Loading State、Full State

在上文中我们提到了 DR 与 BDR 的概念，所有的路由会分为三种角色，DR（Designated Router 指派路由）、BDR（Backup Designated Router 后备指派路由）、DROther（非指定路由）。为了减少链路中的满天飞舞着 OSPF 的数据包，出现了 DR 这个角色，在一个区域中只有个一个 DR 与 BDR。

DR 主要用于与其他路由建立邻接关系，同时所有的邻居或者邻接的路由都会将 LSA 的信息发送到 DR 上，由 DR 作为 LSA 信息的集中点、汇总点，作为 LSDB 广播的发送者，为网络中的其他路由器规划拓扑，并确保区域中所有的 Router 的链路状态数据库保持同步。

BDR 作为 DR 的备选者，通过计时器检测 DR 的更新活动，能在 DR 挂掉之后能够充当 DR 角色。

DROther 与 DR 和 BDR 形成邻接关系，与其他 DROther 角色只发送 HELLO 数据包。这样避免了每台路由器都与其他路由器建立邻居关系，而产生额外的开销。

通常以优先级来选举 DR，优先级高者作为 DR（优先级的取值范围是 0~255），若是优先级为 0 则不参与选举，优先级相同则以 Router ID 做为依据来选举 DR，所有端口的 IP 地址中最大的一个作为 Router ID。若是路由器有回环接口则优先选择，因为回环接口较为稳定。

> 注意：路由器的优先级会影响选举的过程，但是一旦确定之后不会因为新增路由器的优先级高而重新选举或者强制更换已经有效的 DR 与 BDR。

为了使得 OSPF 更加的高效并且可扩展，OSPF 提出了区域的概念，多个区域支持分层的路由与分层的网络结构。

每个网络都必须至少有一个区域，并且至少有一个骨干区域（backbone area），区域编号为 0。

- 网络只有一个区域，该区域便是骨干区域。
- 网络中有多个区域，此方式适用于分层结构的网络，在多区域中必须有一个，并且仅有一个骨干区域（backbone area），同时每个非骨干区域都必须（nonbackbone area）与骨干区域相连。

处于不同区域之间的临界路由称之为区域边界路由（ABR，Area Border Router）

当一个自治系统很大的时候，只有一个区域的话，每台路由器的链路状态数据库（Link state Database，LSDB）将会非常的庞大，而这些信息都交给 SPF 算法去计算，将会消耗巨大的 CPU 资源，而且网络稳定之后若是其中某台路由的信息变化了（信息变化表示如优先级、RID、链路带宽等等的这些信息改变），便需要更新 LSDB 并重新启用 SPF 算法全部重新计算一次，这样将非常的费时与浪费 CPU 资源。

> 注意：若是简单的网络拓扑更改只会之间更新路由表，不会重新启用 SPF 计算。

划分区域的话，便将一个大的区域划分为若干个小的区域，这样一个小的区域中路由数量就不会很多，数量的减少在启用 SPF 的时候对 CPU 的压力就不会这么大。路由的 SPF 计算只会计算区域内部的路径，而区域边界路由传给其他路由的信息并不会这么细致，所以区域内的信息更改对其他区域的路由表不会有太大的影响，只是区域内部的重新计算，这样 CPU 也不会有太大的压力。

总的来说 OSPF 的划分区域有这样的一些优势：

- 路由表减小：区域之间的网络地址可以路由汇总，这样是的路由表的条目不会过大。
- 链路状态更新，系统资源开销减少：将 SPF 所占用的内存与 CPU 都降低。
- SPF 计算的频次减少：LSA　的泛洪会终止与区域的边界，这样降低路由更新所带来的影响，其他区的路由不必重新计算。

## 四、 OSPF 的基本配置

明白了 OSPF 大概的工作流程，我们会发现 OSPF 主要也就是三个步骤。而细节的处理程序会帮我们去做，我们需要做的仅仅只是启动 OSPF 进程，发布网段而已，当然还有一些小配置项，这里暂时不做过多的深究。

因为做的都是简单实现的小实验，不能明显的感受到这些动态路由的差异。但是在实际项目中就不同了，到时候的环境更为的复杂。

我们通过这样的一个实例来配置单区域的 OSPF 功能：

- 实验目的：配置实现 OSPF
- 实验材料：4台路由器以及一台交换机
- 实验方法：
  - 拖动4台路由器以及一台交换机至画布，
  - 配置路由器与交换机的名字与连接线路
  - 配置路由器的端口地址
  - 查看路由表，与尝试 ping 远程网络。
  - 配置 OSPF，然后再次尝试上一步

1.同样通过终端打开 GNS3，拖动四台路由器，一台交换机。配置设备的名称与线路，做出这样的拓扑结构：

![ospf-topology.png](https://doc.shiyanlou.com/document-uid113508labid2226timestamp1477615972500.png)

2.按照图中的表示我们分别配置四台路由设备的接口 IP 地址，其中我们的交换机只是用作中继作用，所以不用做任何的配置，直接工作即可。

```
# Router1 的接口配置
Router1(config)#int lo 0

Router1(config-if)#ip add 202.201.1.1 255.255.255.0

Router1(config-if)#no sh

Router1(config-if)#ex

Router1(config)#int e0/0

Router1(config-if)#ip add 202.202.1.1 255.255.255.0

Router1(config-if)#no sh

Router1(config-if)#ex

# Router2 的接口配置
Router2(config)#int lo 0

Router2(config-if)#ip add 202.203.1.1 255.255.255.0

Router2(config-if)#no sh

Router2(config-if)#ex

Router2(config)#int e0/0

Router2(config-if)#ip add 202.202.1.2 255.255.255.0

Router2(config-if)#no sh

Router2(config-if)#ex

Router2(config)#int e0/1

Router2(config-if)#ip add 202.204.1.1 255.255.255.0

Router2(config-if)#no sh

Router2(config-if)#ex

# Router3 的接口配置
Router3(config)#int lo 0

Router3(config-if)#ip add 192.168.1.1 255.255.255.0

Router3(config-if)#no sh

Router3(config-if)#ex

Router3(config)#int e0/0

Router3(config-if)#ip add 202.204.1.2 255.255.255.0

Router3(config-if)#no sh

Router3(config-if)#ex

# Router4
Router4(config)#int lo 0

Router4(config-if)#ip add 10.3.1.1 255.255.255.0

Router4(config-if)#no sh

Router4(config-if)#ex

Router4(config)#int e0/0

Router4(config-if)#ip add 202.204.1.3 255.255.255.0

Router4(config-if)#no sh

Router4(config-if)#ex
```

3.由此我们变配置好了所有的路由器上的端口 IP 地址，根据我们前面所学的只是必然是无法相互通信的，最多只能 ping 通直连的端口。只有相同 OSPF 参数配置的路由之间才能建立邻接关系，首先我们来启动 OSPF 进程，同时发布自己所拥有的网段。

而 OSPF 是根据无类网络所设计的，所以支持 VSLM 与 CIDR。如此在发布网络是需要加入反掩码，所谓的反掩码便是用 `255.255.255.255 - 当前的子网掩码` 所得到。

上文我们还提到过 OSPF 是基于所设计的，所以至少得有一个区域，而区域之中必须的有一个骨干区域，并且只能有一个。所以若是单区域的情况下该区域只能是骨干区域，骨干区域的预设区域值是 0。

在发布网段的时候必须说明该网段属于哪一个区域之中的。所以发布网络的格式是：

```
network 网络号  反掩码  area 区域号
```

由此我们需要对我们的四台路由器做这样的配置：

```
#Router1 的 OSPF 的配置
#启动 OSPF 进程，并制定其进程 ID
Router1(config)#router ospf 10

#发布自己环回接口地址
Router1(config-router)#network 202.201.1.0 0.0.0.255 area 0

#发布自己的与外连接网络
Router1(config-router)#network 202.202.1.0 0.0.0.255 area 0

#Router2 的 OSPF 的配置
#配置与 Router1 相同的进程 ID 
Router2(config)#router ospf 10

#发布自己的三个网络
Router2(config-router)#network 202.203.1.0 0.0.0.255 area 0
Router2(config-router)#network 202.202.1.0 0.0.0.255 area 0
Router2(config-router)#network 202.204.1.0 0.0.0.255 area 0

#Router3 的 OSPF 的配置
#做同样的配置，只是发布的是自己的网络
Router3(config)#router ospf 10

Router3(config-router)#network 192.168.1.0 0.0.0.255 area 0
Router3(config-router)#network 202.204.1.0 0.0.0.255 area 0

#Router4 的 OSPF 的配置

Router4(config)#router ospf 10

Router4(config-router)#network 10.3.1.0 0.0.0.255 area 0
Router4(config-router)#network 202.204.1.0 0.0.0.255 area 0
```

如此我们便配置好了四台设备中的 OSPF 信息。

3.我们可以通过 `show ip route ospf` 来查看当前的路由表中是不是有通过 OSPF 学习来的网络

![ospf-show-ip-route.png](https://doc.shiyanlou.com/document-uid113508labid2226timestamp1477614876381.png)

同时还可以使用 ping 命令来联通一下远程的网络：

![ospf-show-ping.png](https://doc.shiyanlou.com/document-uid113508labid2226timestamp1477614925779.png)

我们还可以通过 `show ip ospf neighbor` 来查看该设备的邻居关系，还有接口的状态与角色：

![ospf-show-neighbor-all.png](https://doc.shiyanlou.com/document-uid113508labid2226timestamp1477615532103.png)

通过 `show ip protocol` 也可看到 OSPF 相关的信息。

![ospf-show-ip-protocol.png](https://doc.shiyanlou.com/document-uid113508labid2226timestamp1477614981556.png)

我们还可以通过 `debug ip ospf adj` 开启 OSPF 的调试模式，这样系统将会在终端中显示 OSPF 的各种状态变化信息，若是没有信息的出现是因为此时的网络已经稳定，我们可以关闭 Router2 与本端口直连的接口，然后在开启，我可以看到各种调试信息的出现（记得关闭调试模式 `no debug ip ospf`）：

![ospf-show-debug.png](https://doc.shiyanlou.com/document-uid113508labid2226timestamp1477615005490.png)

这便是简单的单区域的 OSPF 配置，单区域的 OSPF 并不会太复杂，其命令也与 RIP 的很类似，同时我们来看一下认证的 OSPF 如何配置，注意在 OSPF 中消息的认证是与区域有关的，所以改一个区域中所有的设备都需要修改：

```
#进入特权模式中
Router1#conf t

#进入 OSPF 10 进程配置
Router1(config)#router ospf 10

#开启区域 0 的认证
Router1(config-router)#area 0 authentication

Router1(config-router)#exit

#进入端口模式中
Router1(config)#int e0/0

#配置该端口的认证密钥
Router1(config-if)#ip ospf authentication-key shiyanlo 
```

同样我们所示只配置了 Router1 中的认证，那么他与其他设备直接则无法通过认证，长时间无法与邻接设备通信则会删除学习到的路由信息

![ospf-show-auth-fail.png](https://doc.shiyanlou.com/document-uid113508labid2226timestamp1477615035785.png)

我们在 Router2 中配置相同的信息，会发现 Router1 不再显示不匹配的信息，并学习了 Router2 中的路由信息，但是因为只配置了与 Router1 直连的端口，与交换机直连的端口没有配置，而大家都是在一个区域 0 中，所以它不再信任 Router3 与 Router 4，因为他们没有提供认证信息。

![ospf-show-route-add-router2.png](https://doc.shiyanlou.com/document-uid113508labid2226timestamp1477615064025.png)

所以一旦一处配置了需要认证，那么所有的该区域的设备都必须做相同的配置。

在接口模式中我们使用这样的命令便可以使用 md5 加密的认证模式

```
#配置该端口的认证明文方式
Router1(config-if)#ip ospf authentication-key shiyanlo 

#配置该端口的认证 md5 加密方式
Router1(config-if)#ip ospf message-digest-key 1 md5 shiyanlou
```

这便是 OSPF 的单区域简单配置与相关的调试命令。

## 五、实验总结

通过本实验我们简单的学习了 OSPF，了解了单间的建立连接的过程，单区域的配置与认证的配置。OSPF 相对于 RIP 来说会复杂很多，本实验只是带领大家认识该协议，所以并未更深入的了解 Hello 的报文结构，多区域的配置方式等等的相关内容。

## 六、参考资料

[1] OSPF 状态的改变：http://blog.sina.com.cn/s/blog_57305f200100pgzh.html [2] Cisco OSPF：http://www.cisco.com/c/en/us/support/docs/ip/open-shortest-path-first-ospf/7039-1.html