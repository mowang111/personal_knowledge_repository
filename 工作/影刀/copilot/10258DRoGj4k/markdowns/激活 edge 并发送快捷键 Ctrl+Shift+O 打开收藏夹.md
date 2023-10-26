---
tags:
---
{'extra_args': ["xbot_visual.desktop.activate:['element']"]}
```python
# 打开edge
process_info=xbot_visual.desktop.launch(process_name="edge")
# 激活edge窗口
xbot_visual.desktop.activate(window="0",element="edge窗口")
# 发送快捷键 Ctrl+Shift+O
xbot_visual.keyboard.send_keys(keys="^+O")
```
---
```python
# 根据标题获取edge窗口并激活窗口
edge_window = xbot_visual.desktop.get(title="edge")
# 发送快捷键 Ctrl+Shift+O 打开收藏夹
xbot_visual.keyboard.send_keys(keys="^+{O}")
```
