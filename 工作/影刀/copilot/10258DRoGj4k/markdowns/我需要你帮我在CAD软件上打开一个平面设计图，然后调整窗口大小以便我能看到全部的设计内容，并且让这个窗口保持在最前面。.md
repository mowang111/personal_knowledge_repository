---
tags:
---
{'err_funcs': ['xbot_visual.desktop.set_topmost']}
```python
# 打开CAD软件
process_info=xbot_visual.desktop.launch(process_name="CAD")
# 点击打开文件按钮
xbot_visual.desktop.click(window="0", element="打开文件按钮")
# 在文件选择对话框中输入文件路径
xbot_visual.desktop.input(window="0", element="文件路径输入框", text="C:\\Documents\\Design.dwg")
# 点击确认打开文件
xbot_visual.desktop.click(window="0", element="确认打开按钮")
# 调整CAD窗口大小
xbot_visual.desktop.resize(window="CAD窗口", width="800", height="600")
# 将CAD窗口设置为最前面
xbot_visual.desktop.set_topmost(window="CAD窗口", set_type="front")
```
---
```python
# 打开CAD软件
process_info=xbot_visual.desktop.launch(process_name="CAD")
# 点击打开文件按钮
xbot_visual.desktop.click(window="0", element="打开文件按钮")
# 在文件选择对话框中输入文件路径
xbot_visual.desktop.input(window="0", element="文件路径输入框", text="C:\\User\\Desktop")
# 在文件选择对话框中输入文件名称
xbot_visual.desktop.input(window="0", element="文件名称输入框", text="平面设计图.dwg")
# 执行打开操作
xbot_visual.desktop.click(window="0", element="文件选择对话框的打开按钮")
# 根据CAD软件窗口名称获取CAD窗口对象
cad_window = xbot_visual.desktop.get(title="CAD")
# 调整CAD软件窗口大小以便能看到全部的设计内容
xbot_visual.desktop.resize(window=cad_window, width="1024", height="768")
```
