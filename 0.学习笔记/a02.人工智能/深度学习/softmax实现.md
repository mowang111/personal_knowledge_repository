## 导入数据集

## 初始化模型参数

输入输出的维度，W,b的初始化

## 模型的实现

softmax

![download](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/download.png)

加一层net包装

## 损失函数

交叉熵损失函数cross_entropy     $-log(y\_hat_y)$

## 计算预测正确的数量

accuracy

## 评估模型准确率

evaluate_accuracy

使用到了累加器Accumulator()

## 累加器

add

reset

\_\_getitem\_\_

### 训练模型

输入模型net, 训练数据train_iter, 损失函数loss, 优化器updater

返回训练损失和精度

1. 计算预测值
2. 计算损失函数
3. 反向传播
4. 用优化器更新参数
5. 将损失，预测正确数，总数加到累加器

## 总训练过程

train_ch3

分多个epoch训练，画图