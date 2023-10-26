---
tags:
---
{'extra_args': ["xbot_visual.desktop.click:['y', 'x']"]}
```python
# 打开Spotify软件
process_info=xbot_visual.desktop.launch(process_name="Spotify")
# 点击创建新的播放列表按钮
xbot_visual.desktop.click(window="0", element="创建新的播放列表按钮")
# 在弹出的对话框中，输入新的播放列表的名称
xbot_visual.desktop.input(window="0", element="播放列表名称输入框", text="新的播放列表")
# 点击保存按钮
xbot_visual.desktop.click(window="0", element="保存按钮")
# 在搜索栏中输入指定的歌曲名称
xbot_visual.desktop.input(window="0", element="搜索栏", text="指定的歌曲")
# 点击搜索按钮
xbot_visual.desktop.click(window="0", element="搜索按钮")
# 假设搜索结果列表的第一首歌曲的添加按钮的坐标为(100, 200)
# 遍历搜索结果列表
for song in xbot_visual.desktop.iter_all_elements(window="0", element="搜索结果列表"):
    # 获取歌曲名称
    song_name = xbot_visual.desktop.get_attribute(window="0", element=song, attribute_name="text")
    # 判断歌曲名称是否为指定的歌曲
    if song_name == "指定的歌曲":
        # 点击添加按钮
        xbot_visual.desktop.click(window="0", element="添加按钮", x="100", y="200")
        # 退出循环
        break
# 将Spotify窗口最小化
xbot_visual.desktop.set_state(window="0", state="minimize")
```
---
```python
# 打开Spotify软件
process_info=xbot_visual.desktop.launch(process_name="Spotify")
# 点击创建新的播放列表按钮
xbot_visual.desktop.click(window="0", element="创建新的播放列表按钮")
# 在弹出的对话框中输入新的播放列表的名称
xbot_visual.desktop.input(window="0", element="播放列表名称输入框", text="新的播放列表")
# 点击保存按钮
xbot_visual.desktop.click(window="0", element="保存按钮")
# 在搜索栏中输入指定的歌曲名称
xbot_visual.desktop.input(window="0", element="搜索栏", text="指定的歌曲")
# 点击搜索按钮
xbot_visual.desktop.click(window="0", element="搜索按钮")
# 获取Spotify窗口
spotify_window = xbot_visual.desktop.get(title="Spotify")
# 遍历歌曲列表，并将其添加到新创建的播放列表中
for song in xbot_visual.desktop.iter_all_elements(window="0", element="歌曲"):
    # 点击添加到播放列表按钮
    xbot_visual.desktop.click(window="0", element="添加到播放列表按钮")
    # 点击播放列表下拉框
    xbot_visual.desktop.click(window="0", element="播放列表下拉框")
    # 选择新创建的播放列表
    xbot_visual.desktop.click(window="0", element="新的播放列表")
# 最后，将Spotify窗口最小化
xbot_visual.desktop.set_state(window=spotify_window, state="minimize")
```
