---
tags:
---
{'extra_args': ["xbot_visual.desktop.exists:['window', 'element']"], 'misss_args': ["xbot_visual.desktop.exists:['title']"]}
```python
# 打开桌面
xbot_visual.desktop.click(window="0", element="桌面", button="left", clicks="2")
# 在桌面上查找应用程序图标
if xbot_visual.desktop.exists(window="0", element="MyApp"):
    # 如果存在，打印存在
    print("存在")
else:
    # 如果不存在，打印不存在
    print("不存在")
```
---
```python
# 获取桌面软件窗口对象
desktop_window = xbot_visual.desktop.get(title="桌面")
# 检查桌面软件窗口是否包含MyApp图标
if xbot_visual.desktop.contains_element(window=desktop_window, element="MyApp图标"):
    # 如果包含MyApp图标，打印已找到MyApp图标
    print("已找到MyApp图标")
# 否则
else:
    # 如果不包含MyApp图标，打印未找到MyApp图标
    print("未找到MyApp图标")
```
