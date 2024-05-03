## Keras 基础介绍

![Image](https://imgbed.momodel.cn/20200112152635.png)

Keras 是一个用 Python 编写的高级神经网络 API，它能够以 TensorFlow，CNTK 或者 Theano 作为后端运行。

Keras 具有如下优点：

- 由于用户友好，高度模块化，可扩展性，可以简单而快速的进行原型设计。
- 同时支持卷积神经网络和循环神经网络，以及两者的组合。
- 在 CPU 和 GPU 上无缝运行。



Keras 的核心数据结构是 model，一种组织网络层的方式。最简单的模型是 Sequential 顺序模型，它把多个网络层线性堆叠起来。

Sequential 模型如下所示：

```python
from tensorflow.keras.models import Sequential
model = Sequential()
```

可以简单地使用 .add() 来堆叠模型：

```python
from tensorflow.keras.layers import Dense

model.add(Dense(units=64, activation='relu', input_dim=100))
model.add(Dense(units=10, activation='softmax'))
```

在完成了模型的构建后, 可以使用 .compile() 来配置学习过程：

```python
model.compile(loss='categorical_crossentropy',
              optimizer='sgd',
              metrics=['accuracy'])
```

然后，就可以批量地在训练数据上进行迭代了。

```python
# x_train 和 y_train 是 Numpy 数组 -- 就像在 Scikit-Learn API 中一样。
model.fit(x_train, y_train, epochs=5, batch_size=32)
```

只需一行代码就能评估模型性能：

```python
loss_and_metrics = model.evaluate(x_test, y_test, batch_size=128)
```

或者对新的数据生成预测：

```python
classes = model.predict(x_test, batch_size=128)
```

