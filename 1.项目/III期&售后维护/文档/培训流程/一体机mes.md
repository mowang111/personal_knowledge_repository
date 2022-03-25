# Mes软件介绍

## 软件架构

本产品结合了公司自主研发的微MES系统（microMES），可以实现用户管理、工艺管理、高级排程、设备管理、追溯管理、质量管理、报表管理。

![img](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/clip_image002.gif)

下图是产品业务的核心流程：

核心流程分成三个界面，未登录界面，任务主界面，任务详细界面，下图是三个界面的切换

最初始时是未登录状态，登录之后进入任务主界面，在任务主界面中查看任务详细界面，任务主界面和任务详细界面都可退出到未登录状态

在新版本的一体机中，我们添加了查看外接设备（打印机，读卡器等）的状态，以太网络和数采网络信息设置，远程协助，系统日志等功能

![1](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/1.gif)



## 用户管理

用户管理包含了用户刷卡登录、用户账号/密码登录等模块。

### 用户刷卡登录

用户刷卡登录主要是为了员工更加方便的登录到系统中，对任务的查看，操作。提高了工作的效率，也简化的许多不必要的登录操作。登录操作直接在系统内部对卡片上的信息进行采集，分析，验证，来判断是否允许登录。

![image-20220214154251805](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20220214154251805.png)

### 用户账号密码登录

用户账号密码登录是在用户进入公司之处，所创建的用户与密码，是登录系统最为基础的依据。同时作为备用的登录方式。

![image-20220214154645908](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20220214154645908.png)

用户账号密码登录界面提供了2个用户输入框，当用户点击输入框，会谈出一个全键盘来让用户输入。与账户输入框不同的是密码输入框设置了密码样式，不会将密码以明码的形式显示出来，很好的避免了账号密码的泄露，提高了账号的安全性。同时，为了方便用户对输入框中的内容清空，系统提供了一个清空的按钮，可以让用户在输入错误时，快捷的删除内容。

下方的文字控件会不断滚动提示“杭州明物智能有限公司提醒您：请输入您的账号密码登陆！若忘记账号密码可返回到首界面刷卡登陆！”点击返回按钮可以放回到之前的界面。

## 任务管理

任务管理主要包含导入工单、工单管理两个模块

![image-20220214155152134](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20220214155152134.png)

### 导入工单

在用户初始登录时，系统会自动分配任务，导入工单功能主要是将管理员保存在系统中的每个员工布置的任务工单导入到智能屏幕上显示出来，简洁明了的让员工理解接下来的任务。任务工单中主要包含了编号、型号、工单号、任务要求、任务状态等等信息。

### 工单查看

工单管理主要包括工单的显示，工单操作。

#### 工单显示

工单可直接在页面上最多显示五条记录，当工单数多于五条时，可通过操作向前5条和向后5条的按钮进行翻页。

工单显示的列共有五列，包括了编号、制令单、型号、任务要求和任务状态信息

##### 工艺信息

另外可查看对应工单的详细信息，点击想要查看的工单的那一行，然后点击右下角的工艺信息按钮，可以跳转到当前工单详细信息的页面。

![image-20220214162536843](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20220214162536843.png)

如上图，工单工艺信息主要包括编号、工单号、型号、任务要求、任务状态、任务报警、二维码区域几个部分

其中任务状态包括三种，告警和正常

![image-20220215053322386](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20220215053322386.png)

![image-20220215053352872](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20220215053352872.png)

另外二维码区域会显示当前工单对应的二维码，生产过程中可用pda扫码来进行工单绑定操作

### 工单操作

对工单的操作主要任务开始、暂停、结束以及打印

![image-20220214155152134](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20220214155152134.png)

其中任务的开始和暂停以及打印操作都可直接在主页面操作，选中任务后，点击开始按钮，该任务的任务状态就会变为进行中的状态，图标会更改为进行中的图标，与此同时，在任务界面中的，数据记录中该任务的任务也会修改为进行中。

同理，当用户点击暂停按钮图标后，表示有事或任务暂时无法完成，需暂停任务，此时任务详情界面的图标会更改为之前的未完成状态。

![image-20220214164411018](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20220214164411018.png)

而点击主页面上的结束按钮后，不会直接结束任务，而是会自动跳转到工单的工艺信息界面，然后需要点击工单信息界面中的结束后才能真正结束任务，结束任务后会自动跳转到主页面。

工单打印可在主页面直接操作，同样是选择需要打印的任务，然后点击右下角的打印按钮，打印的信息包含该任务的编号，工单号，型号，任务要求等等信息。

### 系统告警

当软件发现生产问题时，会自动跳出以下页面，根据提示内容进行对应操作，然后点击返回按钮。

比如当pda绑定工单时，后台发现铜材型号不匹配，就会通知一体机，一体机显示该界面通知操作人员

![image-20220214170744227](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20220214170744227.png)

## 其他辅助功能

其他辅助功能的操作的入口都是需要进入配置界面

### 进入配置界面

