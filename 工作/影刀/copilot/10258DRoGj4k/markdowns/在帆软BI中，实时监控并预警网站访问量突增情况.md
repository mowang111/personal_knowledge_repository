---
tags:
---
{'err_funcs': ['xbot_visual.desktop.close_all']}
```python
# 打开帆软BI
process_info=xbot_visual.desktop.launch(process_name="帆软BI")
# 点击进入实时监控模块
xbot_visual.desktop.click(window="0", element="实时监控")
# 点击进入网站访问量监控
xbot_visual.desktop.click(window="0", element="网站访问量")
# 获取当前网站访问量
web_traffic = xbot_visual.desktop.get_attribute(window="0", element="网站访问量", attribute_name="text")
# 判断网站访问量是否突增
if int(web_traffic) > 1000:
    # 网站访问量突增，输出预警信息
    print("网站访问量突增，当前访问量为：{}".format(web_traffic))
# 关闭帆软BI
xbot_visual.desktop.close_all()
```
  END
---
```python
# 导入time模块
import time
# 打开帆软BI软件
process_info=xbot_visual.desktop.launch(process_name="帆软BI")
# 点击进入网站访问量监控页面
xbot_visual.desktop.click(window="0", element="网站访问量监控")
# 循环，每隔10分钟执行一次
while True:
    # 获取网站访问量数据
    data = xbot_visual.desktop.get_attribute(window="0", element="网站访问量数据", attribute_name="text")
    # 判断网站访问量是否突增
    if int(data) > 1000:
        # 如果网站访问量突增，打印报警信息
        print("网站访问量已突增，请及时处理")
    # 等待10分钟
    time.sleep(600)
```
