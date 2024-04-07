## 论文背景

传统的对抗网络被引入到训练生成模型中，用生成器（Generator）随机生成噪点，判别器（Discriminator）判断判断生成图像真假，两者相互对抗，最终生成器生成判别器无法判断真假的图片。

> 一个有意思的博弈论比喻：如果GANs定义的lossfunction满足零和博弈，并且有足够多的样本，双方都有充足的学习能力情况，在这种情况下，Generator和Discriminator的最优策略即为纳什均衡点，也即：Generator产生的都是“真钞”（材料、工艺技术与真钞一样，只是没有得到授权），Discriminator会把任何一张钞票以1/2的概率判定为真钞。

但是这种对抗网络对生成数据的模式没有控制，如果可以加上一些条件信息，便可以指导数据的生成过程，<font color='red'>比如给定很多不同种类的狗的图片，传统对抗网络只能生成一只狗，但是不能控制狗的种类，如果想要控制输出的内容，比如可以输入一段文字“dog is running”，控制输出的图片，就会生成奔跑的狗的图片</font>

![Reasons Parasite Prevention Is Necessary for Dogs | Forever Vets](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/Forever-Vets-Animal-Hospital_Reasons-Parasite-Prevention-Is-Necessary-for-Dogs_IMAGE1.jpeg)

GAN模型没有损失函数，优化过程是一个**二元极小极大博弈(minimax two-player game)问题**

![image-20220303080242171](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20220303080242171.png)

## 目的

We show that this model can generate MNIST digits conditioned on class labels

## 相关工作

| 问题                                                         | 解决                                                         | 相关论文                                          |
| ------------------------------------------------------------ | ------------------------------------------------------------ | ------------------------------------------------- |
| 问题1：对于一般的监督网络来说，很难对大规模的种类进行预测输出 | 一种方案就是训练识别图像的过程中加入语义信息                 | DeViSE: A Deep Visual-Semantic Embedding Model    |
|                                                              |                                                              |                                                   |
|                                                              |                                                              |                                                   |
|                                                              |                                                              |                                                   |
| 问题2：至今（2014）很多的工作都是着眼于一对一的输入输出，但是实际上很多现实问题都是一对多的输入输出，比如对于同一张图片，不同的人有着不同的描述 | 一种方案是使用条件概率生成模型，输入视为条件变量，一对多，最后映射为不同种类的条件概率分布 | Multimodal learning with deep boltzmann machines. |
|                                                              |                                                              |                                                   |
|                                                              |                                                              |                                                   |
|                                                              |                                                              |                                                   |
|                                                              |                                                              |                                                   |

## 实验设计

他们用的什么优化器呢？用了几层网络呢？为什么这样用呢？

生成器和鉴别器都加入一些额外信息y为条件，比如类标签，作为生成器和鉴别器的附加层输入

生成器中输入噪声$p_z(z)$和额外信息y

鉴别器用x和y作为输入，此例中使用MLP(多层感知器)训练



![image-20220302205640680](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20220302205640680.png)

![image-20220302205722862](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20220302205722862.png)

## 实验结果

### unimodal

#### 生成器

噪声z（100维服从均匀分布的噪声向量）和额外信息y分别映射到隐藏层（200和1000unit），使用Relu的激活函数，在被第二次映射前，链接所有的1200个unit,最终有一个Sigmoid激活函数的层输出784维（28*28）的单通道图像

#### 鉴别器

将x（输入图像）映射到**具有240units和5 pieces的maxout层**，y（类别标签的one hot编码）映射到**具有50 units和5 pieces的maxout层**，在喂给下一个sigmoid层之前，两个maxout层**连在一起为一个240units和4pieces的maxout层**,最终输出为x为来自训练集（真实图像）的概率

#### 训练

使用随机梯度下降训练模型，batch size为100，初始学习率为0.1,随着decay 降到1.00004，学习率也降到0.000001，同时[动量](https://www.jiqizhixin.com/articles/2017-07-01-4)从0.5增长到了0.7

![image-20220302221428232](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20220302221428232.png)

结果是相比于其他的一些网络会好一些，但是没有无条件的对抗网络效果好

### Multimodal

Flickr这些标签图片的网站，他们的图片标签都是用户定义的，没有一般的标签那么规范，更像是接近自然语言的描述，Conceptual word embeddings可以用来将这些自然语言标准化

这次实验就自动为图片加标签，使用条件对抗网络产生一个或多个标签向量

在ImageNet数据集(21000labels)上预训练模型，采用最后一层全连接（4096 units）输出作为图像特征

文本表示是选取YFCC数据集，预处理后用skip-gram model训练成200维的词向量，除去出现次数少于200的词，最后剩下247465个词。

图片使用MIR Flickr 25,000数据集，用convolutional和language模型提取图片和标签，没有标签的图片会被剔除，注释会被当成额外的标签，150000个样本被当作训练集，有多个标签的图片挥别重复放入训练集

为了估计，为每张图片生成100个样例，找到前20个最接近的词汇（using cosine similarity of vector representation of the words in the vocabulary to each sample），再从100个样例中找到十个共同的词汇。

最有效的生成模型接收100维的高斯噪声，将其映射到500维的ReLu层，映射9600维的图片特征向量到2000维的ReLu隐藏层，这些层最终一起映射到一个200维的线性层，输出单词向量。

辨别器模型包括500和1200维的ReLu隐藏层分别对应于单词向量和图片特征，一个1000units和3 pieces的maxout层，作为join layer ，最终喂给一个单个的sigmoid unit

这个模型用随机梯度下降训练，batch size为100，初始学习率为0.1，随着decay 降到1.00004，学习率也降到0.000001，同时[动量](https://www.jiqizhixin.com/articles/2017-07-01-4)从0.5增长到了0.7

架构和参数选择是使用随机网格搜索和人工选择来交叉确认

## 未来工作

现在的结果只是使用单独的标签，希望未来同时使用多个标签会获得更好的结果

构建一个联合式的架构来学习语言模型
