# Windows10下如何使用debug程序？_需要来自debug的权限才能执行本操作-CSDN博客

重要？: No
URL: https://blog.csdn.net/qq_45382733/article/details/112597079

### 一、概述

学习汇编语言时需要使用debug程序，目前64位操作系统并没有自带debug.exe，故需要通过下载[dosbox](https://so.csdn.net/so/search?q=dosbox&spm=1001.2101.3001.7020)软件来配置debug程序的使用。

### 二、下载dosbox

浏览器搜索dosbox进入官网，点击上方download。

进入下面的页面后再点击上面白色大字母DOSBox，然后又会看到download选项，再点击download后自动下载安装包，应该就一千多KB。下载完成后运行该exe文件，一路点击next，选择安装路径后install。完成之后就会在桌面上显示有dosbox的图标了。

![https://img-blog.csdnimg.cn/20210113232454343.png](https://img-blog.csdnimg.cn/20210113232454343.png)

![https://img-blog.csdnimg.cn/20210113234029963.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzQ1MzgyNzMz,size_16,color_FFFFFF,t_70](https://img-blog.csdnimg.cn/20210113234029963.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzQ1MzgyNzMz,size_16,color_FFFFFF,t_70)

![https://img-blog.csdnimg.cn/20210113234832448.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzQ1MzgyNzMz,size_16,color_FFFFFF,t_70](https://img-blog.csdnimg.cn/20210113234832448.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzQ1MzgyNzMz,size_16,color_FFFFFF,t_70)

### 三、下载debug文件

直接上网盘链接：复制这段内容后打开百度网盘App，操作更方便哦。 链接:https://pan.baidu.com/s/1JsudsGy09WNNItpnZM8VrQ 提取码:3288

下载好后可新建一名为debug的文件夹，将debug.exe放入该文件夹。

![https://img-blog.csdnimg.cn/20210114000726532.png](https://img-blog.csdnimg.cn/20210114000726532.png)

### 四、设置配置

在dosbox目录下双击DOSBox0.74-2 Options.bat，将会以文本形式打开，拉到文档最末端，加入下面两条语句后保存退出。

![https://img-blog.csdnimg.cn/20210114001317802.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzQ1MzgyNzMz,size_16,color_FFFFFF,t_70](https://img-blog.csdnimg.cn/20210114001317802.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzQ1MzgyNzMz,size_16,color_FFFFFF,t_70)

### 五、双击桌面dosbox图标命令行输入debug即可使用。

下图为-r命令示例。

![https://img-blog.csdnimg.cn/20210114001617976.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzQ1MzgyNzMz,size_16,color_FFFFFF,t_70](https://img-blog.csdnimg.cn/20210114001617976.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzQ1MzgyNzMz,size_16,color_FFFFFF,t_70)