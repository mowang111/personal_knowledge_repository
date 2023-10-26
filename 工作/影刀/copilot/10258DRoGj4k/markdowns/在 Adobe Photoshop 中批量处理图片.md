---
tags:
---
{'err_funcs': ['xbot_visual.desktop.wait_all_elements_loaded']}
```python
# 打开 Adobe Photoshop
process_info=xbot_visual.desktop.launch(process_name="Adobe Photoshop")
# 点击文件菜单
xbot_visual.desktop.click(window="0", element="文件菜单")
# 点击批量处理选项
xbot_visual.desktop.click(window="0", element="批量处理选项")
# 在批量处理窗口中，点击添加按钮
xbot_visual.desktop.click(window="0", element="添加按钮")
# 在文件选择窗口中，输入图片文件夹的路径
xbot_visual.desktop.input(window="0", element="文件路径输入框", text="C:\\Images")
# 点击打开按钮，批量导入图片
xbot_visual.desktop.click(window="0", element="打开按钮")
# 在批量处理窗口中，选择图片处理的选项，比如调整大小
xbot_visual.desktop.select_by_text(window="0", element="处理选项下拉框", text="调整大小")
# 在调整大小选项中，输入新的尺寸
xbot_visual.desktop.input(window="0", element="尺寸输入框", text="800x600")
# 点击确定按钮，开始批量处理图片
xbot_visual.desktop.click(window="0", element="确定按钮")
# 等待一段时间，等待图片处理完成
xbot_visual.desktop.wait_all_elements_loaded(window="0", element="图片处理进度条")
# 关闭 Photoshop
xbot_visual.desktop.close(window="0")
```
---
```python
# 打开Adobe Photoshop
process_info=xbot_visual.desktop.launch(process_name="Adobe Photoshop")
# 点击文件菜单
xbot_visual.desktop.click(window="0", element="文件菜单")
# 点击打开
xbot_visual.desktop.click(window="0", element="打开")
# 在文件选择对话框中输入图片文件夹路径
xbot_visual.desktop.input(window="0", element="文件路径输入框", text="C:\\Images")
# 点击打开
xbot_visual.desktop.click(window="0", element="打开按钮")
# 点击动作菜单
xbot_visual.desktop.click(window="0", element="动作菜单")
# 点击批量处理
xbot_visual.desktop.click(window="0", element="批量处理")
# 在批量处理对话框中选择动作
xbot_visual.desktop.select_by_text(window="0", element="动作下拉框", text="图片处理动作")
# 点击运行
xbot_visual.desktop.click(window="0", element="运行按钮")
```
