---
tags:
---
{'err_funcs': ['xbot_visual.desktop.save_as.save']}
```python
# 打开下载文件夹
xbot_visual.keyboard.send_keys(keys="#d")
# 将剪切板内容创建一个txt文件
xbot_visual.desktop.save_as.save(file_name="%UserProfile%\\Downloads\\剪切板内容.txt", folder="Downloads")
```
---
```python
# 输入快捷键win+e，打开文件资源管理器
xbot_visual.keyboard.send_keys(keys="#e")
# 双击进入下载文件夹
xbot_visual.desktop.click(window="0", element="下载文件夹", clicks="dbclick")
# 在下载文件夹中右键点击空白处
xbot_visual.desktop.click(window="0", element="下载文件夹空白处", button="right")
# 点击新建文件
xbot_visual.desktop.click(window="0", element="新建文件")
# 在弹出的对话框中输入文件名
xbot_visual.desktop.input(window="0", element="文件名输入框", text="剪贴板内容.txt")
# 输入Enter键，创建文件
xbot_visual.keyboard.send_keys(keys="{enter}")
# 打开这个文件
xbot_visual.desktop.click(window="0", element="剪贴板内容.txt", clicks="dbclick")
# 点击文件输入框
xbot_visual.desktop.click(window="0", element="文件输入框")
# 通过ctrl + v 粘贴剪贴板内容
xbot_visual.keyboard.send_keys(keys="^v")
# 通过ctrl + s 保存文件
xbot_visual.keyboard.send_keys(keys="^s")
# 关闭文件窗口
xbot_visual.desktop.click(window="0", element="关闭文件窗口")
```
