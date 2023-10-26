---
tags:
---
{'err_funcs': ['xbot_visual.desktop.select'], 'extra_args': ["xbot_visual.keyboard.send_keys:['in_focus']"]}
```python
# 打开"日期和时间"设置窗口
xbot_visual.keyboard.send_keys(keys="#{r}", in_focus="True")
# 选择"时区"下拉框
xbot_visual.desktop.select(window="0", element="时区下拉框", option="index",  value="1")
```
---

