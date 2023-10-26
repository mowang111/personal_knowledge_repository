---
tags:
---
{'err_funcs': ['xbot_visual.desktop.send_keys']}
```python
# 获取QQ主窗口对象
qq_window = xbot_visual.desktop.get(title="QQ")
# 隐藏QQ主窗口
xbot_visual.desktop.set_visibility(window=qq_window, visibility="hide")
# 5秒
xbot_visual.desktop.send_keys(window=qq_window, keys="^n")
# 显示QQ主窗口
xbot_visual.desktop.set_visibility(window=qq_window, visibility="show")
```
---
```python
# 获取QQ窗口对象
qq_window = xbot_visual.desktop.get(title="QQ")
# 设置QQ的主界面隐藏
xbot_visual.desktop.set_visibility(window=qq_window, visibility="hide")
# 设置QQ的主界面显示
xbot_visual.desktop.set_visibility(window=qq_window, visibility="show")
```
