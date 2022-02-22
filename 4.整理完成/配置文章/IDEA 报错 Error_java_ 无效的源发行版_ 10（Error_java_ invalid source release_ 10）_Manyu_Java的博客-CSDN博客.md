# IDEA 报错 Error:java: 无效的源发行版: 10（Error:java: invalid source release: 10）

#### 开发工具

*   IntelliJ IDEA 2018.3.5（Ultimate Edition）版本
*   Mac

#### 解决方法

- `Project Settings`页面，保证`Modules`里的`Language Level`版本高于`Project`里的`Project SDK`版本
- 如果使用了`maven-compiler-plugin`插件，请保证`source`和`target`版本高于`Project`里的`Project SDK`版本
- 注意，不是修改`Project`里的`Project Language Level`版本，具体原因参照下面![在这里插入图片描述](https://img-blog.csdnimg.cn/20191113212024414.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L01hbnl1X0phdmE=,size_16,color_FFFFFF,t_70)
  ![在这里插入图片描述](https://img-blog.csdnimg.cn/20191113212104881.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L01hbnl1X0phdmE=,size_16,color_FFFFFF,t_70)
  ![在这里插入图片描述](https://img-blog.csdnimg.cn/20191113212121404.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L01hbnl1X0phdmE=,size_16,color_FFFFFF,t_70)

#### 原因(重点，理解了下次就不会再出错)

*   几个版本的含义
    *   `Modules`的`Project SDK`:项目实际编译所用的版本，即最后生成的class文件是使用该版本编译的，一般都是开发人员自行安装在机器上，取决于运行环境！
    *   `Project`里的`Project Language Level`：项目的全局检查版本，我理解为工程最低支持版本；IDEA会使用自带的`Language Level`指定的jdk版本来对我们的代码进行编译检查
    *   `Modules`里的`Language Level`：指定模块的最低支持版本，作用同`Project Language Level`，只是作用域更小
    *   `maven-compiler-plugin`：作用同`Project Language Level`，不依赖于开发软件，更加有效！
*   几个检查版本的优先级：`maven-compiler-plugin` > `Project Language Level` > `Language Level`, 即只要指定了优先级更高的设置（如`maven-compiler-plugin`）的版本，后者（如`Project Language Level`）不生效；出现错误，原因只会出在优先级更高的配置！
*   版本检查的意义：很多时候，尤其是大的项目，我们无法保证生产环境JDK的版本，与我们实际本地开发的版本一致，所以需要通过该机制进行检查
*   建议：项目在生产运行时，没有IDEA的环境，所以我建议大家使用`maven-compiler-plugin`去进行运行前的版本检查
*   补充：使用`maven-compiler-plugin`时，如修改后问题没有坚决，请先`mvn clean`一下

#### 测试代码

![](https://img-blog.csdnimg.cn/2019111321215912.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L01hbnl1X0phdmE=,size_16,color_FFFFFF,t_70)