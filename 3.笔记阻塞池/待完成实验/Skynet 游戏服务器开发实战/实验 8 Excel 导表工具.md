# 实验介绍

本节实验设计了游戏开发中的导表工具的架构， Excel 转换成游戏配置在游戏开发的流程中已经是必不可少的一部分了。然后演示了导表工具的使用，最后还提出了导表工具的优化方向。

#### 知识点

- Excel 导表工具设计
- 如何使用导表工具
- 导表工具的优化方向

本节实验的代码可以从这里下载：

```txt
https://labfile.oss.aliyuncs.com/courses/2770/code8.zip
```

# Excel 导表工具

#### 导表工具设计

Excel 在游戏开发中已经成为了必不可少的工具了，游戏数值的配置现在都是用 Excel 配置的，然后使用工具把 Excel 转换成游戏开发使用的语言对应的数据结构。

如果游戏开发语言是 Lua ，那么导出的数据结构就是 Lua 的 Table 格式的，如果游戏开发语言是 Javascript ，那么导出的数据结构就是 JSON ，如果游戏开发语言是 Python ，那么导出的数据结构就是 Python 的 Dict 格式。

Excel 的每个 Sheet 都是一个二维表，可以设定一个 Sheet 导出一个数据文件。那设计导表工具只需要考虑导出一个 Sheet 的情况了，输入参数就是 Excel 的文件名和 Sheet 名，以及输出的文件名。如果是命令行工具，使用实例应该是类似这样的：

```bash
excel-export -f 道具表.xls -s 道具 -t items.json
```

其中 `excel-export` 是导表工具的名字， `-f` 参数是需要导入的 Excel 文件名， `-s` 参数是 Sheet 名， `-t` 参数是输出的目标文件名。

工具设计成命令的方式有个好处就是方便拓展，一般游戏开发过程中，会对导表工具进行定制的，比如嵌入到 Unity 编辑器中，或者写个网页来调用导表工具，或者集成 svn/git 版本管理工具。

工具如何使用已经设计好了，接下来就需要考虑 Excel 内容格式了，需要设定一个合适的格式才能正确的导出成想要的数据格式。设计结构如下图：

![Excel 内容格式](https://doc.shiyanlou.com/courses/2770/1456966/9a016a80c96c65328a6214b7838aa4fa-0)

Excel 前 4 行称为表头 Head ，表头下面是数据内容 Body 。 4 行表头分别为：

- 中文名，用于标识该列数据是干什么的
- 数据类型，用于标识该列数据是什么类型的，方便导出对应语言的数据类型
- 字段 Key ，可以理解为该列数据的英文名
- 导出标记，用于区分该列数据是客户端使用的还是服务端使用的或者都用到的

第一列特殊设计为数据的索引，就像数据库的主键一样。上图是以转出 JSON 格式为例。数据类型一般只需要支持最基本的整数和字符串就可以了，也可以拓展支持整数数组和字符串数组，更高级的也能支持 JSON 。

#### 使用导表工具

导表工具使用这个做演示 [hanxi/export.py](https://github.com/hanxi/export.py) 。

先把工具下载下来：

```bash
git clone https://github.com/hanxi/export.py.git
```

然后安装依赖库 `xlrd` ：

```bash
sudo pip3 install xlrd
```

然后进入目录 `export.py` ，接着执行 `python3 export.py` ：

```bash
cd export.py
python3 export.py
```

输出的接过提示如下：

![帮助提示](https://doc.shiyanlou.com/courses/2770/1456966/cbad8557936e670ccbafa5b9f79bf5e3-0)

参数意思解释如下：

- `-f` 为输入的 Excel 文件
- `-s` 为 Excel 的 Sheet 名
- `-t` 输出的文件名，支持后缀： `py` ， `json` ， `lua`
- `-k` 支持两种 Excel 表头格式，我们这里只需要使用默认的就行
- `-o` 导出列类型，支持配置导出 `server` ， `client` ，默认都导出

新增测试的 Excel 文件，文件名为 `ItemTable.xlsx` ，Sheet 名为 `Item` ，内容如下：

| 道具 ID       | 名称          | 售价          |
| ------------- | ------------- | ------------- |
| int           | str           | int           |
| Id            | Name          | Price         |
| server/client | server/client | server/client |
| 1             | 衣服          | 100           |
| 2             | 鞋子          | 200           |

把 `ItemTable.xlsx` 文件保存到和 `export.py` 文件同一个路径下，然后执行下面的导出命令：

```bash
python3 export.py -f ItemTable.xlsx -s Item -t item.lua
```

效果如下：

![导出效果](https://doc.shiyanlou.com/courses/2770/1456966/b31dbf86d424b8e831f7ec48359ca88c-0)

再试试导出 JSON 文件的效果：

```bash
python3 export.py -f ItemTable.xlsx -s Item -t item.json
```

![导出 JSON 文件](https://doc.shiyanlou.com/courses/2770/1456966/78540ecd4967ca3c73832304c679129d-0)

看上图注意到 JSON 的索引变成了字符串，原因是 JSON 的字段 Key 只支持字符串，所以导表工具直接把 Key 转成字符串了。

最后来看看导出 Python 文件的效果：

```bash
python3 export.py -f ItemTable.xlsx -s Item -t item.py
```

![导出 Python 文件](https://doc.shiyanlou.com/courses/2770/1456966/4cb209be4637ced4902066e309ea42e2-0)

#### 导表工具的优化方向

直接拿 `export.py` 到游戏项目里也是可以使用的，但是工具总是会有优化的余地的。优化的方向有下面几个：

- 操作简单
- 版本管理
- 支持更多的数据格式
- 支持更多的编程语言

操作简单是首要的，不可能每次导表的时候都需要输入一串的命令，最简单的处理办法就是写个批处理脚本，读取一个配置文件，后期维护配置文件即可，每次导表时运行批处理脚本即可。还可以根据玩法模块的不同，支持一次只导出一个玩法模块相关的表格。

在团队协作开发，版本管理也是重要的，每次导表都在对应的版本分支里面导。

支持更多的数据格式也是常见的，比如支持数组，支持 JSON ，更高级的还能支持函数。

关于易用性方面的优化，可以参考下面的这个截图，是一个使用 skynet 开发的简单网页，代码框架地址为 [hanxi/simpleweb](https://github.com/hanxi/simpleweb) 。最终效果就是实现其他岗位的人员，比如策划，测试，客户端等人员来修改配置表和重启服务器，达到快速测试和验收配表结果。

![导表工具截图](https://doc.shiyanlou.com/courses/2770/1456966/a9f12617e134254ba5e597343bdd09ed-0)

# 实验总结

在本节实验中，了解到游戏开发流程中将策划配置的 Excel 转换成游戏代码能够方便读取的数据的工具。熟悉了 Excel 导表工具的使用，也对导表工具的优化有了一定的方向。