## GAN

### 论文Generative Adversarial Nets

#### 引言

通过对抗网络建立一个生成模型

训练两个模型：生成器G产生数据分布，辨别器D判断sample是否是真实的，输出的数字表示判断是否为真实的概率。

其中G和D可以都使用多层感知器模型，所以整个系统可以使用反向传播来训练，而不需要<font color='red'>马尔科夫链</font>或者<font color='red'>近似推断</font>对分布进行复杂的采样，所以在计算上有优势

#### 相关工作

之前的工作一直是想直接构建含有特定参数的分布函数的模型，这样的模型可以通过最大化对数似然函数来训练

1. the deep Boltzmann machine 计算上困难
2. generative machines 
3. VAES
4. NCE 使用的损失函数相对复杂
5. predictability minimization
6. Adversatial examples

#### 对抗网络

对抗网络最简单的使用就是生成器和判别器都是MLP

1. learn the generator's distribution
   1. define a prior on input noise variables $p_z(z)$
   2. $G(z;θ_g)$

2. $D(x;θ_d)$来判断x是来自真实采样的数据还是生成器生成的数据，训练的时候给一个标号，真实采样为1，生成器生成为0
3. 训练D的同时也训练G，G来最小化$log(1-D(G(z)))$
   1. 辨别器很好的情况下，该项为0

![image-20220304141446829](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20220304141446829.png)

+ D是完美的情况下，该式两个加和项都是0，而如果D（x）大于0小于1时，两者都是负值，所以，两个加和也是负值，所以想让D更好，就要让V这个值越大
+ G主要是第二项，要使生成器更好，就要骗过辨别器，所以尽量让D(G(z))为1，1-D(G(z))就是0，再加上log就是负无穷，所以想让G更好，就要V这个值越小
+ 这是两人的minmax游戏，最后达到纳什均衡

![image-20220304185448145](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20220304185448145.png)

> 黑色的线表示真实采样的x分布，绿色的表示生成器生成的x分布，蓝色的表示辨别器数采的值

### 算法

![image-20220304185825483](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20220304185825483.png)

> 首先训练生成器，输入噪音z和真实数据x，将这个放进价值函数里求梯度，对辨别器的参数求梯度，更新辨别器，然后做k步，接着取得m个噪音样本，对生成器进行训练，将第二项对生成器的参数求梯度，再更新生成器，至此完成一次迭代

> 问题1：k不能取太小，也不能取太大，取太小，辨别器基本不能辨别，意义不大，取太大，第二项训练的时候接近0，再求导，在生成模型上的更新会有困难

> 问题2：如何判断收敛

### 理论上的结果

1. 目标函数有一个全局最优解，当前仅当生成器学到的分布和真实分布相等。（目标函数正确）

   1. ![image-20220304191050701](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20220304191050701.png)

   2. x是由z通过g生成出来的，x=g(z)![image-20220304191305051](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20220304191305051.png)

      求导求最大值，可得D(x)->proposition  1

      

      可以转换成两个KL散度

      ![image-20220304191328310](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20220304191328310.png)

      ![image-20220304192126274](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20220304192126274.png)

      KL是大于等于0的，当KL取到0时，两个分布相等

      ![image-20220304192328263](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20220304192328263.png)

      也可以表示成JS散度

2. 算法确实可以求解目标函数

   1. ![image-20220304192455364](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20220304192455364.png)
   2. 我们首先是允许算法1中间D每一步都达到最优解（虽然但是，没有允许D每一步都达到最优解），如果对G的优化是执行上面这个步骤，$p_g$会收敛到$p_{data}$
   3. 证明是将$V(G,D)=U(p_g,D)$,展开之后是一个关于$p_g$的凸函数，然后做梯度下降的时候就会得到最优解。

