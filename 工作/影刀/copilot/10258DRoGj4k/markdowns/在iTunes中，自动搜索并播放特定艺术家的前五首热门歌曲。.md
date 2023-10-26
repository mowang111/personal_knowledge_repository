---
tags:
---
{'err_funcs': ['xbot_visual.desktop.wait_until_page_loaded', 'xbot_visual.desktop.sleep']}
```python
# 打开iTunes软件
process_info=xbot_visual.desktop.launch(process_name="iTunes")
# 在搜索框中输入特定艺术家的名称
xbot_visual.desktop.input(window="0", element="iTunes搜索框", text="Taylor Swift")
# 点击搜索按钮
xbot_visual.desktop.click(window="0", element="iTunes搜索按钮")
# 等待搜索结果加载完成
xbot_visual.desktop.wait_until_page_loaded(window="0", timeout="5")
# 遍历搜索结果列表
for song in xbot_visual.desktop.iter_all_elements(window="0", element="iTunes搜索结果列表"):
    # 获取歌曲名称
    song_name = xbot_visual.desktop.get_attribute(window="0", element=song, attribute_name="text")
    # 判断是否为热门歌曲
    if "热门" in song_name:
        # 双击歌曲，播放歌曲
        xbot_visual.desktop.click(window="0", element=song, clicks="dbclick")
        # 等待歌曲播放一段时间
        xbot_visual.desktop.sleep(secs="180")
        # 获取歌曲播放状态
        play_state = xbot_visual.desktop.get_attribute(window="0", element="iTunes播放按钮", attribute_name="text")
        # 如果歌曲正在播放
        if play_state == "暂停":
            # 点击播放按钮，暂停歌曲
            xbot_visual.desktop.click(window="0", element="iTunes播放按钮")
        # 关闭歌曲详情窗口
        xbot_visual.desktop.click(window="0", element="iTunes歌曲详情窗口关闭按钮")
        # 退出循环
        break
```
---
```python
# 导入time模块
import time
# 打开iTunes
process_info=xbot_visual.desktop.launch(process_name="iTunes")
# 在搜索框中输入特定艺术家的名称
xbot_visual.desktop.input(window="0", element="iTunes搜索框", text="艺术家名称")
# 点击搜索按钮
xbot_visual.desktop.click(window="0", element="iTunes搜索按钮")
# 遍历搜索结果
for result in xbot_visual.desktop.iter_all_elements(window="0", element="iTunes搜索结果"):
    # 获取歌曲名称
    song_name = xbot_visual.desktop.get_attribute(window="0", element=result, attribute_name="text")
    # 判断歌曲是否为热门歌曲
    if "热门" in song_name:
        # 双击歌曲，播放歌曲
        xbot_visual.desktop.click(window="0", element=result, clicks="dbclick")
        # 获取当前播放歌曲的信息
        song_info = xbot_visual.desktop.get_attribute(window="0", element="iTunes当前播放歌曲信息", attribute_name="text")
        # 打印当前播放歌曲的信息
        print(song_info)
        # 点击下一首按钮
        xbot_visual.desktop.click(window="0", element="iTunes下一首按钮")
        # 等待5秒
        time.sleep(5)
```
