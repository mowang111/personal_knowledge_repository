---
tags:
---
{'err_funcs': ['xbot_visual.desktop.batch_get_attribute']}
```python
# 打开Slack应用程序
process_info=xbot_visual.desktop.launch(process_name="Slack")
# 点击进入Slack登录界面
xbot_visual.desktop.click(window="0", element="Slack登录界面")
# 输入Slack账号
xbot_visual.desktop.input(window="0", element="账号输入框", text="username")
# 输入Slack密码
xbot_visual.desktop.input_password(window="0", element="密码输入框", password="password")
# 点击登录按钮
xbot_visual.desktop.click(window="0", element="登录按钮")
# 点击进入Slack主界面
xbot_visual.desktop.click(window="0", element="Slack主界面")
# 点击进入频道列表
xbot_visual.desktop.click(window="0", element="频道列表")
# 批量获取频道列表中的信息，返回的数据第一列为频道名称，第二列为频道人数
channel_list=xbot_visual.desktop.batch_get_attribute(window="0", element="频道列表", attribute_name="text")
# 遍历返回的数据
for channel in channel_list:
    # 将频道信息写入到已打开的记事本中
    xbot_visual.desktop.input(window="0", element="记事本输入框", text=channel[0]+" "+channel[1])
```
---
```python
# 打开Slack软件
process_info=xbot_visual.desktop.launch(process_name="Slack")
# 填写用户名
xbot_visual.desktop.input(window="0", element="用户名输入框", text="用户名")
# 填写密码
xbot_visual.desktop.input(window="0", element="密码输入框", text="密码")
# 点击登录按钮
xbot_visual.desktop.click(window="0", element="登录按钮")
# 点击进入频道列表
xbot_visual.desktop.click(window="0", element="频道列表")
# 遍历频道对象列表
for channel in xbot_visual.desktop.iter_all_elements(window="0", element="频道对象"):
    # 获取频道名称
    channel_name = xbot_visual.desktop.get_attribute(window="0", element=channel, attribute_name="text")
    # 将频道名称写入到记事本中
    xbot_visual.desktop.input(window="0", element="记事本编辑区", text=channel_name)
```
