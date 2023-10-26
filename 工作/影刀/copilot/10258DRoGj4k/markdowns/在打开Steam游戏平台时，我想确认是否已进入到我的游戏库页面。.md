---
tags:
---
{'extra_args': ["xbot_visual.desktop.get_active:['window']", "xbot_visual.desktop.contains_element:['limit']"]}
```python
# 打开Steam游戏平台
process_info=xbot_visual.desktop.launch(process_name="Steam")
# 点击进入我的游戏库
xbot_visual.desktop.click(window="0", element="我的游戏库")
# 获取当前激活的窗口
steam_window = xbot_visual.desktop.get_active(window="Steam")
# 判断是否已进入到我的游戏库页面
if xbot_visual.desktop.contains_element(window="0", element="我的游戏库", limit="1"):
    # 打印已进入到我的游戏库页面
    print("已进入到我的游戏库页面")
# 否则
else:
    # 打印未进入到我的游戏库页面
    print("未进入到我的游戏库页面")
```
---
```python
# 获取Steam窗口
steam_window = xbot_visual.desktop.get(title="Steam")
# 检查Steam窗口是否包含我的游戏库元素
if xbot_visual.desktop.contains_element(window=steam_window, element="我的游戏库"):
    # 打印已经进入我的游戏库页面
    print("已经进入我的游戏库页面")
# 否则
else:
    # 打印未进入我的游戏库页面
    print("未进入我的游戏库页面")
```
