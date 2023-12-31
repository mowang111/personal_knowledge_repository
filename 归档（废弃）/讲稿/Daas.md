大家好，我们分享的主题是制造企业的机联网的Dass平台

接下来我将从以下几个方面展开，首先会介绍Dass模式以及其与机联网相关的部分，然后会介绍我们系统的整体架构，接着从系统结构的几个部分，IoTClient、IoTServer、IoTAPI、IoTWeb具体展开，最后介绍我们公司一个相关的应用案例

## DaaS

首先关于DaaS模式，DaaS 数据即服务是一种服务模式，即将数据以服务的形式，向客户提供价值，参与到客户的业务中，它也是软件即服务的一种细分领域。同时DaaS 拥有云计算的通用特点，包括以租代买，按需付费、按用付费。

目前做DaaS的平台有很多，比如Amazon EMR  Core DaaS

- Amazon Elastic MapReduce (Amazon EMR) 是一种 Web 服务，它简化了[大数据](https://cloud.tencent.com/solution/bigdata?from=10680)的处理，提供托管Hadoop框架，可以让用户轻松、快速、经济高效地在多个动态可扩展的 Amazon EC2 实例之间分发和处理大量数据。

- 用户还可以运行其他常用的分发框架（例如 Amazon EMR 中的 Spark 和 Presto）与其他 AWS 数据存储服务（例如 Amazon S3 和 Amazon DynamoDB）中的数据进行互动。

- Amazon EMR 能够安全可靠地处理大数据使用案例，包括日志分析、Web 索引、数据仓库、机器学习、财务分析、科学模拟和生物信息。

  

DaaS模式的基础架构由四个部分组成，客户基于API自研应用从而访问数据，而数据服务是API功能的具体实现，当然数据服务则是由基础数据库和一些非结构化数据作支撑。

在这个基础架构的基础上，可以延伸出更多的应用

一个是DaaS加官方应用，也是目前机联网使用最多的模式，在很多情况下，客户没有应用开发的能力，需要在接口上叠加一个轻量化的图形化工具，比如网页、小程序等，这种模式和SaaS模式比较类似，但其明显的特点是，DaaS模式保留了用户对数据处理的接口

同时在DaaS基础架构之上还可添加应用认证，增加 App认证鉴权之后，能缓解对于API 接口安全的焦虑。借助线下、线上的授权，许可特定的应用来访问特定的接口。

基于对于应用场景的理解，将原始数据进行一定的加工，生成模型数据（间接数据），对外提供模型数据。这将简化客户 app 的开发，同时也在一定程度上保护了原始数据。

一些数据不能直接对外，需要一些脱敏处理，于是可以使用DaaS加脱敏的模式，可以采用动态脱敏或者静态脱敏。动态脱敏是访问时现进行计算，静态脱敏则是提前完成。

传统数据库提供了一些计算能力，比如常见的统计函数、存储过程等。现在的新型数据库的算力越来越强，与其将数据传来传去，受限于带宽，还不如把计算下放到数据库中。同时，这也减少了出库的数据，降低了数据安全风险。

计费有很多种方式，这里提两种，一是在 api 层同步或异步进行计费业务，另一种则是以离线的统计日志数据，生成费用。前者计费及时些，但对于工程能力要求高，同时也会造成接口访问效率的降低；后者系统更健壮，但存在滞后问题，这也可以通过商业措施来解决。

## 机联网DaaS特征

对于机联网部分，DaaS的压缩，清洗和拟合部分比较重要

比如机器的转速一般比较稳定，比如都是1000转每秒，在存储的时候就会存储大量重复的数据，采用数据压缩可大大减少需要的存储容量

同时机器的数据传输会发送错误，数据清洗便是纠正数据错误的最后一道程序，包括检测数据一致性等等

最后当数据有遗漏时，可通过数据拟合，比如取左右两个数据平均值的方式补全数据

Dass优势部分

敏捷性：通过数据访问的整合，客户能够更加快速地对其进行移动，而无需再去考虑底层数据的来源。如果客户需要稍微不同的数据结构或者调用特定位置的数据，DaaS通过最小程度的变更能够非常快速满足需求

成本效益：底层架构由更加专业的工控人员实现，表现层可以外包给传统互联网从业者，同时使得任何变更需求都能更灵活的满足

数据质量：通过服务来控制数据的访问，这对数据质量改进非常有帮助，因为更新点只有一个。当服务彻底测试之后，如果下一次部署不发生变化，那么他们只需要进行回归测试就好了

效率、高可用和弹性： 这些优势来自于虚拟化，物理服务器资源共享将提升效率，跨多个物理服务器的集群可以提高可用性，动态调整和实时迁移集群节点到不同的物理服务器能够增强弹性

## 系统架构

我们首先按照DaaS将机联网系统分成四个部分，IoTClient、IoTServer、IoTAPI、IoTWEB,其中IoTClient软件放置在工位一体机上，主要负责数据的采集和传输，其中工位一体机可搭载Windows、Linux、Android等操作系统，数据采集的协议包括Modbus，西门子的S7系列，欧姆龙、三菱协议等等。IoTClient端将采集到的数据通过例如Mqtt协议交给IoTServer

IoTServer部署在服务器上，负责数据的处理和存储，主要由其中的数据库服务器处理，而云端服务器则可部署其他服务，包括之前提到的App认证鉴权服务、模型生成服务等等，是对数据的进一步保护和封装，根据不同的部署方式，可分为私有化部署和公有化部署，对于数据安全性要求很高的企业，一般将数据库放在本地，进行私有化部署，不过目前的趋势是利用各个云厂商的云数据库服务，更加方便，一般情况下，数据的安全性也可以保证，另外在存储的方式上，数据量很大的情况下，可考虑分布式存储，在其上的IoTAPI层则是为用户提供的数据接口，这里同样可以本地提供接口，也可以将数据库接入云厂商的数据库网关，最后IoTWEB相当于我们提供的一个官方应用，主要负责数据的展示，包括网页端，移动端监控以及云厂商提供的DataV大屏展示

## IoTClient部分

下面是IoTClient部分的界面，其中有设备管理的部分，包括设备的接口，串口连接，以太网连接等，同时包括不同的设备类型，对应不同的通信协议，配置好协议后，即可根据不同变量的不同寄存器地址采到数据。

另外包括对外设的配置，比如摄像头，打印机，刷卡器，扫码枪等等

## IoTServer部分

IoTServer主要是数据的处理和存储服务，支持多种类型的数据库包括，关系数据库和非关系数据库，以及时序数据库。

## IoTAPI部分

接下来是IoTAPI部分，包括设备管理上传记录的api，设备表api等等，规定了请求接口，方式、地址，以及相关响应参数

## IoTWEB部分

IoTWEB，这里的网页部分主要是对设备基本信息的查询，提供多种图形化的展示，

大屏部分对设备综合效率监控分析，统计产线综合效率和设备利用率，显示每台设备当前状态和效率、当前生产任务、生产工艺参数

## 应用案例

应用案例部分是远鸿工厂的例子，这里工位一体机和设备一对一配置，采集产线的设备数据，同时根据设备数据进行相应的任务管理和生产管理。

我的分享结束，谢谢大家！