https://www.cnblogs.com/lfsblack/p/5627809.html

[官方webkit api](https://webkitgtk.org/reference/webkitgtk/stable)

## DOM

DOM(Document Object Model) 文档对象模型，定义一组与平台、语言无关的接口，该接口允许编程语言动态访问和更改结构化文档。

![image-20220218201304871](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20220218201304871.png)

### DOM树

![image-20220218201358203](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20220218201358203.png)

## HTML解释器

![image-20220218201520621](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20220218201520621.png)

框对应于“Frame”类，文档对应于“HTMLDocument”类，HTMLDocument类继承自Document类

+ FrameLoader: 框中内容的加载器
+ DocumentLoader帮助加载HTML文档，并从字节流到构建DOM树
+ DocumentWriter为辅助类，它会创建DOM树的根节点HTMLDocument对象，同时是该类包括两个成员变量，一个是用于文档的字符解码的类，另外一个就是HTML解释器HTMLDocumentParser类
+ HTMLDocumentParser是一个管理类，包括了用于各种工作的其他类，例如字符串到词语需要用到的词法分析器HTMLTokenizer类，该管理类读入字符串输出一个个词语，词语经过XSSAuditor做完安全检查后，输出到HTMLTreeBuilder类
+ HTMLTreeBuilder列负责DOM树的建立，它本身能够通过词语创建一个个的节点对象，然后，借由HTMLConstructionSite类来将这些节点对象构成一棵DOM树

> ![image-20220218204428793](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20220218204428793.png)

## 网页基础设施

![image-20220218205320438](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20220218205320438.png)

+ ChromeClient类需要具备获取各个平台资源的能力，例如WebKit可以调用Chrome类来创建一个新窗口
+ Chrome类需要把WebKit的状态和进度等信息派发给外部的调用者或者说是WebKit的使用者

### DOM的事件机制

事件在工作过程中使用两个主体，一个是事件（event）,另一个是事件目标（EventTarget）,Node节点继承自EventTarget类，Webkit中用EventTarget类来表示DOM规范中Events部分定义的事件目标

每个事件都有属性来标记该事件的事件目标，当事件达到事件目标（如一个元素节点）的时候，在这个目标上注册的监听者（Event Listeners）都会被触发调用，这些监听者的调用顺序不固定，不能依赖监听者注册的顺序来觉得代码逻辑

![image-20220218210834799](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20220218210834799.png)

事件处理包括事件捕获（Event capture）和事件冒泡（Event bubbling）

![image-20220218210937591](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20220218210937591.png)

当渲染引擎接收到一个事件是，它会通过HitTest（WebKit中的一种检查触发事件在哪个区域的算法）检查哪个元素是直接的事件目标，事件捕获是由上倒下，事件冒泡是由下到上。

![image-20220218212131549](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20220218212131549.png)

黑色圆圈表示光标的位置，光标下面的元素注册了一个监听鼠标滚轮事件的函数，当用户滚动鼠标时，浏览器经过HitTest之后，发现由监听者，它需要将这些事件传给WebKit,WebKit实际上醉后调用JavaScript引擎来触发监听者函数。

![image-20220218212505262](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20220218212505262.png)

EventHandler类是处理事件的核心类，它除了需要将各种事件传给JavaScript引擎以调用响应的监听者之外，它还会识别鼠标事件，来触发调用右键菜单、拖放效果等与事件密切相关的工作。

## 渲染基础

### RenderObject

对于可视节点，WebKit需要将它们的内容绘制到最终的网页结果中，所以WebKit会为它们建立相应的RenderObject对象。一个RenderObject对象保存了为绘制DOM节点所需要的各种信息。

+ DOM树的document节点
+ DOM树中的可视节点，例如html、body、div等
+ 某些情况下WebKit需要建立匿名的Renderjie节点，该节点不对应于DOM树中的任何节点，而是WebKit处理上的需要，典型的例子就是匿名的RenderBlock节点

![image-20220218221558698](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20220218221558698.png)

每个Element对象都会递归调用attach函数，该函数检查Element对象是否需要创建RenderObject，如果需要，该函数会使用NodeRenderingContext类来根据DOM节点的类型来创建对应的RenderObject节点

![image-20220218221903330](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20220218221903330.png)

### RenderLayer

### 渲染方式

#### 绘图上下文（GraphicsContext）

在webkit中，绘图操作被定义了一个抽象层，即绘图上下文，所有的绘图操作都是在该上下文中来进行

![image-20220218222358450](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20220218222358450.png)

## 处理点击事件

当用户点击鼠标，在OS语汇里，这叫发生了一次中断(interrupt)。

系统内核(kernel) 如何侦听以及处理interrupt，不妨参阅“Programming Embedded Systems” 一书，Chapter 8. Interrupts。

这里不展开介绍，有两个原因：

   \1. 这些内容很庞杂，而且与本文主题不太相关。

   \2. 从Webkit角度看，它不必关心interrupt 以及interrupt handling 的具体实现，

因为Webkit建筑在GUI Toolkit之上，而GUI Toolkit已经把底层的interrupt handling，严密地封装起来。

Webkit只需要调用GUI Toolkit 的相关APIs，就可以截获鼠标的点击和移动，键盘的输入等等诸多事件。