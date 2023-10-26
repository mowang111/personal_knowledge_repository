---
tags:
---
{'err_funcs': ['xbot_visual.desktop.contains_text']}
```python
# 打开AutoCAD
process_info=xbot_visual.desktop.launch(process_name="AutoCAD")
# 点击AutoCAD中的打开按钮
xbot_visual.desktop.click(window="0", element="打开按钮")
# 在文件路径输入框中输入特定的项目文件路径
xbot_visual.desktop.input(window="0", element="文件路径输入框", text="C:\\Projects\\project.dwg")
# 点击AutoCAD中的确认打开按钮
xbot_visual.desktop.click(window="0", element="确认打开按钮")
# 点击AutoCAD中的保存按钮
xbot_visual.desktop.click(window="0", element="保存按钮")
# 点击AutoCAD中的关闭按钮
xbot_visual.desktop.click(window="0", element="关闭按钮")
# 根据文件路径判断文件是否被正确保存和关闭
if xbot_visual.desktop.contains_text(window="0", text="C:\\Projects\\project.dwg"):
    # 打印文件保存和关闭失败的提示信息
    print("文件保存和关闭失败")
# 否则
else:
    # 打印文件保存和关闭成功的提示信息
    print("文件保存和关闭成功")
```
---
```python
# 打开AutoCAD软件
process_info=xbot_visual.desktop.launch(process_name="AutoCAD")
# 点击打开文件按钮
xbot_visual.desktop.click(window="0", element="打开文件按钮")
# 在文件选择对话框中输入文件路径
xbot_visual.desktop.input(window="0", element="文件路径输入框", text="C:\\Projects\\project.dwg")
# 点击打开按钮
xbot_visual.desktop.click(window="0", element="文件选择对话框打开按钮")
# 点击保存按钮
xbot_visual.desktop.click(window="0", element="保存按钮")
# 点击关闭按钮
xbot_visual.desktop.click(window="0", element="关闭按钮")
# 判断AutoCAD窗口是否已关闭
if xbot_visual.desktop.exists(title="AutoCAD"):
    # 打印AutoCAD窗口未关闭
    print("AutoCAD窗口未关闭")
# 否则
else:
    # 打印AutoCAD窗口已关闭
    print("AutoCAD窗口已关闭")
```
