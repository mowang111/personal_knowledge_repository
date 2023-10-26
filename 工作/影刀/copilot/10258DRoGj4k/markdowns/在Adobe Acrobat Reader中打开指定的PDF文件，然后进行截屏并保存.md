---
tags:
---
{'err_funcs': ['xbot_visual.desktop.wait_window']}
```python
# 打开Adobe Acrobat Reader
process_info=xbot_visual.desktop.launch(process_name="Adobe Acrobat Reader")
# 点击打开文件按钮
xbot_visual.desktop.click(window="0", element="打开文件按钮")
# 在文件路径输入框中输入指定的PDF文件路径
xbot_visual.desktop.input(window="0", element="文件路径输入框", text="C:\\example.pdf")
# 点击打开按钮
xbot_visual.desktop.click(window="0", element="打开按钮")
# 等待PDF文件加载
xbot_visual.desktop.wait_window(window="PDF文件", state="存在")
# 截屏PDF文件
xbot_visual.desktop.screenshot_element(window="PDF文件", element="PDF文件", file_folder="C:\\", file_name="pdf_screenshot.png")
```
---
```python
# 打开Adobe Acrobat Reader
process_info=xbot_visual.desktop.launch(process_name="Adobe Acrobat Reader")
# 点击打开文件按钮
xbot_visual.desktop.click(window="0", element="打开文件按钮")
# 在文件选择窗口中输入文件路径
xbot_visual.desktop.input(window="0", element="文件路径输入框", text="C:\\example.pdf")
# 点击打开按钮
xbot_visual.desktop.click(window="0", element="文件选择窗口打开按钮")
# 截取pdf显示区域的截图
screenshot_path = xbot_visual.desktop.screenshot_element(window="0", element="pdf显示区域", file_folder="C:\\", file_name="screenshot.pn")
```
