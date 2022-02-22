## 一、实验介绍

在上节实验中带领大家完成了 VLAN 间路由的配置，以及了解路由相关协议的分类。同时还完成了静态路由协议的配置和默认路由、浮动路由的认识与配置。本实验将开始动态路由协议的学习，从三个方面（功能，适用范围，如何使用）来入手较为简单的 RIP 协议。

### 1.1 实验涉及的知识点

- RIP 的简介
- RIP 的原理
- RIP 的配置

## 二、RIP 的简介

RIP（Routing Information Protocol 路由信息协议） 属于动态协议中的一种，相对于静态需要手工一台台配置，并且在网络结构发生变化的时候还需要逐个修改的情况下，动态协议不需要逐个配置路由器的路由表，设备之间会通过动态路由协议去相互学习路由表一次来更新路由表，从而实现不同网段、网络之间的相互通信。

这就是 RIP 的功能。

RIP 只能适用中小型的网络，这是 RIP 的适用范围。

为什么 RIP 只能使用于中小型网络？我们在上一实验中提到过 RIP 是属于 Distance-vector routing protocol（距离矢量路由协议），这一类的路由协议使用的是 Bellman-Ford、 Ford–Fulkerson 、DUAL FSM 算法来计算路径的。这样的算法是通过数据包路途会经过多少个路由（也就是多少跳，跳数 Hop Count）来衡量一条路径的好坏，并且设计者当时一个网络的直径不应该超过 15 跳（也就是不应该经过超过 15 个路由），超过该跳数时延会很大，所以在该协议中超过 15 跳的数据包便会被丢弃，标识为不可达。而设计者这样的考虑是因为在 ARPANET 网络的初期建设时就使用的这个算法，所以当时他们所考虑的是跳数，而不像后期的动态路由协议那样考虑的更加的全面。RIP 可以算是最为古老的路由协议之一了。

正因为使用 RIP 的网络直径不能超过 15 跳，所以 RIP 协议只能适用 15 跳以内的中小型网络，并且只能是一种内部网关路由协议（IGP），在一个自治系统（AS）内传递路由信息。

