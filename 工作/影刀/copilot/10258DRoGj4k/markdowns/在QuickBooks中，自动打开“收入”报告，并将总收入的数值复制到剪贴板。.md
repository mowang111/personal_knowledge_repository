---
tags:
---
{'err_funcs': ['xbot_visual.desktop.input.keyboard']}
```python
# 打开QuickBooks
process_info=xbot_visual.desktop.launch(process_name="QuickBooks")
# 点击进入“收入”报告
xbot_visual.desktop.click(window="0", element="收入报告")
# 获取总收入的数值
total_income=xbot_visual.desktop.get_attribute(window="0", element="总收入", attribute_name="text")
# 将总收入的数值复制到剪贴板
xbot_visual.desktop.input.keyboard(window="0", element="总收入", keystrokes="^(c)")
```
---
```python
# 打开QuickBooks
process_info=xbot_visual.desktop.launch(process_name="QuickBooks")
# 点击进入报告页面
xbot_visual.desktop.click(window="0", element="报告")
# 点击进入收入报告
xbot_visual.desktop.click(window="0", element="收入报告")
# 双击鼠标从而全选总收入的数值
xbot_visual.desktop.click(window="0", element="总收入数值", clicks="dbclick")
# 输入ctrl+c复制
xbot_visual.keyboard.send_keys(keys="^c")
```
