| 类型                   | 出现次数 |     |
| ---------------------- | -------- | --- |
| 参数错误               |   13       |     |
| 代码格式错误           |   0       |     |
| 函数不正确             |    46      |     |
| 业务错误               |    12      |
| 模块错误               | 0        |
| 无限重复               | 0        |
| 指令函数中有xbot的变量 |          |
| 不符合定义好的格式     |     4     |
| 正确                   |          |
| 总数                   |          |
|                        |          |


## 模块混合魔法指令训练集
![[Pasted image 20231023155652.png]]

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
![[Pasted image 20231023155741.png]]
### 业务错误
1. 应该先找张三
```python
# 判断聊天记录是否为我和张三的聊天记录
    if ""我和张三"" in record_text:
```

### 语法错误
1. 没有调用魔法流程，而且魔法流程中含有xbot_visual （目前发现两个）
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
```python
我有个PDF文件需要阅读，但是窗口太小看得眼睛疼，可以调整一下PDF阅读器的窗口大小吗，宽度调整为800，高度调整为600。,"```python
# 使用此指令前，先安装必要的python库，使用以下命令
# pip install
def adjust_pdf_window_size(width, height):
    """"""
    title: 调整PDF阅读器窗口大小
    description: 调整PDF阅读器窗口的宽度和高度
    inputs:
        - width (int): 窗口的宽度，eg: 800
        - height (int): 窗口的高度，eg: 600
    outputs:
        - None
    """"""
    pdf_window = xbot_visual.desktop.get(title=""PDF阅读器"")  # 根据PDF阅读器的窗口标题修改
    xbot_visual.desktop.resize(window=pdf_window, width=width, height=height)
    xbot_visual.desktop.move(window=pdf_window, x=""center"", y=""center"")
adjust_pdf_window_size(800, 600)
```
```python
我在一个软件中有个下拉框需要选择，但是我不知道具体选项的文字，只知道是第三个选项。,"```python
# 使用此指令前，先安装必要的python库，使用以下命令
# pip install
def select_option_by_index(index, option_list):
    """"""
    title: 根据索引选择下拉框选项
    description: 根据索引选择下拉框选项
    inputs:
        - index (int): 索引值，从0开始
        - option_list (list): 下拉框选项列表，eg: [""选项1"", ""选项2"", ""选项3""]
    outputs:
        - None
    """"""
    # 选择下拉框
    dropdown = driver.find_element_by_xpath(""下拉框元素xpath"")
    dropdown.click()
    # 选择指定索引的选项
    option = driver.find_element_by_xpath(f""//option[{index+1}]"")
    option.click()
    # 点击确认
    confirm_button = driver.find_element_by_xpath(""确认按钮元素xpath"")
    confirm_button.click()
# 获取下拉框中所有选项
option_list = driver.find_element_by_xpath(""下拉框元素xpath"")
# 选择第三个选项
select_option_by_index(2, option_list)
```
2. 乱编python库的函数，没有定义过
```python
# 判断视频发布时间是否在一小时内
    if is_time_in_range(publish_time, ""1 hour""):
```
```python
# 在客户信息中去除重复信息
    customer_info = remove_duplicate_info(customer_info)
```
3. 乱编函数
	1. 等待相关的还是乱编函数，比如xbot_visual.desktop.wait_for_state
	2. select相关乱编函数，比如select_all，应该是遍历然后select
	3. 创建文件函数，比如desktop.create
	4. 寻找所有elements，应该用find_elements，但是用成了get_all_elements
	5. 函数 xbot_visual.desktop.input.clear 未定义
	6. 函数 xbot_visual.desktop.get_table_data 未定义
		```python
# 获取分析结果表格中的数据
table_data = xbot_visual.desktop.get_table_data(window=""0"",element=""分析结果表格"")
    ```
	  7. contains_text未定义
```python
# 检查文件内容是否包含特定字符串，例如电子邮件地址
    if xbot_visual.desktop.contains_text(window=""0"",text=""电子邮件地址""):
        # 如果包含，打印文件名
        print(f""文件{file}包含电子邮件地址"")
```
    
4. 有部分不知道咋处理的就直接...了
```python
# 选择特定的工具，如画笔工具
xbot_visual.desktop.click(window=""0"",element=""画笔工具"")
# 对图片进行修改
# ...
# 点击保存菜单
xbot_visual.desktop.click(window=""0"",element=""保存菜单"")
# 在文件名输入框中输入保存后的图片路径
```

## native 单模块验证集
![[Pasted image 20231023162139.png]]