在上一实验中我们简单的提到了自治系统（Autonomous System），自治系统就是一堆路由器及其 IP 的集合，并且该集合有专门的机构或者组织管理。一个自制系统中并没有定义一定要有多少台路由器，只要在这个集合中有使用一台指定的 Router 来与其他的集合交换信息的便是一个自治系统。通常是一个互联网服务提供商或一个拥有到多个网络的独立连接的大型组织，其遵循一个单一且明确的路由策略，这样的定义在后期已经废止，新的定义可以查看 [RFC 1930](http://tools.ietf.org/html/rfc1930)。公开被认可的自治系统编号是由互联网地址分派机构（IANA，Internet Assigned Numbers Authority）成批地分配给各个区域互联网注册管理机构（RIR），具体的信息查看[这篇文章](https://zh.wikipedia.org/wiki/自治系统)

通畅在自治系统中使用的路由协议我们便称之为内部网关路由协议（Interior gateway protocol），自治系统之间的传输消息使用的协议我们称之为外部网关路由协议（Exterior Gateway Protocol）

![iprip1.gif](https://doc.shiyanlou.com/document-uid113508labid2213timestamp1477452340451.png) （此图来自于[葉建良的RIP](http://www.clyeh.org/iprip/iprip.htm)）

RIP 协议的使用也十分简单，只需要在相关的设备中开启 RIP 进程，同时发布自己的网络，之后 RIP 便会自己维护自身设备中的路由表信息，保持网络的稳定与通畅。在配置 RIP 之前我们将学习 RIP 学习的原理以及运行的流程，这样更易于对于 RIP 信息的查看、配置参数的使用、网络的排错。

![RIP info.png](https://doc.shiyanlou.com/document-uid113508labid2213timestamp1477451922522.png)

## 三、RIP 的原理

我们通过这样的一个工作场景来阐述 RIP 的工作流程：

![rip-decri.png](https://doc.shiyanlou.com/document-uid113508labid2213timestamp1477460449909.png)

1.在需要运行 RIP 设备上开启 RIP 功能，开启 RIP 功能后，系统会在设备的系统中启动三个进程：

![show-rip-process.png](https://doc.shiyanlou.com/document-uid113508labid2213timestamp1477460896212.png)

分别是 RIP Router 主进程，RIP Send 发送宣告进程以及 RIP Timers 计时进程。

2.RIP 进程在允许 RIP 运行的接口上以广播的形式向邻居发送路由表的请求。

![show-rip-request.png](https://doc.shiyanlou.com/document-uid113508labid2213timestamp1477468015436.png)

3.作为邻居的 Router2 收到了 Router1 发送的 RIP 信息的请求，若是 Router2 上并未启动 RIP 进程则不会理会，若是 Router 2 上开启了 RIP 进程，接收到了 Router1 的请求之后便将路由表信息整合在 RIP 的响应包中回复 Router1 的请求。

![show-rip-respnse.png](https://doc.shiyanlou.com/document-uid113508labid2213timestamp1477468111230.png)

4.Router1 收到了 Router2 的响应 RIP 报文，报文中的 Metric 度量值会加 1，因为度量值在 RIP 中表示的跳数 Hop Count，从 Router2 到 Router1 需要一跳，所以报文中的每一个表项的度量值都会加 1。Router1 查看响应报文中的内容，并不会马上将其中的所有内容都更新到自己的路由表中，会先做这样的一层判断：

- 该路由信息在自身的路由表中不存在便更新到自己的路由表中
- 该路由信息在自身的路由表中存在便与自身的路由表项比较度量值，也就是跳数，若是值大于自身表项的度量值便丢弃，若是值小于自身表项的度量值便替换自身的表项。
- 该路由信息在自身的路由表中存在，并且跳数相同，学习来源也相同，跳数也相同，则路由表将使用新的条目替换已存在的条目。

Router1 判断之后更新自己路由表。

5.Router1 与 Router2 的 RIP 进程启动之后 Timer 也随之工作，其中 Update timer 更新计时器的值为 30 秒，一旦超时便广播（目标地址为 255.255.255.255）更新消息，发送之后重置时间，继续工作，所以每隔 30 秒 Router1 与 Router2 都会相互发送更新应答数据包。

称为更新数据包是因为从其他路由中学习到的表项加入路由表之后都有一个 Invalid timer 无效计时器，其默认值是 180 秒。例如 Router1 在 Router2 中学习到 `192.15.1.0` 网段的路由表项，Invalid timer 便开始计时，当 180 秒之后若是没有收到 Router2 的更新消息，也就是 Invalid timer 已超时，便认为这个网段已经不可达，将其状态标志为 possibly down、跳数值改为 16，因为 RIP 的跳数值最大只能接收 15，所以 16 对 RIP 进程来说表示无穷大，不可达。若是收到更新数据包便更新 Invalid timer 的时间，重置为初始值，重新开始计时。

与无效计时器同时启动的还有 flush timer 清除计时器，其默认值是 240 秒，也就是在 Invalid timer 时间到后 60 秒依然没有收到更新的数据包便将该表项从路由表中删除。

所以更新数据包在不断更新其他路由器中学习到的路由条目的无效计时器与清除计时器。

这边是 RIP 学习数据包，与更新 Timer 和路由信息的整个过程，而这样的 RIP 还是有问题，例如环路问题、收敛时间问题。

此处的环路与之前所接触到二层环路有所区别，此处的环路表示若是 Router1 中有个网段中断了，连接不上，过了 240 秒之后便删除了，但是 Router2 发过来的数据包中却有该信息（之前 Router1 传给它的），Router1 便重新学习了该路由信息，而 Router2 中该项得不到更新便删除了，而 Router1 的更新数据包中有该信息，Router2 又重新学习了，这样循环往复的下去直至条数为 16 才停止这个循环。

而 RIP 对于环路问题有这样的功能来解决：

- 毒性反转（Poison Reverse）、水平分割（Split Horizon）
- 触发更新（Triggered Update）

我们可以通过[这篇文章](http://www.clyeh.org/iprip/iprip.htm)来生动的学习水平分割与触发更新的整个流程。

RIPv1 的收敛时间也一直是 RIP 的一个弊病，需要 3 分钟未收到更新数据包才会进入 possibly down 的状态，进入改状态后再下一次更新的数据包中告知其他设备该链路处于这个状态，在本设备中再经过一分钟也就是 Flush Timer 时间到便会删除该条目，而其他设备在收到更新数据包将该条目更新至 possibly down 状态之后，启动 holddown period 抑制定时器，而抑制定时器的默认时间为 180 秒，也就是该条目还会在外存活 180 秒的时间。由此看出 RIP 的收敛时间十分的缓慢。

RIP 每隔 30 秒就会发送一次更新数据包，所以使用低时延的 UDP 即可，使用的端口号是 520。这便是 RIP 数据包这个在参考模型模型中的每一层所封装的信息：

![show-rip-packet.png](https://doc.shiyanlou.com/document-uid113508labid2213timestamp1477468531964.png)

针对 RIP 的收敛时间，安全等的一些问题，更新出了版本 2，在版本 2 中兼容 1，意味着 RIP V2 可以发送两个版本的数据包，但是 V1 只能发送自身版本的数据包。

版本 2 中做了这样的更新：

| RIP V1               | RIP V2                  |
| -------------------- | ----------------------- |
| 有类 Classful        | 无类classless           |
| 广播更新             | 组播更新                |
| 不支持验证           | 支持明文或 MD5 加密验证 |
| 更新消息中无子网掩码 | 更新消息中包含子网掩码  |
| 不支持VLSM、CIDR     | 支持VLSM、CIDR          |

## 四、RIP 的配置

明白了 RIP 整个工作流程，我们会发现 RIP 整个过程其实十分的简单就是发送请求、接收响应、更新路由表。而细节的处理程序会帮我们去做，我们需要做的仅仅只是启动 RIP 进程，发布网段而已，当然还有一些如版本使用、Timer 修改等的一些小配置项。

我们通过这样的一个实例来配置 RIP 功能：

- 实验目的：配置实现 RIP
- 实验材料：三台路由器
- 实验方法：
  - 拖动三台路由器至画布，
  - 配置路由器的名字与连接线路
  - 配置路由器的端口地址
  - 查看路由表，与尝试 ping 远程网络。
  - 配置 RIP，然后再次尝试上一步

1.同样我们开启实验环境，同时拖出三台路由器、连接起来，并且修改名字分别为 Router1、Router2、Router3

![rip-top.png](https://doc.shiyanlou.com/document-uid113508labid2226timestamp1517194836898.png)

2.按照图中的显示，分别配置三台路由器的接口地址。

```
#Router1

Router1#conf t

Router1(config)#int e0/0

Router1(config-if)#ip add 202.203.1.1 255.255.255.0

Router1(config-if)#no sh

Router1(config-if)#ex

Router1(config)#int lo 0

Router1(config-if)#ip add 192.168.1.1 255.255.255.0

Router1(config-if)#no sh

Router1(config-if)#ex

#Router2

Router2#conf t

Router2(config)#int e0/0

Router2(config-if)#ip add 202.203.1.2 255.255.255.0

Router2(config-if)#no sh

Router2(config-if)#ex

Router2(config)#int e0/1

Router2(config-if)#ip add 202.204.1.2 255.255.255.0

Router2(config-if)#no sh

Router2(config-if)#ex

Router2(config)#int lo 0

Router2(config-if)#ip add 192.15.1.1 255.255.255.0

Router2(config-if)#no sh

Router2(config-if)#ex

#Router3

Router3#conf t

Router3(config)#int e0/0

Router3(config-if)#ip add 202.204.1.1 255.255.255.0

Router3(config-if)#no sh

Router3(config-if)#ex

Router3(config)#int lo 0

Router3(config-if)#ip add 10.3.1.1 255.255.255.0

Router3(config-if)#no sh

Router3(config-if)#ex
```

![rip-config-interface.png](https://doc.shiyanlou.com/document-uid113508labid2213timestamp1477471373927.png)

3.查看此时的路由表信息以及 ping 连接的尝试：

![rip-show-iproute.png](https://doc.shiyanlou.com/document-uid113508labid2213timestamp1477472040760.png)

Router1、Router2、Router3相互 Ping 是不通的，并且路由表中只有自己直连的网段，没有其他路由的网段。

4.在所有设备中开启 RIP 进程，并且发布需要外界知道的网段，当然若是有不希望外界知道的私密网段，可以选择不发布，这样外界就无法知道该网段。同时我们使用 RIP V2 的版本：

```
#Router1 配置
#进入全局配置模式
Router1#conf t

#启动 RIP 进程
Router1(config)#router rip

#配置使用当前的 RIP 版本
Router1(config-router)#version 2

#发布 loopback 所处的网段
Router1(config-router)#network 192.168.1.0

#发布接口所配置的网段
Router1(config-router)#network 202.203.1.0

#Router2 配置

#进入全局配置模式
Router2#conf t

#启动 RIP 进程
Router2(config)#router rip

#配置使用当前的 RIP 版本
Router2(config-router)#version 2

#发布 loopback 所处的网段
Router2(config-router)#network 192.15.1.0

#发布直连 Router1 接口所配置的网段
Router2(config-router)#network 202.203.1.0

#发布直连 Router3 接口所配置的网段
Router2(config-router)#network 202.204.1.0


#Router3 配置
#进入全局配置模式
Router3#conf t

#启动 RIP 进程
Router3(config)#router rip

#配置使用当前的 RIP 版本
Router3(config-router)#version 2

#发布 loopback 所处的网段
Router3(config-router)#network 10.3.1.0

#发布接口所配置的网段
Router3(config-router)#network 202.204.1.0
```

5.查看此时的路由表看是否发生了变化：

![rip-show-iproute-after.png](https://doc.shiyanlou.com/document-uid113508labid2213timestamp1477473462388.png)

同时尝试使用 Router1、Router2、Router3 Ping 其他路由的网段：

![rip-show-ping.png](https://doc.shiyanlou.com/document-uid113508labid2213timestamp1477473962941.png)

由此我们便完成了 RIP 的简单配置，非常的简单。也就是启动进程，发布网段，指定版本就可以了。

配置后可能出现的问题：

1.RIP 版本的不兼容而导致出错

因为部分老的设备在不指定版本的情况下 RIP 默认使用的是 Version 1 的版本，虽然 Version 2 向下兼容，但是 Version 1 并不支持 Version 2 中新增加的功能，所以会出错。我可以使用这个命令查看当前的 RIP 版本：

```
show ip protocol
```

![show-rip-version.png](https://doc.shiyanlou.com/document-uid113508labid2213timestamp1477477577960.png)

若是还有部分设备是需要使用 Version1，我们可以在发送的端口中配置这样一个命令，让它能够同时发送 Version1 与 Version2 的数据包，也能够接受这两个版本的数据包：

```
#配置端口
Router1(config)#int e0/0

#能够同时发送两个版本的数据包
Router1(config-if)#ip rip send version 1 2

#能够同时接受两个版本的数据包
Router1(config-if)#ip rip receive version 1 2
```

![show-rip-version-send.png](https://doc.shiyanlou.com/document-uid113508labid2213timestamp1477495281318.png)

2.不连续网络的路由信息

RIPv1 中路由更新信息中不含有子网掩码，所以不支持不连续的子网，解决方式便是开启 Version2 同时关闭自动路由汇总的功能 `no auto-summar`。因为在 Version2 中开始 VLSM 与 CIDR 的功能。

3.认证密钥的不匹配

RIPv2 中增加了认证机制来增强安全特性，当开启此功能后必须双方都配置口令，不过不匹配的话则忽略双方的更新包。该功能配置于端口上，这样可以防止收到伪造的数据包，来攻击当前的网络，从而避免出现网络的摆动、震荡、不稳定。

若是双方端口的认证不匹配将无法更新路由条目，并且已更新的条目也会因为无效计时器与清除计时器而被删除

就像这样，我在 Router1 上配置了口令，但是在 Router2 的对应端口没有配置

```
#定义密钥链
Router1(config)#key chain shiyanlou

#定义密钥编号
Router1(config-keychain)#key 1

#定义密钥
Router1(config-keychain-key)#key-string shiyanlou

#进入端口配置
Router1(config)#int e0/0

#配置认证密钥的模式为 md5 加密
Router1(config-if)#ip rip authentication mode md5

#配置在该端口使用 shiyanlou 密钥链
Router1(config-if)#ip rip authentication key-chain shiyanlou
```

我们可以查看我们的路由表，此时当中没有了之前从 Router2 中学习到的路由信息了：

![show-rip-auth-delete.png](https://doc.shiyanlou.com/document-uid113508labid2213timestamp1477478732130.png)

我们可以通过 debug 调试模式来查看 Router1 的确是把所有没有认证端口的更新数据包都给忽略掉了，并告知我们原因是 invalid authentication：

```
#开启调试模式
Router1#debug ip rip

#关闭调试模式
Router1#no debug ip rip
```

![show-rip-debug-auth.png](https://doc.shiyanlou.com/document-uid113508labid2213timestamp1477493909271.png)

此时若是我们在 Router2 中做同样的配置，配置好密钥链、密钥编号、对应的密文、使用相同的 md5 加密模式，并且关联密钥链。我们会发现过段时间之后（收敛时间），Router1 又再次学习到了来自 Router2 上的路由信息，开启 debug 模式之后我们会看到这样的提示：

![show-rip-debug-auth-success.png](https://doc.shiyanlou.com/document-uid113508labid2213timestamp1477494378364.png)

若是我们没有采用 MD5 加密认证的方式，在端口中配置的模式是 `ip rip authentication mode text`，认证口令会已明文的方式显示出来，这样是极度不安全的：

![show-rip-debug-auth-text.png](https://doc.shiyanlou.com/document-uid113508labid2213timestamp1477494688879.png)

同时上文我们提到过问了解决环路与收敛时间的问题，提出了触发更新的机制，表示只要路由表中发生了变化，便不用等待 UPdate Timer 时间直接向外发送更新数据包，而这个机制的配置十分的简单，就是在需要端口的配置模式中使用这条命令即可：

```
Router1(config-if)#ip rip triggered
```

> 注意：该命令只能在串口中使用，不能再以太网口中使用。

还有若是需要使用 RIP 协议，但是又嫌弃 RIP 的收敛时间过程，我们可以在 RIP 的配置模式中修改 Timer 们的值：

```
Router2(config-router)#timers basic 10 30 30 100
```

![rip-config-timer.png](https://doc.shiyanlou.com/document-uid113508labid2213timestamp1477496496251.png)

这便是 RIP 的所有相关配置选项以及其运作的方式。

## 五、实验总结

通过本实验我们知道了 RIP 协议到底是个什么样的协议，RIP 协议的工作流程又是如何，同时关于一些 RIP 安全的问题。最后我们真正的配置了一次 RIP 协议，从而达到理论实践两不误。

## 六、参考资料

[1]Distance-vector Routing Protocol：https://en.wikipedia.org/wiki/Distance-vector_routing_protocol [2]葉建良 的 RIP：http://www.clyeh.org/iprip/iprip.htm [3]自治系统：[https://zh.wikipedia.org/wiki/%E8%87%AA%E6%B2%BB%E7%B3%BB%E7%BB%9F](https://zh.wikipedia.org/wiki/自治系统) [4]RIP version：https://learningnetwork.cisco.com/docs/DOC-8402