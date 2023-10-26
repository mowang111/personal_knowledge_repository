---
tags:
---
{'extra_args': ["xbot_visual.desktop.get:['cls', 'idx']"]}
```python
# 获取QQ聊天窗口的消息框元素
qq_chat_window = xbot_visual.desktop.get(title="QQ聊天", cls="TXGuiFoundation", idx="0")
message_box = xbot_visual.desktop.find_element(window=qq_chat_window, element="消息框")
# 对消息框进行截图
xbot_visual.desktop.screenshot_element(window=qq_chat_window, element=message_box, file_folder="C:\\Desktop", file_name="message_box.png")
```
---
```python
# 打开QQ
process_info=xbot_visual.desktop.launch(process_name="QQ")
# 对消息框进行截图
xbot_visual.desktop.screenshot_element(window="0", element="消息框", file_folder="C:\\Desktop", file_name="qq_message.png")
```
