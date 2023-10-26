---
tags:
---
{'err_funcs': ['xbot_visual.desktop.kill_process']}
```python
# 使用 ctrl+alt+del 快捷键唤起任务管理器
xbot_visual.keyboard.send_keys(keys="^%{DELETE}")
# 结束某个正在运行的进程
xbot_visual.desktop.kill_process(process_name="process_name")
```
---
```python
# 使用 ctrl+alt+del 快捷键唤起任务管理器
xbot_visual.keyboard.send_keys(keys="^%{DELETE}")
# 在任务管理器中输入进程名
xbot_visual.desktop.input(window="0", element="任务管理器搜索框", text="chrome.exe")
# 结束进程
xbot_visual.desktop.click(window="0", element="结束任务按钮")
```
