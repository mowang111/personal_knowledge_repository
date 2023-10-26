---
tags:
---
{'err_funcs': ['xbot_visual.desktop.contains_string']}
```python
# 打开Skype
process_info=xbot_visual.desktop.launch(process_name="Skype")
# 检查是否有未读消息
if xbot_visual.desktop.contains_string(window="0", element="未读消息提醒", str_to_be_checked="1"):
    # 点击进入消息列表
    xbot_visual.desktop.click(window="0", element="消息列表")
    # 在输入框中输入回复内容
    xbot_visual.desktop.input(window="0", element="输入框", text="我现在有点忙，稍后再联系你")
    # 点击发送按钮
    xbot_visual.desktop.click(window="0", element="发送按钮")
    # 打印回复已发送
    print("回复已发送")
# 如果没有未读消息
else:
    # 打印没有未读消息
    print("没有未读消息")
```
---
```python
# 获取Skype窗口
skype_window = xbot_visual.desktop.get(title="Skype")
# 检查Skype窗口是否包含未读消息提醒元素
if xbot_visual.desktop.contains_element(window=skype_window, element="未读消息提醒"):
    # 点击进入未读消息列表
    xbot_visual.desktop.click(window="0", element="未读消息")
    # 遍历未读消息对象列表
    for message in xbot_visual.desktop.iter_all_elements(window="0", element="未读消息"):
        # 点击进入消息详情页
        xbot_visual.desktop.click(window="0", element=message)
        # 在消息详情页中输入回复内容
        xbot_visual.desktop.input(window="0", element="回复输入框", text="我现在有点忙，稍后再联系你")
        # 点击发送按钮
        xbot_visual.desktop.click(window="0", element="发送按钮")
        # 点击返回按钮
        xbot_visual.desktop.click(window="0", element="返回按钮")
```
