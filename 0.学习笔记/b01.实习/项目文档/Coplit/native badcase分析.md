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
![[Pasted image 20231023155741.png]]

### 倾向于不使用魔法流程，直接简化流程
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
3. 变量未定义，没有用魔法流程计算average_sales这个变量
```python
for product in xbot_visual.desktop.iter_all_elements(window=""0"",element=""产品销售额""):
# 获取产品的销售额
sales = xbot_visual.desktop.get_attribute(window=""0"",element=product,attribute_name=""text"")
# 判断销售额是否低于平均值
   if sales < average_sales:
       # 如果销售额低于平均值，自动预警
	xbot_visual.desktop.click(window=""0"",element=""预警按钮"")

[""变量未定义{'average_sales'}""]",仅参数错误
```
4. 类似的
```python
# 判断过期日期是否在预警范围内
    if expiration_date < ""2023-12-31"":
        # 如果是，打印预警信息
        print(""物料{0}即将过期，请及时处理"".format(material_name))
```

## native单模块指令训练集
![[Pasted image 20231023155652.png]]
### 业务错误
1. 应该先找张三
```python
# 判断聊天记录是否为我和张三的聊天记录
    if ""我和张三"" in record_text:
```

### 语法错误
1. 没有调用魔法流程，而且魔法流程中含有xbot_visual
```python
我在玩开心消消乐游戏，自动点击所有显示数字8的方块。,"```python
# 使用此指令前，先安装必要的python库，使用以下命令
# pip install
def click_all_eight_blocks():
    """"""
    title: 点击所有显示数字8的方块
    description: 在开心消消乐游戏中，自动点击所有显示数字8的方块
    inputs:
        - None
    outputs:
        - None
    """"""
    # 遍历所有方块元素
    for block in xbot_visual.desktop.iter_all_elements(window=""0"",element=""方块""):
        # 获取方块上显示的数字
        number = xbot_visual.desktop.get_attribute(window=""0"",element=block,attribute_name=""text"")
        # 如果数字为8
        if number == ""8"":
            # 点击该方块
            xbot_visual.desktop.click(window=""0"",element=block)
``` END",[],有效代码
```
2. 乱编python库的函数，没有定义过
```python
# 判断视频发布时间是否在一小时内
    if is_time_in_range(publish_time, ""1 hour""):
```
3. 等待相关的还是乱编函数，比如xbot_visual.desktop.wait_for_state


## native 单模块验证集
![[Pasted image 20231023162139.png]]