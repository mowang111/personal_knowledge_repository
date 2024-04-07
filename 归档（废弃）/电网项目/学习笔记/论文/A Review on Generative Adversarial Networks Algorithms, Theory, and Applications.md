## GAN系列算法

### GAN

#### 零和博弈

![image-20220316190158857](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20220316190158857.png)

#### 非饱和博弈

![image-20220316204148812](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20220316204148812.png)

#### 最大似然博弈

![image-20220316204200252](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20220316204200252.png)

### GAN变体

#### InfoGAN

![image-20220316205003913](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20220316205003913.png)

将输入的噪声分成两部分，不可压缩噪声z，结构化有意义的噪声c

#### CGAN

![image-20220316205316570](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20220316205316570.png)

##### AC-CGAN

##### cGANs with projection discriminator

大多数基于cGANs的方法的鉴别器[31]、[41]、[152]-[154]通过简单地将（嵌入）y连接到输入或中间层的特征向量，将条件信息y输入鉴别器,cGANs with projection discriminator采用条件向量y和特征向量之间的内积

##### pix2pix

Isola et al. [156] used cGANs and sparse regularization for image-to-image translation.

![image-20220319102449659](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20220319102449659.png)

pix2pixHD

![image-20220319104650766](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20220319104650766.png)

#### CycleGAN

#### <font color='red'>f-GAN</font>

![image-20220319214455477](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20220319214455477.png)

> 可以考虑用f散度对鉴别器做优化

#### IPMs

![image-20220319214705513](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20220319214705513.png)



##### MMD

![image-20220319215603939](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20220319215603939.png)

##### WGAN

![image-20220319215543362](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20220319215543362.png)

###### WGAN-GP

![image-20220319220343233](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20220319220343233.png)

#### LS-GAN

## GAN训练

#### 改变目标函数

##### Least squares generative adversarial networks (LSGANs)

##### Hinge loss based GAN

##### Energy-based generative adversarial network (EBGAN):

##### Boundary equilibrium generative adversarial networks (BEGAN)

##### Mode regularized generative adversarial networks (MDGAN) 

##### Unrolled GAN

#### 技巧

#### 结构上优化

##### The original GANs

使用MLP，只适用于小的数据集，再更复杂的图像上没有好的泛化能力

##### Laplacian generative adversarial networks(LAPGAN) and SinGAN

##### Deep convolutional generative adversarial networks (DCGANs):

DcNNs定义G和D

##### Progressive GAN（PGGAN）

渐进式神经网络，渐进式GAN的关键思想是逐步增长生成器和鉴别器：从低分辨率开始，添加新的层，随着训练的进展，建模越来越精细

##### Self-Attention Generative Adversarial Network (SAGAN):

SAGAN 被提出允许对图像生成任务的注意力驱动，随机依赖建模

在鉴别器上使用光谱归一化技术

对生成器和鉴别器都使用了频谱归一化，发现这改善了训练动力学

TTUR规则（？）

AttnGan 

##### BigGANs and StyleGAN

BigGANs是GANs的大规模TPU实现

BigBiGAN 通过添加一个编码器和修改鉴别器，将其扩展到表示学习中,利用更少的标签训练BigGANs模型

StyleGAN架构，StyleGAN的生成器是一个非常高质量的生成器，可以用于其他生成任务，比如生成人脸。这特别令人兴奋，因为它允许分离不同的因素，如头发，年龄和性别，涉及控制最后一个例子的外观，然后我们可以分开控制它们

##### <font color='red'>Hybrids of autoencoders and GANs</font>

##### <font color='red'>Multi-discriminator learning</font>

##### Multi-generator learning

##### Multi-GAN learning

## GAN与其他机器学习算法结合

## GAN典型应用