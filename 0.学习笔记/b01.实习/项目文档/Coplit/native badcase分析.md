| 类型                   | 出现次数 |     |
| ---------------------- | -------- | --- |
| 参数错误               |          |     |
| 代码格式错误           |          |     |
| 函数不正确             |          |     |
| 业务错误               |          |     |
| 模块错误               | 0        |     |
| 无限重复               | 0        |     |
| 指令函数中有xbot的变量 |          |     |
| 不符合定义好的格式     |          |     |
| 正确                   |          |     |
| 总数                   |          |     |
|                        |          |     |


## 模块混合魔法指令训练集
1. 希望抽取成正则的魔法指令来提取信息，但是用错了，这种本来训练集就多一些，错的也多一些，三四个吧
```python
# 获取商品名称
name = xbot_visual.desktop.get_attribute(window=""0"",element=item,attribute_name=""text"")
# 获取商品价格
price = xbot_visual.desktop.get_attribute(window=""0"",element=item,attribute_name=""text"")
```
2. 希望写成魔法指令的，但是他简化了
```python
# 在提醒时间设置中，将时间提前5分钟
xbot_visual.desktop.input(window=""0"",element=""提醒时间设置"",text=""+5"")
```
