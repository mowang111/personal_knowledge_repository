---
tags:
---
{'extra_args': ["xbot_visual.desktop.drag_to_element:['file_path']"], 'misss_args': ["xbot_visual.desktop.drag_to_element:['window', 'target']"]}
```python
# 拖拽example.txt文件到微信消息输入框
xbot_visual.desktop.drag_to_element(file_path="C:/Users/Username/Desktop/example.txt", element="微信消息输入框")
# 打印执行情况消息
print("文件已经拖拽到微信消息输入框")
```
---
```python
# 检查微信窗口是否存在
if xbot_visual.desktop.exists(title="微信"):
    # 检查微信窗口是否包含消息输入框
    if xbot_visual.desktop.contains_element(window="0", element="消息输入框"):
        # 如果存在消息输入框，拖拽example.txt文件到消息输入框中
        xbot_visual.desktop.drag_to_element(window="0", element="example.txt文件", target="消息输入框")
        # 打印执行情况消息
        print("example.txt文件已拖拽到消息输入框中")
    # 否则
    else:
        # 如果不存在消息输入框，打印未找到消息输入框
        print("未找到消息输入框")
# 否则
else:
    # 如果不存在微信窗口，打印未找到微信窗口
    print("未找到微信窗口")
```
