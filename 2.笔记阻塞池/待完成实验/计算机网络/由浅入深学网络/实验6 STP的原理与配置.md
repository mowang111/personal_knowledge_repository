## 一、实验介绍

本实验将带领大家解决局域网中常见的环路问题，了解 STP 的运行原理，以及其适用的场景与配置的方法。

### 1.1 实验涉及的知识点

- STP 的来源
- STP 的原理
- STP 的发展
- RSTP 的配置
- MSTP 的配置

## 二、STP 的来源

在网络规划与整体设计的时候，为了避免单点故障的情况发生，我们会尽量的设置冗余的网络链路。而所谓的单点故障便是线路上只有一个出口的时候，一旦出现问题整个网络便无法正常工作了，比如：

![单点故障.png](https://doc.shiyanlou.com/document-uid113508labid2217timestamp1476837443544.png)

这就是典型的单点故障，为了提高网络的可靠性，强健壮性，我们会将网络设计成拥有冗余线路的网络，那么就会将上述的链路改造成这样：

![冗余线路.png](https://doc.shiyanlou.com/document-uid113508labid2217timestamp1476838206033.png)

为了让链路冗余，也就是有多条线路可发送数据帧，当主要的线路出故障无法使用时，还有另外一条线路可以使用，从而提高链路的可靠性。但是这样的情况造成环路的出现，正如上述的网络情况，会导致这样的情况发生：

![STP-why.png](https://doc.shiyanlou.com/document-uid113508labid2217timestamp1476786662668.png)

广播数据帧的不断死循环，从而导致广播风暴。线路中全是广播数据帧，占满了所有的线路带宽，从而使得需要正常通信的数据帧根本无法发送出去，这是一种情况；还可能会导致多帧复用，也就是相同内容的数据帧通过两条线路发给了同一台设备，当设备收到第二个数据帧的时候并不知道与前一个是相同的，所以还是会耗费时间、耗费 CPU 等系统资源去解析他，发现时重复的才会丢弃；还可能导致 MAC 地址表紊乱，所谓的 MAC 地址表紊乱也就是 MAC 地址漂移的不断出现，MAC 地址漂移是 MAC 地址表中的某个 MAC 地址对应的接口不断的变更，因为多帧复用中源 MAC 地址相同，但是接收到他们的端口却不同，而他们都会记录在 MAC 地址表中，所以出现了 MAC 地址漂移的情况，如果网络足够的大的话还会导致 MAC 地址溢出的情况发生。

所以总的来说环路会造成这样的一些问题存在：

- 广播风暴
- 多帧复用
- MAC 地址漂移

为了解决这样的问题发生，STP 协议应运而生，全名为　Spanning Tree Protocol（生成树协议），因为一棵树的生长是从根开始向外开枝散叶的，这样并不会有环路的出现，如图所示：

![生成树-树.png](https://doc.shiyanlou.com/document-uid113508labid2217timestamp1476840739672.png)

STP 的出现可以达到这样的效果：

- 防止广播风暴
- 防止环路的出现
- 防止 MAC 地址漂移
- 放置多帧复用

## 三、STP 的原理

STP 如何防止环路的出现呢？原理很简单，就是通过许多的参考值来衡量，然后停止一条路中的某个端口的转发，从而断掉了环路，确保数据帧在某一时刻从一个源出发，到达网络中任何一个目标的路径只有一条。若单纯只是这样冗余线路是没有意义的，这个断掉的端口会随着参考值的变化而产生变化，比如在其他线路出故障的时候这个端口便会恢复。

STP 的产生解决了这样的问题，其中已 IEEE802.1D 版本最为流行，它依靠 STA（Spanning Tree Algorithm，生成树算法） 算法来决定交换机上的哪些端口会被堵塞，来将环路修剪成无环路。在其中提出了根桥（RootBridge）、根端口（RootPort）、指定端口（DesignatedPort）、路径开销（PathCost）等等的一些概念。

而 STP 的实现需要经历这样的四个过程

- 选举根桥（RootBridge）
- 选择根端口（RootPort）
- 选择指定端口（DesignatedPort）
- 选择非指定端口（备选端口），设为阻塞状态

1.在网络中交换机之间会发送 BPDU（Bridge Protocol Data Unit），通过 BPDU 中的信息来选择根桥，而所谓的根桥，就像是一棵树的根，枝叶将从哪里发散出来一般。在 BPDU 报文中会包含这样的一些信息：

| 字节 | 内容 | 含义 | |--------|--------| |2|Protocol ID(协议ID)|该值总为0| |1|Version(版本号)|STP的版本(为IEEE 802.1d时值为0)| |1|Message type（报文类型）|BPDU类型(配置BPDU=0，TCN BPDU=80)| |1|Flags(标记域：LSB(最低有效位)=TCN标志|MSB(最高有效位)=TCA标志| |8|Root ID(根网桥ID)|根信息由2字节优先级和6字节 MAC 组成。这个信息组合标明已经被选定为根网桥的设备标识| |4|Cost of path(路径成本)|路径成本为到达根网桥交换机的STP开销。表明这个BPDU从根网桥传输了多远，成本是多少。这个字段的值用来决定哪些端口将进行转发，哪些端口将被阻断| |8|Bridge ID(发送网络桥ID)|发送该BPDU的网桥信息。由网桥的优先级和网桥ID组成| |2|Port ID(端口ID)|发送该BPDU的网桥端口ID| |2|Message age(计时器)|计时器用于说明生成树用多长时间完成它的每项功能。这些功能包括报文老化时间、最大老化时间、访问时间和转发延迟| |2|Max age(最大老化时间)|网桥将将根桥看做不可用前保留根ID的最大时间| |2|Hellotime(访问时间)|根网桥连续发送BPDU的时间间隔| |2|Forward delay(转发延迟)|网桥在监听学习状态所停留的时间|

其中 Root ID 便是用于选举网桥用的，Root ID 是由 2 字节（16 位）的优先级、6字节（48位）的 MAC 地址组成。其中两字节的优先级（Prirotiy）默认值是 32768，取值范围:0-65535，当然也可以手动修改，收到各方的 Root ID 的时候首先比较的就是优先级，值小者便是树根，若是值相同则比较 MAC 地址。

在交换机中有很多端口，每个端口都有一个 MAC 地址，而此处的 MAC 地址并不是端口的 MAC 地址而是交换机的背板地址，用于表示这台交换机的。与端口 MAC 地址的格式相同，若是优先级的值相同便比较这个 MAC 地址，值小者为 Root Bridge 根桥。

如这样的一个例子便是这样，优先级相同，便比较 MAC 地址值：

网络初始的时候所有的设备都认为自己是根桥，然后向相邻的设备发送 BPDU，当收到其他设备的 BPDU 报文便会解析得到其他设备的 Root ID，然后对比自己的 Root ID 中优先级与 MAC 地址（此处的优先级相同，不得已将对比 MAC 地址部分）。若高于其他设备则修改自己的 Root ID 为值低者，直到收到所有的 BDPU，所有的设备同步出一致的 RootBridge。

![RB.png](https://doc.shiyanlou.com/document-uid113508labid2217timestamp1476857556805.png)

2.选出了 RootBridge，便应该选出根端口 RootPort，在其他设备上选出能够最快到达根桥的端口作为根端口（每台设备都有除了根桥设备）。每个非根桥有且只有一个 RP（主要作用是负责接收并且监听根桥的BPDU），一般是与根桥直连的端口。

选举的过程是这样：

（1）比较每个端口到达根桥的 Cost 值，具有最小 Cost 的端口成为 RP 端口，而 Cost 表示的是本端口收到一个对端网桥的 BPDU 以后，累加本端口的 Cost 之后的总路径开销，主要以链路上的带宽来获得与累加该值

![8021d-1998-costs.png](https://doc.shiyanlou.com/document-uid113508labid2217timestamp1476855769995.png) （此图来自于[packetlife](http://packetlife.net/media/blog/attachments/357/8021d-1998-costs.png)）

（2）若是 Cost 值相等的情况下则比较 BID，若是不同设备其 BID 是不可能相同（因为 MAC 地址的存在）

（3）但是若是环路发生在两台设备的情况下就会发生 BID 相等的情况了，那么 BID 相同的情况下会比较端口 ID 了。

所以整个比较的顺序就是：

- 到根桥的路径开销 Cost 值（会叠加）
- BID 的值（首先是自己的，然后 BPDU 经过的桥的 BID 也比较）
- PortID 的值：由两字节组成=接口优先级（1 字节，默认值 128，范围 0~255）+接口编号（1 字节）

这就是 BID 相同情况下的环路了：

![same-bid.png](https://doc.shiyanlou.com/document-uid113508labid2217timestamp1476857083952.png)

而在我们上述的例子中我们可以看到，Switch 2 与 Switch 3 的 e0/0 端口距离根桥最近，他们的 Cost 值最小，所以这两个端口为根端口：

![RP](https://doc.shiyanlou.com/document-uid113508labid2217timestamp1476858375707.png)

3.选举出了 RP 之后，便需要选择指定端口（DesignatedPort，DP）。在每一个交换机之间的链路上选择一个端口，作为指定端口。而上述的例子中一共就三条链路 2 <--> 1，3 <--> 1，2 <--> 3。其中Switch1 与 Switch2 连接的端口中 Switch 2 的已经作为 RootPort，所以 Switch 1 与 Switch 2 连接的端口 e0/0 便是一个指定端口，与 Switch 3 的同理使得 Switch 1 的另一个端口也为指定端口 DP。

而剩下的一个 DP 就在 Switch 2 与 Switch 3 相连的两个端口中选出，而选举的方式与 RootPort 相同：

- 到根桥的路径开销 Cost 值
- BID 的值
- PortID 的值

而上述的例子中 Cost 值明显是相同的，所以便查看 BID 的情况，而 Switch 2 的 MAC 地址尾数 0200 小于 Switch 3 的 MAC 地址尾数 0300 所以 Switch 2 上的端口是 DP：

![DP.png](https://doc.shiyanlou.com/document-uid113508labid2217timestamp1476859170900.png)

4.选择非指定端口也就是备选端口，设为阻塞状态。在所有的角色与端口选择完毕之后将这些 RP，DP 端口的状态设置为转发状态，这种状态下的端口才可以转发数据帧，而剩余的端口将被设置为阻塞状态，该状态下的端口无法接收与转发数据帧。由此换里就被断掉了：

![BLK.png](https://doc.shiyanlou.com/document-uid113508labid2213timestamp1477029878799.png)

这就是 STP 解决环路问题的整个过程，而为了应变网络拓扑的变化，网络情况的变化，每个端口的角色并不会是一尘不变的，这样能够适应所有的网络环境，提高网络的可靠性，健壮性。

而 STP 感应网络的结构变化是通过计时器与 BPDU 来实现的。一个有三个计时器：

- Hello Time：这是根桥发送 BPDU 数据 的时间间隔，也是网络初始化的时候每个网桥发送各自的 BPDU 的时间间隔。这个时间默认为 2 秒。
- Forwarding Time：指一个端口 Listening 时间，默认为 15s，为了保证 BPDU 在全网中的转发，所以做如此设定，这个值是可以配置的，由于 Forwarding Time 的限制，一般建议网络的直径应小于 7。
- Max Age：存储 BPDU 最长的时间，超过这个时间端口没有接收到新的 BPDU，会丢弃以前的报文，同时会采取相应的措施。这个时间默认为 20s.

每一个使用 STP 的二层端口存都会有这样的 5 种状态：

- 阻塞（Blocking）：端口不能参与其他帧的转发与接收，只接受 BPDU，但不发送，同时不学习 MAC 地址。
- 侦听（Listening）：端口自阻塞状态后的第一个过渡状态。不能参与其他帧的转发与接收，只接受与发送 BPDU，同时不学习 MAC 地址。
- 学习（Learning）：处于准备参与帧转发状态，不能参与其他帧的转发与接收，只接受与发送 BPDU，同时学习 MAC 地址。
- 转发（Forwarding）：端口可以正式转发帧了。
- 禁止（Disabled）：端口不参与STP，不收发任何的帧。

Learning 学习状态存在的原因在于当拓扑发生变化，新的配置消息要经过一定的时延才能传播到整个网络，这个时延称为Forward Delay，默认值是15秒。 而设备的端口还没有发现自己在新的拓扑中，没有停止转发，这样会产生临时环路。为了解决这个问题，STP 使用了一种定时器策略，即在端口从阻塞状态到转发状态中间加上一个 Learning 状态，只学习 MAC 地址但不转发的中间状态，而两次状态切换的时间长度都是 Forward Delay，虽然可以防止临时环路。但是使得收敛时间是原来的至少两倍 Forward Delay。

> **收敛时间**是指网络设备发现网络的拓扑结构发生变化后，信息同步的过程中所共花费的时间

他们状态转变是这样的一个顺序：

![port-states.png](https://doc.shiyanlou.com/document-uid113508labid2217timestamp1476861682341.png) （此图来自于[tomicki](http://www.tomicki.net/images/port_states.png)）

## 四、STP 的发展

STP 的发展主要分为这样几个阶段：

1.最初 IEEE 以 802.1D 标准形式发布的 STP 技术，这是单生成树，把整个交换网络作为一个生成树的实例，被开发出来时还没有交换机（第一版802.1D发布于1990年，当时是桥接环境），所以并该协议中并没有 VLAN 的概念，只能存在于单一的 VLAN 中。

就是这点的不足 Cisco 开发出自己的 STP 叫 PVST（Per Vlan Spanning Tree），网络中的每个 VLAN 运行一个独立的生成树实例，这就是 Per Vlan 名字的由来。这种解决方案使得每个 VLAN 使用不同的逻辑拓扑。该协议基与 802.1D，但是只支持 ISL 的封装。

2.IEEE 做出了一点升级，在 802.1Q with CST（common spanning tree）中使得 STP 支持多 VLAN，但是所有的 VLAN 却是共享一个 CST（common spanning tree）。一个 VLAN 受影响其他的 vlan 也会被牵连。

随着 802.1Q 的发布，以及其在市场上的流行，思科也对自己的 PVST 做出了升级，使其支持 802.1Q 的 VLAN，因此更名为 PVST+。经过改进的PVST+协议在VLAN 1上运行的是普通STP协议，在其他VLAN上运行PVST协议。

3.STP 的缺陷不仅仅在与 VLAN 上，同时他的收敛速度也是一个很大的问题，所以 802.1w 推出了快速生成树协议RSTP(Rapid Spanning Tree Protocol)，使得收敛速度快得多(最快1秒以内)。

STP 的升级，使得 Cisco 也不甘落后，基于 802.1w 也升级出了快速收敛版本的 PVST+，称为 RPVST+。

4.思科在此之前提出了 MISTP（Multiple Instances Spanning Tree Protocol），它既有 PVST 的 VLAN 认知能力和负载均衡能力，又拥有十分好的低 CPU 占用率。不过，极差的向下兼容性和协议的私有性阻挡了 MISTP 的大范围应用。

在解决了 STP 的收敛时间上的问题之后，IEEE 开始解决 STP　共享一颗生成树的问题，由思科的 MISTP 衍生出了 MSTP（Multiple Spanning Tree Protocol，多生成树）。该协议提出域与实例的概念，MSTP 把一个交换网络划分成多个域，每个域内形成多棵生成树，生成树之间彼此独立。这样就很好的解决了之前所带来的问题。

这便是迄今为止 STP 的整个发展过程，MSTP 似乎也能够暂时满足人们的需求了，所以该协议也没有进一步发展的势头。

## 五、RPVST 的配置

通过上文了解到 STP 的原理与发展，PVST 系列作为 Cisco 自己的私有协议，在 Cisco 的设备中都默认开启了 RPVST 的功能。通过这样一个实验我们来体验一下 RSTP 的功能与配置，同时学习 RSTP 在 STP　上的一些优化：

- 实验目的：查看与配置 RSTP
- 实验材料：两台交换机
- 实验方法：
  - 拖动两台交换机至画布，两台用作模拟交换机
  - 配置交换机的名字与连接线路，成环路
  - 开启设备与 wireshark 抓包与查看 STP 配置信息
  - 配置 STP

1.做好准备工作，终端开启 GNS3，拖出设备至画布，对应端口两两互连，形成环路：

![rpvst-de.png](https://doc.shiyanlou.com/document-uid113508labid2217timestamp1476924976629.png)

2.开启设备，同时开启 Wireshark 查看数据帧。同时登陆上两台设备。

这就是交换机之间用于交流的 BPDU，就是通过这些数据帧交换信息来确定谁是 RootBridge，就像是民主选总统一般，只是规则不同而已：

![rpvst-packet.png](https://doc.shiyanlou.com/document-uid113508labid2217timestamp1476933778729.png)

随意选中一个数据帧我们可以看到其中的内容，其中看到目的 MAC 地址是一个组播地址，这是由 IEEE 802 所保留的一个组播地址，专用与网桥的组地址，这是官方的描述：IEEE Std 802.1D Bridge Group Address。

![rpvst-packet1.png](https://doc.shiyanlou.com/document-uid113508labid2217timestamp1476933806010.png)

再看看数据帧中的信息，因为是 RSTP 的帧结构所以与上文所说的结构有细微的差别，RSTP 是在 STP 的基础上改进的，所以原理并不会相差太大，但是在端口状态，与 BDPU 的信息上做了一些细微的改进，来提升状态改变所需的时间与收敛的速度。

![rpvst-packet2.png](https://doc.shiyanlou.com/document-uid113508labid2217timestamp1476954611612.png)

在数据帧上 RSTP 中主要增加的 BPDU 的 flags，增加这些的原因是在 RSTP 中对交换机的状态与端口的状态做了这样的一些修改：

增加了几种端口的 role，原来只有 RootPort，DesignatedPort。现在增加有 Alternate Port（替换端口）、Backup Port（备用端口）、Edge Port（边缘端口）。

- Alternate Port: 替代端口，用于在根端口出故障的时候替换根端口，它可以迅速替代成为新的根端口并进入 Forwarding 状态。
- Backup Port: 备份端口，是指定端口的备份端口，但是只作用于两端口都是是点到点的链路。
- Edge Port: 边缘端口。指网桥上连接到终端设备的端口，能够直接进入 Forwarding 的状态，此类端口可以实现快速迁移。一般为了避免人恶意攻击或形成新的环路需要开启 BPDU Guard 功能，这样在该端口收到 BPDU 数据包的时候就会自动关闭 shutdown 端口

而在原来的 5 中端口状态中做出了改进与优化，只保留了三个状态：Discarding、Learning、Forwarding

- Discarding：表示不转发数据帧的状态
- Learning:表示学习状态，依然是为了隔离直接到转发状态的作用
- Forwarding：表示转发状态，用于转发数据帧，不能参与其他帧的转发与接收，只接受与发送 BPDU，同时学习 MAC 地址。

在 BPDU 的 flags 标志位中也有一些改进，原来的标志位中只有 TC（Topology Change）来表示当前的拓扑结构是否改变与 TCA（Topology Change ACK）来确认当前拓扑结构的改变，现在新加了 Proposal（提议）的标志位与 Agreement（同意提议）的标志位还有表明端口角色的 Port Role 标志位与端口状态的标志位由 Learning、Forwarding 值来判断。

这样的优化，让一个本来是 Block 的端口转变成 Forwarding 状态不再需要 50 秒的时延，如此大大的加快了收敛速度。

3.我们若是对系统所指定的根桥并不满意，我们想手动指定一个根桥，那么我们可以执行这样一些命令，如例子中 Switch 1 与 Switch 2 的优先级相同，MAC 地址低为根桥，所以 Switch 1 必然为根桥，此时我们想让 Switch 2 作为根桥（此处是以我的例子来推断），那么我们做这样的配置：

在 Switch 2 中我们可以通过 这个命令来查看此时 STP 的状态

```
#所以的查看命令都在特权模式中

Switch2#show spanning-tree 
```

![rstp-show-spanning.png](https://doc.shiyanlou.com/document-uid113508labid2217timestamp1476958940632.png)

接下来便进入全局模式中配置该交换机的优先级

```
#进入全局模式
Switch2#conf t

#因为 PVST 是根据 vlan 来的，所以必须指定 vlan
#通过 primary 来指定该交换机作为主要，提升优先级
Switch2(config)#spanning-tree vlan 1 root primary
```

![rstp-change-rootport-switch2](https://doc.shiyanlou.com/document-uid113508labid2217timestamp1476959677686.png)

通过截图我们了解到这么一行简单的命令已经成功的让 Switch 2 转变成了根交换机，主要的做法就是让其优先级降级，所以这个命令也可以这样去执行：

```
Switch2(config)#spanning-tree vlan 1 root 24767
```

既然从命令上来看 Switch 2 作为主要，那么当然可以配置次要，所以在非根交换机中可以使用这个命令：

```
Switch1(config)#spanning-tree vlan 1 root secondary
```

使用这个命令之后会将优先级修改成 secondary 的默认值 28673。

当我们遇到设备性能不是很好的时候想切换成 STP（PVST），或者我们此时设备完全能够支持 MST，我们可以使用这个命令来切换当前 STP 使用的版本：

```
#三种模式中选择一种
Switch1(config)#spanning-tree mode mst/pvst/rapid-pvst
```

![rstp-change-mode.png](https://doc.shiyanlou.com/document-uid113508labid2217timestamp1476960309206.png)

当我们确定某个端口作为连接终端主机的时候，我们可以将该端口配置为 EdgePort

```
#进入需要配置该模式的端口中
Switch1(config-if)#int e2/0

#将该端口配置为边缘端口
Switch1(config-if)#spanning-tree portfast 
```

![rstp-config-edge.png](https://doc.shiyanlou.com/document-uid113508labid2217timestamp1476961159699.png)

开启边缘端口之后我们同时还要做保护措施，开启 BPDU 保护，也就是说当这个端口接受到 BPDU 数据包之后直接 shutdown 关闭该端口

```
#同样在该端口中开启
Switch1(config-if)#spanning-tree bpduguard enable
```

这就是 RSTP 的配置过程了，命令并不多，只要掌握其运作的原理，配置起来，差错起来并不难，我们来回顾一下一共有这些命令：

```
#修改该交换机的优先级，成为根交换机
spanning-tree vlan 1 root primary

#修改该交换机的优先级，成为非根交换机
spanning-tree vlan 1 root secondary

#修改当前的 STP 版本
spanning-tree mode mst/pvst/rapid-pvst

#在接口中，配置其为边缘端口
spanning-tree portfast 

#在边缘端口上配置 BPDU 保护
spanning-tree bpduguard enable
```

## 五、MSTP 的配置

在 RSTP 中解决了收敛速度的问题，而 PVST 只是针对每一个 vlan 去生成一颗数，BPDU 会每隔两秒钟发一次，这样一旦 vlan 的数量上去了，链路上的 BPDU 的数量将无法想象，而且这么多的生成树维护起来也十分的困难，所以诞生出了 MSTP，MSTP 可以对网络中众多的 VLAN 进行分组，把 VLAN 分到组中来管理，一个组就是一个 Instance，每个组只会生成公用一颗数，这样便解决了 PVST 所带来的问题。

而 MSTP 的配置也并不复杂，只是在原有的 STP 之上增加了域与 Instance 的概念，同时优先级的概念也升级到域的层次上。所以在配置的改变上也就增加了与此关联的命令：

```
#首先得在全局模式中将 STP 模式改成 mstp
(config)#spanning-tree mode mst

#然后就是进入 MSTP 的配置模式
(config)#spanning-tree mst configuration

#配置创建实例并关联某个或多个 vlan
(config-mst)#instance 1 vlan 2

#配置当前的 mstp 修改的版本
(config-mst)#reversion 0

#查看当前的 instance 配置
(config-mst)#show pending

#配置该设备在实例中的优先级
(config)#spanning-tree mst 1 priority 8192

#配置该实例所在的区域名字
(config-mst)#name region1
```

基于之前的实验环境的基础之上我们创建 2 个 vlan，让他们分别位于不同的 instance 中：

```
Switch2(config)#vlan 2

Switch2(config-vlan)#name test1

Switch2(config-vlan)#exit

Switch2(config)#vlan 3

Switch2(config-vlan)#name test2

Switch2(config-vlan)#exit
```

然后我们将其配置在不同的 instance 中：

```
Switch2(config)#spanning-tree mode mst

Switch2(config)#spanning-tree mst config

Switch2(config-mst)#instance 1 vlan 2

Switch2(config-mst)#instance 2 vlan 3

Switch2(config-mst)#name region1

Switch2(config-mst)#exit
```

接着设置该设备在不同的 instance 中的优先级或者说是扮演的角色，是否为 RootBridege：

```
#直接设置优先级
Switch2(config)#spanning-tree mst 1 priority 8192

#通过设置角色来改变优先级
Switch2(config)#spanning-tree mst 2 root primary 
```

如此我们便完成了一个设备中的 mstp 的配置，但是这样并不会起到任何的作用，因为 mstp 向下兼容，所以另一台设备即使不配置 STP 也能正常工作，若要是的 mstp 工作，我们需要 Switch1 拥有相同的配置，vlan 的同步可以使用 VTP 来同步，而 spanning-tree 除了优先级其他都与 Switch2 相同。

因为 MSTP 采用二级结构。分区域（region）运行 STP，在同一个 region 中需要满足这样三个条件：

- instance（instance是从1-4094）和 vlan 对应关系相同
- name 一致，也就是区域名相同
- revision一致，当前的修改版本相同

在每个区域内的 STP 我们称为 IST（ internal spanning tree，内部生成树）。在整个 MSTP 拓扑中，可以拥有多个 region，在 region 之间运行的生成树称为CST（common spanning tree，公共树），协议是RSTP。每个 region 有一个根桥称为regional root，整个系统有一个总根桥。

而在端口的角色上也多了主端口（Master）、域边界端口。

这便是 MSTP 配置过程，该过程并没有任何执行的过程，希望大家能结合之前的知识点（VLAN，VTP）来将剩下的部分完成。若能在两台设备中 `show spanning-tree` 出这样的结果，代表你成功的完成了：

![show-mstp-result.png](https://doc.shiyanlou.com/document-uid113508labid2217timestamp1477020420411.png)

## 七、实验总结

通过本实验我们了解了 STP 的原理，STP 的配置，以及 STP 的进化过程，同时还完成了他们分别如何配置，重在理解，配置命令并不多，都是根据其原理所走的流程而来。

## 八、课后作业

1.独立配置完上述未完成的配置

2.做出以下填空：

![homework1](https://doc.shiyanlou.com/document-uid113508labid2213timestamp1477026588423.png)

![homework2.png](https://doc.shiyanlou.com/document-uid113508labid2213timestamp1477027979645.png)

![homework3.png](https://doc.shiyanlou.com/document-uid113508labid2213timestamp1477027270506.png)

参考答案：

第一题:

| 交换机 | 角色 | e0/0 端口|e0/1 端口| |--------|--------| |SwitchA| |e0/0: RP,FWD| e0/1:DP,FWD| |SwitchB|RB|e0/0:DP，FWD| e0/1:DP，FWD| |SwitchC| |e0/0: RP,FWD| e0/1:AP,BLK|

第二题:

| 交换机 | 角色 | e0/0 端口|e0/1 端口| |--------|--------| |SwitchA|RB|e0/0:DP，FWD|e0/1:DP，FWD| |SwitchB||e0/0: DP,FWD| e0/1:RP，FWD| |SwitchC||e0/0: RP,FWD| e0/1:DP,FWD | |SwitchD||e0/0: RP,FWD| e0/1:DP,BLK e0/2:DP,FWD| |SwitchE||e0/0: RP,FWD||

第三题：

| 交换机 | 角色 | e0/0 端口|e0/1 端口| |--------|--------| |SwitchA| |e0/0: RP,FWD| e0/1:AP,BLK| |SwitchB|RB|e0/0:DP，FWD| e0/1:DP，FWD|

## 九、参考资料

[1] BPDU 报文:http://baike.baidu.com/item/BPDU [2] STP 发展：http://network.51cto.com/art/201307/404013.htm [3] STP 历史：[http://weirdnetworking.com/2016/01/23/stp%E5%8D%8F%E8%AE%AE%E5%AF%B9%E6%AF%94%E5%8F%8A%E5%8E%86%E5%8F%B2/](http://weirdnetworking.com/2016/01/23/stp协议对比及历史/) [4] MSTP 原理：http://www.cisco.com/c/en/us/td/docs/switches/lan/catalyst3560/software/release/12-2_52_se/configuration/guide/3560scg/swmstp.html#wp1035423