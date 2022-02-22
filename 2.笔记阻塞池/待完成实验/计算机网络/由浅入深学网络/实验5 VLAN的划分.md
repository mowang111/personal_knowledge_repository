## 一、实验介绍

本实验将带领大家认识 VLAN，以及 VLAN 的配置与相关协议的使用。

### 1.1 实验涉及的知识点

- VLAN 的使用
- Trunk 模式
- VTP 的配置

## 二、VLAN 的使用

在上一节实验中我们了解到一台交换机的所有端口为一个广播域，若是交换机互联会使得广播域的进一步扩大，这样使得广播风暴产生的几率显著提高，同时局域网的安全性也不高，并且不易于管理。

同时在传统的局域网中每个网段便是一个逻辑工作组，多个逻辑工作组之间的通讯需要交换机或路由器来相互连接，若是一个节点需要从在工作组之间切换也是一件非常麻烦的事情。

由此在 1999 年 IEEE 颁布了 VLAN 实现方案的草案，VLAN（Virtual Local Area Network）称为虚拟局域网。以软件的形式实现了逻辑工作组的划分与管理，逻辑工作组的节点不再受到物理位置的限制，同时一个 VLAN 就是一个广播域，减小了广播域。

就像是在课堂上划分了不同的项目小组，组内的事情只需要在组内交流即可，不用在课堂上发言，让所有人都听。

总的来说 VLAN 有这样的一些优点：

- 控制网络的广播风暴：因为限制了广播范围，减少了参与广播的设备数量，从而减小了产生广播风暴的几率，并且即使产生广播风暴也会限制在一个 VLAN 的内部中，不会影响其他的 VLAN 与设备。
- 提高了网络的性能：减小了广播范围，使得数据只在 VLAN 内部广播，避免了无用数据包的传递，从而减少主干网络的流量，提高了网络的速度与效率。
- 增强网络的安全性：将交换机上的一些端口划分为不同的VLAN，就可以限制特定用户的访问，控制广播组的大小和位置，甚至锁定网络成员的MAC地址，这样就限制了未经安全许可的用户和网络成员对网络的使用。
- 易于管理：网络管理员可以轻松的管理整个网络，可以很简单的创建与删除一个 VLAN 工作组。

为了更有效的利用，通常会将一个 IP 网段划分为多个子网，一个子网对应一个 VLAN，同时将相同的工作组的端口映射在相同的 VLAN 中。

我们可以通过这样一个例子来直观的感受到 VLAN 减小了广播域，减少了不必要的数据转发。同时也学习如何创建 VLAN。

- 实验目的：学习配置 vlan，查看广播域的减小
- 实验材料：四台交换机
- 实验方法：
  - 拖动四台交换机至画布，其中三台用作模拟 PC，一台用作模拟交换机
  - 配置交换机的名字与模拟 PC 的名字
  - 开启设备与 wireshark 抓包与配置vlan 以及端口 IP
  - 查看广播数据包是否都能收到
  - 配置端口至不同的 vlan 中
  - 查看其中一个 VLAN 的广播包是否会发送到其他 VLAN 中

1.首先我们在终端中打开 GNS3，同时在画布中拖出 4 台交换机，其中一台改名为 `Switch1`，其他三台用作模拟 PC，分别命名为 PC1、PC2、PC3，同时修改其图标的样式：

