---
tags:
---
{'err_funcs': ['xbot_visual.desktop.wait_until_page_loaded']}
```python
# 打开西门子MES软件
process_info=xbot_visual.desktop.launch(process_name="西门子MES")
# 点击进入报告生成模块
xbot_visual.desktop.click(window="0", element="报告生成")
# 选择生成月报告
xbot_visual.desktop.select_by_text(window="0", element="报告类型", text="月报告")
# 点击生成报告按钮
xbot_visual.desktop.click(window="0", element="生成报告")
# 等待报告生成完成
xbot_visual.desktop.wait_until_page_loaded(page="报告生成")
# 点击保存报告按钮
xbot_visual.desktop.click(window="0", element="保存报告")
# 在弹出的保存对话框中，输入报告名称
xbot_visual.desktop.input(window="0", element="文件名输入框", text="生产效率报告")
# 点击保存按钮
xbot_visual.desktop.click(window="0", element="保存按钮")
```
---
```python
# 打开西门子MES软件
process_info=xbot_visual.desktop.launch(process_name="西门子MES")
# 点击进入报告生成页面
xbot_visual.desktop.click(window="0", element="报告生成")
# 点击月报告生成按钮
xbot_visual.desktop.click(window="0", element="月报告生成按钮")
# 点击导出报告按钮
xbot_visual.desktop.click(window="0", element="导出报告")
```