1. 首页进入配置目录
   ![Pasted-image-20211201191316.png](https://raw.githubusercontent.com/mowang111/image-hosting/master/yuanhong/Pasted-image-20211201191316.png)

2. 其他页面进入配置界面

![image-20220214165327037](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20220214165327037.png)

![Pasted-image-20211201191519.png](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/Pasted-image-20211201191519.png)

### 状态查看

状态查看的部分主要包括外设（打印机，刷卡器）以及网络状态

#### 外设状态

外设的状态查看目前可通过如下按钮进入

![image-20220214175454677](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20220214175454677.png)

打印机

![image-20220214181737702](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20220214181737702.png)

刷卡器

![image-20220214181815006](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20220214181815006.png)

检查状态都是点击检查状态的按钮，状态显示为on则正常，off为不正常。

#### 网络状态

网络状态可直接通过上方图标的颜色判断，当其为黑色时，表示一体机软件为启动，当其为绿色是表示该项正常，为红色是表示该项不正常

![image-20220214182431241](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20220214182431241.png)

其中1号图标为以太网络，2号图标为与后台的连接状态，3号图标为数采网络。

### 以太网络和数采网络ip修改

以太网络和数采网络配置主要是对其ip地址进行配置，数采网络和以太网络的配置步骤相同，只是以太网络配置的是连接网络的网卡的ip，而数采网络配置的是连接数采设备的网卡的ip。

1. 有两个网络可以配置ip，一个是以太网络，一个是数采网络，以下先以以太网络配置为例介绍
   ![Pasted-image-20211205214252.png](https://raw.githubusercontent.com/mowang111/image-hosting/master/yuanhong/Pasted-image-20211205214252.png)

2. 点击以太网络按钮后，进入以下以太网络配置界面
       ![Pasted-image-20211205214510.png](https://raw.githubusercontent.com/mowang111/image-hosting/master/yuanhong/Pasted-image-20211205214510.png)
   
3. 以太网络的配置有两种方式，一种是自动获取配置，即是通过DHCP动态获取，另一种是手动配置，为了便于后台的全局调试，建议依次手动配置顺序ip
     1. 动态获取IP，直接点击自动获取按钮即可
        ![Pasted-image-20211205215315.png](https://raw.githubusercontent.com/mowang111/image-hosting/master/yuanhong/Pasted-image-20211205215315.png)
     2. 手动配置ip步骤：
        1. 首先点击ip地址后面的输入框进行输入
           ![Pasted-image-20211205215552.png](https://raw.githubusercontent.com/mowang111/image-hosting/master/yuanhong/Pasted-image-20211205215552.png)
        2. 然后点击默认网关后面的输入网关地址
           ![Pasted-image-20211205215710.png](https://raw.githubusercontent.com/mowang111/image-hosting/master/yuanhong/Pasted-image-20211205215710.png)
        3. IP地址和默认网关都配置完成后，点击配置完成按钮即可
           ![Pasted-image-20211205215822.png](https://raw.githubusercontent.com/mowang111/image-hosting/master/yuanhong/Pasted-image-20211205215822.png)
        4. 全部配置好的界面如下图所示
           ![Pasted-image-20211205220111.png](https://raw.githubusercontent.com/mowang111/image-hosting/master/yuanhong/Pasted-image-20211205220111.png)

  ### 远程协助

远程协助主要是当某台设备出现故障时，可联系维护人员对该台设备进行检查的前的措施，其主要保证维护人员可以在后台连接上该一体机

1. 在配置目录中点击远程协助，进入远程协助界面
       ![Pasted-image-20211201191624.png](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/Pasted-image-20211201191624.png)
2. 在远程协助界面配置端口号
       ![Pasted-image-20211201191748.png](https://raw.githubusercontent.com/mowang111/image-hosting/master/yuanhong/Pasted-image-20211201191748.png)
   点击此"11901"数字可以配置端口号，端口号的配置需要注意以下几点:
     + 每台一体机配置的端口号不能相同
       
     + 配置端口号的范围在11900-11950之间，建议从11901按顺序依次配置
       
     + 需要将配置的端口号告知后台管理人员
   
3. 端口号配置完成后点击"开始"按钮即可
       ![Pasted-image-20211201192654.png](https://raw.githubusercontent.com/mowang111/image-hosting/master/yuanhong/Pasted-image-20211201192654.png)
4. 上述流程后，后台便可以直接登录一体机进行问题排查
5. 问题排查完毕后，需要手动结束远程协助，点击"结束"按钮即可
       ![Pasted-image-20211201192900.png](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/Pasted-image-20211201192900.png)

### 系统日志

![image-20220215064854347](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20220215064854347.png)

1.同样可以在配置文件界面找到系统日志的入口

2.当进入系统日志页面后点击获取日志按钮，近期的日志就会显示出来，最上面的时间最近

3.系统日志一般记录的是出错的信息。

### 物料管理

![image-20220215064951446](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20220215064951446.png)

在物料信息部分可查看当前批号和铜材型号，以及历史批号和铜材型号的对应情况。
