## webkit项目结构

![这里写图片描述](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/wKiom1OoFoXiajoAAACtCpO9nQU069.jpg)

![image-20220218145231769](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20220218145231769.png)

![image-20220218145206152](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20220218145206152.png)

![image-20220218145354915](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20220218145354915.png)

## webkit源码结构

![image-20220218152352914](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20220218152352914.png)

Webkit源码结构还是十分清晰的，基本上每个模块对应一个子目录。主要代码在Source/目录下，如下

- WebCore/: 平台无关，各个不同移植所共享
  - css/: CSS解析器
  - dom/: DOM解析器
  - html/: HTML解析器
  - inspector/: 调试相关
  - loader/: 资源加载模块
  - page/: 与页面相关的全局对象，如window，navigator，DOM事件，动画等
  - storage/: cookie处理和HTML5中的LocalStorage处理
- JavaScriptCore/：Webkit中默认的JS引擎，Blink中改为V8
- WebKit/ WebKit2/：嵌入式接口层
- WTF/：基础类库，如字符串操作，线程，算法等

![image-20220218153127211](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20220218153127211.png)

## webkit渲染过程

### 第一阶段：从网页的 URL 到构建完 DOM 树

![从网页 URL 到 DOM 树](https://img-blog.csdn.net/20180627230408522?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3VzZXJrYW5n/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)
*从网页 URL 到 DOM 树*

具体过程如下：

1. 当用户输入网页 URL 的时候，WebKit 调用其资源加载器加载该 URL 对应的网页
2. 加载器依赖网络模块建立连接，发送请求并接收答复
3. WebKit 接收到各种网页或者资源的数据，其中某些资源可能是同步或异步获取的
4. 网页被交给 HTML 解释器转变成一系列的词语（Token）
5. 解释器根据词语构建节点（Node），形成 DOM 树
6. 如果节点是 JavaScript 代码的话，调用 JavaScript 引擎解释并执行
7. JavaScript 代码可能会修改 DOM 树的结构
8. 如果节点需要依赖其他资源，例如图片，CSS，视频等，调用资源加载器来加载它们，但是它们是异步的，不会阻碍当前 DOM 树的继续创建；**如果是 JavaScript 资源 URL（没有标记异步方式），则需要停止当前 DOM 树的创建，直到 JavaScript 的资源加载并被 JavaScript 引擎执行后才继续 DOM 树的创建**

在上述过程中，网页在加载和渲染的过程中会触发 “**DOMContentLoaded**” 事件和 “**onload**” 事件，分别在 DOM 树构建完之后，以及 DOM 树建完并且网页所依赖的资源都加载完之后发生，因为某些资源的加载并不会阻碍 DOM 树的创建，所以这两个事件多数时候不是同时发生的。

### 第二阶段：从 DOM 树到构建完 [WebKit](https://so.csdn.net/so/search?q=WebKit&spm=1001.2101.3001.7020) 的绘图上下文

![从 CSS 和 DOM 树到绘图上下文](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/20180627233356705)
*从 CSS 和 DOM 树到绘图上下文*

具体过程如下：

1. CSS 文件被 CSS 解释器解释成内部表示结构
2. CSS 解释器工作完之后，在 DOM 树上附加解释后的样式信息，这就是 RenderObject 树
3. RenderObject 节点在创建的同时，WebKit 会根据网页的层次结构创建 RenderLayer 树，同时构建一个虚拟的绘图上下文。

RenderObject 树的建立并不表示 DOM 树会被销毁，事实上，上述图中的四个内部表示结构一直存在，直到网页被销毁，因为它们对于网页的渲染起了非常大的作用。

### 第三阶段：从绘图上下文到生成最终的图像

![从绘图上下文到最终的图像](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/2018062723450047)
*从绘图上下文到最终的图像*

具体过程如下：

1. 绘图上下文是一个与平台无关的抽象类，它将每个绘图操作桥接到不同的具体实现类，也就是绘图具体实现类
2. 绘图实现类也可能有简单的实现，也可能有复杂的实现。在 Chromium 中，它的实现相当复杂，需要 Chromium 的合成器来完成复杂的多进程和 GPU 加速机制
3. 绘图实现类将 2D 图形库或者 3D 图形库绘制的结果保存下来，交给浏览器来同浏览器界面一起显示

这个过程实际上可能不像图中描述的那么简单，现在浏览器为了绘图上的高效性和安全性，可能会在这一过程中引入复杂的机制。而且，绘图也从之前单纯的软件渲染，到现在的 GPU 硬件渲染、混合渲染模型等方式。

## webkit资源加载机制

![image-20220218155346719](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20220218155346719.png)

### 资源加载器

+ 针对某种资源类型的特定加载器，仅加载某一种资源，例如ImageLoader类

+ 资源缓存机制的资源及再去,CachedResourceLoader类

+ 通用资源加载器，ResourceLoader类，其属于CachedResource类，但同CachedResourceLoader类没用继承关系

  

### HTML解释器

