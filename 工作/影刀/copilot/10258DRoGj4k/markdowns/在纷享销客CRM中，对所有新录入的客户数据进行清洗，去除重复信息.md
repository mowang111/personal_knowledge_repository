---
tags:
---
{'err_funcs': ['xbot_visual.desktop.wait_update', 'xbot_visual.desktop.wait_update']}
```python
# 打开纷享销客CRM软件
process_info=xbot_visual.desktop.launch(process_name="纷享销客CRM")
# 点击进入客户管理模块
xbot_visual.desktop.click(window="0", element="客户管理")
# 点击进入客户列表
xbot_visual.desktop.click(window="0", element="客户列表")
# 点击进入新录入客户筛选条件
xbot_visual.desktop.click(window="0", element="新录入客户")
# 点击进入清洗按钮
xbot_visual.desktop.click(window="0", element="清洗")
# 等待清洗完成
xbot_visual.desktop.wait_update(window="0", element="清洗", prop_name="text")
# 点击进入去重按钮
xbot_visual.desktop.click(window="0", element="去重")
# 等待去重完成
xbot_visual.desktop.wait_update(window="0", element="去重", prop_name="text")
```
---
```python
# 打开纷享销客CRM软件
process_info=xbot_visual.desktop.launch(process_name="纷享销客CRM")
# 点击进入客户管理模块
xbot_visual.desktop.click(window="0", element="客户管理")
# 新建一个集合用于存储已经处理过的客户姓名
customer_name_set = set()
# 遍历所有新录入的客户数据对象
for customer_data in xbot_visual.desktop.iter_all_elements(window="0", element="新录入的客户数据"):
    # 获取客户姓名
    customer_name = xbot_visual.desktop.get_attribute(window="0", element=customer_data, attribute_name="text")
    # 判断客户姓名是否已经处理过
    if customer_name not in customer_name_set:
        # 如果没有处理过，将客户姓名添加到集合中
        customer_name_set.add(customer_name)
    # 如果已经处理过
    else:
        # 删除该客户数据
        xbot_visual.desktop.click(window="0", element="删除客户数据")
```
