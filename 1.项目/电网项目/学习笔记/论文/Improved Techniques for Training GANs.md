训练GAN的提升技巧

## 相关工作

| 提升点                              | 相关论文                                                     | 备注                                                         |
| ----------------------------------- | ------------------------------------------------------------ | ------------------------------------------------------------ |
| 提高GAN训练的稳定性和生成样本的质量 | Emily Denton, Soumith Chintala, Arthur Szlam, and Rob Fergus. Deep generative image models using a laplacian pyramid of adversarial networks. arXiv preprint arXiv:1506.05751, 2015. |                                                              |
|                                     | Alec Radford, Luke Metz, and Soumith Chintala. Unsupervised representation learning with deep convolutional generative adversarial networks. arXiv preprint arXiv:1511.06434, 2015 | DCGAN                                                        |
|                                     | Daniel Jiwoong Im, Chris Dongjoo Kim, Hui Jiang, and Roland Memisevic. Generating images with recurrent adversarial networks. arXiv preprint arXiv:1602.05110, 2016. |                                                              |
|                                     | Donggeun Yoo, Namil Kim, Sunggyun Park, Anthony S Paek, and In So Kweon. Pixel-level domain transfer. arXiv preprint arXiv:1603.07442, 2016 |                                                              |
| 特征匹配（feature matching）        | Arthur Gretton, Olivier Bousquet, Alex Smola, and Bernhard Scholkopf. Measuring statistical depen- ¨ dence with hilbert-schmidt norms. In Algorithmic learning theory, pages 63–77. Springer, 2005. | maximum mean discrepancy                                     |
|                                     | Kenji Fukumizu, Arthur Gretton, Xiaohai Sun, and Bernhard Scholkopf. Kernel measures of conditional ¨ dependence. In NIPS, volume 20, pages 489–496, 2007. | *                                                            |
|                                     | Alex Smola, Arthur Gretton, Le Song, and Bernhard Scholkopf. A hilbert space embedding for distribu- ¨ tions. In Algorithmic learning theory, pages 13–31. Springer, 2007 | *                                                            |
|                                     | Yujia Li, Kevin Swersky, and Richard S. Zemel. Generative moment matching networks. CoRR, abs/1502.02761, 2015. |                                                              |
|                                     | Gintare Karolina Dziugaite, Daniel M Roy, and Zoubin Ghahramani. Training generative neural networks via maximum mean discrepancy optimization. arXiv preprint arXiv:1505.03906, 2015. |                                                              |
| 小批量特征（minibatch features）    | Sergey Ioffe and Christian Szegedy. Batch normalization: Accelerating deep network training by reducing internal covariate shift. arXiv preprint arXiv:1502.03167, 2015. | batch normalization                                          |
| virtual batch normalization         | *                                                            |                                                              |
| GANs 被用来进行半监督训练           | Ilya Sutskever, Rafal Jozefowicz, Karol Gregor, et al. Towards principled unsupervised learning. arXiv preprint arXiv:1511.06440, 2015 |                                                              |
|                                     | Jost Tobias Springenberg. Unsupervised and semi-supervised learning with categorical generative adversarial networks. arXiv preprint arXiv:1511.06390, 2015 |                                                              |
| predict image labels                | Augustus Odena. Semi-supervised learning with generative adversarial networks. arXiv preprint arXiv:1606.01583, 2016 | Odena [15] proposes to extend GANs to predict image labels like we do in Section 5, but without our feature matching extension (Section 3.1) which we found to be critical for obtaining state-of-the-art performance. |

## 针对GAN的训练

对于代价函数非凸，参数连续，参数空间高维的场景，现有的算法不知道是否可行

**当一个玩家相对于 x 最小化 xy，而另一个玩家相对于 y 最小化 −xy 时，梯度下降进入稳定的轨道，而不是收敛的 x = y = 0，即所需的平衡点**（？）（Ian Goodfellow, Yoshua Bengio, and Aaron Courville. Deep Learning. 2016. MIT Press.）

### Feature matching

避免生成器过度拟合当前的判别器，比如当真实数据包括红色和圆形两个特征时，此时的辨别器只能提取到红色这一个特征，而生成器刚好都生成的是红色这一特征，但是其中包含了其他形状的数据，辨别器无法区分生成器生成的数据和真实数据，也无法给生成器反馈，两个达到了一个虚假的平衡（？理解好像不对，不懂）。

### Minibatch discrimination

