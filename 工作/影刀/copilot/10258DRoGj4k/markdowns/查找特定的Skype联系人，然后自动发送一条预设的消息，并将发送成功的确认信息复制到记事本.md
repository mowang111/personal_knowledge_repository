---
tags:
---
{'err_funcs': ['xbot_visual.desktop.wait_element']}
```python
# 打开Skype
process_info=xbot_visual.desktop.launch(process_name="Skype")
# 在搜索框中输入联系人名称
xbot_visual.desktop.input(window="0", element="Skype搜索框", text="特定的Skype联系人")
# 点击搜索按钮
xbot_visual.desktop.click(window="0", element="Skype搜索按钮")
# 点击进入联系人对话框
xbot_visual.desktop.click(window="0", element="特定的Skype联系人对话框")
# 在消息输入框中输入预设的消息
xbot_visual.desktop.input(window="0", element="Skype消息输入框", text="这是一条预设的消息")
# 点击发送按钮
xbot_visual.desktop.click(window="0", element="Skype发送按钮")
# 等待发送成功的确认信息出现
xbot_visual.desktop.wait_element(window="0", element="Skype发送成功确认信息")
# 获取发送成功的确认信息文本
success_message = xbot_visual.desktop.get_attribute(window="0", element="Skype发送成功确认信息", attribute_name="text")
# 将发送成功的确认信息文本复制到记事本
xbot_visual.desktop.input(window="0", element="记事本编辑区", text=success_message)
```
---
```python
# 打开Skype软件
process_info=xbot_visual.desktop.launch(process_name="Skype")
# 在搜索框中输入联系人名称
xbot_visual.desktop.input(window="0", element="搜索框", text="联系人名称")
# 点击搜索按钮
xbot_visual.desktop.click(window="0", element="搜索按钮")
# 点击进入联系人对话框
xbot_visual.desktop.click(window="0", element="联系人对话框")
# 在消息输入框中输入预设的消息
xbot_visual.desktop.input(window="0", element="消息输入框", text="预设的消息")
# 点击发送按钮
xbot_visual.desktop.click(window="0", element="发送按钮")
# 获取发送成功的确认信息
success_message = xbot_visual.desktop.get_attribute(window="0", element="发送成功的确认信息", attribute_name="text")
# 双击记事本图标打开记事本
xbot_visual.desktop.click(window="0", element="记事本图标", clicks="dbclick")
# 输入发送成功的确认消息到记事本
xbot_visual.desktop.input(window="0", element="记事本输入框", text=success_message)
```