![vlan-top.png](https://doc.shiyanlou.com/document-uid113508labid2126timestamp1476702459080.png)

2.在 Switch1 中配置两个 vlan 来做对比，分别为 vlan 2 与 vlan 3（因为每个 switch 中都有一个 native or default vlan，其 ID 是 1，作用在下文讲解）

```
#配置交换机的 vlan 信息

#进入全局配置模式
Switch1#conf t

#创建 ID 为 2 的 vlan，并进入配置
Switch1(config)#vlan 2

#配置 vlan2 的名字
Switch1(config-vlan)#name test1

#退出 vlan2 的配置模式
Switch1(config-vlan)#exit

#创建 ID 为 3 的 vlan，并进入配置
Switch1(config)#vlan 3

#配置 vlan2 的名字
Switch1(config-vlan)#name test2

#退出 vlan3 的配置模式
Switch1(config-vlan)#exit
```

![vlan-config.png](https://doc.shiyanlou.com/document-uid113508labid2126timestamp1476751894902.png)

3.虽然配置好了 vlan，但是端口都默认在 native vlan 中，我们可以先配置好各自的 IP 地址，ping 一下其中的一台，看广播的 ARP 数据包会在其他链路上吗？

![vlan-first-ip.png](https://doc.shiyanlou.com/document-uid113508labid2126timestamp1476752436497.png)

```
# 配置 PC1 的 IP 地址

#进入全局配置模式
PC1#conf t

#配置端口
PC1(config)#int e0/0

#关闭交换模式
PC1(config-if)#no switch

#配置 IP 地址
PC1(config-if)#ip add 192.168.1.1 255.255.255.0

#激活
PC1(config-if)#no sh

#退出
PC1(config-if)#end
```

相同的方式，配置 PC2 与 PC3 的 IP，地址分别为 `192.168.1.2` 与 `192.168.1.3`，然后我们通过 PC1 去 ping PC3，根据我们之前的讲解此处应该会接收到一些广播数据包，来查找 PC3，我们可以通过 wireshark 来看到这些数据包的存在：

![vlan-test-broadcast.png](https://doc.shiyanlou.com/document-uid113508labid2126timestamp1476753523764.png)

4.此时我们将连接 PC1 与 PC2 的端口 e0/0 与 e0/1 都配置在 vlan2 中，然后将 PC3 连接的端口 e0/2 配置在 vlan3 中，同时清理一下 MAC 地址表与 ARP 映射表，我们再来查看广播的数据包是否会蔓延到 vlan3。

首先将各个端口配置到相应的 vlan 中

```
#配置 switch 的端口 vlan 划分

#同时配置 e0/0 e0/1 两个端口
Switch1(config)#int range e0/0-1 

#将两个端口配置到 vlan2 中去
Switch1(config-if-range)#switch access vlan 2

#退出两个端口的配置
Switch1(config-if-range)#ex

#配置连接 PC3 的端口
Switch1(config)#int e0/2

#分配到 vlan3 中
Switch1(config-if)#switch access vlan 3

#退出配置
Switch1(config-if)#exit

#回到特权模式中
Switch1(config)#end

#在特权模式中查看 vlan 信息
Switch1#show vlan 
```

![vlan-access.png](https://doc.shiyanlou.com/document-uid113508labid2126timestamp1476754472872.png)

此时的我们可以看到，我们的 vlan 信息已经正确配置，vlan 的信息没有显示完最后一行有个 `more`，此时敲回车、敲空格可以把剩下的信息显示出来。

此时我们需要清理所有机器上面的 MAC 地址表与 ARP 映射表，否则当我们再去 ping 其他机器的时候，表中有记录，并不会再去广播数据包。

```
#清理 MAC 地址表与 ARP 表，所有的机器都执行一遍

#清理 MAC 地址表
PC1#clear mac address-table dynamic

#清理 ARP 表
PC1#clear arp
```

清理了 ARP，MAC 地址表之后，同时此时的 PC1 与 PC3 的端口已经处于不同的 vlan 中，此时我们再使用 PC1 去 ping PC3 机器。

![vlan-test-access.png](https://doc.shiyanlou.com/document-uid113508labid2126timestamp1476756381667.png)

因为此时的两台机器已经不在一个广播域中了，所以 PC1 是无法 ping 通 PC3 的，同时我们来查看广播的数据包：

![vlan-btoadcast-forword.png](https://doc.shiyanlou.com/document-uid113508labid2126timestamp1476782739440.png)

从图中我们可以看到 ID 为 2000 以后的数据包，PC1 再次 ping PC3 的时候，此时因为清理了 ARP 与 MAC 地址表，所以 PC1 会广播再次询问 PC3 的 IP 地址对应的 MAC 地址是谁，但是这个数据包并没有被广播转发到 PC3 对应的端口，因为他们在不同的 vlan 中，处于不同的广播域中，所以光靠这样的数据转发是转发不过去的。

由此我们看到了 vlan 是可以隔离广播域的，有效的减小广播域的范围，将一些只需要在部分范围内广播的数据包限定在一定范围中。

在试验中我们创建 vlan 的 ID 是从 2 开始的，这是因为在本机中存在一个 vlan 1，它是系统默认生成的 vlan，一般称之为 default vlan，或者 native vlan。（当然不同厂商的称呼不同，华为的便叫做 pvid，或者有些特殊的没有这样的默认 vlan）

而 vlan1 的存在是因为 Cisco 是一个大厂商，有许多自己的协议（比如之前提到过的 CDP），设备之间交互这种独有的数据，需要在二层中无障碍的传输，而数据帧中是需要添加 vlan 信息的，但是添加 vlan 信息的话，具体的 vlan 信息又不知道，所以想办法不加 vlan 的标签信息，由此设置了 native vlan，通过 native vlan 传输的数据是不需要添加 vlan 信息的。

为什么数据帧会添加 vlan 信息呢？既然我们划分了 vlan 的话，若是不添加 vlan tag 标志信息，那么与原始的数据包相同，这样的话如何区分该数据包所处的 vlan 呢？如何来隔离广播域呢？所以在交换机与交换机之间传输时便需要添加 vlan 信息。

在使用 VLAN ID 的时候有这样的一个范围，其最大值为 4095，而其中一部分有特殊的作用：

| VLAN 范围 | 状态 | 用途 | 通过 VTP 扩散| |--------|--------| | 0与4095 | 保留 | 仅限系统的使用，用户不能查看和使用这两个 vlan | --- | | 1 | 正常 | Cisco 默认 VLAN，用户可以使用该 VLAN，但是不能删除 | 可以 | | 2~~1001| 正常 | 用于以太网的 VLAN，用户可以创建、使用、删除 | 可以 | | 1002~~1005 | 正常 | 用于 FDDI 和 令牌环的思科默认 VLAN，用户不能删除| 可以 | | 1006~1024 | 保留 | 仅限系统使用，用户不能查看与使用 | --- | | 1025～4095 | 扩展 vlan | 仅用于以太网 vlan | |

在我们的实验中只有一台交换机，而 vlan 的信息是在于交换机与端口之上，而我们所看到的数据包是终端设备与交换机之间，所以我们所看到的数据帧中并没有这样的信息。而当两台交换机之间相互传递信息的时候就会发现该标签，而该标签是在信息从交换机出来的时候添加封装信息包头时加上的。

## 三、Trunk 模式

在交换机的汇聚链接上，可以通过对数据帧添加 VLAN 信息，构建跨越多台交换机的 VLAN。而这种添加 VLAN 信息的功能由 VLAN 中继（trunk）封装协议来搞定。

而这样的封装协议有这样两个较为常用：

- IEEE802.1Q
- ISL（Inter-Switch Link Protocol）：交换链路内协议，该协议是思科的私有协议

两个协议能够完成相同的任务，但 ISL 是思科的私有协议，所以它只能在思科设备之间是使用，而 IEEE802.1Q 是公共协议，所有的设备都支持，包括思科的设备。

同时两中方式所产生的数据帧也是不同的：

- IEEE802.1Q 的方式是在原有的以太帧中目的 MAC 地址与源地址之后添加信息，同时因为以太帧的结构改变所以 CRC 循环校验码也会重新计算。

| 目的 MAC 地址 | 源 MAC 地址 | TPID |TCI|type |数据部分|CRC| |--------|--------| |||表明这是802.1Q 的帧（新加的）|优先级、规范、VLAN ID的信息（新加的）|||重新计算的|

- ISL 的方式是不改变原有的以太帧，只是在原来的以太帧的头部加上 ISL 包头，在尾部加上这个新的以太帧的 CRC 循环校验码

| ISL包头| 目的 MAC 地址 | 源 MAC 地址 |数据部分|CRC|CRC| |--------|--------| |VLAN 等等的一些信息（新增的）||||原有的 CRC|重新计算的|

具体的数据包信息我们可以通过[这篇文章](http://blog.csdn.net/baniel01/article/details/8487746)来学习了解。因为在实际部署过程中很少有全是思科的设备，所以 ISL 使用的并不是那么的广泛，更多的时候使用 802.1Q。

正因为这样的协议出现也使得出现了不同的链路模式，而不同的链路对应着相应的端口模式，以此来区别该端口是用作交换机之间相连接的中继端口的链路（中继也就是中间接力），还是与用户相连接的接入端口的链路，所以交换机中的链路模式有：

- 接入链路（Access Link，或称访问链路）：他只能与一个 Vlan 关联，并且只能传送不带标签(untagged)的以太网帧，也就是原始的以太帧没有经过终极协议加工过的。将没有也无法识别Vlan标签的设备(如用户主机 PC)连接到配置Vlan的交换机端口。
- 汇聚链路(Trunk Link，或称干道链路、中继链路) ：可与多个Vlan相关联，可传输发往多个 Vlan 的带标签(tagged)帧。连接两个能够识别 Vlan 标签的设备(如交换机)，
- 混合链路(Hybrid Link)：既可传送不带标签的帧，也可传送带标签的帧。但对于一个特定 Vlan，传送的所有帧必须类型相同，即对于一个 Vlan，传送的帧要么不带标签，要么携带相同标签。

相应的链路模式对应着相应模式的端口。

这也就是为什么在刚刚的试验中，与 PC 相连的端口我们都配置成 Access 模式，并关联一个 VLAN ID。

这是对于 VLAN 的一个初步了解，若是想更深入学习 VLAN 相关知识的同学可以通过[这篇文章](http://www.cnblogs.com/clover-toeic/p/3741115.html)来了解 VLAN 的扩展、PVlan、SuperVlan 的一些信息。

## 四、VTP 功能

通过上文我们知道存在着交换机互联的情况下，比如说公司的二楼与三楼都有着研发部与人事部的同学，两层楼的 vlan 信息相同，此时我们若是修改其中一台设备中的 vlan 信息，必须同时去修改另外一台中的信息，这是一两台的情况下已经这么麻烦了，若是几十台呢？由此出现了一个非常方便的协议： VTP（VLAN Trunking Protocol）

VTP 是 VLAN 中继协议，也被称为虚拟局域网干道协议。它是思科私有协议。作用是十几台交换机在企业网中，配置 VLAN 工作量大，可以使用 VTP 协议，把一台交换机配置成 VTP Server, 其余交换机配置成 VTP Client,这样可以自动学习到 server 上的 VLAN 信息。

Cisco 的设备默认开启了 VTP 功能，并且默认的模式是 Server 模式，所以只要你将端口设置成了 Trunk 模式，相连的设备便会学习到 Vlan 信息。我们可以做这样的一个小实验来体验一下 VTP 功能所带来的便捷之处：

- 实验目的：学习配置 trunk 与 vtp
- 实验材料：两台交换机
- 实验方法：
  - 拖动两台交换机至画布，两台用做模拟交换机
  - 配置交换机名字
  - 配置 vlan 与相应端口的模式
  - 查看相邻交换机的 vlan 信息

1.首先在画布中拖动两台交换机，相互连接，并修改他们的名字，分别为 Switch1、Switch2

![vtp-devices.png](https://doc.shiyanlou.com/document-uid113508labid2126timestamp1476772837303.png)

2.接着开启设备，首先查看两台设备的 vlan 信息，然后配置其端口模式与 vtp 模式：

```
#在特权模式中查看该设备的 vlan 信息
show vlan
```

此时两台设备中都是默认的 vlan 信息，然后我们配置 Switch 1 中的 vlan 信息

```
#进入全局配置模式
Switch1#conf t

#创建 vlan2
Switch1(config)#vlan 2

#配置 vlan2 的名称
Switch1(config-vlan)#name test2

#退出 vlan2 的配置模式
Switch1(config-vlan)#exit

#创建 vlan3
Switch1(config)#vlan 3

#配置 vlan3 的名称
Switch1(config-vlan)#name test3

#回到特权模式中
Switch1(config-vlan)#end

#查看此时的vlan信息
Switch1#show vlan
```

![vtp-create-vlan.png](https://doc.shiyanlou.com/document-uid113508labid2126timestamp1476773334000.png)

同时我们可以看见此时的 Switch 2 中还是只有默认的 vlan 信息：

![vtp-vlan-origin.png](https://doc.shiyanlou.com/document-uid113508labid2126timestamp1476773464329.png)

然后我们配置 Switch 1 中的端口的模式与 VTP 信息：

```
#配置相连的端口 e0/0 
Switch1(config)#int e0/0

#设置使用 trunk 模式时的封装协议
Switch1(config-if)#switchport trunk encapsulation dot1q 

#设置该端口为 trunk 模式
Switch1(config-if)#switchport mode trunk

#激活端口
Switch1(config-if)#no sh

Switch1(config-if)#exit

#在全局模式中配置 vtp 模式为 server，其实默认就是 server
Switch1(config)#vtp mode server

#配置 vtp 域的名称
Switch1(config)#vtp domain test-vlan
```

![vtp-config-switch1.png](https://doc.shiyanlou.com/document-uid113508labid2126timestamp1476773689015.png)

我们可以在特权模式中使用这个命令来查看 VTP 的相关信息：

```
Switch1#show vtp status
```

![vtp-switch1-vtp-shwo.png](https://doc.shiyanlou.com/document-uid113508labid2126timestamp1476774080671.png)

配置好了 Switch 1 的相关配置之后，我们来配置 Switch 2 中的端口模式，配置完之后我们可以直接查看我们的 Vlan 信息与 VTP 信息：

```
Switch2(config)#int e0/0

Switch2(config-if)#switch trun en do 

Switch2(config-if)#switch mode trunk

Switch2(config-if)#no sh

Switch2(config-if)#end
```

![vtp-switch2-trunk.png](https://doc.shiyanlou.com/document-uid113508labid2126timestamp1476774304856.png)

配置好了之后我们直接来查看 vlan 的信息是不是直接就同步过来了呢：

![vtp-switch2-show-vlan.png](https://doc.shiyanlou.com/document-uid113508labid2126timestamp1476774430808.png)

还有我们的 VTP 域名是否以改过来了呢：

![vtp-switch2-show-vtp.png](https://doc.shiyanlou.com/document-uid113508labid2126timestamp1476774560588.png)

这便是 vtp 的功能，你可以尝试一下再次修改 Switch1 中的 vlan 信息是否会同步过来呢？答案肯定是可以的，同时你也可以尝试一下若是修改 Switche2 中的域名，当你再次修改 Switch1 中的 vlan 信息，又是否会同步过来呢？答案是不可以的，你可以尝试一下。

在 VTP 中分为三种模式：

- Server：服务器模式，在 VTP 服务器上能创建、修改和删除 VLAN，并且这些信息会在 Trunk 链路上通告给域中的其它交换机；VTP 服务器收到其它同为服务器模式的交换机 VTP 通告后会更改自己的 VLAN 信息来同步。VTP 服务器会把 VLAN 信息保存在 NVRAM(即 flash:vlan.dat 文件)中，重新启动交换机这些 VLAN 还会存在。每个 VTP 域必须至少有 1 台服务器，当然也可以有多台。
- Client：客户端模式，在 VTP 客户机上不允许创建、修改和删除 VLAN，它只会监听来自其它交换机的 VTP 通告，若是有所不同便修改自己的 vlan 信息，接收到的 VTP 信息也会在 Trunk 链路上向其它交换机转发，VTP Client 把 VLAN 信息保存在 RAM 中，交换机重启动后这些信息会丢失。
- Transparent：透明模式，该模式中的交换机不完全参与 VTP，可以在这种模式的交换机上创建、修改和删除VLAN，但是不会将这些信息发送给其他交换机，同时也不会同步其他交换机发来的信息。他只是充当一个中继的角色。

| 模式 | 可做操作 | 是否通告让其他设备同步 | |--------|--------| | Server | 创建、修改、删除 | 发通告| | Client | 都不可 | 发通告| | Transparent | 创建、修改、删除 | 至转发收到的，但是不发自己的让其他设备同步|

这里所谓的通告就是将自己修改的信息发送给其他设备，让他们同步修改，但是这个必须有一个前提，就是他们在同一个 VTP 域中，不同的 VTP 域之间不会同步信息。

VTP 中还有一个修剪功能，他的作用是减少中继链路中的不必要的广播信息，如图中这个例子：

这是开启修建功能前数据包转发的情况：

![vtp-pruning-before.png](https://doc.shiyanlou.com/document-uid113508labid2126timestamp1476777835565.png)

这是开启修建功能后数据包转发的情况：

![vtp-pruning-after.png](https://doc.shiyanlou.com/document-uid113508labid2126timestamp1476778236518.png)

开启了修建功能之后便会有这样这能的选择，节省网络中不必要的数据包发送，开启修建功能的命令如下：

```
#在全局模式中
Switch1（config）#vtp pruning
```

这边是 VTP 功能的粗略介绍与使用的方法，若是想更进一步的知道 VTP 通告中的数据包格式可以查看[这篇文章]http://blog.sina.com.cn/s/blog_635e1a9e01017pdl.html

## 五、实验总结

通过本实验的学习，我们掌握了 VLAN 的具体功能、如何使用 VLAN、使用 Trunk 链路让端口可以传送多个 vlan 的信息、使用 VTP 协议使得 VLAN 的管理与控制更加的智能与方便。

## 六、参考资料

[1] VLAN 中继：http://blog.csdn.net/baniel01/article/details/8487746 [2] VLAN mode:http://www.cnblogs.com/clover-toeic/p/3741115.html [3] VTP:http://blog.sina.com.cn/s/blog_635e1a9e01017pdl.html