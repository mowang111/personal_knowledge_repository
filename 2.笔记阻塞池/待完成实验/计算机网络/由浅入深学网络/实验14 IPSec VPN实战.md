## 一、实验介绍

VPN 是现在网络中常用的技术，那什么是 VPN，被广泛使用的 IPSec VPN 又是如何配置而出的？本节实验主要带领大家体验 IPSec VPN 的功能实现，而相关的理论知识暂不做谈论（因为涉及面过广，加密算法，ACL 访问控制以及 NAT 等各种场景本实验的篇幅讲不完），期待后续的相关专题课程

### 1.1 实验涉及的知识点

- VPN 的简介
- IPSec 的简介
- IPSec 的简单工作流程
- IPSec 的配置

![VPN.png](https://doc.shiyanlou.com/document-uid113508labid2232timestamp1478190496369.png)

## 二、VPN 的简介

在公共网络设施上使用 Tunneling、加密、解密等技术实现私有网络的连接，各个私有连接在公共网络上与其它的私有网络之间相互不可见，这就是 VPN。

也就是说只要满足这样条件的网络我们都将其称之为 VPN 虚拟私有网络：

- 使用共享的公共环境，也就通过公网服务实现各个私有网络的连接；
- 不同的私有网络间相互不可见的。

VPN（Virtual Private Network），虚拟的私有网络，所谓的虚拟表示的这是一个逻辑上的专用线路来连接远在各个不同地方的私有网络，这里的私有网络便是对外所不公开的、自己使用的局域网。

使用 VPN 是因为随着公司业务的扩展在距离很远的地方有不同的分布，但是又需要使他们能够访问私有的数据、资源等等，通过公网访问太不安全，通过专线访问成本太高，所以有了 VPN。可以使用低廉的公网价格享受类似于专线的服务，并且数据经过加密非常的安全。

像我们上节实验所提到的 Frame Relay 帧中继技术所提供的 PVC 永久的虚拟电路与 VPN 是有差异的，同时 VPN 与 Frame Relay 的性能上还是有很大的差距，我们可以通过[这样一篇文章](http://www.cisco.com/warp/public/cc/so/neso/vpn/vpnsp/vpnmi_wp.htm)来看看他们之间的对比。

相对于帧中继来说 VPN 更加的安全、灵活。

## 三、 IPSec 的简介

在接触到一个新的事物时我们首先会关心：

- 这个东西是什么？
- 这个东西用于何处？
- 这个东西怎么用？

上文我们便了解到 VPN 是虚拟专用网络，表示一套逻辑上建立在公网上的私有网络。而在 VPN 的发展中属　IPSec VPN（IP Security） 使用的最为广泛，主要在于其有这样的一些特点：

- 私有性：IPSec 在传输数据包之前，将数据包加密，这样保证了三层及以上层次的数据得到了保护，不易被人窃取私密信息；
- 完整性：IPSec 在目的地要验证数据包，以此来保证数据包在传输过程中没有被修改。例如提供了 Hash 算法（单向散列算法）中 MD5、SHA1 等等，通过该算法加工后的数据会生成世界上唯一的字符串，即使内容做了一点点的修改，修改一个字节，一个字符，一个比特位重新加工出来的字符串都会与之前的不同；
- 防重发：通过序列号实现放置数据包被捕捉与重复数据包；
- 身份验证：用于判断数据是否源于正确的创建者。

这个被广泛使用、不断发展的协议适合应用于这样的一些场景：

- Site-to-Site：顾名思义站点到站点间做的配置，例如成都总公司与广州子公司之间的出口路由上配置，这两个出口都是固定长期不会变化的。
- End-to-End：顾名思义便是端到端之间的应用，例如我家中的 PC 上有一些私密的数据，此时我出差在外需要访问这些私密的数据，这样 PC 与 PC 之间的连接便是端到端之间的连接。
- End-to-Site：顾名思义便是端到站点之间连接的应用，例如我出差在广州，此时我需要访问成都总公司服务器中的数据，该服务器放置在公司的局域网内部，此时我需要访问内网中的数据便将我的终端 PC 与内网的出口路由做链接，这样我便能访问内网中的所有资源了。

IPSec 的使用只需要在两端出口的路由上做简单的配置即可使用。并且配置好后不会有太繁重的维护任务，长期使用。

IPSec 的功能如此的强大能够为我们提供加密、认证等等的一些列功能，这显然不是一个协议所能办到的事情，所以 IPSec（Internet Protocol Security）是一个协议组或者说是协议簇，IPSec 就是这一套协议组合的名字。这个组合专门用于 IP 数据通信的安全方面，其中大致包含这样一些主要的协议：

- AH（Authentication Header）：网络认证头部协议，主要用于数据源验证、数据完整性校验和防报文重放功能。
- ESP（Encapsulating Security Payload）：封装安全有效负荷，同样是一个安全协议，与 AH 类似，但是除了 AH 拥有的功能之外还有数据包的加密功能，在 IPSec 中可以使用 AH 或者 ESP 或者两者一起使用。
- IKE（Internet Key Exchange）：密钥管理协议，在加密过程会涉及的共享密钥，公钥，私钥等等，所以需要一个专门管理的协议。

- ISAKMP(Internet Security Association and Key Management Protocol)：网络安全联盟的密钥管理协议，这是 IKE 协议中的一部分，AH 与 ESP 的使用时都需要该协议的支持

这就是 IPSec，虽然还是模模糊糊，但是至少知道我们知道了它是什么，用于哪里的。

## 四、 IPSec 的简单工作流程

IPSec 的整个使用过程从原始数据到加密到路由之间的发送筛选等等一系列的过程十分的复杂，此处只是简单的说明一下其运行中的过程：

- IP 数据包到达了安全路由器上，路由去会根据此数据包的源 IP 地址、端口号等等的信息与设置好的 ACL 对比（ACL，Access Control List，称之为访问控制列表，就像一个安全名单一样，这样信息与该名单上的信息匹配就会做一些特殊的处理）；
- 若是在 ACL 中安全通过了，便查看路由器中的路由表，有没有相关的目的 IP 地址信息，若是有便根据路由表的指示将其发送至本机的目的端口中去；
- 在端口上再次匹配 ACL，若是符合条件没有问题，便交给 IPSec 来处理；
- IPSec 处理的第一步便是检查 SA 的模式

- 检查是 Tunel 模式
- 检查是 Transport 模式（因为两种模式的　IP　数据包头处理方式不同）

- IPSec 处理数据，使用 AH 或者 ESP 的方式，亦或者两者同时使用，各种封装的方式。
- 若是使用 ESP 的方式将加上新的 IP Header，若是使用的 AH 则加上的数据包头与原理的相同。

这边是整个发送数据包的大致过程，两种封装模式的不同导致添加的数据包头就不同，我们可以看[这样一篇文章](http://www.h3c.com.cn/MiniSite/Technology_Circle/Technology_Column/ICG/ICG_Technology/201005/675214_97665_0.htm)来了解之间具体有什么不同。

## 五、 IPSec 的配置

再多的理论只是也不是太明白，直接操作一番便知道 IPSec 是如何实现安全通信，已经远程两个局域网络的连接。

- 实验目的：配置实现 IPSec VPN
- 实验材料：四台路由器
- 实验方法：
  - 拖动四台路由器（两台用作 PC 的充当，两台用作出口路由的充当）
  - 配置路由器名字与连接线路
  - 配置路由器的端口地址
  - 配置 IPSec
  - 验证 IPSec

1.按照惯例，利用我们的终端打开 GNS3，然后拖出四台路由器，做出这样的拓扑:

![ipsec-topo.png](https://doc.shiyanlou.com/document-uid113508labid2231timestamp1478156405432.png)

2.按照拓扑图上的要求配置各个端口的 IP 地址。（每个连接线上的是该连接的网段，端口旁的 `.1` 是主机号）

```
## Router1 config code

#进入全局模式
Router1#conf t

#配置与 PC 连接的端口
Router1(config)#int e0/0

#配置 IP 地址
Router1(config-if)#ip add 192.168.1.1 255.255.255.0

#激活端口
Router1(config-if)#no sh

#退出该端口的配置
Router1(config-if)#exit

#配置与外网连接的端口
Router1(config)#int e0/1

#配置 IP 地址
Router1(config-if)#ip add 1.1.1.1 255.255.255.0

#激活端口
Router1(config-if)#no sh

#退出端口配置
Router1(config-if)#exit

## Router2 cofig code

#进入全局配置模式
Router2#conf t

#配置与内网连接的端口
Router2(config)#int e0/0

#配置 IP 地址
Router2(config-if)#ip add 10.3.1.1 255.255.255.0

#激活端口
Router2(config-if)#no sh

#退出该端口配置
Router2(config-if)#exit

#进入与外网连接的端口
Router2(config)#int e0/1

#配置 IP 地址
Router2(config-if)#ip add 1.1.1.2 255.255.255.0

#激活端口
Router2(config-if)#no sh

#退出该端口的配置
Router2(config-if)#exit


## PC1 config code

#配置全局模式
PC1#conf t

#配置连接端口
PC1(config)#int e0/0

#配置 IP 地址
PC1(config-if)#ip add 192.168.1.2 255.255.255.0

#激活端口
PC1(config-if)#no sh

#退出配置该端口模式
PC1(config-if)#exit

#关闭路由模式
PC1(config)#no ip routing 

#配置默认网关
PC1(config)#ip default-gateway 192.168.1.1

## PC2 config code

#进入全局模式
PC2#conf t

#配置连接端口
PC2(config)#int e0/0

#配置 IP 地址
PC2(config-if)#ip add 10.3.1.2 255.255.255.0

#激活端口
PC2(config-if)#no sh

#退出端口配置
PC2(config-if)#exit

#关闭路由模式
PC2(config)#no ip routing

#设置默认网关
PC2(config)#ip default-gateway 10.3.1.1
```

由此我们便配置好了各个端口的 IP 地址，我们可以用两台 PC 去 ping 各自的网关以及直连路由上端口的 IP 地址，例如 PC1：

![ipsec-config-ip-test.png](https://doc.shiyanlou.com/document-uid113508labid2231timestamp1478159823412.png)

同时可以使用 PC2、Router1、Router2 测试。

如此我们便完成了第二个步骤。

3.配置 RIP 动态路由

在配置 VPN 之前我们首先得保证整个网络都是通的，也就是说若是我本地的机器都不能上网这还说个啥的 VPN，数据加密呀。

```
## Router 1 config code for RIP 

#进入全局模式
Router1#conf t

#开启 RIP 进程
Router1(config)#router rip

#发布网段
Router1(config-router)#net 1.1.1.0

#发布网段
Router1(config-router)#net 192.168.1.0

## Router 2 config code for RIP 

#进入全局模式
Router2#conf t

#开启 RIP 进程
Router2(config)#router rip

#发布网段
Router2(config-router)#net 1.1.1.0

#发布网段
Router2(config-router)#net 10.3.1.0
```

配置好动态路由之后我们发现此时的网络环境已经是全网通的状态了。例如 PC1：

![ipsec-config-ip-test-full-network.png](https://doc.shiyanlou.com/document-uid113508labid2231timestamp1478161004946.png)

4.此时的网络处于全网通的状态，我们便可以开始配置 IPSec VPN 了。

上文我们提到过 IPSec 是一个协议组合，里面有很多的协议组成的，有 IKE 的密钥管理，封装方式等等，其中在两个站点建立连接的时候最重要的是两个协商

- 一个协商是 IKE 安全通道的建立协商
- 一个协商是 IPSec 安全参数的协商

在 IKE 协商协商的时候比对这样一些参数双方是否一致：

- 使用的加密算法
- Hash 算法（单向散列算法）
- DH 算法（Diffie-Hellman key exchange算法）用于密钥交换
- 身份认证
- IKE 协商的生存时间：两个端点协商认可对方之后并不会永久生效，会有个生存时间。超时之后会再次协商

所谓的协商就是比对双发使用的参数是否一致，而这个参数的集合叫做 IKE policy，也就是 IKE 的策略集。

在 IPSec 协商的时候也会有一些参数：

- 使用的加密算法
- Hash 算法（单向散列算法）
- 使用的封装模式（AH、ESP）
- 使用的安全协议
- IPsec 协商的生存时间：两个端点协商认可对方之后并不会永久生效，会有个生存时间。超时之后会再次协商

而 IPSec 的协商参数集合也有一个名字叫做 `transfer set`转换集。

了解整个建立过程之后我们便开始配置 VPN 了，通过上述讲的过程我们首先配置会配置 IKE policy 然后配置 IPSec 转换集：

```
## Router1 config for policy and transfer set

#开启 isakmp，当然默认便是开启的，该命令可用可不用
Router1(config)#crypto isakmp enable 

#首先进入全局模式中，创建一个 isakmp 的策略集，并指定改策略集的优先级（可自定义）
Router1(config)#crypto isakmp policy 10

#进入了策略集的配置中，指定使用 3DES 的加密算法
Router1(config-isakmp)#encryption 3des

#指定使用 md5 的 Hash 单向散列算法
Router1(config-isakmp)#hash md5

#指定使用预共享密钥对的认证方式（认证方式也有其他选择）
Router1(config-isakmp)#authentication pre-share

#指定使用的 DH 密钥交换的算法（使用的算法有 1，2两种选择）
Router1(config-isakmp)#group 2

#指定策略集的生存时间（时间可自定义）
Router1(config-isakmp)#lifetime 86400

#这就是策略集中所有需要指定的参数，配置好了，我们便退出策略集的配置
Router1(config-isakmp)#exit

#创建 shiyanlou 这个密钥（可自定义），并将这个密钥发送给对端的 IP 地址，因为我们选择的是预共享密钥的认证方式
Router1(config)#crypto isakmp key shiyanlou address 1.1.1.2


#由此我们便配置好了 IKE 的协商相关参数

#下面我们将开始配置转换集的相关内容了

#创建一个扩展 ACL（访问控制列表因为本期课的编排问题没有讲解到，大家可以找找相关的资料学习，或者期待进阶课程）
#VPN-shiyanlou 是该访问控制列表的名称，可自定义
Router1(config)#ip access-list extended VPN-shiyanlou

#在该访问控制列表的策略中允许源地址是内部网段的地址通向目的 IP 地址是 10.3.1.0 的网段
# 192.168.1.0 是源网络号，0.0.0.255 是反子网掩码，10.3.1.0 是目的网络号，后面是反子网掩码
Router1(config-ext-nacl)#permit ip 192.168.1.0 0.0.0.255 10.3.1.0 0.0.0.255

#完成了该 ACL 的配置，便退出配置模式
Router1(config-ext-nacl)#exit

#由此我们创建一个策略集 shiyanlou-set（可自定义），使用 esp 的两种封装模式

#每个转换集最多可以有 1 个 AH 与 2 个 ESP 封装模式
Router1(config)#crypto ipsec transform-set shiyanlou-set esp-3des esp-md5-hmac

#因为加密，hash，生存时间我们在 IKE 中已经配置。
#这部分他们公用，所以不用在配置，可以退出该配置模式
Router1(cfg-crypto-trans)#exit

#创建一个总的 crypto 集合给端口应用

#集合的名字 shiyanlou-map(可自定义)
Router1(config)#crypto map shiyanlou-map 10 ipsec-isakmp

#上述命令输入之后会有这样的警告说没有指定对端线路 IP 与 ACL 安全策略是不会开启的

#只有两项同时配置了才会处于应用的状态
% NOTE: This new crypto map will remain disabled until a peer
and a valid access list have been configured.

#设置对端的 IP 地址
Router1(config-crypto-map)#set peer 1.1.1.2

#设置该集合使用的转换集合
Router1(config-crypto-map)#set transform-set shiyanlou-set

#使用的访问控制列表
Router1(config-crypto-map)#match address VPN-shiyanlou

#如此便配置完成了
Router1(config-crypto-map)#exit

#每个端口只能使用一个 crypto map
```

如此我们便配置好了 Router1 的所有协商内容了。你可能会觉得很麻烦要配置这么多集合，为什么不配置在一次，一个 policy，一个 transfer-set，一个 crpyto map。

这也是我们之前所提到过的模块化思想，一个 policy 可用优先级来区分，这样可以设置多个 policy。这是密钥交换、设备之间的认证一部分的功能不应该与 transfer set 糅杂在一起，应为 policy 是设备间的认证，transfer 是应用于端口上，端口之间的协商。

而 crypto map 的独立是因为若是有其他的端口需要使用相同的策略可以直接重用，而不用重新在协议套，不直接使用 transfer set 是因为可能我们使用的转换集是一样的但是我们的 ACL 策略不同，我在使用的使用可以在创建一个 crypto map 使用同样的转换集，只是新建一个 ACL 来应用而已，但是没有 crypto map 我们就必须转换集与 ACL 都重新协议套了。

所以说了这么多，这些的独立就是为了重用，在修改的时候也相互独立，管理方便。

配置好了 Router1，我们便来配置其对端的 Router2，配置上基本一模一样，因为所有的参数在协商的时候都会对比，只有相同的时候才会成功，所以几乎一模一样，但是注意在配置 peer，authentication 的密钥分享地址上要写成 Router1 的 IP 地址哦，因为那才是 Router2 的对端 IP 地址嘛。

```
## Router2 config code for IKE and IPSec

#与上述配置几乎相同，只有在不同之处有注释
Router2(config)#crypto isakmp policy 10

Router2(config-isakmp)#encryption 3des

Router2(config-isakmp)#hash md5

Router2(config-isakmp)#authentication pre-share

Router2(config-isakmp)#group 2

Router2(config-isakmp)#lifetime 86400

Router2(config-isakmp)#exit

#此处是对端的 IP 地址
Router2(config)#crypto isakmp key shiyanlou address 1.1.1.1

Router2(config)#ip access-list extended VPN-shiyanlou

#此处的源地址是本地内网的网络号
Router2(config-ext-nacl)#permit ip 10.3.1.0 0.0.0.255 192.168.1.0 0.0.0.255 

Router2(config-ext-nacl)#exit

Router2(config)#$crypto ipsec transform-set shiyanlou-set esp-3des esp-md5-hmac

Router2(cfg-crypto-trans)#exit

Router2(config)#crypto map shiyanlou-map 10 ipsec-isakmp

% NOTE: This new crypto map will remain disabled until a peer

and a valid access list have been configured.

#这是对端的 IP 地址
Router2(config-crypto-map)#set peer 1.1.1.1

Router2(config-crypto-map)#set transform-set shiyanlou-set

Router2(config-crypto-map)#match address VPN-shiyanlou

Router2(config-crypto-map)#exit
```

由此我们便配置好了 Router2 上的相关参数了

5.将相关的 crypto map 应用在相应的端口上

```
#Router1 code for apply transfer set

#进入与外部连接的端口上
Router1(config)#int e0/1

#应用相关的 crypto map
Router1(config-if)#crypto map shiyanlou-map

#Router2 code for apply transfer set

#进入与外部连接的端口上
Router2(config)#int e0/1

#应用相关的 crypto map
Router2(config-if)#crypto map shiyanlou-map
```

6.由此我们便完成了所有关于协商相关的配置，我们便来验证我们的配置是否成功。

此时我们再次使用 PC1 去 ping PC2。再次之前我们先打开 Router1 与 Router2 之间链路上 wireshark 的监听，我们可以看到有这样的数据包出现：

![ipsec-get-capture-test-success.png](https://doc.shiyanlou.com/document-uid113508labid2231timestamp1478167284869.png)

我们捕获到了 isakmp 相关的数据包，说明 Router 之间使用该协议相互通信，当然这并不能说明什么，我们只用这样的命令来查看 session，只要发起过回话就会有 session 的记录：

```
Router2#show crypto seession
```

![ipsec-show-session.png](https://doc.shiyanlou.com/document-uid113508labid2231timestamp1478167658010.png)

同时我们还可以使用这个命令查看 sa 的状态：

```
Router2#show crypto isakmp sa
```

![ipsec-show-sa.png](https://doc.shiyanlou.com/document-uid113508labid2231timestamp1478167833762.png)

这些都足以证明我们此时使用的 Tunnel 的加密隧道在通信中。

相关的调试命令有这样一些，在这里就不逐一的为大家展示了，大家可以仔细观察相关的信息：

```
show crypto isakmp policy

show crypto ipsec transform-set

show cryto map

show crypto ipsec sa

debug crypto ipsec 

debug crypto isakmp
```

debug 的使用开启之后不会立即有信息出来，只有在相互通信时才有相关的信息蹦出来。

## 实验总结

通过本实验的学习我们粗略的认识了 VPN，同时也大概的了解 IPsec 是个什么东西，同时也完成了相关的配置，中间可能用到了没有讲到过的知识点，期待能出后续的相关课程为大家补充。