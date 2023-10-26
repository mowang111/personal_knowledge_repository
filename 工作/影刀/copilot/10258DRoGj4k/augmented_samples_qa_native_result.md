需求,实现,错误信息,状态
从已经打开的记事本中读取好友名称，通过钉钉给好友发送消息，格式为“好友名称”+ 你好。,"```python
# 获取已经打开的记事本窗口
notepad_window = xbot_visual.desktop.get(title=""记事本"")
# 从记事本中读取好友名称
friend_name = xbot_visual.desktop.get_attribute(window=notepad_window, element=""文本输入框"", attribute_name=""text"")
# 通过钉钉搜索好友
xbot_visual.desktop.input(window=""0"", element=""钉钉搜索框"", text=friend_name)
# 点击搜索结果中的好友
xbot_visual.desktop.click(window=""0"", element=""好友"")
# 在聊天框中输入消息
xbot_visual.desktop.input(window=""0"", element=""钉钉聊天框"", text=friend_name + ""你好"")
# 点击发送按钮
xbot_visual.desktop.click(window=""0"", element=""发送"")
``` END",{},[]
获取钉钉通讯录名单，将名单信息再写入到已经打开的记事本中,"```python
# 打开钉钉
process_info=xbot_visual.desktop.launch(process_name=""钉钉"")
# 点击进入钉钉通讯录
xbot_visual.desktop.click(window=""0"", element=""钉钉通讯录"")
# 创建一个空的名单列表
name_list = []
# 遍历所有的名单
for name in xbot_visual.desktop.iter_all_elements(window=""0"", element=""名单""):
    # 将名单信息添加到名单列表中
    name_list.append(xbot_visual.desktop.get_attribute(window=""0"", element=name, attribute_name=""text""))
# 将名单信息写入到已经打开的记事本中
xbot_visual.desktop.input(window=""0"", element=""记事本输入框"", text=str(name_list))
``` END",{},[]
帮我把企业微信我和张三的最近30条聊天记录转发给李四，表情不算在计数内,"```python
# 打开企业微信
process_info=xbot_visual.desktop.launch(process_name=""企业微信"")
# 点击进入聊天记录
xbot_visual.desktop.click(window=""0"", element=""聊天记录"")
# 点击进入我和张三的聊天窗口
xbot_visual.desktop.click(window=""0"", element=""我和张三"")
# 点击进入转发功能
xbot_visual.desktop.click(window=""0"", element=""转发"")
# 在搜索框中输入李四
xbot_visual.desktop.input(window=""0"", element=""搜索框"", text=""李四"")
# 选择搜索结果中的李四
xbot_visual.desktop.click(window=""0"", element=""搜索结果-李四"")
# 点击确认转发
xbot_visual.desktop.click(window=""0"", element=""确认转发"")
``` END",{},[]
帮我自动回复企业微信所有艾特我的消息，回复的消息统一为“不好意思我在忙，晚点我会联系您，感谢理解”  ,"```python
# 打开企业微信
process_info=xbot_visual.desktop.launch(process_name=""企业微信"")
# 点击进入消息列表
xbot_visual.desktop.click(window=""0"", element=""消息列表"")
# 遍历所有艾特我的消息对象
for message in xbot_visual.desktop.iter_all_elements(window=""0"", element=""艾特我的消息""):
    # 点击进入消息详情
    xbot_visual.desktop.click(window=""0"", element=message)
    # 获取消息发送人
    sender = xbot_visual.desktop.get_attribute(window=""0"", element=""消息发送人"", attribute_name=""text"")
    # 获取消息内容
    content = xbot_visual.desktop.get_attribute(window=""0"", element=""消息内容"", attribute_name=""text"")
    # 判断是否为艾特消息
    if ""艾特"" in content:
        # 点击回复按钮
        xbot_visual.desktop.click(window=""0"", element=""回复按钮"")
        # 在输入框中输入回复内容
        xbot_visual.desktop.input(window=""0"", element=""输入框"", text=""不好意思我在忙，晚点我会联系您，感谢理解"")
        # 点击发送按钮
        xbot_visual.desktop.click(window=""0"", element=""发送按钮"")
    # 点击返回按钮
    xbot_visual.desktop.click(window=""0"", element=""返回按钮"")
```  END",{},[]
我生病了，帮我在钉钉上请个假，日期就今天下午到明天晚上吧，请假备注“头痛需要休息，望批准”  ,"```python
# 打开钉钉
process_info=xbot_visual.desktop.launch(process_name=""钉钉"")
# 点击进入请假页面
xbot_visual.desktop.click(window=""0"", element=""请假"")
# 填写请假开始时间为今天下午
xbot_visual.desktop.input(window=""0"", element=""开始时间"", text=""今天下午"")
# 填写请假结束时间为明天晚上
xbot_visual.desktop.input(window=""0"", element=""结束时间"", text=""明天晚上"")
# 填写请假备注
xbot_visual.desktop.input(window=""0"", element=""备注"", text=""头痛需要休息，望批准"")
# 点击提交按钮
xbot_visual.desktop.click(window=""0"", element=""提交"")
``` END",{},[]
登录账单管理软件，勾选时间、金额、备注这几栏，按照时间排序后，将账单截图保存到桌面后，再通过微信发送给老板。,"```python
# 打开账单管理软件
process_info=xbot_visual.desktop.launch(process_name=""账单管理软件"")
# 输入账号
xbot_visual.desktop.input(window=""0"", element=""账号输入框"", text=""username"")
# 输入密码
xbot_visual.desktop.input_password(window=""0"", element=""密码输入框"", password=""password"")
# 点击登录
xbot_visual.desktop.click(window=""0"", element=""登录按钮"")
# 点击勾选时间
xbot_visual.desktop.click(window=""0"", element=""勾选时间"")
# 点击勾选金额
xbot_visual.desktop.click(window=""0"", element=""勾选金额"")
# 点击勾选备注
xbot_visual.desktop.click(window=""0"", element=""勾选备注"")
# 点击按照时间排序
xbot_visual.desktop.click(window=""0"", element=""按照时间排序"")
# 点击账单截图
xbot_visual.desktop.click(window=""0"", element=""账单截图"")
# 设置截图保存路径为桌面
xbot_visual.desktop.input(window=""0"", element=""截图保存路径"", text=""C:\\Users\\Administrator\\Desktop"")
# 点击保存
xbot_visual.desktop.click(window=""0"", element=""保存"")
# 点击发送给老板
xbot_visual.desktop.click(window=""0"", element=""发送给老板"")
# 关闭账单管理软件
xbot_visual.desktop.close(window=""0"")
``` END",{},[]
帮我在Paint软件的中心部分上画一个正方形，边长是100个像素,"```python
# 打开Paint软件
process_info=xbot_visual.desktop.launch(process_name=""Paint"")
# 点击绘图区域，激活绘图区域窗口
xbot_visual.desktop.click(window=""0"", element=""绘图区域"", clicks=""dbclick"")
# 点击矩形绘制工具
xbot_visual.desktop.click(window=""0"", element=""矩形绘制工具"")
# 在绘图区域上点击并拖拽，绘制正方形
xbot_visual.desktop.drag_to_element(window=""0"", element=""绘图区域"", target=""100,100"")
``` END",{},[]
将vscode窗口都移到屏幕左上角，而且窗口大小调整为100×100,"```python
# 获取vscode窗口对象
vscode_window = xbot_visual.desktop.get(title=""vscode"")
# 将vscode窗口移动到屏幕左上角
xbot_visual.desktop.move(window=vscode_window, x=""0"", y=""0"")
# 调整vscode窗口大小为100×100
xbot_visual.desktop.resize(window=vscode_window, width=""100"", height=""100"")
``` END",{},[]
调整Photoshop窗口大小为 800x600，移动窗口至屏幕左上角，并在工具栏选择画笔工具。,"```python
# 获取Photoshop窗口
photoshop_window = xbot_visual.desktop.get(title=""Photoshop"")
# 调整窗口大小为800x600
xbot_visual.desktop.resize(window=photoshop_window, width=""800"", height=""600"")
# 移动窗口至屏幕左上角
xbot_visual.desktop.move(window=photoshop_window, x=""0"", y=""0"")
# 在工具栏选择画笔工具
xbot_visual.desktop.click(window=""0"", element=""画笔工具"")
``` END",{},[]
我需要在桌面上新建一个记事本文件，然后打开文件，将窗口大小调整为一个200*200像素,"```python
# 双击记事本图标
xbot_visual.desktop.click(window=""0"", element=""记事本图标"", clicks=""dbclick"")
# 点击文件菜单
xbot_visual.desktop.click(window=""0"", element=""文件菜单"")
# 点击新建
xbot_visual.desktop.click(window=""0"", element=""新建"")
# 点击打开
xbot_visual.desktop.click(window=""0"", element=""打开"")
# 点击窗口大小调整按钮
xbot_visual.desktop.click(window=""0"", element=""窗口大小调整按钮"")
# 调整窗口大小为200*200像素
xbot_visual.desktop.resize(window=""0"", width=""200"", height=""200"")
``` END",{},[]
我需要在桌面上新建一个记事本文件，然后打开文件，将窗口大小调整为一个200*200像素,"```python
# 双击记事本图标
xbot_visual.desktop.click(window=""0"", element=""记事本图标"", clicks=""dbclick"")
# 点击文件菜单
xbot_visual.desktop.click(window=""0"", element=""文件菜单"")
# 点击新建
xbot_visual.desktop.click(window=""0"", element=""新建"")
# 点击打开
xbot_visual.desktop.click(window=""0"", element=""打开"")
# 点击窗口大小调整按钮
xbot_visual.desktop.click(window=""0"", element=""窗口大小调整按钮"")
# 调整窗口大小为200*200像素
xbot_visual.desktop.resize(window=""0"", width=""200"", height=""200"")
``` END",{},[]
在购物软件客户端上，筛选出所有价格在 1000元到3000元的商品列表，并抓取每个商品对应的商家名称，将数据以[商品：商家名称]的形式打印输出。,"```python
# 打开购物软件客户端
process_info=xbot_visual.desktop.launch(process_name=""购物软件"")
# 点击进入商品筛选页面
xbot_visual.desktop.click(window=""0"", element=""商品筛选"")
# 设置价格区间为1000元到3000元
xbot_visual.desktop.input(window=""0"", element=""价格区间"", text=""1000-3000"")
# 点击确认筛选
xbot_visual.desktop.click(window=""0"", element=""确认筛选"")
# 遍历商品对象列表
for item in xbot_visual.desktop.iter_all_elements(window=""0"", element=""商品对象""):
    # 获取商品对象的文本，格式为[商品名称：商家名称]
    text = xbot_visual.desktop.get_attribute(window=""0"", element=item, attribute_name=""text"")
    # 打印提取到的信息
    print(text)
``` END",{},[]
将QQ音乐“最近播放”列表中的歌曲按顺序播放，并且进行喜欢标记。,"```python
# 打开QQ音乐
process_info=xbot_visual.desktop.launch(process_name=""QQ音乐"")
# 点击进入“最近播放”列表
xbot_visual.desktop.click(window=""0"", element=""最近播放"")
# 遍历歌曲列表
for song in xbot_visual.desktop.iter_all_elements(window=""0"", element=""歌曲""):
    # 点击歌曲，播放歌曲
    xbot_visual.desktop.click(window=""0"", element=song)
    # 点击喜欢按钮，进行喜欢标记
    xbot_visual.desktop.click(window=""0"", element=""喜欢"")
``` END",{},[]
新建一个300*300的PhotoShop画布，然后使用椭圆形状工具在画布中心画一个半径为100的圆。,"```python
# 打开PhotoShop
process_info=xbot_visual.desktop.launch(process_name=""PhotoShop"")
# 点击新建画布按钮
xbot_visual.desktop.click(window=""0"", element=""新建画布按钮"")
# 设置画布宽度为300
xbot_visual.desktop.input(window=""0"", element=""画布宽度输入框"", text=""300"")
# 设置画布高度为300
xbot_visual.desktop.input(window=""0"", element=""画布高度输入框"", text=""300"")
# 点击确认新建画布
xbot_visual.desktop.click(window=""0"", element=""确认新建画布按钮"")
# 选择椭圆形状工具
xbot_visual.desktop.click(window=""0"", element=""椭圆形状工具"")
# 计算圆心坐标
center_x = 300 / 2
center_y = 300 / 2
# 在画布中心画一个半径为100的圆
xbot_visual.desktop.draw(window=""0"", element=""画布"", start_x=center_x, start_y=center_y, end_x=center_x+100, end_y=center_y+100)
``` END",{'err_funcs': ['xbot_visual.desktop.draw']},['err_funcs']
进入钉钉的“我的任务”模块，将所有未完成的任务名称打印出来。,"```python
# 打开钉钉
process_info=xbot_visual.desktop.launch(process_name=""钉钉"")
# 点击进入“我的任务”模块
xbot_visual.desktop.click(window=""0"", element=""我的任务"")
# 遍历未完成的任务对象列表
for task in xbot_visual.desktop.iter_all_elements(window=""0"", element=""未完成的任务对象""):
    # 获取任务名称
    task_name = xbot_visual.desktop.get_attribute(window=""0"", element=task, attribute_name=""text"")
    # 打印任务名称
    print(task_name)
``` END",{},[]
查找所有微信未读消息，然后逐一进行回复，回复内容统一为“收到，我会尽快回复您。”。,"```python
# 打开微信
process_info=xbot_visual.desktop.launch(process_name=""微信"")
# 遍历未读消息对象列表
for message in xbot_visual.desktop.iter_all_elements(window=""0"", element=""未读消息""):
    # 点击未读消息，进入聊天窗口
    xbot_visual.desktop.click(window=""0"", element=message)
    # 在输入框中输入回复内容
    xbot_visual.desktop.input(window=""0"", element=""微信聊天输入框"", text=""收到，我会尽快回复您。"")
    # 点击发送按钮，发送回复
    xbot_visual.desktop.click(window=""0"", element=""微信发送按钮"")
    # 关闭聊天窗口，返回微信主界面
    xbot_visual.desktop.click(window=""0"", element=""微信返回按钮"")
``` END",{},[]
我要出差，帮我在买票软件客户端上预定一张从北京到上海的机票，日期为明天。,"```python
# 打开买票软件客户端
process_info=xbot_visual.desktop.launch(process_name=""买票软件"")
# 点击进入预定机票页面
xbot_visual.desktop.click(window=""0"", element=""预定机票"")
# 选择出发城市为北京
xbot_visual.desktop.select_by_text(window=""0"", element=""出发城市"", text=""北京"")
# 选择到达城市为上海
xbot_visual.desktop.select_by_text(window=""0"", element=""到达城市"", text=""上海"")
# 选择日期为明天
xbot_visual.desktop.select_by_text(window=""0"", element=""日期"", text=""明天"")
# 点击搜索按钮
xbot_visual.desktop.click(window=""0"", element=""搜索"")
# 选择第一张机票
xbot_visual.desktop.click(window=""0"", element=""第一张机票"")
# 点击预定按钮
xbot_visual.desktop.click(window=""0"", element=""预定"")
``` END",{},[]
帮我在QQ空间客户端上发布一条动态，内容为“今天天气真好，心情也特别好！”,"```python
# 打开QQ空间客户端
process_info=xbot_visual.desktop.launch(process_name=""QQ空间"")
# 点击进入发布动态页面
xbot_visual.desktop.click(window=""0"", element=""发布动态"")
# 在内容输入框中输入“今天天气真好，心情也特别好！”
xbot_visual.desktop.input(window=""0"", element=""内容输入框"", text=""今天天气真好，心情也特别好！"")
# 点击发布按钮
xbot_visual.desktop.click(window=""0"", element=""发布按钮"")
``` END",{},[]
"在微信聊天框中输入一段文字""你好，我是xbot""并发送。","```python
# 打开微信
process_info=xbot_visual.desktop.launch(process_name=""微信"")
# 在微信聊天框中输入""你好，我是xbot""
xbot_visual.desktop.input(window=""0"", element=""微信聊天框"", text=""你好，我是xbot"")
# 点击发送按钮
xbot_visual.desktop.click(window=""0"", element=""发送按钮"")
``` END",{},[]
"在网易云音乐软件上，找到""周杰伦""的专辑""七里香""，然后播放第一首歌曲。","```python
# 打开网易云音乐软件
process_info=xbot_visual.desktop.launch(process_name=""网易云音乐"")
# 在搜索框中输入""周杰伦""
xbot_visual.desktop.input(window=""0"", element=""搜索框"", text=""周杰伦"")
# 点击搜索按钮
xbot_visual.desktop.click(window=""0"", element=""搜索按钮"")
# 点击进入""七里香""专辑
xbot_visual.desktop.click(window=""0"", element=""七里香专辑"")
# 点击播放第一首歌曲
xbot_visual.desktop.click(window=""0"", element=""第一首歌曲"")
``` END",{},[]
使用迅雷下载一个磁力链接，磁力链接在记事本文件里面。,"```python
# 打开记事本
xbot_visual.desktop.click(window=""0"", element=""记事本"", clicks=""dbclick"")
# 输入磁力链接
xbot_visual.desktop.input(window=""0"", element=""记事本编辑区"", text=""magnet链接"")
# 点击下载按钮
xbot_visual.desktop.click(window=""0"", element=""迅雷下载按钮"")
``` END",{},[]
"在酷狗音乐软件上，找到""林俊杰""的专辑""江南""，停止当前播放的歌曲，然后播放该专辑的第二首歌曲。","```python
# 打开酷狗音乐软件
process_info=xbot_visual.desktop.launch(process_name=""酷狗音乐"")
# 点击进入专辑列表
xbot_visual.desktop.click(window=""0"", element=""专辑列表"")
# 在搜索框中输入""林俊杰""
xbot_visual.desktop.input(window=""0"", element=""搜索框"", text=""林俊杰"")
# 点击搜索按钮
xbot_visual.desktop.click(window=""0"", element=""搜索"")
# 点击进入""江南""专辑
xbot_visual.desktop.click(window=""0"", element=""江南"")
# 点击停止按钮
xbot_visual.desktop.click(window=""0"", element=""停止"")
# 点击播放""江南""专辑的第二首歌曲
xbot_visual.desktop.click(window=""0"", element=""第二首歌曲"")
``` END",{},[]
"找到微信上所有最近联系的好友，如果他们的昵称中包含""张""字，就给他们发送一个""你好""的消息。","```python
# 打开微信
process_info=xbot_visual.desktop.launch(process_name=""微信"")
# 点击进入最近联系人列表
xbot_visual.desktop.click(window=""0"", element=""最近联系人"")
# 遍历好友列表
for friend in xbot_visual.desktop.iter_all_elements(window=""0"", element=""好友""):
    # 获取好友昵称
    nickname = xbot_visual.desktop.get_attribute(window=""0"", element=friend, attribute_name=""text"")
    # 判断昵称中是否包含""张""字
    if ""张"" in nickname:
        # 点击进入好友聊天窗口
        xbot_visual.desktop.click(window=""0"", element=friend)
        # 在聊天输入框中输入""你好""
        xbot_visual.desktop.input(window=""0"", element=""聊天输入框"", text=""你好"")
        # 点击发送按钮
        xbot_visual.desktop.click(window=""0"", element=""发送按钮"")
        # 点击返回按钮，回到好友列表
        xbot_visual.desktop.click(window=""0"", element=""返回按钮"")
``` END",{},[]
绘制一个带有边框的圆形，并在中心填充颜色。,"```python
# 打开绘图软件
process_info=xbot_visual.desktop.launch(process_name=""绘图软件"")
# 点击绘图工具
xbot_visual.desktop.click(window=""0"", element=""绘图工具"")
# 点击圆形绘制按钮
xbot_visual.desktop.click(window=""0"", element=""圆形绘制按钮"")
# 点击边框样式设置
xbot_visual.desktop.click(window=""0"", element=""边框样式设置"")
# 选择边框样式
xbot_visual.desktop.select_by_text(window=""0"", element=""边框样式下拉框"", text=""实线"")
# 点击边框颜色设置
xbot_visual.desktop.click(window=""0"", element=""边框颜色设置"")
# 选择边框颜色
xbot_visual.desktop.select_by_text(window=""0"", element=""边框颜色下拉框"", text=""红色"")
# 点击填充颜色设置
xbot_visual.desktop.click(window=""0"", element=""填充颜色设置"")
# 选择填充颜色
xbot_visual.desktop.select_by_text(window=""0"", element=""填充颜色下拉框"", text=""黄色"")
# 点击确定按钮
xbot_visual.desktop.click(window=""0"", element=""确定按钮"")
# 在绘图区域点击鼠标，绘制圆形
xbot_visual.desktop.click(window=""0"", element=""绘图区域"",x=""100"",y=""100"",click_type=""dbclick"")
``` END","{'extra_args': [""xbot_visual.desktop.click:['y', 'click_type', 'x']""]}",['extra_args']
"找到百度网盘中所有以"".pdf""结尾的文件，并打开它们。","```python
# 打开百度网盘
web_page = xbot_visual.web.create(web_type=""chrome"", url=""https://pan.baidu.com/"")
# 输入账号
xbot_visual.web.input(page=web_page, element=""#username"", text=""username"")
# 输入密码
xbot_visual.web.input_password(page=web_page, element=""#password"", password=""password"")
# 点击登录
xbot_visual.web.click(page=web_page, element='#login')
# 点击文件
xbot_visual.web.click(page=web_page, element='#file')
# 遍历文件列表
for file in xbot_visual.web.iter_all_elements(page=web_page, element='.file'):
    # 获取文件名
    file_name = xbot_visual.web.get_attribute(page=web_page, element=file, attribute_name='text')
    # 判断文件名是否以"".pdf""结尾
    if file_name.endswith("".pdf""):
        # 点击文件，打开文件
        xbot_visual.web.click(page=web_page, element=file)
``` END",{},[]
我在玩开心消消乐游戏，自动点击所有显示数字8的方块。,"```python
# 打开开心消消乐游戏
process_info=xbot_visual.desktop.launch(process_name=""开心消消乐"")
# 遍历所有方块对象
for block in xbot_visual.desktop.iter_all_elements(window=""0"", element=""方块""):
    # 获取方块对象的文本
    block_text = xbot_visual.desktop.get_attribute(window=""0"", element=block, attribute_name=""text"")
    # 判断方块上是否显示数字8
    if ""8"" in block_text:
        # 点击方块
        xbot_visual.desktop.click(window=""0"", element=block)
``` END",{},[]
自动领取购物软件所有可用的红包。,"```python
# 打开购物软件
process_info=xbot_visual.desktop.launch(process_name=""购物软件"")
# 点击进入红包页面
xbot_visual.desktop.click(window=""0"", element=""红包页面"")
# 遍历红包元素列表
for red_packet in xbot_visual.desktop.iter_all_elements(window=""0"", element=""红包元素""):
    # 点击领取红包
    xbot_visual.desktop.click(window=""0"", element=red_packet)
    # 获取领取结果
    result = xbot_visual.desktop.get_attribute(window=""0"", element=""领取结果"", attribute_name=""text"")
    # 判断领取结果
    if result == ""领取成功"":
        # 关闭领取结果对话框
        xbot_visual.desktop.click(window=""0"", element=""关闭按钮"")
    else:
        # 关闭领取结果对话框
        xbot_visual.desktop.click(window=""0"", element=""关闭按钮"")
        # 跳出循环
        break
``` END",{},[]
在快手客户端中，自动点赞所有发布时间在一小时内的视频。,"```python
# 打开快手客户端
process_info=xbot_visual.desktop.launch(process_name=""快手"")
# 遍历视频对象列表
for video in xbot_visual.desktop.iter_all_elements(window=""0"", element=""视频对象""):
    # 获取视频发布时间
    video_time=xbot_visual.desktop.get_attribute(window=""0"", element=video, attribute_name=""text"")
    # 判断视频发布时间是否在一小时内
    if video_time in ""1小时"":
        # 点赞视频
        xbot_visual.desktop.click(window=""0"", element=""点赞按钮"")
``` END",{},[]
打开音乐播放器，将播放模式设置为随机播放，并在播放列表中选择一首歌曲进行播放。,"```python
# 打开音乐播放器
process_info=xbot_visual.desktop.launch(process_name=""音乐播放器"")
# 点击进入播放模式设置
xbot_visual.desktop.click(window=""0"", element=""播放模式设置"")
# 选择随机播放模式
xbot_visual.desktop.select_by_text(window=""0"", element=""播放模式"", text=""随机播放"")
# 点击确认设置
xbot_visual.desktop.click(window=""0"", element=""确认设置"")
# 点击进入播放列表
xbot_visual.desktop.click(window=""0"", element=""播放列表"")
# 选择一首歌曲
xbot_visual.desktop.select_by_index(window=""0"", element=""歌曲"", index=""1"")
# 点击播放按钮
xbot_visual.desktop.click(window=""0"", element=""播放"")
``` END",{},[]
在一个视频播放软件中，将播放速度设置为1.5倍速，然后播放一个指定的视频。,"```python
# 打开视频播放软件
process_info=xbot_visual.desktop.launch(process_name=""视频播放软件"")
# 点击进入播放速度设置
xbot_visual.desktop.click(window=""0"", element=""播放速度设置"")
# 设置播放速度为1.5倍速
xbot_visual.desktop.input(window=""0"", element=""播放速度输入框"", text=""1.5"")
# 点击确认
xbot_visual.desktop.click(window=""0"", element=""确认按钮"")
# 点击进入视频播放
xbot_visual.desktop.click(window=""0"", element=""视频播放"")
# 点击进入视频列表
xbot_visual.desktop.click(window=""0"", element=""视频列表"")
# 双击播放指定的视频
xbot_visual.desktop.click(window=""0"", element=""指定的视频"", clicks=""dbclick"")
``` END",{},[]
将外卖软件的默认的送餐地址设置为指定的地址。,"```python
# 打开外卖软件
process_info=xbot_visual.desktop.launch(process_name=""外卖软件"")
# 点击进入地址设置页面
xbot_visual.desktop.click(window=""0"", element=""地址设置"")
# 在地址输入框中输入指定的地址
xbot_visual.desktop.input(window=""0"", element=""地址输入框"", text=""指定的地址"")
# 点击保存按钮，保存地址设置
xbot_visual.desktop.click(window=""0"", element=""保存按钮"")
``` END",{},[]
使用视频播放软件播放指定的视频，然后将音量调整到50%，并设置为全屏播放。,"```python
# 打开视频播放软件
process_info=xbot_visual.desktop.launch(process_name=""视频播放软件"")
# 点击打开视频按钮
xbot_visual.desktop.click(window=""0"", element=""打开视频按钮"")
# 在文件选择窗口中输入视频文件路径
xbot_visual.desktop.input(window=""0"", element=""文件路径输入框"", text=""C:\\Videos\\example.mp4"")
# 点击播放按钮
xbot_visual.desktop.click(window=""0"", element=""播放按钮"")
# 获取音量滑块的位置信息
volume_slider = xbot_visual.desktop.get_attribute(window=""0"", element=""音量滑块"", attribute_name=""position"")
# 将音量滑块位置转换为鼠标点击的位置
volume_position = (volume_slider[""x""] + 10, volume_slider[""y""] + 10)
# 调整音量到50%
xbot_visual.desktop.click(window=""0"", element=""音量滑块"", clicks=""1"", interval=""100"", button=""left"")
# 设置为全屏播放
xbot_visual.desktop.click(window=""0"", element=""全屏按钮"")
``` END","{'extra_args': [""xbot_visual.desktop.click:['interval']""]}",['extra_args']
在股票软件中，搜索并打开指定的股票，然后将股票添加到自选股，并设置提醒当股票价格低于100元时进行通知。,"```python
# 打开股票软件
process_info=xbot_visual.desktop.launch(process_name=""股票软件"")
# 在搜索框中输入股票名称
xbot_visual.desktop.input(window=""0"", element=""股票搜索框"", text=""股票名称"")
# 点击搜索按钮
xbot_visual.desktop.click(window=""0"", element=""搜索按钮"")
# 点击股票进入股票详情页
xbot_visual.desktop.click(window=""0"", element=""股票"")
# 点击添加到自选股按钮
xbot_visual.desktop.click(window=""0"", element=""添加到自选股按钮"")
# 点击设置提醒按钮
xbot_visual.desktop.click(window=""0"", element=""设置提醒按钮"")
# 在提醒价格输入框中输入100
xbot_visual.desktop.input(window=""0"", element=""提醒价格输入框"", text=""100"")
# 点击确定按钮
xbot_visual.desktop.click(window=""0"", element=""确定按钮"")
``` END",{},[]
使用网易云音乐搜索并播放指定的歌曲，然后添加到我喜欢的音乐，并设置为单曲循环。,"```python
# 打开网易云音乐
process_info=xbot_visual.desktop.launch(process_name=""网易云音乐"")
# 在搜索框中输入指定的歌曲名称
xbot_visual.desktop.input(window=""0"", element=""网易云音乐搜索框"", text=""歌曲名称"")
# 点击搜索按钮
xbot_visual.desktop.click(window=""0"", element=""网易云音乐搜索按钮"")
# 点击播放按钮
xbot_visual.desktop.click(window=""0"", element=""网易云音乐播放按钮"")
# 点击添加到喜欢的音乐按钮
xbot_visual.desktop.click(window=""0"", element=""网易云音乐添加到喜欢的音乐按钮"")
# 点击设置按钮
xbot_visual.desktop.click(window=""0"", element=""网易云音乐设置按钮"")
# 点击单曲循环按钮
xbot_visual.desktop.click(window=""0"", element=""网易云音乐单曲循环按钮"")
``` END",{},[]
在地图软件中，搜索并打开指定的地点，然后获取地点的经纬度并打印输出，最后保存该地点的地图截图到桌面。,"```python
# 打开地图软件
process_info=xbot_visual.desktop.launch(process_name=""地图软件"")
# 在搜索框中输入指定的地点
xbot_visual.desktop.input(window=""0"", element=""搜索框"", text=""地点"")
# 点击搜索按钮
xbot_visual.desktop.click(window=""0"", element=""搜索按钮"")
# 等待地图加载
xbot_visual.desktop.wait_window(window=""地图窗口"", state=""地图加载完成"")
# 获取地点的经纬度文本
location_text = xbot_visual.desktop.get_attribute(window=""0"", element=""经纬度文本"", attribute_name=""text"")
# 打印经纬度
print(location_text)
# 截取地图图片
xbot_visual.desktop.screenshot_element(window=""地图窗口"", element=""地图区域"", file_folder=""C:\\Users\\Desktop"", file_name=""地图.png"")
``` END",{'err_funcs': ['xbot_visual.desktop.wait_window']},['err_funcs']
我想最小化当前激活窗口。,"```python
# 获取当前激活窗口
active_window = xbot_visual.desktop.get_active()
# 最小化当前激活窗口
xbot_visual.desktop.set_state(window=active_window, state=""minimize"")
``` END",{},[]
qq客户端的窗口已经激活的，现在我需要使用账号密码登录qq客户端，账号是10010,"```python
# 打开qq客户端
process_info=xbot_visual.desktop.launch(process_name=""qq"")
# 点击qq账号输入框
xbot_visual.desktop.click(window=""0"", element=""qq账号输入框"")
# 输入qq账号
xbot_visual.desktop.input(window=""0"", element=""qq账号输入框"", text=""10010"")
# 点击qq密码输入框
xbot_visual.desktop.click(window=""0"", element=""qq密码输入框"")
# 输入qq密码
xbot_visual.desktop.input_password(window=""0"", element=""qq密码输入框"", password=""123456"")
# 点击qq登录按钮
xbot_visual.desktop.click(window=""0"", element=""qq登录按钮"")
``` END",{},[]
"需要在电脑上的文件管理器中找到目标文件夹（如""我的文档""），并将该文件夹窗口移动至屏幕左上角。","```python
# 获取文件夹窗口
file_folder_window = xbot_visual.desktop.get(title=""文件夹"")
# 移动文件夹窗口至屏幕左上角
xbot_visual.desktop.move(window=file_folder_window, x=""0"", y=""0"")
``` END",{},[]
需要在电脑上的文件管理器中找到图片文件夹，然后将鼠标悬浮到第一张图片上,"```python
# 打开文件管理器
xbot_visual.keyboard.send_keys(keys=""#{e}"")
# 点击图片文件夹
xbot_visual.desktop.click(window=""0"", element=""图片文件夹"")
# 鼠标悬浮到第一张图片上
xbot_visual.desktop.hover(window=""0"", element=""第一张图片"")
``` END",{},[]
打开任务管理器，杀死Notepad进程。,"```python
# 打开任务管理器
xbot_visual.keyboard.send_keys(keys=""^+{ESC}"")
# 输入Notepad
xbot_visual.desktop.input(window=""0"", element=""任务名称"", text=""Notepad"")
# 点击结束任务
xbot_visual.desktop.click(window=""0"", element=""结束任务"")
``` END",{},[]
在已经打开的PDF阅读器中，找到指定的页码（如第5页），并将该页码的内容截图保存。,"```python
# 打开PDF阅读器
process_info=xbot_visual.desktop.launch(process_name=""PDF阅读器"")
# 点击进入页码输入框
xbot_visual.desktop.click(window=""0"", element=""页码输入框"")
# 在页码输入框中输入指定的页码
xbot_visual.desktop.input(window=""0"", element=""页码输入框"", text=""5"")
# 按下回车键，跳转到指定页码
xbot_visual.keyboard.send_keys(keys=""{ENTER}"")
# 截取指定页码的内容
xbot_visual.desktop.screenshot_element(window=""0"", element=""指定页码"", file_folder=""C:\\Desktop"", file_name=""page.png"")
``` END",{},[]
"打开CAD软件，找到指定的图层（如""第一层""），并将该图层的窗口状态设置为最大化。","```python
# 打开CAD软件
process_info=xbot_visual.desktop.launch(process_name=""CAD"")
# 点击图层下拉框
xbot_visual.desktop.click(window=""0"", element=""图层下拉框"")
# 选择指定的图层
xbot_visual.desktop.click(window=""0"", element=""第一层"")
# 获取图层窗口
cad_layer_window = xbot_visual.desktop.get(title=""图层"")
# 设置图层窗口状态为最大化
xbot_visual.desktop.set_state(window=cad_layer_window, state=""maximize"")
``` END",{},[]
"在购物软件客户端上将""女装""分类下的所有商品加入购物车。","```python
# 打开购物软件客户端
process_info=xbot_visual.desktop.launch(process_name=""购物软件"")
# 点击进入""女装""分类
xbot_visual.desktop.click(window=""0"", element=""女装分类"")
# 遍历商品对象列表
for item in xbot_visual.desktop.iter_all_elements(window=""0"", element=""商品对象""):
    # 点击商品对象，将商品加入购物车
    xbot_visual.desktop.click(window=""0"", element=item)
# 点击购物车按钮，进入购物车
xbot_visual.desktop.click(window=""0"", element=""购物车按钮"")
``` END",{},[]
在咖啡点餐客户端软件中，为每个咖啡类别点一个小杯的美式咖啡，然后结账。,"```python
# 打开咖啡点餐客户端软件
process_info=xbot_visual.desktop.launch(process_name=""咖啡点餐"")
# 点击进入咖啡类别
xbot_visual.desktop.click(window=""0"", element=""咖啡类别"")
# 为美式咖啡点一个小杯
xbot_visual.desktop.click(window=""0"", element=""美式咖啡小杯"")
# 点击结账
xbot_visual.desktop.click(window=""0"", element=""结账"")
``` END",{},[]
播放音乐播放器中所有收藏的歌曲,"```python
# 打开音乐播放器
process_info=xbot_visual.desktop.launch(process_name=""音乐播放器"")
# 点击进入收藏列表
xbot_visual.desktop.click(window=""0"", element=""收藏"")
# 遍历所有歌曲对象
for song in xbot_visual.desktop.iter_all_elements(window=""0"", element=""歌曲对象""):
    # 点击播放歌曲
    xbot_visual.desktop.click(window=""0"", element=song)
``` END",{},[]
用户需要在文档编辑软件中打开指定文档，修改文档中的一些内容后保存，然后在聊天软件中发送给同事。,"```python
# 打开文档编辑软件
process_info=xbot_visual.desktop.launch(process_name=""文档编辑软件"")
# 点击打开文件按钮
xbot_visual.desktop.click(window=""0"", element=""打开文件按钮"")
# 在文件路径输入框中输入文件路径
xbot_visual.desktop.input(window=""0"", element=""文件路径输入框"", text=""C:\\example\\document.txt"")
# 点击确认打开按钮
xbot_visual.desktop.click(window=""0"", element=""确认打开按钮"")
# 在文档中输入一些内容
xbot_visual.desktop.input(window=""0"", element=""文档编辑区"", text=""这是修改后的文档内容"")
# 点击保存按钮
xbot_visual.desktop.click(window=""0"", element=""保存按钮"")
# 点击发送按钮
xbot_visual.desktop.click(window=""0"", element=""发送按钮"")
``` END",{},[]
用户需要在视频播放软件中播放指定视频，然后在播放到一半的时候暂停，调整播放速度为2倍速后继续播放。,"```python
# 打开视频播放软件
process_info=xbot_visual.desktop.launch(process_name=""视频播放软件"")
# 点击进入视频播放界面
xbot_visual.desktop.click(window=""0"", element=""视频播放界面"")
# 点击进入视频列表界面
xbot_visual.desktop.click(window=""0"", element=""视频列表界面"")
# 点击播放指定视频
xbot_visual.desktop.click(window=""0"", element=""指定视频"")
# 点击播放按钮
xbot_visual.desktop.click(window=""0"", element=""播放按钮"")
# 等待视频播放到一半
xbot_visual.desktop.wait_play_complete(window=""0"", element=""播放进度条"", play_status=""playing"", percent=""50%"")
# 点击暂停按钮
xbot_visual.desktop.click(window=""0"", element=""暂停按钮"")
# 点击设置按钮
xbot_visual.desktop.click(window=""0"", element=""设置按钮"")
# 点击进入播放速度设置界面
xbot_visual.desktop.click(window=""0"", element=""播放速度设置界面"")
# 选择2倍速
xbot_visual.desktop.select_by_text(window=""0"", element=""播放速度下拉框"", text=""2倍速"")
# 点击确认按钮
xbot_visual.desktop.click(window=""0"", element=""确认按钮"")
# 点击继续播放按钮
xbot_visual.desktop.click(window=""0"", element=""继续播放按钮"")
``` END",{'err_funcs': ['xbot_visual.desktop.wait_play_complete']},['err_funcs']
用户需要在计算器软件中进行一些复杂的计算，然后获取计算结果。,"```python
# 打开计算器软件
process_info=xbot_visual.desktop.launch(process_name=""计算器"")
# 在计算器中输入复杂的计算表达式
xbot_visual.desktop.input(window=""0"", element=""计算器输入框"", text=""2*3+4/2"")
# 点击计算按钮
xbot_visual.desktop.click(window=""0"", element=""计算按钮"")
# 获取计算结果
result = xbot_visual.desktop.get_attribute(window=""0"", element=""计算结果"", attribute_name=""text"")
# 打印计算结果
print(f""计算结果为：{result}"")
``` END",{},[]
用户需要在音频编辑软件中打开音频文件，剪切10秒到20秒的片段，保存到指定位置，并将操作过程截图，保存到桌面。,"```python
# 打开音频编辑软件
process_info=xbot_visual.desktop.launch(process_name=""音频编辑软件"")
# 点击打开文件按钮
xbot_visual.desktop.click(window=""0"", element=""打开文件按钮"")
# 在文件选择窗口中输入文件路径
xbot_visual.desktop.input(window=""0"", element=""文件路径输入框"", text=""C:\\path\\to\\audio_file.mp3"")
# 点击确认打开文件
xbot_visual.desktop.click(window=""0"", element=""确认打开文件按钮"")
# 在时间轴上选择10秒到20秒的片段
xbot_visual.desktop.drag_to_element(window=""0"", element=""时间轴"", target=""10秒"")
# 点击剪切按钮
xbot_visual.desktop.click(window=""0"", element=""剪切按钮"")
# 点击保存按钮
xbot_visual.desktop.click(window=""0"", element=""保存按钮"")
# 在保存对话框中输入保存路径
xbot_visual.desktop.input(window=""0"", element=""保存路径输入框"", text=""C:\\path\\to\\output_file.mp3"")
# 点击确认保存
xbot_visual.desktop.click(window=""0"", element=""确认保存按钮"")
# 截取软件操作过程的截图
xbot_visual.desktop.screenshot_element(window=""0"", element=""软件窗口"", file_folder=""C:\\Users\\Desktop"", file_name=""screenshot.png"")
``` END",{},[]
"我需要将指定微信窗口移动到屏幕的指定位置（例如：坐标为(100, 200)的位置）","```python
# 获取指定微信窗口
wechat_window = xbot_visual.desktop.get(title=""微信"")
# 移动窗口到指定位置
xbot_visual.desktop.move(window=wechat_window, x=""100"", y=""200"")
``` END",{},[]
在WinRAR软件中选择文件进行压缩,"```python
# 打开WinRAR软件
process_info=xbot_visual.desktop.launch(process_name=""WinRAR"")
# 点击打开文件按钮
xbot_visual.desktop.click(window=""0"", element=""打开文件按钮"")
# 在文件选择窗口中输入文件路径
xbot_visual.desktop.input(window=""0"", element=""文件路径输入框"", text=""C:\\example.txt"")
# 点击确认打开文件
xbot_visual.desktop.click(window=""0"", element=""确认打开文件按钮"")
# 点击压缩按钮
xbot_visual.desktop.click(window=""0"", element=""压缩按钮"")
# 在压缩设置窗口中输入压缩文件路径
xbot_visual.desktop.input(window=""0"", element=""压缩文件路径输入框"", text=""C:\\example.zip"")
# 点击开始压缩按钮
xbot_visual.desktop.click(window=""0"", element=""开始压缩按钮"")
``` END",{},[]
使用Adobe Reader打开PDF文件,"```python
# 打开Adobe Reader
process_info=xbot_visual.desktop.launch(process_name=""Adobe Reader"")
# 点击打开文件按钮
xbot_visual.desktop.click(window=""0"", element=""打开文件按钮"")
# 在文件选择对话框中输入文件路径
xbot_visual.desktop.input(window=""0"", element=""文件路径输入框"", text=""C:\\example.pdf"")
# 点击打开按钮
xbot_visual.desktop.click(window=""0"", element=""打开按钮"")
``` END",{},[]
在QQ音乐中搜索并播放指定歌曲,"```python
# 打开QQ音乐
process_info=xbot_visual.desktop.launch(process_name=""QQ音乐"")
# 在搜索框中输入指定歌曲名称
xbot_visual.desktop.input(window=""0"", element=""搜索框"", text=""指定歌曲名称"")
# 点击搜索按钮
xbot_visual.desktop.click(window=""0"", element=""搜索按钮"")
# 点击播放指定歌曲
xbot_visual.desktop.click(window=""0"", element=""指定歌曲"")
``` END",{},[]
使用QQ软件，在QQ好友列表中，选择第一个好友，发送一句“你好！”,"```python
# 打开QQ软件
process_info=xbot_visual.desktop.launch(process_name=""QQ"")
# 点击进入QQ好友列表
xbot_visual.desktop.click(window=""0"", element=""QQ好友列表"")
# 点击第一个好友
xbot_visual.desktop.click(window=""0"", element=""第一个好友"")
# 在聊天框中输入""你好！""
xbot_visual.desktop.input(window=""0"", element=""聊天输入框"", text=""你好！"")
# 点击发送按钮
xbot_visual.desktop.click(window=""0"", element=""发送按钮"")
``` END",{},[]
截取PDF阅读器当前页的图像，并保存,"```python
# 打开PDF阅读器
process_info=xbot_visual.desktop.launch(process_name=""PDF阅读器"")
# 点击截图按钮
xbot_visual.desktop.click(window=""0"", element=""截图按钮"")
# 保存截图
xbot_visual.desktop.input(window=""0"", element=""保存路径输入框"", text=""C:\\Desktop\\sample.png"")
# 点击确认保存
xbot_visual.desktop.click(window=""0"", element=""保存按钮"")
``` END",{},[]
获取计算器中所有的数字按钮元素，并依次点击,"```python
# 打开计算器
xbot_visual.desktop.click(window=""0"", element=""计算器"")
# 获取所有的数字按钮元素
number_buttons = xbot_visual.desktop.find_elements(window=""0"", element=""计算器数字按钮"")
# 遍历数字按钮元素列表
for button in number_buttons:
    # 点击数字按钮
    xbot_visual.desktop.click(window=""0"", element=button)
``` END",{},[]
调整桌面软件位置并最大化显示,"```python
# 打开桌面软件
process_info=xbot_visual.desktop.launch(process_name=""桌面软件"")
# 移动桌面软件窗口位置
xbot_visual.desktop.move_window(window=""0"", x=""100"", y=""100"")
# 调整桌面软件窗口大小
xbot_visual.desktop.resize_window(window=""0"", width=""800"", height=""600"")
# 最大化桌面软件窗口
xbot_visual.desktop.set_state(window=""0"", state=""maximize"")
``` END","{'err_funcs': ['xbot_visual.desktop.move_window', 'xbot_visual.desktop.resize_window']}",['err_funcs']
"我在使用金山词霸查单词，需要查找""robot""这个单词的中文意思，希望能帮我查找并显示结果。","```python
# 打开金山词霸
process_info=xbot_visual.desktop.launch(process_name=""金山词霸"")
# 在搜索框内输入""robot""
xbot_visual.desktop.input(window=""0"", element=""金山词霸搜索框"", text=""robot"")
# 点击搜索按钮
xbot_visual.desktop.click(window=""0"", element=""金山词霸搜索按钮"")
# 获取单词的中文意思
word_meaning = xbot_visual.desktop.get_attribute(window=""0"", element=""金山词霸单词中文意思"", attribute_name=""text"")
# 打印中文意思
print(word_meaning)
``` END",{},[]
"我在使用QQ客户端，需要把我的个性签名改成""今天天气真好！""。","```python
# 打开QQ客户端
process_info=xbot_visual.desktop.launch(process_name=""QQ"")
# 点击进入个性签名编辑框
xbot_visual.desktop.click(window=""0"", element=""个性签名编辑框"")
# 在个性签名编辑框中输入""今天天气真好！""
xbot_visual.desktop.input(window=""0"", element=""个性签名编辑框"", text=""今天天气真好！"")
# 点击保存按钮
xbot_visual.desktop.click(window=""0"", element=""保存按钮"")
``` END",{},[]
"我在使用PS软件，需要打开桌面路径下为""test1.jpg""和""test2.jpg""的图片文件。","```python
# 打开PS软件
process_info=xbot_visual.desktop.launch(process_name=""PS"")
# 点击打开图片按钮
xbot_visual.desktop.click(window=""0"", element=""打开图片按钮"")
# 在文件路径输入框中输入桌面路径
xbot_visual.desktop.input(window=""0"", element=""文件路径输入框"", text=""C:\\Users\\User\\Desktop"")
# 在文件名输入框中输入""test1.jpg""
xbot_visual.desktop.input(window=""0"", element=""文件名输入框"", text=""test1.jpg"")
# 在文件名输入框中输入""test2.jpg""
xbot_visual.desktop.input(window=""0"", element=""文件名输入框"", text=""test2.jpg"")
# 点击确认打开图片
xbot_visual.desktop.click(window=""0"", element=""确认打开图片按钮"")
``` END",{},[]
我需要你帮我在CAD软件上打开一个平面设计图，然后调整窗口大小以便我能看到全部的设计内容，并且让这个窗口保持在最前面。,"```python
# 打开CAD软件
process_info=xbot_visual.desktop.launch(process_name=""CAD"")
# 点击打开文件按钮
xbot_visual.desktop.click(window=""0"", element=""打开文件按钮"")
# 在文件选择对话框中输入文件路径
xbot_visual.desktop.input(window=""0"", element=""文件路径输入框"", text=""C:\\Documents\\Design.dwg"")
# 点击确认打开文件
xbot_visual.desktop.click(window=""0"", element=""确认打开按钮"")
# 调整CAD窗口大小
xbot_visual.desktop.resize(window=""CAD窗口"", width=""800"", height=""600"")
# 将CAD窗口设置为最前面
xbot_visual.desktop.set_topmost(window=""CAD窗口"", set_type=""front"")
``` END",{'err_funcs': ['xbot_visual.desktop.set_topmost']},['err_funcs']
我需要你帮我打开一个视频播放软件，然后调整窗口大小为适合观看的大小，并且将这个窗口隐藏起来。,"```python
# 打开视频播放软件
process_info=xbot_visual.desktop.launch(process_name=""视频播放软件"")
# 获取视频播放软件窗口
video_window = xbot_visual.desktop.get(title=""视频播放软件"")
# 调整窗口大小为适合观看的大小
xbot_visual.desktop.resize(window=video_window, width=""800"", height=""600"")
# 将视频播放软件窗口隐藏
xbot_visual.desktop.set_visibility(window=video_window, visibility=""hide"")
``` END",{},[]
我需要你帮我在一个文本编辑器软件上打开一个文件，然后在特定的行输入一段文字，最后保存并关闭文件。,"```python
# 打开文本编辑器软件
process_info=xbot_visual.desktop.launch(process_name=""文本编辑器"")
# 点击打开文件按钮
xbot_visual.desktop.click(window=""0"", element=""打开文件按钮"")
# 在文件选择对话框中输入文件路径
xbot_visual.desktop.input(window=""0"", element=""文件路径输入框"", text=""C:\\path\\to\\file.txt"")
# 点击确认打开文件
xbot_visual.desktop.click(window=""0"", element=""确认打开按钮"")
# 在特定的行输入一段文字
xbot_visual.desktop.input(window=""0"", element=""文本输入框"", text=""这是要插入的文字"")
# 点击保存按钮
xbot_visual.desktop.click(window=""0"", element=""保存按钮"")
# 点击关闭文件按钮
xbot_visual.desktop.click(window=""0"", element=""关闭文件按钮"")
``` END",{},[]
"我想在安装了一款名为""Demo""的软件，但是我希望它的窗口大小固定在800*600，然后默认隐藏，只有当我需要的时候我才会手动去打开它。","```python
# 打开Demo软件
process_info=xbot_visual.desktop.launch(process_name=""Demo"")
# 获取Demo窗口
demo_window = xbot_visual.desktop.get(title=""Demo"")
# 设置Demo窗口大小为800*600
xbot_visual.desktop.resize(window=demo_window, width=""800"", height=""600"")
# 设置Demo窗口默认隐藏
xbot_visual.desktop.set_visibility(window=demo_window, visibility=""hide"")
``` END",{},[]
"我正在使用一款名为""Account Software""的账务软件，我需要在一个叫做""password""的输入框中输入密码""123456""。","```python
# 打开""Account Software""软件
process_info=xbot_visual.desktop.launch(process_name=""Account Software"")
# 在""password""输入框中输入密码""123456""
xbot_visual.desktop.input(window=""0"", element=""password"", text=""123456"")
``` END",{},[]
"我正在使用一款名为""Music Player""的音乐播放软件，我需要将它的窗口大小调整为1200*800，并且让它显示在屏幕上。","```python
# 获取""Music Player""窗口
music_player_window = xbot_visual.desktop.get(title=""Music Player"")
# 调整窗口大小为1200*800
xbot_visual.desktop.resize(window=music_player_window, width=""1200"", height=""800"")
# 将窗口显示在屏幕上
xbot_visual.desktop.set_state(window=music_player_window, state=""normal"")
``` END",{},[]
我想知道当前我正在使用的是哪一个软件窗口。,"```python
# 获取当前激活的窗口
active_window = xbot_visual.desktop.get_active()
# 获取窗口名称
window_name = xbot_visual.desktop.get_info(window=active_window, info='title')
# 打印窗口名称
print(window_name)
``` END",{'err_funcs': ['xbot_visual.desktop.get_info']},['err_funcs']
我需要在微信上向一位好友发送一条信息，内容是“明天的会议推迟到下午2点”，请帮我操作一下。,"```python
# 打开微信
process_info=xbot_visual.desktop.launch(process_name=""微信"")
# 点击进入好友聊天窗口
xbot_visual.desktop.click(window=""0"", element=""好友聊天"")
# 在消息输入框中输入内容
xbot_visual.desktop.input(window=""0"", element=""消息输入框"", text=""明天的会议推迟到下午2点"")
# 点击发送按钮
xbot_visual.desktop.click(window=""0"", element=""发送按钮"")
``` END",{},[]
我需要你帮我隐藏一个正在运行的软件窗口。,"```python
# 获取指定软件窗口
software_window = xbot_visual.desktop.get(title=""软件窗口"")
# 隐藏软件窗口
xbot_visual.desktop.set_visibility(window=software_window, visibility=""hide"")
``` END",{},[]
在我的CAD软件中设置一些参数。在参数设置窗口，设置线型为实线，颜色为红色，线宽为0.5mm。,"```python
# 打开CAD软件
process_info=xbot_visual.desktop.launch(process_name=""CAD"")
# 点击进入CAD软件的参数设置窗口
xbot_visual.desktop.click(window=""0"", element=""参数设置"")
# 在线型下拉框中选择实线
xbot_visual.desktop.select_by_index(window=""0"", element=""线型下拉框"", index=""1"")
# 在颜色下拉框中选择红色
xbot_visual.desktop.select_by_index(window=""0"", element=""颜色下拉框"", index=""2"")
# 在线宽输入框中输入0.5
xbot_visual.desktop.input(window=""0"", element=""线宽输入框"", text=""0.5"")
# 点击确认按钮，保存参数设置
xbot_visual.desktop.click(window=""0"", element=""确认按钮"")
``` END",{},[]
我有个PDF文件需要阅读，但是窗口太小看得眼睛疼，可以调整一下PDF阅读器的窗口大小吗，宽度调整为800，高度调整为600。,"```python
# 打开PDF文件
xbot_visual.pdf.open(file_path=""C:\\Users\\Administrator\\Desktop\\sample.pdf"")
# 调整PDF阅读器窗口大小
xbot_visual.desktop.resize(window=""0"", width=""800"", height=""600"")
``` END",{'err_funcs': ['xbot_visual.pdf.open']},['err_funcs']
我需要隐藏我的QQ聊天窗口，不让别人看到我正在和谁聊天。,"```python
# 获取QQ聊天窗口对象
qq_chat_window = xbot_visual.desktop.get(title=""QQ聊天"")
# 隐藏QQ聊天窗口
xbot_visual.desktop.set_visibility(window=qq_chat_window, visibility=""hide"")
``` END",{},[]
我需要在Photoshop软件中选择画笔的大小，可以通过下拉框选择，我需要选择第3个选项。,"```python
# 打开Photoshop软件
process_info=xbot_visual.desktop.launch(process_name=""Photoshop"")
# 点击进入画笔设置
xbot_visual.desktop.click(window=""0"", element=""画笔设置"")
# 选择画笔大小下拉框
xbot_visual.desktop.select_by_index(window=""0"", element=""画笔大小下拉框"", index=""3"")
``` END",{},[]
我在Windows记事本中写了一些文字，但是窗口太小，看不清楚，帮我把记事本窗口调整到最大。,"```python
# 打开Windows记事本
process_info=xbot_visual.desktop.launch(process_name=""Windows记事本"")
# 在记事本中的输入框中输入文字
xbot_visual.desktop.input(window=""0"", element=""记事本输入框"", text=""一些文字"")
# 调整记事本窗口大小为最大
xbot_visual.desktop.resize(window=""0"", width=""max"", height=""max"")
``` END",{},[]
我在一个软件中有个下拉框需要选择，但是我不知道具体选项的文字，只知道是第三个选项。,"```python
# 选择下拉框的第三个选项
xbot_visual.desktop.select_by_index(window=""0"", element=""下拉框"", index=""3"")
``` END",{},[]
我有一个文件需要在Adobe Acrobat Reader DC软件中打开，并调整窗口大小，使其占满整个屏幕。,"```python
# 打开Adobe Acrobat Reader DC软件
process_info=xbot_visual.desktop.launch(process_name=""Adobe Acrobat Reader DC"")
# 点击打开文件按钮
xbot_visual.desktop.click(window=""0"", element=""打开文件按钮"")
# 在文件选择窗口中输入文件路径
xbot_visual.desktop.input(window=""0"", element=""文件路径输入框"", text=""C:\\example.pdf"")
# 点击确认打开文件
xbot_visual.desktop.click(window=""0"", element=""确认打开按钮"")
# 获取Adobe Acrobat Reader DC窗口
acrobat_window = xbot_visual.desktop.get(title=""Adobe Acrobat Reader DC"")
# 调整窗口大小，使其占满整个屏幕
xbot_visual.desktop.resize(window=acrobat_window, width=""100%"", height=""100%"")
``` END",{},[]
"我想在CAD上画一条线，起点是(0, 0)，终点是(100, 100)，然后保存退出。","```python
# 打开CAD软件
process_info=xbot_visual.desktop.launch(process_name=""CAD"")
# 点击绘制线条按钮
xbot_visual.desktop.click(window=""0"", element=""绘制线条按钮"")
# 点击起点输入框
xbot_visual.desktop.click(window=""0"", element=""起点输入框"")
# 在起点输入框中输入(0, 0)
xbot_visual.desktop.input(window=""0"", element=""起点输入框"", text=""(0, 0)"")
# 点击终点输入框
xbot_visual.desktop.click(window=""0"", element=""终点输入框"")
# 在终点输入框中输入(100, 100)
xbot_visual.desktop.input(window=""0"", element=""终点输入框"", text=""(100, 100)"")
# 点击确认绘制按钮
xbot_visual.desktop.click(window=""0"", element=""确认绘制按钮"")
# 点击保存按钮
xbot_visual.desktop.click(window=""0"", element=""保存按钮"")
# 点击退出按钮
xbot_visual.desktop.click(window=""0"", element=""退出按钮"")
``` END",{},[]
我需要在微信窗口和当前激活的窗口来回切换。,"```python
# 获取微信窗口
wechat_window = xbot_visual.desktop.get(title=""微信"")
# 获取当前激活的窗口
active_window = xbot_visual.desktop.get_active()
# 切换到微信窗口
xbot_visual.desktop.activate(window=wechat_window)
# 切换回当前激活的窗口
xbot_visual.desktop.activate(window=active_window)
``` END",{},[]
"我需要你在记事本上输入一段文本""Hello, World!""。然后重新激活之前的窗口","```python
# 打开记事本
process_info=xbot_visual.desktop.launch(process_name=""记事本"")
# 在记事本上输入一段文本""Hello, World!""
xbot_visual.desktop.input(window=""0"", element=""记事本编辑区域"", text=""Hello, World!"")
# 重新激活之前的窗口
xbot_visual.desktop.activate(window=""0"")
``` END",{},[]
"我需要在WinRAR中，创建一个新的压缩文件，并设置密码为""123456""，然后将该文件隐藏起来，不让其他人看到。","```python
# 打开WinRAR软件
process_info=xbot_visual.desktop.launch(process_name=""WinRAR"")
# 点击创建新的压缩文件按钮
xbot_visual.desktop.click(window=""0"", element=""创建新的压缩文件按钮"")
# 在弹出的对话框中，输入压缩文件的名称
xbot_visual.desktop.input(window=""0"", element=""文件名输入框"", text=""sample.rar"")
# 在对话框中，设置压缩文件的密码为""123456""
xbot_visual.desktop.input(window=""0"", element=""密码输入框"", text=""123456"")
# 在对话框中，确认密码
xbot_visual.desktop.input(window=""0"", element=""确认密码输入框"", text=""123456"")
# 点击对话框中的""确定""按钮，创建压缩文件
xbot_visual.desktop.click(window=""0"", element=""确定按钮"")
# 点击对话框中的""取消""按钮，关闭对话框
xbot_visual.desktop.click(window=""0"", element=""取消按钮"")
# 点击WinRAR主窗口的""隐藏""按钮，将压缩文件隐藏起来
xbot_visual.desktop.click(window=""0"", element=""隐藏按钮"")
``` END",{},[]
"我需要在已经打开的Word文档中中，将字体设置为""宋体""，字号设置为""12""，并勾选""加粗""和""斜体""选项。","```python
# 获取已经打开的Word文档
word_document = xbot_visual.desktop.get(title=""Word"")
# 点击字体设置按钮
xbot_visual.desktop.click(window=""0"", element=""字体设置按钮"")
# 选择""宋体""字体
xbot_visual.desktop.select_by_text(window=""0"", element=""字体下拉框"", text=""宋体"")
# 选择""12""号字体
xbot_visual.desktop.select_by_text(window=""0"", element=""字号下拉框"", text=""12"")
# 勾选""加粗""选项
xbot_visual.desktop.set_checkbox(window=""0"", element=""加粗选项"", check_state=""check"")
# 勾选""斜体""选项
xbot_visual.desktop.set_checkbox(window=""0"", element=""斜体选项"", check_state=""check"")
``` END",{},[]
"我需要在Windows资源管理器中，将视图模式切换为""详细信息""。","```python
# 打开Windows资源管理器
xbot_visual.keyboard.send_keys(keys=""#{e}"")
# 点击视图选项卡
xbot_visual.desktop.click(window=""0"", element=""视图选项卡"")
# 点击详细信息按钮
xbot_visual.desktop.click(window=""0"", element=""详细信息按钮"")
``` END",{},[]
"我今天需要远程开会，所以打开我的电脑上的Zoom软件，然后在搜索框中输入会议ID：""123456789""，然后点击加入。","```python
# 打开Zoom软件
process_info=xbot_visual.desktop.launch(process_name=""Zoom"")
# 在搜索框中输入会议ID
xbot_visual.desktop.input(window=""0"", element=""Zoom搜索框"", text=""123456789"")
# 点击加入
xbot_visual.desktop.click(window=""0"", element=""Zoom加入按钮"")
``` END",{},[]
鼠标悬浮到钉钉头像上，然后鼠标右击。,"```python
# 鼠标悬浮到钉钉头像上
xbot_visual.desktop.hover(window=""0"", element=""钉钉头像"")
# 鼠标右击
xbot_visual.mouse.click(click_type=""right"", key=""0"")
``` END","{'extra_args': [""xbot_visual.mouse.click:['key']""]}",['extra_args']
把我现在打开的两个记事本都移动到桌面左上角。,"```python
# 获取当前激活窗口
active_window = xbot_visual.desktop.get_active()
# 获取桌面窗口
desktop_window = xbot_visual.desktop.get(title=""桌面"")
# 移动第一个记事本到桌面左上角
xbot_visual.desktop.move(window=active_window, x=""0"", y=""0"")
# 移动第二个记事本到桌面左上角
xbot_visual.desktop.move(window=active_window, x=""0"", y=""0"")
``` END",{},[]
隐藏我启动的微信窗口,"```python
# 获取我启动的微信窗口
wechat_window = xbot_visual.desktop.get(title=""微信"")
# 隐藏窗口
xbot_visual.desktop.set_visibility(window=wechat_window, visibility=""hide"")
``` END",{},[]
登录QQ,"```python
# 打开QQ登录页面
web_page = xbot_visual.web.create(web_type=""chrome"", url=""https://im.qq.com/"")
# 输入账号
xbot_visual.web.input(page=web_page, element=""#username"", text=""username"")
# 输入密码
xbot_visual.web.input_password(page=web_page, element=""#pwd"", password=""password"")
# 点击登录
xbot_visual.web.click(page=web_page, element='#login')
``` END",{},[]
登录生意参谋软件,"```python
# 打开生意参谋软件
process_info=xbot_visual.desktop.launch(process_name=""生意参谋"")
# 输入账号
xbot_visual.desktop.input(window=""0"", element=""账号输入框"", text=""username"")
# 输入密码
xbot_visual.desktop.input_password(window=""0"", element=""密码输入框"", password=""password"")
# 点击登录
xbot_visual.desktop.click(window=""0"", element=""登录按钮"")
``` END",{},[]
登录旺店通,"```python
# 打开旺店通登录页面
web_page = xbot_visual.web.create(web_type=""chrome"", url=""https://login.wangdian.cn/"")
# 输入账号
xbot_visual.web.input(page=web_page, element=""#username"", text=""username"")
# 输入密码
xbot_visual.web.input_password(page=web_page, element=""#pwd"", password=""password"")
# 点击登录
xbot_visual.web.click(page=web_page, element='#login')
``` END",{},[]
登录eas,"```python
# 打开eas软件
process_info=xbot_visual.desktop.launch(process_name=""eas"")
# 输入用户名
xbot_visual.desktop.input(window=""0"", element=""用户名输入框"", text=""admin"")
# 输入密码
xbot_visual.desktop.input_password(window=""0"", element=""密码输入框"", password=""123456"")
# 点击登录
xbot_visual.desktop.click(window=""0"", element=""登录按钮"")
``` END",{},[]
隐藏 VSCode 窗口,"```python
# 获取VSCode窗口
vscode_window = xbot_visual.desktop.get(title=""VSCode"")
# 隐藏VSCode窗口
xbot_visual.desktop.set_visibility(window=vscode_window, visibility=""hide"")
``` END",{},[]
对Word窗口进行截图,"```python
# 获取Word窗口
word_window = xbot_visual.desktop.get(title=""Word"")
# 对Word窗口进行截图
xbot_visual.desktop.screenshot_element(window=word_window, element=""Word窗口"", file_folder=""C:\\Desktop"", file_name=""Word.png"")
``` END",{},[]
将obsidian窗口最小化,"```python
# 获取obsidian窗口
obsidian_window = xbot_visual.desktop.get(title=""obsidian"")
# 将obsidian窗口最小化
xbot_visual.desktop.set_state(window=obsidian_window, state=""minimize"")
``` END",{},[]
设置QQ的主界面隐藏，然后再显示出来,"```python
# 获取QQ主窗口对象
qq_window = xbot_visual.desktop.get(title=""QQ"")
# 隐藏QQ主窗口
xbot_visual.desktop.set_visibility(window=qq_window, visibility=""hide"")
# 5秒
xbot_visual.desktop.send_keys(window=qq_window, keys=""^n"")
# 显示QQ主窗口
xbot_visual.desktop.set_visibility(window=qq_window, visibility=""show"")
``` END",{'err_funcs': ['xbot_visual.desktop.send_keys']},['err_funcs']
为了保护隐私，需要将某个聊天软件的窗口隐藏起来,"```python
# 获取聊天软件窗口对象
chat_window = xbot_visual.desktop.get(title=""聊天软件"")
# 隐藏聊天软件窗口
xbot_visual.desktop.set_visibility(window=chat_window, visibility=""hide"")
``` END",{},[]
关闭所有的记事本进程,"```python
# 打开任务管理器
xbot_visual.keyboard.send_keys(keys=""^+{ESCAPE}"")
# 选择进程选项卡
xbot_visual.desktop.click(window=""0"", element=""进程选项卡"")
# 遍历进程列表
for process in xbot_visual.desktop.iter_all_elements(window=""0"", element=""进程列表""):
    # 获取进程名称
    process_name = xbot_visual.desktop.get_attribute(window=""0"", element=process, attribute_name=""text"")
    # 判断进程是否为记事本进程
    if ""记事本"" in process_name:
        # 选择记事本进程
        xbot_visual.desktop.click(window=""0"", element=process)
        # 点击结束任务按钮
        xbot_visual.desktop.click(window=""0"", element=""结束任务按钮"")
        # 点击确定按钮
        xbot_visual.desktop.click(window=""0"", element=""确定按钮"")
``` END",{},[]
调整记事本的窗口大小为800x600，然后打开微信窗口，回复一个消息，重新激活记事本,"```python
# 获取记事本窗口
notepad_window = xbot_visual.desktop.get(title=""记事本"")
# 调整记事本窗口大小为800x600
xbot_visual.desktop.resize(window=notepad_window, width=""800"", height=""600"")
# 打开微信窗口
xbot_visual.desktop.click(window=""0"", element=""微信窗口"")
# 在微信窗口中输入框输入消息
xbot_visual.desktop.input(window=""0"", element=""微信输入框"", text=""回复消息"")
# 点击发送按钮
xbot_visual.desktop.click(window=""0"", element=""发送按钮"")
# 重新激活记事本窗口
xbot_visual.desktop.activate(window=notepad_window)
``` END",{},[]
依次激活所有记事本窗口,"```python
# 获取所有记事本窗口对象列表
notepad_windows = xbot_visual.desktop.get_all(title=""记事本"")
# 遍历记事本窗口对象列表
for notepad_window in notepad_windows:
    # 激活记事本窗口
    xbot_visual.desktop.activate(window=notepad_window)
``` END",{},[]
鼠标悬停在指定桌面软件(win)元素上，然后双击鼠标左键,"```python
# 鼠标悬停在指定桌面软件(win)元素上
xbot_visual.desktop.hover(window=""0"", element=""指定桌面软件(win)元素"")
# 双击鼠标左键
xbot_visual.mouse.click(click_type=""dbclick"")
``` END",{},[]
使用点击的方式将所有启动的资源管理器窗口最小化,"```python
# 循环遍历所有资源管理器窗口对象
for explorer_window in xbot_visual.desktop.get_all(title=""资源管理器""):
    # 点击资源管理器窗口最小化按钮
    xbot_visual.desktop.click(window=""0"", element=""最小化按钮"")
``` END",{},[]
我需要截取指定微信聊天窗口的截图并保存D:\\Screenshots路径下，文件名为screenshot.png。,"```python
# 打开微信
process_info=xbot_visual.desktop.launch(process_name=""微信"")
# 点击进入指定微信聊天窗口
xbot_visual.desktop.click(window=""0"", element=""指定微信聊天窗口"")
# 截取聊天窗口的截图
xbot_visual.desktop.screenshot_element(window=""0"", element=""指定微信聊天窗口"", file_folder=""D:\\Screenshots"", file_name=""screenshot.png"")
``` END",{},[]
鼠标点击的方式打开我edge的收藏夹 打印所有收藏对象名称,"```python
# 打开edge浏览器
web_page = xbot_visual.web.create(web_type=""edge"", url=""https://www.edge.com/"")
# 鼠标点击打开收藏夹
xbot_visual.web.click(page=web_page, element=""收藏夹"")
# 遍历所有收藏对象
for element in xbot_visual.web.iter_all_elements(page=web_page, element=""所有收藏对象""):
    # 打印对象名称
    print(xbot_visual.web.get_attribute(page=web_page, element=element, attribute_name=""text""))
``` END",{},[]
激活 edge 并发送快捷键 Ctrl+Shift+O 打开收藏夹,"```python
# 打开edge
process_info=xbot_visual.desktop.launch(process_name=""edge"")
# 激活edge窗口
xbot_visual.desktop.activate(window=""0"",element=""edge窗口"")
# 发送快捷键 Ctrl+Shift+O
xbot_visual.keyboard.send_keys(keys=""^+O"")
``` END","{'extra_args': [""xbot_visual.desktop.activate:['element']""]}",['extra_args']
依次将我所有的企微好友删除,"```python
# 打开企微
process_info=xbot_visual.desktop.launch(process_name=""企微"")
# 点击进入好友列表
xbot_visual.desktop.click(window=""0"", element=""好友列表"")
# 遍历好友对象列表
for friend in xbot_visual.desktop.iter_all_elements(window=""0"", element=""好友对象""):
    # 点击进入好友信息
    xbot_visual.desktop.click(window=""0"", element=friend)
    # 点击删除好友
    xbot_visual.desktop.click(window=""0"", element=""删除好友"")
    # 确认删除
    xbot_visual.desktop.click(window=""0"", element=""确认删除"")
    # 点击返回
    xbot_visual.desktop.click(window=""0"", element=""返回"")
``` END",{},[]
"""登录QQ时填写密码完成后，隐藏该窗口，以保护我的隐私""","```python
# 打开QQ登录窗口
process_info=xbot_visual.desktop.launch(process_name=""QQ"")
# 输入QQ账号
xbot_visual.desktop.input(window=""0"", element=""QQ账号输入框"", text=""123456"")
# 输入QQ密码
xbot_visual.desktop.input_password(window=""0"", element=""QQ密码输入框"", password=""123456"")
# 勾选记住密码
xbot_visual.desktop.set_checkbox(window=""0"", element=""记住密码复选框"", check_state=""check"")
# 点击登录按钮
xbot_visual.desktop.click(window=""0"", element=""登录按钮"")
# 获取QQ窗口
qq_window = xbot_visual.desktop.get(title=""QQ"")
# 隐藏QQ窗口
xbot_visual.desktop.set_visibility(window=qq_window, visibility=""hide"")
``` END",{},[]
"""把所有标题为 mytitle 的窗口大小调整为(800, 600)""","```python
# 获取所有标题为 mytitle 的窗口
mytitle_windows = xbot_visual.desktop.get_all(title=""mytitle"")
# 遍历窗口列表
for window in mytitle_windows:
    # 调整窗口大小为(800, 600)
    xbot_visual.desktop.resize(window=window, width=""800"", height=""600"")
``` END",{},[]
我需要获取所有打开的记事本窗口，并将它们全部最小化,"```python
# 获取所有打开的记事本窗口
notepad_windows = xbot_visual.desktop.get_all(title=""记事本"")
# 遍历记事本窗口列表
for window in notepad_windows:
    # 将记事本窗口最小化
    xbot_visual.desktop.set_state(window=window, state=""minimize"")
``` END",{},[]
win+r唤起windows 运行弹窗，并输入 regedit,"```python
# 双击win键唤起windows 运行弹窗
xbot_visual.keyboard.send_keys(keys=""#r"")
# 输入regedit
xbot_visual.keyboard.send_keys(keys=""regedit"")
``` END",{},[]
激活KeepMouseSpeedOK窗口 并勾选开机自启,"```python
# 获取KeepMouseSpeedOK窗口对象
keep_mousespeedok_window = xbot_visual.desktop.get(title=""KeepMouseSpeedOK"")
# 勾选开机自启
xbot_visual.desktop.set_checkbox(window=keep_mousespeedok_window, element=""勾选开机自启"", check_state=""check"")
# 激活KeepMouseSpeedOK窗口
xbot_visual.desktop.activate(window=keep_mousespeedok_window)
``` END",{},[]
使用everything搜索名为 sample 的文件,"```python
# 打开everything
process_info=xbot_visual.desktop.launch(process_name=""everything"")
# 在搜索框中输入文件名
xbot_visual.desktop.input(window=""0"", element=""搜索框"", text=""sample"")
# 点击搜索按钮
xbot_visual.desktop.click(window=""0"", element=""搜索按钮"")
``` END",{},[]
钉钉的代办事项列表给我一份,"```python
# 打开钉钉
process_info=xbot_visual.desktop.launch(process_name=""钉钉"")
# 点击进入代办事项模块
xbot_visual.desktop.click(window=""0"", element=""代办事项"")
# 遍历所有待办事项元素
for element in xbot_visual.desktop.iter_all_elements(window=""0"", element=""待办事项元素""):
    # 获取待办事项文本
    todo_text = xbot_visual.desktop.get_attribute(window=""0"", element=element, attribute_name=""text"")
    # 打印待办事项文本
    print(todo_text)
``` END",{},[]
通过双击 Notepad 的标题栏的方式最大化,"```python
# 获取Notepad窗口对象
notepad_window = xbot_visual.desktop.get(title=""Notepad"")
# 双击Notepad窗口标题栏
xbot_visual.desktop.click(window=notepad_window, element=""title"", clicks=""dbclick"")
``` END",{},[]
鼠标悬浮电池，查看我的电池电量,"```python
# 打开电池图标
xbot_visual.desktop.click(window=""0"", element=""电池图标"", button=""dbclick"")
# 鼠标悬浮电池
xbot_visual.desktop.hover(window=""0"", element=""电池"")
# 点击查看电池电量
xbot_visual.desktop.click(window=""0"", element=""查看电池电量"")
``` END",{},[]
鼠标悬浮到桌面底部状态栏的网络链接按钮上，查看网络状态并截图,"```python
# 打开网络状态窗口
xbot_visual.desktop.click(window=""0"", element=""网络状态"")
# 鼠标悬浮到桌面底部状态栏的网络链接按钮上
xbot_visual.desktop.hover(window=""0"", element=""桌面底部状态栏的网络链接按钮"")
# 截图网络状态
xbot_visual.desktop.screenshot_element(window=""0"", element=""网络状态窗口"", file_folder=""C:\\"", file_name=""network_status.png"")
``` END",{},[]
对QQ聊天窗口的消息框进行截图保存,"```python
# 获取QQ聊天窗口的消息框元素
qq_chat_window = xbot_visual.desktop.get(title=""QQ聊天"", cls=""TXGuiFoundation"", idx=""0"")
message_box = xbot_visual.desktop.find_element(window=qq_chat_window, element=""消息框"")
# 对消息框进行截图
xbot_visual.desktop.screenshot_element(window=qq_chat_window, element=message_box, file_folder=""C:\\Desktop"", file_name=""message_box.png"")
``` END","{'extra_args': [""xbot_visual.desktop.get:['cls', 'idx']""]}",['extra_args']
关闭有关“Python”的所有窗口。,"```python
# 获取所有包含“Python”关键字的窗口
python_windows = xbot_visual.desktop.get_all(title=""*Python*"")
# 遍历窗口列表
for window in python_windows:
    # 关闭窗口
    xbot_visual.desktop.close(window=window)
``` END",{},[]
获取QQ聊天窗口中的聊天记录。,"```python
# 打开QQ
process_info=xbot_visual.desktop.launch(process_name=""QQ"")
# 点击进入指定的QQ聊天窗口
xbot_visual.desktop.click(window=""0"", element=""QQ聊天窗口"")
# 遍历聊天记录元素列表
for chat_record in xbot_visual.desktop.iter_all_elements(window=""0"", element=""聊天记录元素""):
    # 获取聊天记录文本
    chat_record_text = xbot_visual.desktop.get_attribute(window=""0"", element=chat_record, attribute_name=""text"")
    # 打印聊天记录
    print(chat_record_text)
``` END",{},[]
获取记事本窗口中的文本。,"```python
# 获取记事本窗口中的文本
text = xbot_visual.desktop.get_attribute(window=""0"", element=""记事本窗口"", attribute_name=""text"")
``` END",{},[]
在计算器中输入一个数学表达式并计算,"```python
# 打开计算器
process_info=xbot_visual.desktop.launch(process_name=""计算器"")
# 在计算器中输入一个数学表达式
xbot_visual.desktop.input(window=""0"", element=""计算器输入框"", text=""2+2"")
# 点击计算按钮
xbot_visual.desktop.click(window=""0"", element=""计算按钮"")
``` END",{},[]
在QQ中搜索并打开相亲相爱一家人群聊,"```python
# 打开QQ
process_info=xbot_visual.desktop.launch(process_name=""QQ"")
# 在搜索框中输入群聊名称
xbot_visual.desktop.input(window=""0"", element=""搜索框"", text=""相亲相爱一家人"")
# 点击搜索按钮
xbot_visual.desktop.click(window=""0"", element=""搜索按钮"")
# 点击群聊
xbot_visual.desktop.click(window=""0"", element=""相亲相爱一家人群聊"")
``` END",{},[]
在文件资源管理器中打开一个特定路径,"```python
# 打开文件资源管理器
xbot_visual.keyboard.send_keys(keys=""#{e}"")
# 输入特定路径
xbot_visual.desktop.input(window=""0"", element=""文件路径输入框"", text=""C:\\Users\\Username\\Documents"")
# 按下回车键
xbot_visual.keyboard.send_keys(keys=""{enter}"")
``` END",{},[]
在任务管理器中结束一个特定的进程,"```python
# 打开任务管理器
xbot_visual.keyboard.send_keys(keys=""ctrl + shift + esc"")
# 在进程列表中输入进程名称
xbot_visual.desktop.input(window=""0"", element=""进程名称输入框"", text=""process_name"")
# 点击查找按钮
xbot_visual.desktop.click(window=""0"", element=""查找按钮"")
# 获取进程列表中的第一个进程对象
process = xbot_visual.desktop.find_element(window=""0"", element=""进程对象"")
# 点击结束进程按钮
xbot_visual.desktop.click(window=""0"", element=""结束进程按钮"")
# 点击确认结束进程的提示框
xbot_visual.desktop.click(window=""0"", element=""确认结束进程提示框"")
``` END",{},[]
获取Windows系统计算机管理窗口，并将其移动到屏幕左上角,"```python
# 获取Windows系统计算机管理窗口
computer_management_window = xbot_visual.desktop.get(title=""计算机管理"")
# 将计算机管理窗口移动到屏幕左上角
xbot_visual.desktop.move(window=computer_management_window, x=""0"", y=""0"")
``` END",{},[]
获取Windows系统计算机管理窗口，并将其调整为800x600的大小,"```python
# 获取Windows系统计算机管理窗口
computer_management_window = xbot_visual.desktop.get(title=""计算机管理"")
# 将计算机管理窗口调整为800x600的大小
xbot_visual.desktop.resize(window=computer_management_window, width=""800"", height=""600"")
``` END",{},[]
"在Windows系统的""设备管理器""窗口中，进入蓝牙设备配置页面","```python
# 打开Windows系统的""设备管理器""窗口
xbot_visual.keyboard.send_keys(keys=""#{r}"")
# 在""设备管理器""窗口中，输入""蓝牙""进行搜索
xbot_visual.desktop.input(window=""0"", element=""搜索框"", text=""蓝牙"")
# 在""设备管理器""窗口中，选择蓝牙设备
xbot_visual.desktop.click(window=""0"", element=""蓝牙设备"")
# 在""设备管理器""窗口中，点击""配置""按钮，进入蓝牙设备配置页面
xbot_visual.desktop.click(window=""0"", element=""配置"")
``` END",{},[]
"现在有Windows系统的""系统属性""窗口，怎么进入环境变量配置","```python
# 获取系统属性窗口
system_properties_window = xbot_visual.desktop.get(title=""系统属性"")
# 点击环境变量配置按钮
xbot_visual.desktop.click(window=""0"", element=""环境变量配置"")
``` END",{},[]
"在Windows系统的""日期和时间""设置窗口中，选择""时区""下拉框的第一个选项","```python
# 打开""日期和时间""设置窗口
xbot_visual.keyboard.send_keys(keys=""#{r}"", in_focus=""True"")
# 选择""时区""下拉框
xbot_visual.desktop.select(window=""0"", element=""时区下拉框"", option=""index"",  value=""1"")
``` END","{'err_funcs': ['xbot_visual.desktop.select'], 'extra_args': [""xbot_visual.keyboard.send_keys:['in_focus']""]}","['err_funcs', 'extra_args']"
激活计算器窗口，然后调整其窗口大小为宽度500px，高度500px,"```python
# 打开计算器
process_info=xbot_visual.desktop.launch(process_name=""计算器"")
# 激活计算器窗口
xbot_visual.desktop.activate(window=""0"")
# 调整计算器窗口大小为宽度500px，高度500px
xbot_visual.desktop.resize(window=""0"", width=""500"", height=""500"")
``` END",{},[]
激活QQ聊天窗口，然后将其最小化,"```python
# 获取QQ聊天窗口
qq_chat_window = xbot_visual.desktop.get(title=""QQ聊天"")
# 激活QQ聊天窗口
xbot_visual.desktop.activate(window=qq_chat_window)
# 将QQ聊天窗口最小化
xbot_visual.desktop.set_state(window=qq_chat_window, state=""minimize"")
``` END",{},[]
激活微信窗口，然后对其进行截图保存,"```python
# 获取微信窗口
wechat_window = xbot_visual.desktop.get(title=""微信"")
# 激活微信窗口
xbot_visual.desktop.activate(window=wechat_window)
# 对微信窗口进行截图
screenshot_path = xbot_visual.desktop.screenshot_element(window=wechat_window, element=""微信窗口"", file_folder=""C:\\Desktop"", file_name=""wechat.png"")
``` END",{},[]
激活QQ音乐窗口，然后通过索引选择下拉框选项“我的音乐”(第一项),"```python
# 获取QQ音乐窗口
qqmusic_window = xbot_visual.desktop.get(title=""QQ音乐"")
# 通过索引选择下拉框选项“我的音乐”(第一项)
xbot_visual.desktop.select_by_index(window=qqmusic_window, element=""下拉框"", index=""1"")
``` END",{},[]
激活Word窗口，然后将其最大化,"```python
# 获取Word窗口并激活
word_window = xbot_visual.desktop.get(title=""Word"")
# 将Word窗口最大化
xbot_visual.desktop.set_state(window=word_window, state=""maximize"")
``` END",{},[]
在QQ上通过文本设置状态为“忙碌”,"```python
# 打开QQ
process_info=xbot_visual.desktop.launch(process_name=""QQ"")
# 点击进入状态设置
xbot_visual.desktop.click(window=""0"", element=""状态设置"")
# 在文本框中输入“忙碌”
xbot_visual.desktop.input(window=""0"", element=""状态文本框"", text=""忙碌"")
# 点击保存按钮
xbot_visual.desktop.click(window=""0"", element=""保存按钮"")
``` END",{},[]
隐藏飞书对话框窗口,"```python
# 获取飞书窗口对象
feishu_window = xbot_visual.desktop.get(title=""飞书"")
# 隐藏飞书窗口
xbot_visual.desktop.set_visibility(window=feishu_window, visibility=""hide"")
``` END",{},[]
在PotPlayer中通过索引设置音频轨道,"```python
# 打开PotPlayer软件
process_info=xbot_visual.desktop.launch(process_name=""PotPlayer"")
# 点击进入音频轨道设置
xbot_visual.desktop.click(window=""0"", element=""音频轨道设置"")
# 选择第一个音频轨道
xbot_visual.desktop.select_by_index(window=""0"", element=""音频轨道下拉框"", index=""1"")
``` END",{},[]
在网易云音乐上通过文本设置播放模式为“单曲循环”,"```python
# 打开网易云音乐
process_info=xbot_visual.desktop.launch(process_name=""网易云音乐"")
# 点击进入设置页面
xbot_visual.desktop.click(window=""0"", element=""设置按钮"")
# 在设置页面中，通过文本设置播放模式为“单曲循环”
xbot_visual.desktop.select_by_text(window=""0"", element=""播放模式下拉框"", text=""单曲循环"")
``` END",{},[]
截取计算器应用的截图,"```python
# 打开计算器应用
process_info=xbot_visual.desktop.launch(process_name=""计算器"")
# 截取计算器应用的截图
xbot_visual.desktop.screenshot_element(window=""0"", element=""计算器窗口"", file_folder=""C:\\Pictures"", file_name=""计算器.png"")
``` END",{},[]
获取Windows资源管理器中的所有文件夹名称,"```python
# 获取Windows资源管理器窗口
explorer_window = xbot_visual.desktop.get(title=""资源管理器"")
# 遍历文件夹对象列表
for folder in xbot_visual.desktop.iter_all_elements(window=""0"", element=""文件夹对象""):
    # 获取文件夹名称
    folder_name = xbot_visual.desktop.get_attribute(window=""0"", element=folder, attribute_name=""text"")
    # 打印文件夹名称
    print(folder_name)
``` END",{},[]
最大化微信窗口,"```python
# 打开微信
process_info=xbot_visual.desktop.launch(process_name=""微信"")
# 最大化微信窗口
xbot_visual.desktop.set_state(window=""0"", state=""maximize"")
``` END",{},[]
"在屏幕上移动鼠标至坐标(100, 200)","```python
# 移动鼠标至(100, 200)
xbot_visual.mouse.move(x=""100"", y=""200"")
``` END",{},[]
对QQ聊天窗口进行截图保存,"```python
# 获取QQ聊天窗口的截图
xbot_visual.desktop.screenshot_element(window=""0"", element=""QQ聊天窗口"", file_folder=""C:\\Desktop"", file_name=""QQ聊天窗口.png"")
``` END",{},[]
将画图工具的窗口大小调整为宽度500px，高度300px,"```python
# 获取画图工具窗口
paint_window = xbot_visual.desktop.get(title=""画图工具"")
# 调整窗口大小为宽度500px，高度300px
xbot_visual.desktop.resize(window=paint_window, width=""500"", height=""300"")
``` END",{},[]
将网易云音乐的窗口大小调整为宽度800px，高度600px,"```python
# 获取网易云音乐窗口
netease_cloud_music_window = xbot_visual.desktop.get(title=""网易云音乐"")
# 调整窗口大小
xbot_visual.desktop.resize(window=netease_cloud_music_window, width=""800"", height=""600"")
``` END",{},[]
"在屏幕上移动鼠标至坐标(300, 400)","```python
# 移动鼠标至(300, 400)
xbot_visual.mouse.move(x=""300"", y=""400"")
``` END",{},[]
在QQ聊天窗口中，查看最后一条接收的消息，并对其截图。,"```python
# 打开QQ软件
process_info=xbot_visual.desktop.launch(process_name=""QQ"")
# 点击进入QQ聊天窗口
xbot_visual.desktop.click(window=""0"", element=""QQ聊天窗口"")
# 获取最后一条接收的消息对象
last_message = xbot_visual.desktop.find_element(window=""0"", element=""最后一条接收的消息"")
# 截图最后一条接收的消息
xbot_visual.desktop.screenshot_element(window=""0"", element=last_message, file_folder=""C:\\"", file_name=""message.png"")
``` END",{},[]
打开Steam，搜索游戏“Dota 2”，并对搜索结果进行截图。,"```python
# 打开Steam
process_info=xbot_visual.desktop.launch(process_name=""Steam"")
# 在Steam中的搜索框内输入游戏名称""Dota 2""
xbot_visual.desktop.input(window=""0"", element=""Steam搜索框"", text=""Dota 2"")
# 对搜索结果进行截图
xbot_visual.desktop.screenshot_element(window=""0"", element=""Steam搜索结果"", file_folder=""C:\\Desktop"", file_name=""Dota 2搜索结果.png"")
``` END",{},[]
在金蝶ERP软件中新建采购订单,"```python
# 打开金蝶ERP软件
process_info=xbot_visual.desktop.launch(process_name=""金蝶ERP"")
# 点击进入采购模块
xbot_visual.desktop.click(window=""0"", element=""采购模块"")
# 点击新建采购订单按钮
xbot_visual.desktop.click(window=""0"", element=""新建采购订单"")
# 填写供应商信息
xbot_visual.desktop.input(window=""0"", element=""供应商输入框"", text=""供应商名称"")
# 填写商品信息
xbot_visual.desktop.input(window=""0"", element=""商品输入框"", text=""商品名称"")
# 填写数量
xbot_visual.desktop.input(window=""0"", element=""数量输入框"", text=""10"")
# 点击保存按钮
xbot_visual.desktop.click(window=""0"", element=""保存按钮"")
``` END",{},[]
在WMS软件中完成接收入库货物并分配库位的操作,"```python
# 打开WMS软件
process_info=xbot_visual.desktop.launch(process_name=""WMS"")
# 点击进入接收入库模块
xbot_visual.desktop.click(window=""0"", element=""接收入库"")
# 选择需要接收入库的货物
xbot_visual.desktop.click(window=""0"", element=""货物名称"")
# 点击确认接收入库
xbot_visual.desktop.click(window=""0"", element=""确认接收入库"")
# 点击进入分配库位模块
xbot_visual.desktop.click(window=""0"", element=""分配库位"")
# 选择需要分配库位的货物
xbot_visual.desktop.click(window=""0"", element=""货物名称"")
# 点击确认分配库位
xbot_visual.desktop.click(window=""0"", element=""确认分配库位"")
``` END",{},[]
在巨益OMS软件中创建新的客户订单,"```python
# 打开巨益OMS软件
process_info=xbot_visual.desktop.launch(process_name=""巨益OMS"")
# 点击进入订单管理模块
xbot_visual.desktop.click(window=""0"", element=""订单管理"")
# 点击新建订单按钮
xbot_visual.desktop.click(window=""0"", element=""新建订单"")
# 在客户名称输入框中输入客户名称
xbot_visual.desktop.input(window=""0"", element=""客户名称输入框"", text=""新客户"")
# 在商品名称输入框中输入商品名称
xbot_visual.desktop.input(window=""0"", element=""商品名称输入框"", text=""商品A"")
# 在数量输入框中输入商品数量
xbot_visual.desktop.input(window=""0"", element=""数量输入框"", text=""1"")
# 点击保存按钮
xbot_visual.desktop.click(window=""0"", element=""保存按钮"")
``` END",{},[]
在西门子MES软件中新建生产工单,"```python
# 打开西门子MES软件
process_info=xbot_visual.desktop.launch(process_name=""西门子MES"")
# 点击进入生产工单管理模块
xbot_visual.desktop.click(window=""0"", element=""生产工单管理"")
# 点击新建工单按钮
xbot_visual.desktop.click(window=""0"", element=""新建工单"")
# 在工单名称输入框中输入工单名称
xbot_visual.desktop.input(window=""0"", element=""工单名称输入框"", text=""生产工单1"")
# 在产品类型下拉框中选择产品类型
xbot_visual.desktop.select_by_text(window=""0"", element=""产品类型下拉框"", text=""产品类型1"")
# 在生产数量输入框中输入生产数量
xbot_visual.desktop.input(window=""0"", element=""生产数量输入框"", text=""100"")
# 点击保存按钮，新建生产工单
xbot_visual.desktop.click(window=""0"", element=""保存按钮"")
``` END",{},[]
在探迹SCRM软件中导入新的社交媒体客户数据并进行标签分类，比如来自twitter,"```python
# 打开探迹SCRM软件
process_info=xbot_visual.desktop.launch(process_name=""探迹SCRM"")
# 点击进入客户管理模块
xbot_visual.desktop.click(window=""0"", element=""客户管理"")
# 点击导入客户数据按钮
xbot_visual.desktop.click(window=""0"", element=""导入客户数据"")
# 在弹出的文件选择窗口中，选择要导入的数据文件
xbot_visual.desktop.input(window=""0"", element=""文件路径输入框"", text=""C:\\Users\\User\\Desktop\\客户数据.csv"")
# 点击确认导入按钮
xbot_visual.desktop.click(window=""0"", element=""确认导入"")
# 点击进入标签管理模块
xbot_visual.desktop.click(window=""0"", element=""标签管理"")
# 在标签列表中，选择""来自twitter""标签
xbot_visual.desktop.click(window=""0"", element=""来自twitter"")
# 点击确认添加标签按钮
xbot_visual.desktop.click(window=""0"", element=""确认添加标签"")
``` END",{},[]
在CRM软件中创建新的销售线索并进行追踪,"```python
# 打开CRM软件
process_info=xbot_visual.desktop.launch(process_name=""CRM"")
# 点击进入销售线索模块
xbot_visual.desktop.click(window=""0"", element=""销售线索"")
# 点击创建新的销售线索
xbot_visual.desktop.click(window=""0"", element=""创建新的销售线索"")
# 在姓名输入框中输入客户姓名
xbot_visual.desktop.input(window=""0"", element=""姓名输入框"", text=""客户姓名"")
# 在电话输入框中输入客户电话
xbot_visual.desktop.input(window=""0"", element=""电话输入框"", text=""客户电话"")
# 在地址输入框中输入客户地址
xbot_visual.desktop.input(window=""0"", element=""地址输入框"", text=""客户地址"")
# 点击保存销售线索
xbot_visual.desktop.click(window=""0"", element=""保存销售线索"")
# 点击进入销售线索追踪模块
xbot_visual.desktop.click(window=""0"", element=""销售线索追踪"")
# 在搜索框中输入客户姓名
xbot_visual.desktop.input(window=""0"", element=""搜索框"", text=""客户姓名"")
# 点击搜索按钮
xbot_visual.desktop.click(window=""0"", element=""搜索按钮"")
# 获取第一个搜索结果对象
search_result = xbot_visual.desktop.find_element(window=""0"", element=""搜索结果"")
# 点击第一个搜索结果，进入客户详情页
xbot_visual.desktop.click(window=""0"", element=search_result)
# 点击进入客户跟进记录模块
xbot_visual.desktop.click(window=""0"", element=""客户跟进记录"")
# 点击添加新的跟进记录
xbot_visual.desktop.click(window=""0"", element=""添加新的跟进记录"")
# 在跟进内容输入框中输入跟进内容
xbot_visual.desktop.input(window=""0"", element=""跟进内容输入框"", text=""跟进内容"")
# 点击保存跟进记录
xbot_visual.desktop.click(window=""0"", element=""保存跟进记录"")
# 点击返回客户详情页
xbot_visual.desktop.click(window=""0"", element=""返回按钮"")
# 点击返回销售线索追踪模块
xbot_visual.desktop.click(window=""0"", element=""返回按钮"")
``` END",{},[]
在致远OA软件中提交一个请假申请,"```python
# 打开致远OA软件
process_info=xbot_visual.desktop.launch(process_name=""致远OA"")
# 点击进入请假申请页面
xbot_visual.desktop.click(window=""0"", element=""请假申请"")
# 填写请假开始时间
xbot_visual.desktop.input(window=""0"", element=""开始时间"", text=""2022-01-01"")
# 填写请假结束时间
xbot_visual.desktop.input(window=""0"", element=""结束时间"", text=""2022-01-03"")
# 填写请假事由
xbot_visual.desktop.input(window=""0"", element=""请假事由"", text=""身体不适"")
# 点击提交按钮
xbot_visual.desktop.click(window=""0"", element=""提交"")
``` END",{},[]
在Ultimus BPM软件中提交一个请假申请,"```python
# 打开Ultimus BPM软件
process_info=xbot_visual.desktop.launch(process_name=""Ultimus BPM"")
# 点击进入请假申请页面
xbot_visual.desktop.click(window=""0"", element=""请假申请"")
# 填写请假开始时间
xbot_visual.desktop.input(window=""0"", element=""请假开始时间"", text=""2022-01-01"")
# 填写请假结束时间
xbot_visual.desktop.input(window=""0"", element=""请假结束时间"", text=""2022-01-03"")
# 填写请假原因
xbot_visual.desktop.input(window=""0"", element=""请假原因"", text=""身体不适"")
# 点击提交按钮
xbot_visual.desktop.click(window=""0"", element=""提交"")
``` END",{},[]
将当前激活窗口隐藏,"```python
# 获取当前激活窗口
active_window = xbot_visual.desktop.get_active()
# 隐藏窗口
xbot_visual.desktop.set_visibility(window=active_window, visibility=""hide"")
``` END",{},[]
将当前激活窗口移动到桌面左上角,"```python
# 获取当前激活窗口
active_window = xbot_visual.desktop.get_active()
# 将当前激活窗口移动到桌面左上角
xbot_visual.desktop.move(window=active_window, x=""0"", y=""0"")
``` END",{},[]
关闭当前激活窗口,"```python
# 获取当前激活窗口
active_window = xbot_visual.desktop.get_active()
# 关闭当前激活窗口
xbot_visual.desktop.close(window=active_window)
``` END",{},[]
在QQ聊天软件中，获取特定好友的最近10条聊天记录，并将其写入到记事本中,"```python
# 打开QQ聊天软件
process_info=xbot_visual.desktop.launch(process_name=""QQ"")
# 点击进入特定好友的聊天窗口
xbot_visual.desktop.click(window=""0"", element=""特定好友聊天窗口"")
# 遍历聊天记录元素列表
for index, element in enumerate(xbot_visual.desktop.iter_all_elements(window=""0"", element=""聊天记录元素"")):
    # 获取聊天记录内容
    chat_content = xbot_visual.desktop.get_attribute(window=""0"", element=element, attribute_name=""text"")
    # 将聊天记录内容写入到记事本中
    xbot_visual.desktop.input(window=""0"", element=""记事本编辑区"", text=chat_content)
    # 按下回车键换行
    xbot_visual.keyboard.send_keys(keys=""{enter}"")
    # 判断是否已经获取了10条聊天记录
    if index >= 9:
        # 如果已经获取了10条聊天记录，则退出循环
        break
``` END",{},[]
在西门子MES中，自动生成每月的生产效率报告,"```python
# 打开西门子MES软件
process_info=xbot_visual.desktop.launch(process_name=""西门子MES"")
# 点击进入报告生成模块
xbot_visual.desktop.click(window=""0"", element=""报告生成"")
# 选择生成月报告
xbot_visual.desktop.select_by_text(window=""0"", element=""报告类型"", text=""月报告"")
# 点击生成报告按钮
xbot_visual.desktop.click(window=""0"", element=""生成报告"")
# 等待报告生成完成
xbot_visual.desktop.wait_until_page_loaded(page=""报告生成"")
# 点击保存报告按钮
xbot_visual.desktop.click(window=""0"", element=""保存报告"")
# 在弹出的保存对话框中，输入报告名称
xbot_visual.desktop.input(window=""0"", element=""文件名输入框"", text=""生产效率报告"")
# 点击保存按钮
xbot_visual.desktop.click(window=""0"", element=""保存按钮"")
``` END",{'err_funcs': ['xbot_visual.desktop.wait_until_page_loaded']},['err_funcs']
在西门子MES中，设置每天上午8点自动检查所有设备的工作状况,"```python
# 打开西门子MES软件
process_info=xbot_visual.desktop.launch(process_name=""西门子MES"")
# 点击进入设备管理模块
xbot_visual.desktop.click(window=""0"", element=""设备管理"")
# 点击进入定时任务设置模块
xbot_visual.desktop.click(window=""0"", element=""定时任务设置"")
# 点击创建新的定时任务
xbot_visual.desktop.click(window=""0"", element=""创建新的定时任务"")
# 在定时任务名称输入框中输入任务名称
xbot_visual.desktop.input(window=""0"", element=""定时任务名称"", text=""设备工作状况检查"")
# 在定时任务时间设置框中输入上午8点
xbot_visual.desktop.input(window=""0"", element=""定时任务时间设置"", text=""08:00"")
# 在定时任务周期设置框中选择每天
xbot_visual.desktop.select_by_text(window=""0"", element=""定时任务周期设置"", text=""每天"")
# 在定时任务执行模块选择框中选择设备工作状况检查
xbot_visual.desktop.select_by_text(window=""0"", element=""定时任务执行模块选择"", text=""设备工作状况检查"")
# 点击保存定时任务
xbot_visual.desktop.click(window=""0"", element=""保存定时任务"")
# 关闭西门子MES软件
xbot_visual.desktop.close(window=""0"")
``` END",{},[]
在帆软BI中，自动为每个部门生成月度工作绩效报告,"```python
# 打开帆软BI软件
process_info=xbot_visual.desktop.launch(process_name=""帆软BI"")
# 点击进入报表设计模式
xbot_visual.desktop.click(window=""0"", element=""报表设计模式"")
# 遍历部门列表
for department in xbot_visual.desktop.iter_all_elements(window=""0"", element=""部门列表""):
    # 选择部门
    xbot_visual.desktop.click(window=""0"", element=department)
    # 点击生成报告按钮
    xbot_visual.desktop.click(window=""0"", element=""生成报告按钮"")
    # 设置报告保存路径
    xbot_visual.desktop.input(window=""0"", element=""保存路径输入框"", text=""C:\\Reports\\{0}_月度工作绩效报告.pdf"".format(department))
    # 点击保存按钮
    xbot_visual.desktop.click(window=""0"", element=""保存按钮"")
    # 点击确认覆盖提示
    xbot_visual.desktop.click(window=""0"", element=""确认覆盖提示"")
    # 点击关闭报告
    xbot_visual.desktop.click(window=""0"", element=""关闭报告"")
# 关闭帆软BI软件
xbot_visual.desktop.close(window=""0"")
``` END",{},[]
在帆软BI中，设置每季度生成财务数据报告,"```python
# 打开帆软BI软件
process_info=xbot_visual.desktop.launch(process_name=""帆软BI"")
# 点击进入报表设置页面
xbot_visual.desktop.click(window=""0"", element=""报表设置"")
# 选择季度报表生成频率
xbot_visual.desktop.select_by_text(window=""0"", element=""报表生成频率"", text=""每季度"")
# 点击保存设置
xbot_visual.desktop.click(window=""0"", element=""保存设置"")
# 关闭帆软BI软件
xbot_visual.desktop.close(window=""0"")
``` END",{},[]
在九恒星中，自动为所有新添加的固定资产生成折旧表,"```python
# 打开九恒星软件
process_info=xbot_visual.desktop.launch(process_name=""九恒星"")
# 点击进入固定资产管理模块
xbot_visual.desktop.click(window=""0"", element=""固定资产管理"")
# 点击进入折旧表生成模块
xbot_visual.desktop.click(window=""0"", element=""折旧表生成"")
# 遍历所有新添加的固定资产对象
for asset in xbot_visual.desktop.iter_all_elements(window=""0"", element=""新添加的固定资产""):
    # 双击打开固定资产详情窗口
    xbot_visual.desktop.click(window=""0"", element=asset, clicks=""dbclick"")
    # 点击生成折旧表按钮
    xbot_visual.desktop.click(window=""0"", element=""生成折旧表"")
    # 关闭固定资产详情窗口
    xbot_visual.desktop.click(window=""0"", element=""关闭"")
``` END",{},[]
在九恒星中，设置每月25日自动对所有员工进行工资发放,"```python
# 打开九恒星软件
process_info=xbot_visual.desktop.launch(process_name=""九恒星"")
# 点击进入工资管理模块
xbot_visual.desktop.click(window=""0"", element=""工资管理"")
# 点击进入员工列表
xbot_visual.desktop.click(window=""0"", element=""员工列表"")
# 点击进入工资发放设置
xbot_visual.desktop.click(window=""0"", element=""工资发放设置"")
# 点击设置自动发放
xbot_visual.desktop.click(window=""0"", element=""设置自动发放"")
# 设置发放日期为25
xbot_visual.desktop.input(window=""0"", element=""发放日期"", text=""25"")
# 点击保存
xbot_visual.desktop.click(window=""0"", element=""保存"")
``` END",{},[]
微信窗口已经打开登陆了，现在我需要自动实时为所有收到的转账消息发送“已收到，谢谢”回复,"```python
# 获取微信窗口
wechat_window = xbot_visual.desktop.get(title=""微信"")
# 循环
for message in xbot_visual.desktop.iter_all_elements(window=""0"", element=""微信消息元素""):
    # 获取消息内容
    message_text = xbot_visual.desktop.get_attribute(window=""0"", element=message, attribute_name=""text"")
    # 判断是否为转账消息
    if ""转账"" in message_text:
        # 点击消息进入聊天窗口
        xbot_visual.desktop.click(window=""0"", element=message)
        # 在聊天输入框中输入回复内容
        xbot_visual.desktop.input(window=""0"", element=""微信聊天输入框"", text=""已收到，谢谢"")
        # 点击发送按钮
        xbot_visual.desktop.click(window=""0"", element=""微信发送按钮"")
        # 回到微信主窗口
        xbot_visual.desktop.set_focus(window=wechat_window)
``` END",{'err_funcs': ['xbot_visual.desktop.set_focus']},['err_funcs']
在帆软BI中，实时监控并预警网站访问量突增情况,"```python
# 打开帆软BI
process_info=xbot_visual.desktop.launch(process_name=""帆软BI"")
# 点击进入实时监控模块
xbot_visual.desktop.click(window=""0"", element=""实时监控"")
# 点击进入网站访问量监控
xbot_visual.desktop.click(window=""0"", element=""网站访问量"")
# 获取当前网站访问量
web_traffic = xbot_visual.desktop.get_attribute(window=""0"", element=""网站访问量"", attribute_name=""text"")
# 判断网站访问量是否突增
if int(web_traffic) > 1000:
    # 网站访问量突增，输出预警信息
    print(""网站访问量突增，当前访问量为：{}"".format(web_traffic))
# 关闭帆软BI
xbot_visual.desktop.close_all()
```
  END",{'err_funcs': ['xbot_visual.desktop.close_all']},['err_funcs']
在微信中，自动回复所有新消息，内容为“当前不在线，稍后回复”,"```python
# 打开微信
process_info=xbot_visual.desktop.launch(process_name=""微信"")
# 遍历所有新消息对象
for new_message in xbot_visual.desktop.iter_all_elements(window=""0"", element=""新消息""):
    # 点击新消息，进入聊天窗口
    xbot_visual.desktop.click(window=""0"", element=new_message)
    # 在聊天输入框中输入回复内容
    xbot_visual.desktop.input(window=""0"", element=""聊天输入框"", text=""当前不在线，稍后回复"")
    # 点击发送按钮，发送回复
    xbot_visual.desktop.click(window=""0"", element=""发送按钮"")
# 关闭微信
xbot_visual.desktop.close(window=""0"")
``` END",{},[]
在蓝凌OA中，自动提交本月的出差报销单，附加相关票据图片,"```python
# 打开蓝凌OA
process_info=xbot_visual.desktop.launch(process_name=""蓝凌OA"")
# 点击进入出差报销单模块
xbot_visual.desktop.click(window=""0"", element=""出差报销单"")
# 点击进入本月报销单列表
xbot_visual.desktop.click(window=""0"", element=""本月报销单"")
# 遍历报销单列表
for ele in xbot_visual.desktop.iter_all_elements(window=""0"", element=""报销单列表""):
    # 点击进入报销单详情
    xbot_visual.desktop.click(window=""0"", element=ele)
    # 点击上传票据按钮
    xbot_visual.desktop.click(window=""0"", element=""上传票据"")
    # 在文件选择窗口中，输入票据图片路径
    xbot_visual.desktop.input(window=""0"", element=""文件路径输入框"", text=""C:\\票据图片.png"")
    # 点击确认上传
    xbot_visual.desktop.click(window=""0"", element=""确认上传"")
    # 点击返回报销单列表
    xbot_visual.desktop.click(window=""0"", element=""返回"")
    # 点击返回出差报销单模块
    xbot_visual.desktop.click(window=""0"", element=""返回"")
``` END",{},[]
在纷享销客CRM中，对所有新录入的客户数据进行清洗，去除重复信息,"```python
# 打开纷享销客CRM软件
process_info=xbot_visual.desktop.launch(process_name=""纷享销客CRM"")
# 点击进入客户管理模块
xbot_visual.desktop.click(window=""0"", element=""客户管理"")
# 点击进入客户列表
xbot_visual.desktop.click(window=""0"", element=""客户列表"")
# 点击进入新录入客户筛选条件
xbot_visual.desktop.click(window=""0"", element=""新录入客户"")
# 点击进入清洗按钮
xbot_visual.desktop.click(window=""0"", element=""清洗"")
# 等待清洗完成
xbot_visual.desktop.wait_update(window=""0"", element=""清洗"", prop_name=""text"")
# 点击进入去重按钮
xbot_visual.desktop.click(window=""0"", element=""去重"")
# 等待去重完成
xbot_visual.desktop.wait_update(window=""0"", element=""去重"", prop_name=""text"")
``` END","{'err_funcs': ['xbot_visual.desktop.wait_update', 'xbot_visual.desktop.wait_update']}",['err_funcs']
在巨益OMS中，自动为所有新订单匹配最近的发货仓库,"```python
# 打开巨益OMS软件
process_info=xbot_visual.desktop.launch(process_name=""巨益OMS"")
# 点击进入订单管理模块
xbot_visual.desktop.click(window=""0"", element=""订单管理"")
# 点击进入新订单模块
xbot_visual.desktop.click(window=""0"", element=""新订单"")
# 遍历所有新订单对象
for order in xbot_visual.desktop.iter_all_elements(window=""0"", element=""新订单对象""):
    # 点击进入订单详情
    xbot_visual.desktop.click(window=""0"", element=order)
    # 获取订单信息
    order_info = xbot_visual.desktop.get_attribute(window=""0"", element=""订单信息"", attribute_name=""text"")
    # 获取发货仓库信息
    warehouse_info = xbot_visual.desktop.get_attribute(window=""0"", element=""发货仓库信息"", attribute_name=""text"")
    # 打印订单信息
    print(""订单信息："" + order_info + ""，发货仓库信息："" + warehouse_info)
    # 点击保存按钮
    xbot_visual.desktop.click(window=""0"", element=""保存"")
# 关闭巨益OMS软件
xbot_visual.desktop.close(window=""0"")
``` END",{},[]
打开旺店通ERP，对采购模块进行数据录入，设置默认供应商为“XX公司”,"```python
# 打开旺店通ERP
process_info=xbot_visual.desktop.launch(process_name=""旺店通ERP"")
# 点击进入采购模块
xbot_visual.desktop.click(window=""0"", element=""采购模块"")
# 设置默认供应商为“XX公司”
xbot_visual.desktop.input(window=""0"", element=""默认供应商输入框"", text=""XX公司"")
# 对采购模块进行数据录入
xbot_visual.desktop.input(window=""0"", element=""采购模块输入框"", text=""采购数据"")
# 点击保存按钮
xbot_visual.desktop.click(window=""0"", element=""保存按钮"")
``` END",{},[]
MATLAB中自动打开一个新的脚本，编写一个简单的计算函数，并将其保存到指定的文件夹中,"```python
# 打开MATLAB软件
process_info=xbot_visual.desktop.launch(process_name=""MATLAB"")
# 点击新建脚本按钮
xbot_visual.desktop.click(window=""0"", element=""新建脚本按钮"")
# 在脚本编辑区输入计算函数
xbot_visual.desktop.input(window=""0"", element=""脚本编辑区"", text=""function result = myFunction(a, b)\nresult = a + b;\nend"")
# 点击保存按钮
xbot_visual.desktop.click(window=""0"", element=""保存按钮"")
# 在保存对话框中输入文件名
xbot_visual.desktop.input(window=""0"", element=""文件名输入框"", text=""myFunction.m"")
# 在保存对话框中输入文件夹路径
xbot_visual.desktop.input(window=""0"", element=""文件夹路径输入框"", text=""C:\\MyScripts"")
# 点击保存对话框中的保存按钮
xbot_visual.desktop.click(window=""0"", element=""保存对话框保存按钮"")
``` END",{},[]
查找特定的Skype联系人，然后自动发送一条预设的消息，并将发送成功的确认信息复制到记事本,"```python
# 打开Skype
process_info=xbot_visual.desktop.launch(process_name=""Skype"")
# 在搜索框中输入联系人名称
xbot_visual.desktop.input(window=""0"", element=""Skype搜索框"", text=""特定的Skype联系人"")
# 点击搜索按钮
xbot_visual.desktop.click(window=""0"", element=""Skype搜索按钮"")
# 点击进入联系人对话框
xbot_visual.desktop.click(window=""0"", element=""特定的Skype联系人对话框"")
# 在消息输入框中输入预设的消息
xbot_visual.desktop.input(window=""0"", element=""Skype消息输入框"", text=""这是一条预设的消息"")
# 点击发送按钮
xbot_visual.desktop.click(window=""0"", element=""Skype发送按钮"")
# 等待发送成功的确认信息出现
xbot_visual.desktop.wait_element(window=""0"", element=""Skype发送成功确认信息"")
# 获取发送成功的确认信息文本
success_message = xbot_visual.desktop.get_attribute(window=""0"", element=""Skype发送成功确认信息"", attribute_name=""text"")
# 将发送成功的确认信息文本复制到记事本
xbot_visual.desktop.input(window=""0"", element=""记事本编辑区"", text=success_message)
``` END",{'err_funcs': ['xbot_visual.desktop.wait_element']},['err_funcs']
在Photoshop中打开指定的图片，然后使用特定的工具对图片进行修改，保存后将修改后的图片路径复制到记事本,"```python
# 打开Photoshop
process_info=xbot_visual.desktop.launch(process_name=""Photoshop"")
# 点击文件菜单
xbot_visual.desktop.click(window=""0"", element=""文件菜单"")
# 点击打开选项
xbot_visual.desktop.click(window=""0"", element=""打开选项"")
# 在文件路径输入框中输入指定的图片路径
xbot_visual.desktop.input(window=""0"", element=""文件路径输入框"", text=""C:\\path\\to\\image.jpg"")
# 点击打开按钮
xbot_visual.desktop.click(window=""0"", element=""打开按钮"")
# 选择特定的工具，比如画笔工具
xbot_visual.desktop.click(window=""0"", element=""画笔工具"")
# 对图片进行修改
# 点击保存选项
xbot_visual.desktop.click(window=""0"", element=""保存选项"")
# 在保存对话框中输入保存路径和文件名
xbot_visual.desktop.input(window=""0"", element=""保存路径输入框"", text=""C:\\path\\to\\modified_image.jpg"")
# 点击保存按钮
xbot_visual.desktop.click(window=""0"", element=""保存按钮"")
# 点击关闭按钮
xbot_visual.desktop.click(window=""0"", element=""关闭按钮"")
# 打开记事本
xbot_visual.desktop.click(window=""0"", element=""记事本"")
# 将保存后的图片路径复制到记事本
xbot_visual.desktop.input(window=""0"", element=""记事本编辑区"", text=""C:\\path\\to\\modified_image.jpg"")
``` END",{},[]
在Adobe Reader中打开指定的PDF文件，然后将其中的文本内容复制到记事本,"```python
# 打开Adobe Reader
process_info=xbot_visual.desktop.launch(process_name=""Adobe Reader"")
# 点击打开文件按钮
xbot_visual.desktop.click(window=""0"", element=""打开文件按钮"")
# 在文件路径输入框中输入指定的PDF文件路径
xbot_visual.desktop.input(window=""0"", element=""文件路径输入框"", text=""C:\\example.pdf"")
# 点击打开按钮
xbot_visual.desktop.click(window=""0"", element=""打开按钮"")
# 点击复制按钮
xbot_visual.desktop.click(window=""0"", element=""复制按钮"")
# 打开记事本
xbot_visual.desktop.click(window=""0"", element=""记事本"")
# 在记事本中粘贴文本内容
xbot_visual.desktop.click(window=""0"", element=""粘贴按钮"")
``` END",{},[]
在Zoom中自动加入指定的会议，然后将会议的屏幕分享进行截图并保存,"```python
# 打开Zoom软件
process_info=xbot_visual.desktop.launch(process_name=""Zoom"")
# 点击加入会议按钮
xbot_visual.desktop.click(window=""0"", element=""加入会议"")
# 在会议ID输入框中输入指定的会议ID
xbot_visual.desktop.input(window=""0"", element=""会议ID输入框"", text=""1234567890"")
# 点击加入按钮
xbot_visual.desktop.click(window=""0"", element=""加入"")
# 点击屏幕分享按钮
xbot_visual.desktop.click(window=""0"", element=""屏幕分享"")
# 打开截图软件
screenshot_process_info=xbot_visual.desktop.launch(process_name=""截图软件"")
# 在截图软件中点击截图按钮
xbot_visual.desktop.click(window=""0"", element=""截图按钮"")
# 在截图软件中点击保存按钮
xbot_visual.desktop.click(window=""0"", element=""保存按钮"")
# 在保存对话框中输入文件名
xbot_visual.desktop.input(window=""0"", element=""文件名输入框"", text=""zoom_screenshot"")
# 在保存对话框中输入保存路径
xbot_visual.desktop.input(window=""0"", element=""保存路径输入框"", text=""C:\\Users\\User\\Pictures"")
# 在保存对话框中点击确认按钮
xbot_visual.desktop.click(window=""0"", element=""确认按钮"")
``` END",{},[]
在Adobe Acrobat Reader中打开指定的PDF文件，然后进行截屏并保存,"```python
# 打开Adobe Acrobat Reader
process_info=xbot_visual.desktop.launch(process_name=""Adobe Acrobat Reader"")
# 点击打开文件按钮
xbot_visual.desktop.click(window=""0"", element=""打开文件按钮"")
# 在文件路径输入框中输入指定的PDF文件路径
xbot_visual.desktop.input(window=""0"", element=""文件路径输入框"", text=""C:\\example.pdf"")
# 点击打开按钮
xbot_visual.desktop.click(window=""0"", element=""打开按钮"")
# 等待PDF文件加载
xbot_visual.desktop.wait_window(window=""PDF文件"", state=""存在"")
# 截屏PDF文件
xbot_visual.desktop.screenshot_element(window=""PDF文件"", element=""PDF文件"", file_folder=""C:\\"", file_name=""pdf_screenshot.png"")
``` END",{'err_funcs': ['xbot_visual.desktop.wait_window']},['err_funcs']
在Adobe Photoshop中自动化打开特定图片文件，对其进行预设的编辑操作，例如调整亮度、对比度等，然后保存并关闭,"```python
# 打开Adobe Photoshop
process_info=xbot_visual.desktop.launch(process_name=""Adobe Photoshop"")
# 点击文件菜单
xbot_visual.desktop.click(window=""0"", element=""文件菜单"")
# 点击打开选项
xbot_visual.desktop.click(window=""0"", element=""打开选项"")
# 在文件选择对话框中输入特定图片文件的路径
xbot_visual.desktop.input(window=""0"", element=""文件路径输入框"", text=""C:\\path\\to\\image.jpg"")
# 点击打开按钮
xbot_visual.desktop.click(window=""0"", element=""打开按钮"")
# 在菜单栏中点击图像选项
xbot_visual.desktop.click(window=""0"", element=""图像选项"")
# 在下拉菜单中选择调整选项
xbot_visual.desktop.select_by_text(window=""0"", element=""调整选项"", text=""调整"")
# 在调整面板中找到亮度选项
xbot_visual.desktop.input(window=""0"", element=""亮度输入框"", text=""50"")
# 在调整面板中找到对比度选项
xbot_visual.desktop.input(window=""0"", element=""对比度输入框"", text=""50"")
# 点击确定按钮
xbot_visual.desktop.click(window=""0"", element=""确定按钮"")
# 在菜单栏中点击文件选项
xbot_visual.desktop.click(window=""0"", element=""文件选项"")
# 在下拉菜单中选择保存选项
xbot_visual.desktop.select_by_text(window=""0"", element=""保存选项"", text=""保存"")
# 在保存对话框中输入保存路径和文件名
xbot_visual.desktop.input(window=""0"", element=""保存路径输入框"", text=""C:\\path\\to\\edited_image.jpg"")
# 点击保存按钮
xbot_visual.desktop.click(window=""0"", element=""保存按钮"")
# 在菜单栏中点击文件选项
xbot_visual.desktop.click(window=""0"", element=""文件选项"")
# 在下拉菜单中选择关闭选项
xbot_visual.desktop.select_by_text(window=""0"", element=""关闭选项"", text=""关闭"")
``` END",{},[]
在Skype中自动拨打指定的电话号码，然后挂断,"```python
# 打开Skype软件
process_info=xbot_visual.desktop.launch(process_name=""Skype"")
# 点击拨号按钮
xbot_visual.desktop.click(window=""0"", element=""拨号按钮"")
# 在电话号码输入框中输入指定的电话号码
xbot_visual.desktop.input(window=""0"", element=""电话号码输入框"", text=""123456789"")
# 点击拨打按钮
xbot_visual.desktop.click(window=""0"", element=""拨打按钮"")
# 等待一段时间，模拟通话
xbot_visual.desktop.input(window=""0"", element=""电话号码输入框"", text=""123456789"")
# 点击挂断按钮
xbot_visual.desktop.click(window=""0"", element=""挂断按钮"")
``` END",{},[]
在Slack上自动打开指定的频道，上传并分享指定的文件,"```python
# 打开Slack软件
process_info=xbot_visual.desktop.launch(process_name=""Slack"")
# 点击进入指定的频道
xbot_visual.desktop.click(window=""0"", element=""指定的频道"")
# 点击上传文件按钮
xbot_visual.desktop.click(window=""0"", element=""上传文件按钮"")
# 在文件选择窗口中输入文件路径
xbot_visual.desktop.input(window=""0"", element=""文件路径输入框"", text=""C:\\example.txt"")
# 点击确认上传按钮
xbot_visual.desktop.click(window=""0"", element=""确认上传按钮"")
# 点击分享文件按钮
xbot_visual.desktop.click(window=""0"", element=""分享文件按钮"")
``` END",{},[]
在钉钉上自动打开指定的讨论组，将指定的文件拖入并发送,"```python
# 打开钉钉
process_info=xbot_visual.desktop.launch(process_name=""钉钉"")
# 点击进入指定的讨论组
xbot_visual.desktop.click(window=""0"", element=""指定的讨论组"")
# 拖拽文件到讨论组窗口
xbot_visual.desktop.drag_to_element(window=""0"", element=""指定的文件"", target=""讨论组窗口"")
# 点击发送按钮
xbot_visual.desktop.click(window=""0"", element=""发送按钮"")
``` END",{},[]
在Adobe Premiere中自动导入指定文件夹的视频，按照预设的剪辑模板进行剪辑，并导出到指定位置,"```python
# 打开Adobe Premiere
process_info=xbot_visual.desktop.launch(process_name=""Adobe Premiere"")
# 点击导入按钮
xbot_visual.desktop.click(window=""0"", element=""导入按钮"")
# 在文件选择窗口中输入文件夹路径
xbot_visual.desktop.input(window=""0"", element=""文件路径输入框"", text=""C:\\Videos"")
# 点击确认导入按钮
xbot_visual.desktop.click(window=""0"", element=""确认导入按钮"")
# 点击新建项目按钮
xbot_visual.desktop.click(window=""0"", element=""新建项目按钮"")
# 选择剪辑模板
xbot_visual.desktop.select_by_text(window=""0"", element=""剪辑模板下拉框"", text=""模板1"")
# 遍历视频列表
for video in xbot_visual.desktop.iter_all_elements(window=""0"", element=""视频列表""):
    # 双击视频，将其添加到时间线
    xbot_visual.desktop.click(window=""0"", element=video, clicks=""dbclick"")
# 点击导出按钮
xbot_visual.desktop.click(window=""0"", element=""导出按钮"")
# 在导出设置窗口中输入导出路径
xbot_visual.desktop.input(window=""0"", element=""导出路径输入框"", text=""C:\\ExportedVideos"")
# 点击确认导出按钮
xbot_visual.desktop.click(window=""0"", element=""确认导出按钮"")
``` END",{},[]
通过自动化工具，登录到Slack应用程序，并获取所有的频道列表，并将这些信息写入到已打开的记事本中,"```python
# 打开Slack应用程序
process_info=xbot_visual.desktop.launch(process_name=""Slack"")
# 点击进入Slack登录界面
xbot_visual.desktop.click(window=""0"", element=""Slack登录界面"")
# 输入Slack账号
xbot_visual.desktop.input(window=""0"", element=""账号输入框"", text=""username"")
# 输入Slack密码
xbot_visual.desktop.input_password(window=""0"", element=""密码输入框"", password=""password"")
# 点击登录按钮
xbot_visual.desktop.click(window=""0"", element=""登录按钮"")
# 点击进入Slack主界面
xbot_visual.desktop.click(window=""0"", element=""Slack主界面"")
# 点击进入频道列表
xbot_visual.desktop.click(window=""0"", element=""频道列表"")
# 批量获取频道列表中的信息，返回的数据第一列为频道名称，第二列为频道人数
channel_list=xbot_visual.desktop.batch_get_attribute(window=""0"", element=""频道列表"", attribute_name=""text"")
# 遍历返回的数据
for channel in channel_list:
    # 将频道信息写入到已打开的记事本中
    xbot_visual.desktop.input(window=""0"", element=""记事本输入框"", text=channel[0]+"" ""+channel[1])
``` END",{'err_funcs': ['xbot_visual.desktop.batch_get_attribute']},['err_funcs']
在Spotify应用中搜索特定的歌曲或者歌手，并将查询结果的歌曲列表写入到记事本中,"```python
# 打开Spotify应用
process_info=xbot_visual.desktop.launch(process_name=""Spotify"")
# 在搜索框中输入特定的歌曲或者歌手
xbot_visual.desktop.input(window=""0"", element=""Spotify搜索框"", text=""歌曲或者歌手名称"")
# 点击搜索按钮
xbot_visual.desktop.click(window=""0"", element=""Spotify搜索按钮"")
# 获取查询结果的歌曲列表
song_list = xbot_visual.desktop.get_attribute(window=""0"", element=""查询结果的歌曲列表"", attribute_name=""text"")
# 将歌曲列表写入到记事本中
xbot_visual.desktop.input(window=""0"", element=""记事本编辑区"", text=song_list)
``` END",{},[]
在QQ音乐中自动创建一个新的歌单，并添加特定的歌曲到歌单中,"```python
# 打开QQ音乐
process_info=xbot_visual.desktop.launch(process_name=""QQ音乐"")
# 点击进入歌单页面
xbot_visual.desktop.click(window=""0"", element=""歌单"")
# 点击创建新歌单按钮
xbot_visual.desktop.click(window=""0"", element=""创建新歌单"")
# 在弹出的对话框中输入歌单名称
xbot_visual.desktop.input(window=""0"", element=""歌单名称输入框"", text=""My Favorite Songs"")
# 点击确认创建歌单
xbot_visual.desktop.click(window=""0"", element=""确认创建"")
# 点击进入歌曲添加页面
xbot_visual.desktop.click(window=""0"", element=""添加歌曲"")
# 循环添加歌曲
for song in [""song1"", ""song2"", ""song3""]:
    # 在搜索框中输入歌曲名称
    xbot_visual.desktop.input(window=""0"", element=""搜索框"", text=song)
    # 点击搜索按钮
    xbot_visual.desktop.click(window=""0"", element=""搜索"")
    # 勾选搜索结果中的第一首歌曲
    xbot_visual.desktop.click(window=""0"", element=""勾选歌曲"")
    # 点击添加到歌单按钮
    xbot_visual.desktop.click(window=""0"", element=""添加到歌单"")
    # 选择刚创建的歌单
    xbot_visual.desktop.click(window=""0"", element=""My Favorite Songs"")
    # 点击确认添加
    xbot_visual.desktop.click(window=""0"", element=""确认添加"")
    # 清空搜索框
    xbot_visual.desktop.input(window=""0"", element=""搜索框"", text="""")
# 关闭QQ音乐
xbot_visual.desktop.close(window=""0"")
``` END",{},[]
在Skype中启动一个新的视频通话，添加指定的联系人，然后结束通话，并验证通话是否被正确启动和结束,"```python
# 打开Skype
process_info=xbot_visual.desktop.launch(process_name=""Skype"")
# 点击视频通话按钮，启动一个新的视频通话
xbot_visual.desktop.click(window=""0"", element=""视频通话按钮"")
# 在搜索框中输入指定的联系人
xbot_visual.desktop.input(window=""0"", element=""搜索框"", text=""指定的联系人"")
# 点击添加按钮，将指定的联系人添加到视频通话中
xbot_visual.desktop.click(window=""0"", element=""添加按钮"")
# 点击开始通话按钮
xbot_visual.desktop.click(window=""0"", element=""开始通话按钮"")
# 判断视频通话是否被正确启动
if xbot_visual.desktop.get_attribute(window=""0"", element=""视频通话状态"", attribute_name=""text"") == ""通话中"":
    # 打印视频通话启动成功
    print(""视频通话启动成功"")
# 点击结束通话按钮
xbot_visual.desktop.click(window=""0"", element=""结束通话按钮"")
# 判断视频通话是否被正确结束
if xbot_visual.desktop.get_attribute(window=""0"", element=""视频通话状态"", attribute_name=""text"") == ""未通话"":
    # 打印视频通话结束成功
    print(""视频通话结束成功"")
``` END",{},[]
在Slack中创建一个新的频道，邀请指定的成员，并发送一条消息，然后验证频道是否被正确创建和消息是否被正确发送,"```python
# 打开Slack
process_info=xbot_visual.desktop.launch(process_name=""Slack"")
# 点击进入频道列表
xbot_visual.desktop.click(window=""0"", element=""频道列表"")
# 点击创建新频道按钮
xbot_visual.desktop.click(window=""0"", element=""创建新频道"")
# 在弹出的对话框中输入频道名称
xbot_visual.desktop.input(window=""0"", element=""频道名称输入框"", text=""新频道"")
# 点击邀请成员按钮
xbot_visual.desktop.click(window=""0"", element=""邀请成员"")
# 在弹出的对话框中输入成员名称
xbot_visual.desktop.input(window=""0"", element=""成员名称输入框"", text=""成员1"")
# 选择成员
xbot_visual.desktop.click(window=""0"", element=""成员1"")
# 点击确认邀请按钮
xbot_visual.desktop.click(window=""0"", element=""确认邀请"")
# 点击创建频道按钮
xbot_visual.desktop.click(window=""0"", element=""创建频道"")
# 在新频道中发送一条消息
xbot_visual.desktop.input(window=""0"", element=""消息输入框"", text=""新频道的消息"")
# 点击发送按钮
xbot_visual.desktop.click(window=""0"", element=""发送按钮"")
# 在搜索框中输入频道名称
xbot_visual.desktop.input(window=""0"", element=""搜索框"", text=""新频道"")
# 获取搜索结果
search_result = xbot_visual.desktop.get_attribute(window=""0"", element=""搜索结果"", attribute_name=""text"")
# 判断搜索结果中是否包含频道名称
if ""新频道"" in search_result:
    # 打印搜索结果
    print(search_result)
    # 打印验证信息
    print(""频道创建成功"")
# 否则
else:
    # 打印验证信息
    print(""频道创建失败"")
``` END",{},[]
在Zoom中启动一个新的会议，添加指定的参与者，然后结束会议，并验证会议是否被正确启动和结束,"```python
# 打开Zoom软件
process_info=xbot_visual.desktop.launch(process_name=""Zoom"")
# 点击创建会议按钮
xbot_visual.desktop.click(window=""0"", element=""创建会议"")
# 在搜索框中输入参与者名称
xbot_visual.desktop.input(window=""0"", element=""搜索框"", text=""参与者名称"")
# 选择搜索结果中的参与者
xbot_visual.desktop.click(window=""0"", element=""搜索结果"")
# 点击添加参与者按钮
xbot_visual.desktop.click(window=""0"", element=""添加参与者"")
# 点击开始会议按钮
xbot_visual.desktop.click(window=""0"", element=""开始会议"")
# 判断会议是否被正确启动
if xbot_visual.desktop.get_attribute(window=""0"", element=""会议状态"", attribute_name=""text"") == ""会议中"":
    # 打印会议状态
    print(xbot_visual.desktop.get_attribute(window=""0"", element=""会议状态"", attribute_name=""text""))
    # 点击结束会议按钮
    xbot_visual.desktop.click(window=""0"", element=""结束会议"")
    # 判断会议是否被正确结束
    if xbot_visual.desktop.get_attribute(window=""0"", element=""会议状态"", attribute_name=""text"") == ""已结束"":
        # 打印会议状态
        print(xbot_visual.desktop.get_attribute(window=""0"", element=""会议状态"", attribute_name=""text""))
# 关闭Zoom软件
xbot_visual.desktop.close(window=""0"")
``` END",{},[]
在钉钉应用中检查是否有新的未读消息,"```python
# 打开钉钉
process_info=xbot_visual.desktop.launch(process_name=""钉钉"")
# 检查是否有新的未读消息
if xbot_visual.desktop.contains_string(window=""0"", element=""新消息提醒"", text=""新消息""):
    # 如果有新的未读消息，打印提醒
    print(""您有新的未读消息！"")
# 否则
else:
    # 如果没有新的未读消息，打印提醒
    print(""没有新的未读消息"")
``` END",{'err_funcs': ['xbot_visual.desktop.contains_string']},['err_funcs']
在Skype中查找最近的5个未接电话，并将这些电话的详细信息记录在记事本中,"```python
# 打开Skype
process_info=xbot_visual.desktop.launch(process_name=""Skype"")
# 点击进入未接电话列表
xbot_visual.desktop.click(window=""0"", element=""未接电话"")
# 遍历未接电话对象列表
for index, phone in enumerate(xbot_visual.desktop.iter_all_elements(window=""0"", element=""未接电话对象"")):
    # 如果已经找到5个未接电话
    if index >= 5:
        # 退出遍历
        break
    # 获取电话号码
    phone_number = xbot_visual.desktop.get_attribute(window=""0"", element=phone, attribute_name=""text"")
    # 将电话号码写入记事本
    xbot_visual.desktop.input(window=""0"", element=""记事本编辑区"", text=phone_number)
    # 按下回车键
    xbot_visual.keyboard.send_keys(keys=""{enter}"")
``` END",{},[]
在Spotify中搜索特定的歌曲或艺术家，播放选定的歌曲，并调整音量,"```python
# 打开Spotify软件
process_info=xbot_visual.desktop.launch(process_name=""Spotify"")
# 在搜索框中输入特定的歌曲或艺术家
xbot_visual.desktop.input(window=""0"", element=""Spotify搜索框"", text=""歌曲或艺术家名称"")
# 点击搜索按钮
xbot_visual.desktop.click(window=""0"", element=""Spotify搜索按钮"")
# 点击播放按钮
xbot_visual.desktop.click(window=""0"", element=""Spotify播放按钮"")
# 拖动音量滑块，将音量调整到合适的大小
xbot_visual.desktop.drag_to_element(window=""0"", element=""Spotify音量滑块"", target=""Spotify音量调整"")
``` END",{},[]
利用微信自动传输功能选择并发送特定的文件,"```python
# 打开微信
process_info=xbot_visual.desktop.launch(process_name=""微信"")
# 点击进入文件传输窗口
xbot_visual.desktop.click(window=""0"", element=""文件传输"")
# 点击进入文件选择窗口
xbot_visual.desktop.click(window=""0"", element=""文件选择"")
# 在文件选择窗口中选择特定的文件
xbot_visual.desktop.input(window=""0"", element=""文件路径输入框"", text=""C:\\path\\to\\file"")
# 点击发送按钮
xbot_visual.desktop.click(window=""0"", element=""发送"")
``` END",{},[]
在启动Adobe Photoshop后，将其窗口移动到屏幕中央，然后调整窗口的大小，使其宽度为800，高度为600。打开“文件”菜单，选择“新建”选项，然后在弹出的对话框中输入新文件的名称和大小，最后点击“确定”按钮。,"```python
# 打开Adobe Photoshop
process_info=xbot_visual.desktop.launch(process_name=""Adobe Photoshop"")
# 点击文件菜单
xbot_visual.desktop.click(window=""0"", element=""文件菜单"")
# 选择新建选项
xbot_visual.desktop.click(window=""0"", element=""新建选项"")
# 在弹出的对话框中输入新文件的名称
xbot_visual.desktop.input(window=""0"", element=""文件名称输入框"", text=""new_file"")
# 在弹出的对话框中输入新文件的大小
xbot_visual.desktop.input(window=""0"", element=""文件大小输入框"", text=""800x600"")
# 点击确定按钮
xbot_visual.desktop.click(window=""0"", element=""确定按钮"")
``` END",{},[]
启动Spotify，输入用户名和密码进行登录，然后将其窗口最小化。接着，使用键盘快捷键打开“我的音乐库”页面，然后在搜索框中输入指定的歌曲或歌手名称，最后点击“播放”按钮。,"```python
# 启动Spotify
process_info=xbot_visual.desktop.launch(process_name=""Spotify"")
# 输入用户名
xbot_visual.desktop.input(window=""0"", element=""用户名输入框"", text=""username"")
# 输入密码
xbot_visual.desktop.input_password(window=""0"", element=""密码输入框"", password=""password"")
# 点击登录
xbot_visual.desktop.click(window=""0"", element=""登录按钮"")
# 最小化窗口
xbot_visual.desktop.set_state(window=""0"", state=""minimize"")
# 使用键盘快捷键打开“我的音乐库”页面
xbot_visual.keyboard.send_keys(keys=""ALT+M"")
# 在搜索框中输入指定的歌曲或歌手名称
xbot_visual.desktop.input(window=""0"", element=""搜索框"", text=""歌曲或歌手名称"")
# 点击“播放”按钮
xbot_visual.desktop.click(window=""0"", element=""播放按钮"")
``` END",{},[]
启动微信，输入账号密码进行登录，然后将其窗口改为全屏显示。接着，点击“文件传输助手”并在对话框中输入指定的文本，最后点击“发送”按钮。,"```python
# 启动微信
process_info=xbot_visual.desktop.launch(process_name=""微信"")
# 输入账号
xbot_visual.desktop.input(window=""0"", element=""微信账号输入框"", text=""123456"")
# 输入密码
xbot_visual.desktop.input_password(window=""0"", element=""微信密码输入框"", password=""123456"")
# 点击登录
xbot_visual.desktop.click(window=""0"", element=""微信登录按钮"")
# 获取微信窗口
wechat_window = xbot_visual.desktop.get(title=""微信"")
# 将微信窗口设置为全屏
xbot_visual.desktop.set_state(window=wechat_window, state=""maximize"")
# 点击文件传输助手
xbot_visual.desktop.click(window=""0"", element=""文件传输助手"")
# 在对话框中输入指定的文本
xbot_visual.desktop.input(window=""0"", element=""对话框"", text=""Hello, World!"")
# 点击发送按钮
xbot_visual.desktop.click(window=""0"", element=""发送按钮"")
``` END",{},[]
启动TeamViewer，输入账号密码进行登录，然后将其窗口移动到屏幕右上角，再调整窗口大小，使其宽度为400，高度为300。最后，点击“连接”按钮，并在弹出的对话框中输入要连接的设备的ID和密码。,"```python
# 启动TeamViewer
process_info=xbot_visual.desktop.launch(process_name=""TeamViewer"")
# 输入账号
xbot_visual.desktop.input(window=""0"", element=""账号输入框"", text=""username"")
# 输入密码
xbot_visual.desktop.input_password(window=""0"", element=""密码输入框"", password=""password"")
# 点击登录
xbot_visual.desktop.click(window=""0"", element=""登录按钮"")
# 获取TeamViewer窗口
teamviewer_window = xbot_visual.desktop.get(title=""TeamViewer"")
# 将TeamViewer窗口移动到屏幕右上角
xbot_visual.desktop.move(window=teamviewer_window, x=""1000"", y=""0"")
# 调整TeamViewer窗口大小，使其宽度为400，高度为300
xbot_visual.desktop.resize(window=teamviewer_window, width=""400"", height=""300"")
# 点击连接按钮
xbot_visual.desktop.click(window=""0"", element=""连接按钮"")
# 在弹出的对话框中输入要连接的设备的ID
xbot_visual.desktop.input(window=""0"", element=""设备ID输入框"", text=""device_id"")
# 在弹出的对话框中输入要连接的设备的密码
xbot_visual.desktop.input_password(window=""0"", element=""设备密码输入框"", password=""device_password"")
# 点击对话框中的连接按钮，进行连接
xbot_visual.desktop.click(window=""0"", element=""对话框连接按钮"")
``` END",{},[]
启动QQ音乐，输入用户名和密码进行登录，然后将其窗口最小化。接着，点击“我的歌单”选项，然后在搜索框中输入指定的歌曲或歌手名称，最后点击“播放”按钮。,"```python
# 启动QQ音乐
process_info=xbot_visual.desktop.launch(process_name=""QQ音乐"")
# 输入用户名
xbot_visual.desktop.input(window=""0"", element=""用户名输入框"", text=""username"")
# 输入密码
xbot_visual.desktop.input_password(window=""0"", element=""密码输入框"", password=""password"")
# 点击登录
xbot_visual.desktop.click(window=""0"", element=""登录按钮"")
# 最小化窗口
xbot_visual.desktop.set_state(window=""0"", state=""minimize"")
# 点击我的歌单
xbot_visual.desktop.click(window=""0"", element=""我的歌单选项"")
# 在搜索框中输入指定的歌曲或歌手名称
xbot_visual.desktop.input(window=""0"", element=""搜索框"", text=""歌曲或歌手名称"")
# 点击播放按钮
xbot_visual.desktop.click(window=""0"", element=""播放按钮"")
``` END",{},[]
在 Adobe Photoshop 中批量处理图片,"```python
# 打开 Adobe Photoshop
process_info=xbot_visual.desktop.launch(process_name=""Adobe Photoshop"")
# 点击文件菜单
xbot_visual.desktop.click(window=""0"", element=""文件菜单"")
# 点击批量处理选项
xbot_visual.desktop.click(window=""0"", element=""批量处理选项"")
# 在批量处理窗口中，点击添加按钮
xbot_visual.desktop.click(window=""0"", element=""添加按钮"")
# 在文件选择窗口中，输入图片文件夹的路径
xbot_visual.desktop.input(window=""0"", element=""文件路径输入框"", text=""C:\\Images"")
# 点击打开按钮，批量导入图片
xbot_visual.desktop.click(window=""0"", element=""打开按钮"")
# 在批量处理窗口中，选择图片处理的选项，比如调整大小
xbot_visual.desktop.select_by_text(window=""0"", element=""处理选项下拉框"", text=""调整大小"")
# 在调整大小选项中，输入新的尺寸
xbot_visual.desktop.input(window=""0"", element=""尺寸输入框"", text=""800x600"")
# 点击确定按钮，开始批量处理图片
xbot_visual.desktop.click(window=""0"", element=""确定按钮"")
# 等待一段时间，等待图片处理完成
xbot_visual.desktop.wait_all_elements_loaded(window=""0"", element=""图片处理进度条"")
# 关闭 Photoshop
xbot_visual.desktop.close(window=""0"")
``` END",{'err_funcs': ['xbot_visual.desktop.wait_all_elements_loaded']},['err_funcs']
使用TeamViewer远程控制其他电脑,"```python
# 打开TeamViewer
process_info=xbot_visual.desktop.launch(process_name=""TeamViewer"")
# 点击连接按钮
xbot_visual.desktop.click(window=""0"", element=""连接"")
# 输入远程电脑ID
xbot_visual.desktop.input(window=""0"", element=""远程电脑ID输入框"", text=""123456789"")
# 点击远程控制按钮
xbot_visual.desktop.click(window=""0"", element=""远程控制按钮"")
``` END",{},[]
在Spotify软件中搜索并播放音乐,"```python
# 打开Spotify软件
process_info=xbot_visual.desktop.launch(process_name=""Spotify"")
# 在搜索框中输入歌曲名称
xbot_visual.desktop.input(window=""0"", element=""Spotify搜索框"", text=""歌曲名称"")
# 点击搜索按钮
xbot_visual.desktop.click(window=""0"", element=""Spotify搜索按钮"")
# 点击播放按钮
xbot_visual.desktop.click(window=""0"", element=""Spotify播放按钮"")
``` END",{},[]
使用微信桌面版发送文件,"```python
# 打开微信
process_info=xbot_visual.desktop.launch(process_name=""微信"")
# 点击进入文件传输助手
xbot_visual.desktop.click(window=""0"", element=""文件传输助手"")
# 点击进入添加文件对话框
xbot_visual.desktop.click(window=""0"", element=""添加文件"")
# 在文件选择对话框中输入文件路径
xbot_visual.desktop.input(window=""0"", element=""文件路径输入框"", text=""C:\\example.txt"")
# 点击确认添加文件
xbot_visual.desktop.click(window=""0"", element=""确认添加"")
# 点击发送文件
xbot_visual.desktop.click(window=""0"", element=""发送文件"")
# 关闭微信
xbot_visual.desktop.close(window=""0"")
``` END",{},[]
使用Spotify播放特定歌曲,"```python
# 打开Spotify软件
process_info=xbot_visual.desktop.launch(process_name=""Spotify"")
# 在搜索框中输入歌曲名称
xbot_visual.desktop.input(window=""0"", element=""Spotify搜索框"", text=""歌曲名称"")
# 点击搜索按钮
xbot_visual.desktop.click(window=""0"", element=""Spotify搜索按钮"")
# 点击播放按钮
xbot_visual.desktop.click(window=""0"", element=""Spotify播放按钮"")
``` END",{},[]
使用Adobe Photoshop打开一张图片，然后保存,"```python
# 打开Adobe Photoshop
process_info=xbot_visual.desktop.launch(process_name=""Adobe Photoshop"")
# 点击文件菜单
xbot_visual.desktop.click(window=""0"", element=""文件菜单"")
# 点击打开选项
xbot_visual.desktop.click(window=""0"", element=""打开选项"")
# 在文件选择对话框中输入图片路径
xbot_visual.desktop.input(window=""0"", element=""文件路径输入框"", text=""C:\\path\\to\\image.jpg"")
# 点击打开按钮
xbot_visual.desktop.click(window=""0"", element=""打开按钮"")
# 点击文件菜单
xbot_visual.desktop.click(window=""0"", element=""文件菜单"")
# 点击保存选项
xbot_visual.desktop.click(window=""0"", element=""保存选项"")
# 在保存对话框中输入保存路径和文件名
xbot_visual.desktop.input(window=""0"", element=""保存路径输入框"", text=""C:\\path\\to\\new_image.jpg"")
# 点击保存按钮
xbot_visual.desktop.click(window=""0"", element=""保存按钮"")
``` END",{},[]
使用TeamViewer进行远程协助,"```python
# 打开TeamViewer
process_info=xbot_visual.desktop.launch(process_name=""TeamViewer"")
# 点击连接按钮
xbot_visual.desktop.click(window=""0"", element=""连接"")
# 输入远程主机ID
xbot_visual.desktop.input(window=""0"", element=""远程主机ID输入框"", text=""123456789"")
# 点击远程控制按钮
xbot_visual.desktop.click(window=""0"", element=""远程控制按钮"")
# 输入远程主机密码
xbot_visual.desktop.input(window=""0"", element=""远程主机密码输入框"", text=""password"")
# 点击登录按钮
xbot_visual.desktop.click(window=""0"", element=""登录按钮"")
```
 END",{},[]
针对Adobe Photoshop软件，设计一个自动化流程来批量处理图片。首先，需要打开Adobe Photoshop软件，并调整窗口大小以适应屏幕。然后，使用鼠标点击“文件”菜单并选择“打开”选项，进入图片文件夹。在文件夹中，需要选择所有的图片文件并打开。接着，对每一张图片进行一系列的处理，如调整亮度、对比度，添加滤镜等。最后，将处理后的图片保存并关闭。,"```python
# 打开Adobe Photoshop软件
process_info=xbot_visual.desktop.launch(process_name=""Adobe Photoshop"")
# 点击文件菜单
xbot_visual.desktop.click(window=""0"", element=""文件菜单"")
# 点击打开选项
xbot_visual.desktop.click(window=""0"", element=""打开选项"")
# 在文件选择对话框中，输入图片文件夹的路径
xbot_visual.desktop.input(window=""0"", element=""文件路径输入框"", text=""C:\\Images"")
# 点击打开按钮，打开图片文件夹
xbot_visual.desktop.click(window=""0"", element=""打开按钮"")
# 处理所有打开的图片
for image in xbot_visual.desktop.iter_all_elements(window=""0"", element=""图片""):
    # 点击图片
    xbot_visual.desktop.click(window=""0"", element=image)
    # 调整亮度
    xbot_visual.desktop.input(window=""0"", element=""亮度输入框"", text=""50"")
    # 调整对比度
    xbot_visual.desktop.input(window=""0"", element=""对比度输入框"", text=""50"")
    # 添加滤镜
    xbot_visual.desktop.click(window=""0"", element=""滤镜按钮"")
    # 点击保存按钮
    xbot_visual.desktop.click(window=""0"", element=""保存按钮"")
    # 在保存对话框中，输入保存路径和文件名
    xbot_visual.desktop.input(window=""0"", element=""保存路径输入框"", text=""C:\\ProcessedImages\\"" + image + ""_processed.jpg"")
    # 点击保存按钮，保存图片
    xbot_visual.desktop.click(window=""0"", element=""保存按钮"")
    # 关闭图片
    xbot_visual.desktop.click(window=""0"", element=""关闭按钮"")
# 关闭Adobe Photoshop
xbot_visual.desktop.close(window=""0"")
``` END",{},[]
对于Spotify软件，实现一个自动化流程来自动创建一个新的播放列表。首先，打开Spotify软件并调整窗口大小。然后，通过鼠标点击“创建新的播放列表”按钮，输入新的播放列表的名称并保存。接着，通过搜索栏搜索指定的歌曲，并将搜索到的歌曲添加到新创建的播放列表中。最后，将Spotify窗口最小化。,"```python
# 打开Spotify软件
process_info=xbot_visual.desktop.launch(process_name=""Spotify"")
# 点击创建新的播放列表按钮
xbot_visual.desktop.click(window=""0"", element=""创建新的播放列表按钮"")
# 在弹出的对话框中，输入新的播放列表的名称
xbot_visual.desktop.input(window=""0"", element=""播放列表名称输入框"", text=""新的播放列表"")
# 点击保存按钮
xbot_visual.desktop.click(window=""0"", element=""保存按钮"")
# 在搜索栏中输入指定的歌曲名称
xbot_visual.desktop.input(window=""0"", element=""搜索栏"", text=""指定的歌曲"")
# 点击搜索按钮
xbot_visual.desktop.click(window=""0"", element=""搜索按钮"")
# 假设搜索结果列表的第一首歌曲的添加按钮的坐标为(100, 200)
# 遍历搜索结果列表
for song in xbot_visual.desktop.iter_all_elements(window=""0"", element=""搜索结果列表""):
    # 获取歌曲名称
    song_name = xbot_visual.desktop.get_attribute(window=""0"", element=song, attribute_name=""text"")
    # 判断歌曲名称是否为指定的歌曲
    if song_name == ""指定的歌曲"":
        # 点击添加按钮
        xbot_visual.desktop.click(window=""0"", element=""添加按钮"", x=""100"", y=""200"")
        # 退出循环
        break
# 将Spotify窗口最小化
xbot_visual.desktop.set_state(window=""0"", state=""minimize"")
``` END","{'extra_args': [""xbot_visual.desktop.click:['y', 'x']""]}",['extra_args']
对于TeamViewer软件，实现一个自动化流程来自动连接到另一台计算机。首先，打开TeamViewer软件并调整窗口大小。然后，输入目标计算机的ID和密码，并点击“连接”按钮。接着，将TeamViewer窗口移动到屏幕的指定位置。最后，设置TeamViewer窗口为最大化状态。,"```python
# 打开TeamViewer软件
process_info=xbot_visual.desktop.launch(process_name=""TeamViewer"")
# 点击连接按钮
xbot_visual.desktop.click(window=""0"", element=""连接"")
# 输入目标计算机的ID
xbot_visual.desktop.input(window=""0"", element=""ID输入框"", text=""目标计算机ID"")
# 输入目标计算机的密码
xbot_visual.desktop.input(window=""0"", element=""密码输入框"", text=""目标计算机密码"")
# 点击连接按钮
xbot_visual.desktop.click(window=""0"", element=""连接"")
# 调整TeamViewer窗口大小
xbot_visual.desktop.resize(window=""0"", width=""800"", height=""600"")
# 移动TeamViewer窗口到指定位置
xbot_visual.desktop.move(window=""0"", x=""100"", y=""100"")
# 设置TeamViewer窗口为最大化状态
xbot_visual.desktop.set_state(window=""0"", state=""maximize"")
``` END",{},[]
对于微信软件，设计一个自动化流程来自动发送消息。首先，打开微信软件并调整窗口大小。然后，通过搜索栏搜索指定的联系人，并点击该联系人的聊天窗口。接着，输入消息内容，并通过快捷键Ctrl+Enter发送消息。最后，关闭微信窗口。,"```python
# 打开微信
process_info=xbot_visual.desktop.launch(process_name=""微信"")
# 调整微信窗口大小
xbot_visual.desktop.resize(window=""0"", width=""800"", height=""600"")
# 在搜索栏输入指定的联系人
xbot_visual.desktop.input(window=""0"", element=""微信搜索栏"", text=""指定的联系人"")
# 点击进入指定联系人的聊天窗口
xbot_visual.desktop.click(window=""0"", element=""指定联系人聊天窗口"")
# 输入消息内容
xbot_visual.desktop.input(window=""0"", element=""微信消息输入框"", text=""Hello, World!"")
# 通过快捷键Ctrl+Enter发送消息
xbot_visual.keyboard.send_keys(keys=""^+{ENTER}"")
# 关闭微信窗口
xbot_visual.desktop.close(window=""0"")
``` END",{},[]
使用 win+r 键唤起 windows 运行窗口，输入“excel”并回车，打开 Excel 文件。,"```python
# 使用 win+r 键唤起 windows 运行窗口
xbot_visual.keyboard.send_keys(keys=""#r"")
# 输入“excel”
xbot_visual.desktop.input(window=""0"", element=""运行窗口输入框"", text=""excel"")
# 按下回车键
xbot_visual.keyboard.send_keys(keys=""{enter}"")
``` END",{},[]
使用 win+s 键唤起搜索窗口，输入“chrome”并回车，打开 Chrome 浏览器。,"```python
# 使用 win+s 键唤起搜索窗口
xbot_visual.keyboard.send_keys(keys=""#{s}"")
# 输入“chrome”
xbot_visual.desktop.input(window=""0"", element=""搜索框"", text=""chrome"")
# 按下回车键
xbot_visual.keyboard.send_keys(keys=""{enter}"")
# 打开 Chrome 浏览器
xbot_visual.desktop.click(window=""0"", element=""Chrome"")
``` END",{},[]
在 word 文档中，通过 ctrl+s 快捷键保存当前正在编辑的文档。,"```python
# 打开 word 文档
xbot_visual.desktop.click(window=""0"", element=""word文档"")
# 保存快捷键 ctrl+s
xbot_visual.keyboard.send_keys(keys=""^s"")
``` END",{},[]
使用 alt+f4 快捷键关闭当前打开的 PowerPoint。,"```python
# 打开PowerPoint
process_info=xbot_visual.desktop.launch(process_name=""PowerPoint"")
# 发送alt+f4快捷键
xbot_visual.keyboard.send_keys(keys=""!{F4}"")
``` END",{},[]
使用 win+e 快捷键打开 windows 资源管理器，并访问特定文件夹。,"```python
# 使用 win+e 快捷键打开 windows 资源管理器
xbot_visual.keyboard.send_keys(keys=""#e"")
# 在资源管理器地址栏输入特定文件夹路径
xbot_visual.desktop.input(window=""0"", element=""资源管理器地址栏"", text=""C:\\MyFolder"")
# 按下回车键，访问特定文件夹
xbot_visual.keyboard.send_keys(keys=""{enter}"")
``` END",{},[]
唤起任务管理器，结束某个正在运行的进程。,"```python
# 打开任务管理器
xbot_visual.keyboard.send_keys(keys=""^+{ESCAPE}"")
# 结束进程
xbot_visual.desktop.kill(process_name=""notepad.exe"")
``` END",{'err_funcs': ['xbot_visual.desktop.kill']},['err_funcs']
在 Notepad++ 中，通过 ctrl+tab 快捷键切换到下一个已打开的标签。,"```python
# 打开 Notepad++
process_info=xbot_visual.desktop.launch(process_name=""Notepad++"")
# 通过 ctrl+tab 快捷键切换到下一个已打开的标签
xbot_visual.keyboard.send_keys(keys=""^+{TAB}"")
``` END",{},[]
"使用 Win+R 键唤起Windows运行窗口，输入""control""并回车，打开控制面板。","```python
# 使用 Win+R 键唤起Windows运行窗口
xbot_visual.keyboard.send_keys(keys=""#r"")
# 输入""control""并回车
xbot_visual.keyboard.send_keys(keys=""control\n"")
# 打开控制面板
xbot_visual.desktop.click(window=""0"", element=""控制面板"")
``` END",{},[]
使用Win+E键打开我的电脑，找到特定的文件并打开。,"```python
# 使用Win+E键打开我的电脑
xbot_visual.keyboard.send_keys(keys=""#e"")
# 在文件资源管理器中输入文件名
xbot_visual.desktop.input(window=""0"", element=""文件名输入框"", text=""example.txt"")
# 打开文件
xbot_visual.desktop.click(window=""0"", element=""打开按钮"")
``` END",{},[]
使用Win+Tab键切换到其他正在运行的应用程序。,"```python
# 使用Win+Tab键切换到其他正在运行的应用程序
xbot_visual.keyboard.send_keys(keys=""#{VK_TAB}"")
``` END",{},[]
使用Win+D键最小化所有窗口，显示桌面。,"```python
# 按下Win+D键
xbot_visual.keyboard.send_keys(keys=""#d"")
``` END",{},[]
打开Windows运行窗口，输入“msconfig”并回车，打开系统配置。,"```python
# 打开Windows运行窗口
xbot_visual.keyboard.send_keys(keys=""#r"")
# 输入“msconfig”
xbot_visual.desktop.input(window=""0"", element=""Windows运行窗口"", text=""msconfig"")
# 回车
xbot_visual.keyboard.send_keys(keys=""{enter}"")
# 打开系统配置
xbot_visual.desktop.click(window=""0"", element=""系统配置"")
``` END",{},[]
锁定电脑。,"```python
# 打开屏幕保护设置
xbot_visual.keyboard.send_keys(keys=""win+R"")
# 输入屏幕保护设置命令
xbot_visual.keyboard.send_keys(keys=""cmd /c start /d %windir% /s ScreenSaverSettings.exe"")
# 点击确定按钮
xbot_visual.desktop.click(window=""0"", element=""确定"")
``` END",{},[]
"在Windows搜索窗口中，输入""Excel""并回车，打开Microsoft Excel。","```python
# 打开Windows搜索
xbot_visual.keyboard.send_keys(keys=""#{r}"")
# 在Windows搜索窗口中，输入""Excel""并回车
xbot_visual.desktop.input(window=""0"", element=""Windows搜索输入框"", text=""Excel{enter}"")
# 点击打开的Microsoft Excel窗口
xbot_visual.desktop.click(window=""0"", element=""Microsoft Excel窗口"")
``` END",{},[]
使用Win+I键打开Windows设置。,"```python
# 打开Windows设置
xbot_visual.keyboard.send_keys(keys=""#i"")
``` END",{},[]
使用 win+r 键唤起 windows 运行窗口，输入“excel”并回车，打开 Excel 文件。,"```python
# 使用 win+r 键唤起 windows 运行窗口
xbot_visual.keyboard.send_keys(keys=""#r"")
# 输入“excel”
xbot_visual.desktop.input(window=""0"", element=""运行窗口输入框"", text=""excel"")
# 按下回车键
xbot_visual.keyboard.send_keys(keys=""{enter}"")
``` END",{},[]
使用 win+s 键唤起搜索窗口，输入“chrome”并回车，打开 Chrome 浏览器。,"```python
# 使用 win+s 键唤起搜索窗口
xbot_visual.keyboard.send_keys(keys=""#{s}"")
# 输入“chrome”
xbot_visual.desktop.input(window=""0"", element=""搜索框"", text=""chrome"")
# 按下回车键
xbot_visual.keyboard.send_keys(keys=""{enter}"")
# 打开 Chrome 浏览器
xbot_visual.desktop.click(window=""0"", element=""Chrome"")
``` END",{},[]
在 word 文档中，通过 ctrl+s 快捷键保存当前正在编辑的文档。,"```python
# 打开 word 文档
xbot_visual.desktop.click(window=""0"", element=""word文档"")
# 保存快捷键 ctrl+s
xbot_visual.keyboard.send_keys(keys=""^s"")
``` END",{},[]
使用 alt+f4 快捷键关闭当前打开的 PowerPoint。,"```python
# 打开PowerPoint
process_info=xbot_visual.desktop.launch(process_name=""PowerPoint"")
# 使用 alt+f4 快捷键关闭当前打开的 PowerPoint
xbot_visual.keyboard.send_keys(keys=""!{F4}"")
``` END",{},[]
使用 ctrl+alt+del 快捷键唤起任务管理器，结束某个正在运行的进程。,"```python
# 使用 ctrl+alt+del 快捷键唤起任务管理器
xbot_visual.keyboard.send_keys(keys=""^%{DELETE}"")
# 结束某个正在运行的进程
xbot_visual.desktop.kill_process(process_name=""process_name"")
``` END",{'err_funcs': ['xbot_visual.desktop.kill_process']},['err_funcs']
"使用Win+R键唤起Windows运行窗口，输入""winword""并回车，打开Microsoft Word。","```python
# 使用Win+R键唤起Windows运行窗口
xbot_visual.keyboard.send_keys(keys=""#r"")
# 输入""winword""
xbot_visual.desktop.input(window=""0"", element=""Windows运行窗口输入框"", text=""winword"")
# 按下回车键
xbot_visual.keyboard.send_keys(keys=""{enter}"")
``` END",{},[]
使用Win+L键锁定电脑。,"```python
# 打开记事本
process_info=xbot_visual.desktop.launch(process_name=""记事本"")
# 按下Win键
xbot_visual.keyboard.send_keys(keys=""#{lwin}"")
# 按下L键
xbot_visual.keyboard.send_keys(keys=""L"")
``` END",{},[]
在微信中通过扫描二维码登录，并发送特定的消息给特定的联系人。,"```python
# 打开微信
process_info=xbot_visual.desktop.launch(process_name=""微信"")
# 点击扫描二维码登录按钮
xbot_visual.desktop.click(window=""0"", element=""扫描二维码登录"")
# 扫描二维码登录
xbot_visual.desktop.input(window=""0"", element=""二维码扫描输入框"", text=""二维码内容"")
# 点击登录按钮
xbot_visual.desktop.click(window=""0"", element=""登录"")
# 点击搜索框
xbot_visual.desktop.click(window=""0"", element=""搜索框"")
# 输入联系人名称
xbot_visual.desktop.input(window=""0"", element=""搜索框"", text=""联系人名称"")
# 点击搜索结果中的联系人
xbot_visual.desktop.click(window=""0"", element=""搜索结果"")
# 输入要发送的消息
xbot_visual.desktop.input(window=""0"", element=""消息输入框"", text=""要发送的消息"")
# 点击发送按钮
xbot_visual.desktop.click(window=""0"", element=""发送按钮"")
``` END",{},[]
在Adobe Photoshop中打开一个指定的图片文件，然后调整其亮度，保存并关闭。,"```python
# 打开Adobe Photoshop
process_info=xbot_visual.desktop.launch(process_name=""Adobe Photoshop"")
# 点击文件菜单
xbot_visual.desktop.click(window=""0"", element=""文件菜单"")
# 点击打开选项
xbot_visual.desktop.click(window=""0"", element=""打开选项"")
# 在文件选择对话框中输入图片文件的路径
xbot_visual.desktop.input(window=""0"", element=""文件路径输入框"", text=""C:\\path\\to\\image.jpg"")
# 点击打开按钮
xbot_visual.desktop.click(window=""0"", element=""打开按钮"")
# 点击图像菜单
xbot_visual.desktop.click(window=""0"", element=""图像菜单"")
# 点击调整选项
xbot_visual.desktop.click(window=""0"", element=""调整选项"")
# 在调整对话框中找到亮度选项
xbot_visual.desktop.select_by_text(window=""0"", element=""亮度下拉框"", text=""亮度"")
# 调整亮度滑块的值
xbot_visual.desktop.input(window=""0"", element=""亮度滑块"", text=""50"")
# 点击确定按钮
xbot_visual.desktop.click(window=""0"", element=""确定按钮"")
# 点击文件菜单
xbot_visual.desktop.click(window=""0"", element=""文件菜单"")
# 点击保存选项
xbot_visual.desktop.click(window=""0"", element=""保存选项"")
# 在保存对话框中输入保存路径和文件名
xbot_visual.desktop.input(window=""0"", element=""保存路径输入框"", text=""C:\\path\\to\\new_image.jpg"")
# 点击保存按钮
xbot_visual.desktop.click(window=""0"", element=""保存按钮"")
# 点击关闭按钮
xbot_visual.desktop.click(window=""0"", element=""关闭按钮"")
```  END",{},[]
在Photoshop中自动打开指定文件夹的图片，进行一键美化处理，并保存到指定位置。,"```python
# 打开Photoshop
process_info=xbot_visual.desktop.launch(process_name=""Photoshop"")
# 点击文件菜单
xbot_visual.desktop.click(window=""0"", element=""文件菜单"")
# 点击打开选项
xbot_visual.desktop.click(window=""0"", element=""打开选项"")
# 在文件路径输入框中输入指定文件夹的路径
xbot_visual.desktop.input(window=""0"", element=""文件路径输入框"", text=""C:\\path\\to\\folder"")
# 按下回车键确认打开
xbot_visual.keyboard.send_keys(keys=""{ENTER}"")
# 在文件名输入框中输入指定图片的文件名
xbot_visual.desktop.input(window=""0"", element=""文件名输入框"", text=""image.jpg"")
# 按下回车键确认打开图片
xbot_visual.keyboard.send_keys(keys=""{ENTER}"")
# 点击滤镜菜单
xbot_visual.desktop.click(window=""0"", element=""滤镜菜单"")
# 点击一键美化选项
xbot_visual.desktop.click(window=""0"", element=""一键美化选项"")
# 点击文件菜单
xbot_visual.desktop.click(window=""0"", element=""文件菜单"")
# 点击保存选项
xbot_visual.desktop.click(window=""0"", element=""保存选项"")
# 在保存路径输入框中输入指定位置的路径
xbot_visual.desktop.input(window=""0"", element=""保存路径输入框"", text=""C:\\path\\to\\save"")
# 在文件名输入框中输入保存的文件名
xbot_visual.desktop.input(window=""0"", element=""文件名输入框"", text=""beautified_image.jpg"")
# 按下回车键确认保存
xbot_visual.keyboard.send_keys(keys=""{ENTER}"")
``` END",{},[]
在旺店通ERP中，对采购模块进行数据录入，设置默认供应商为“XX公司”,"```python
# 打开旺店通ERP软件
process_info=xbot_visual.desktop.launch(process_name=""旺店通ERP"")
# 点击进入采购模块
xbot_visual.desktop.click(window=""0"", element=""采购模块"")
# 点击进入供应商设置
xbot_visual.desktop.click(window=""0"", element=""供应商设置"")
# 在默认供应商输入框中输入“XX公司”
xbot_visual.desktop.input(window=""0"", element=""默认供应商输入框"", text=""XX公司"")
# 点击保存按钮，保存设置
xbot_visual.desktop.click(window=""0"", element=""保存按钮"")
# 点击进入采购订单
xbot_visual.desktop.click(window=""0"", element=""采购订单"")
# 点击新建采购订单
xbot_visual.desktop.click(window=""0"", element=""新建采购订单"")
# 在供应商输入框中输入“XX公司”
xbot_visual.desktop.input(window=""0"", element=""供应商输入框"", text=""XX公司"")
# 在商品输入框中输入商品名称
xbot_visual.desktop.input(window=""0"", element=""商品输入框"", text=""商品名称"")
# 在数量输入框中输入商品数量
xbot_visual.desktop.input(window=""0"", element=""数量输入框"", text=""商品数量"")
# 点击保存按钮，保存采购订单
xbot_visual.desktop.click(window=""0"", element=""保存按钮"")
``` END",{},[]
在探迹SCRM中，设置每周对所有新关注用户的自动欢迎消息。,"```python
# 打开探迹SCRM
process_info=xbot_visual.desktop.launch(process_name=""探迹SCRM"")
# 点击进入设置页面
xbot_visual.desktop.click(window=""0"", element=""设置"")
# 点击进入自动回复设置页面
xbot_visual.desktop.click(window=""0"", element=""自动回复设置"")
# 勾选开启自动回复
xbot_visual.desktop.set_checkbox(window=""0"", element=""开启自动回复"", check_state=""checked"")
# 勾选开启自动回复新关注用户
xbot_visual.desktop.set_checkbox(window=""0"", element=""开启自动回复新关注用户"", check_state=""checked"")
# 输入自动回复消息
xbot_visual.desktop.input(window=""0"", element=""自动回复消息"", text=""欢迎关注！"")
# 点击保存按钮
xbot_visual.desktop.click(window=""0"", element=""保存"")
# 点击进入用户管理页面
xbot_visual.desktop.click(window=""0"", element=""用户管理"")
# 点击进入新关注用户页面
xbot_visual.desktop.click(window=""0"", element=""新关注用户"")
# 点击进入批量操作页面
xbot_visual.desktop.click(window=""0"", element=""批量操作"")
# 点击进入发送消息页面
xbot_visual.desktop.click(window=""0"", element=""发送消息"")
# 输入欢迎消息
xbot_visual.desktop.input(window=""0"", element=""消息输入框"", text=""欢迎关注！"")
# 点击发送按钮
xbot_visual.desktop.click(window=""0"", element=""发送"")
# 关闭探迹SCRM
xbot_visual.desktop.close(window=""0"")
``` END",{},[]
在生意参谋中，查找并分析近一个月热销产品的搜索关键词。,"```python
# 打开生意参谋
process_info=xbot_visual.desktop.launch(process_name=""生意参谋"")
# 点击进入热销产品模块
xbot_visual.desktop.click(window=""0"", element=""热销产品"")
# 点击设置时间按钮
xbot_visual.desktop.click(window=""0"", element=""设置时间"")
# 选择近一个月
xbot_visual.desktop.select_by_text(window=""0"", element=""时间选择框"", text=""近一个月"")
# 点击确认
xbot_visual.desktop.click(window=""0"", element=""确认"")
# 遍历热销产品列表
for product in xbot_visual.desktop.iter_all_elements(window=""0"", element=""热销产品列表""):
    # 获取产品名称
    product_name = xbot_visual.desktop.get_attribute(window=""0"", element=product, attribute_name=""text"")
    # 打印产品名称
    print(product_name)
    # 双击进入产品详情
    xbot_visual.desktop.click(window=""0"", element=product, clicks=""dbclick"")
    # 获取产品搜索关键词
    keyword = xbot_visual.desktop.get_attribute(window=""0"", element=""产品搜索关键词"", attribute_name=""text"")
    # 打印产品搜索关键词
    print(keyword)
    # 关闭产品详情
    xbot_visual.desktop.click(window=""0"", element=""关闭按钮"")
``` END",{},[]
在飞鸽中，为新上架的产品设置自动推送广告。,"```python
# 打开飞鸽
process_info=xbot_visual.desktop.launch(process_name=""飞鸽"")
# 点击进入产品管理模块
xbot_visual.desktop.click(window=""0"", element=""产品管理"")
# 点击进入广告设置模块
xbot_visual.desktop.click(window=""0"", element=""广告设置"")
# 遍历新上架的产品
for product in xbot_visual.desktop.iter_all_elements(window=""0"", element=""新上架产品""):
    # 选中当前产品
    xbot_visual.desktop.click(window=""0"", element=product)
    # 点击设置自动推送广告按钮
    xbot_visual.desktop.click(window=""0"", element=""设置自动推送广告"")
    # 等待设置完成
    xbot_visual.desktop.click(window=""0"", element=""完成"")
``` END",{},[]
找到Steam库中安装的前五款游戏，从中选择玩家最近玩过的一款游戏，创建快捷方式。,"```python
# 打开Steam
process_info=xbot_visual.desktop.launch(process_name=""Steam"")
# 点击进入Steam库
xbot_visual.desktop.click(window=""0"", element=""Steam库"")
# 遍历游戏列表
for game in xbot_visual.desktop.iter_all_elements(window=""0"", element=""游戏列表""):
    # 获取游戏名称
    game_name = xbot_visual.desktop.get_attribute(window=""0"", element=game, attribute_name=""text"")
    # 判断游戏是否是玩家最近玩过的一款游戏
    if game_name == ""玩家最近玩过的一款游戏"":
        # 双击进入游戏
        xbot_visual.desktop.click(window=""0"", element=game, clicks=""dbclick"")
        # 点击创建快捷方式
        xbot_visual.desktop.click(window=""0"", element=""创建快捷方式"")
        # 退出循环
        break
``` END",{},[]
在Spotify桌面应用程序中，自动搜索特定的歌单，打开歌单并将歌单名称和包含的歌曲数量记录在一个记事本文件中。,"```python
# 打开Spotify桌面应用程序
process_info=xbot_visual.desktop.launch(process_name=""Spotify"")
# 在搜索框中输入特定的歌单名称
xbot_visual.desktop.input(window=""0"", element=""Spotify搜索框"", text=""特定的歌单名称"")
# 点击搜索按钮
xbot_visual.desktop.click(window=""0"", element=""Spotify搜索按钮"")
# 点击第一个搜索结果，即特定的歌单
xbot_visual.desktop.click(window=""0"", element=""特定的歌单"")
# 获取歌单名称
playlist_name = xbot_visual.desktop.get_attribute(window=""0"", element=""歌单名称"", attribute_name=""text"")
# 获取歌单中包含的歌曲数量
song_count = xbot_visual.desktop.get_attribute(window=""0"", element=""歌单中的歌曲数量"", attribute_name=""text"")
# 将歌单名称和包含的歌曲数量写入记事本文件
xbot_visual.desktop.input(window=""0"", element=""记事本编辑区"", text=""歌单名称：{0}，歌曲数量：{1}"".format(playlist_name, song_count))
``` END",{},[]
在Spotify中，自动查找播放次数超过1000次的歌曲，并创建一个新的播放列表。,"```python
# 打开Spotify软件
process_info=xbot_visual.desktop.launch(process_name=""Spotify"")
# 点击进入搜索框
xbot_visual.desktop.click(window=""0"", element=""搜索框"")
# 在搜索框中输入歌曲名称
xbot_visual.desktop.input(window=""0"", element=""搜索框"", text=""歌曲名称"")
# 点击搜索按钮
xbot_visual.desktop.click(window=""0"", element=""搜索按钮"")
# 遍历搜索结果列表
for song in xbot_visual.desktop.iter_all_elements(window=""0"", element=""搜索结果列表""):
    # 获取歌曲的播放次数
    play_count = xbot_visual.desktop.get_attribute(window=""0"", element=song, attribute_name=""text"")
    # 判断播放次数是否超过1000次
    if int(play_count) > 1000:
        # 右键点击歌曲，弹出菜单
        xbot_visual.desktop.click(window=""0"", element=song, button=""right"")
        # 点击添加到播放列表选项
        xbot_visual.desktop.click(window=""0"", element=""添加到播放列表选项"")
# 点击创建新的播放列表按钮
xbot_visual.desktop.click(window=""0"", element=""创建新的播放列表按钮"")
# 在弹出的对话框中输入播放列表名称
xbot_visual.desktop.input(window=""0"", element=""播放列表名称输入框"", text=""新的播放列表"")
# 点击确认按钮，创建播放列表
xbot_visual.desktop.click(window=""0"", element=""确认按钮"")
``` END",{},[]
在人力资源管理软件Workday里，找到所有即将过生日的员工，自动筛选出高级管理层，然后标记他们以便发送生日卡。,"```python
# 打开Workday软件
process_info=xbot_visual.desktop.launch(process_name=""Workday"")
# 点击进入员工管理模块
xbot_visual.desktop.click(window=""0"", element=""员工管理"")
# 点击进入生日提醒模块
xbot_visual.desktop.click(window=""0"", element=""生日提醒"")
# 筛选出高级管理层
xbot_visual.desktop.select_by_text(window=""0"", element=""筛选条件"", text=""高级管理层"")
# 点击确认筛选
xbot_visual.desktop.click(window=""0"", element=""确认"")
# 遍历所有即将过生日的员工对象
for employee in xbot_visual.desktop.iter_all_elements(window=""0"", element=""即将过生日的员工""):
    # 标记员工对象
    xbot_visual.desktop.input(window=""0"", element=employee, text=""生日卡"")
``` END",{},[]
在Skype中，自动化搜索特定的联系人，并向其发送预定的文本信息。,"```python
# 打开Skype软件
process_info=xbot_visual.desktop.launch(process_name=""Skype"")
# 在搜索框中输入特定的联系人名称
xbot_visual.desktop.input(window=""0"", element=""Skype搜索框"", text=""特定的联系人名称"")
# 点击搜索按钮
xbot_visual.desktop.click(window=""0"", element=""Skype搜索按钮"")
# 点击进入特定的联系人聊天窗口
xbot_visual.desktop.click(window=""0"", element=""特定的联系人聊天窗口"")
# 在消息输入框中输入预定的文本信息
xbot_visual.desktop.input(window=""0"", element=""Skype消息输入框"", text=""预定的文本信息"")
# 点击发送按钮，发送文本信息
xbot_visual.desktop.click(window=""0"", element=""Skype发送按钮"")
``` END",{},[]
在AutoCAD中打开一个特定的项目文件，然后保存并关闭文件，并验证文件是否被正确保存和关闭。,"```python
# 打开AutoCAD
process_info=xbot_visual.desktop.launch(process_name=""AutoCAD"")
# 点击AutoCAD中的打开按钮
xbot_visual.desktop.click(window=""0"", element=""打开按钮"")
# 在文件路径输入框中输入特定的项目文件路径
xbot_visual.desktop.input(window=""0"", element=""文件路径输入框"", text=""C:\\Projects\\project.dwg"")
# 点击AutoCAD中的确认打开按钮
xbot_visual.desktop.click(window=""0"", element=""确认打开按钮"")
# 点击AutoCAD中的保存按钮
xbot_visual.desktop.click(window=""0"", element=""保存按钮"")
# 点击AutoCAD中的关闭按钮
xbot_visual.desktop.click(window=""0"", element=""关闭按钮"")
# 根据文件路径判断文件是否被正确保存和关闭
if xbot_visual.desktop.contains_text(window=""0"", text=""C:\\Projects\\project.dwg""):
    # 打印文件保存和关闭失败的提示信息
    print(""文件保存和关闭失败"")
# 否则
else:
    # 打印文件保存和关闭成功的提示信息
    print(""文件保存和关闭成功"")
``` END",{'err_funcs': ['xbot_visual.desktop.contains_text']},['err_funcs']
在微信中搜索指定的联系人，查看他们的在线状态，并将此信息保存在记事本文件中。,"```python
# 打开微信
process_info=xbot_visual.desktop.launch(process_name=""微信"")
# 在搜索框中输入指定的联系人
xbot_visual.desktop.input(window=""0"", element=""微信搜索框"", text=""指定的联系人"")
# 点击搜索按钮
xbot_visual.desktop.click(window=""0"", element=""微信搜索按钮"")
# 获取在线状态
online_status = xbot_visual.desktop.get_attribute(window=""0"", element=""微信在线状态"", attribute_name=""text"")
# 点击记事本窗口
xbot_visual.desktop.click(window=""0"", element=""记事本窗口"")
# 输入在线状态
xbot_visual.desktop.input(window=""0"", element=""记事本编辑区"", text=online_status)
``` END",{},[]
在Spotify中搜索特定的歌曲或艺术家，播放选定的歌曲，并调整音量为50。,"```python
# 打开Spotify软件
process_info=xbot_visual.desktop.launch(process_name=""Spotify"")
# 在搜索框中输入特定的歌曲或艺术家
xbot_visual.desktop.input(window=""0"", element=""Spotify搜索框"", text=""歌曲或艺术家名称"")
# 点击搜索按钮
xbot_visual.desktop.click(window=""0"", element=""Spotify搜索按钮"")
# 选择第一首搜索结果
xbot_visual.desktop.click(window=""0"", element=""Spotify搜索结果1"")
# 点击播放按钮
xbot_visual.desktop.click(window=""0"", element=""Spotify播放按钮"")
# 拖动音量滑块到50
xbot_visual.desktop.drag_to_element(window=""0"", element=""Spotify音量滑块"", target=""Spotify音量50"")
``` END",{},[]
在MATLAB中自动打开一个新的脚本，编写一个简单的计算函数，并将其保存到指定的文件夹中。,"```python
# 打开MATLAB
process_info=xbot_visual.desktop.launch(process_name=""MATLAB"")
# 点击新建脚本按钮
xbot_visual.desktop.click(window=""0"", element=""新建脚本"")
# 在脚本编辑区输入计算函数
xbot_visual.desktop.input(window=""0"", element=""脚本编辑区"", text=""function result = myFunction(a, b)\nresult = a + b;\nend"")
# 点击保存按钮
xbot_visual.desktop.click(window=""0"", element=""保存"")
# 在保存对话框中输入文件名
xbot_visual.desktop.input(window=""0"", element=""文件名输入框"", text=""myFunction.m"")
# 在保存对话框中输入文件夹路径
xbot_visual.desktop.input(window=""0"", element=""文件夹路径输入框"", text=""C:\\MyScripts"")
# 点击保存对话框中的保存按钮
xbot_visual.desktop.click(window=""0"", element=""保存按钮"")
``` END",{},[]
在巨益OMS中，自动为所有新订单匹配最近的发货仓库。,"```python
# 打开巨益OMS软件
process_info=xbot_visual.desktop.launch(process_name=""巨益OMS"")
# 点击进入订单管理模块
xbot_visual.desktop.click(window=""0"", element=""订单管理"")
# 点击进入新订单列表
xbot_visual.desktop.click(window=""0"", element=""新订单"")
# 遍历所有新订单对象
for order in xbot_visual.desktop.iter_all_elements(window=""0"", element=""新订单对象""):
    # 点击进入订单详情
    xbot_visual.desktop.click(window=""0"", element=order)
    # 获取订单信息
    order_info = xbot_visual.desktop.get_attribute(window=""0"", element=""订单信息"", attribute_name=""text"")
    # 获取发货仓库信息
    warehouse_info = xbot_visual.desktop.get_attribute(window=""0"", element=""发货仓库信息"", attribute_name=""text"")
    # 打印订单信息
    print(order_info)
    # 打印发货仓库信息
    print(warehouse_info)
    # 点击确认匹配
    xbot_visual.desktop.click(window=""0"", element=""确认匹配"")
``` END",{},[]
在九恒星中，查看所有与某一客户的交易记录，了解其支付习惯。,"```python
# 打开九恒星
process_info=xbot_visual.desktop.launch(process_name=""九恒星"")
# 点击进入客户管理模块
xbot_visual.desktop.click(window=""0"", element=""客户管理"")
# 在搜索框中输入客户姓名
xbot_visual.desktop.input(window=""0"", element=""搜索框"", text=""客户姓名"")
# 点击搜索按钮
xbot_visual.desktop.click(window=""0"", element=""搜索"")
# 双击进入客户详情
xbot_visual.desktop.click(window=""0"", element=""客户详情"", clicks=""dbclick"")
# 点击进入交易记录
xbot_visual.desktop.click(window=""0"", element=""交易记录"")
# 遍历交易记录表格
for record in xbot_visual.desktop.iter_all_elements(window=""0"", element=""交易记录表格""):
    # 获取交易金额
    amount = xbot_visual.desktop.get_attribute(window=""0"", element=record, attribute_name=""text"")
    # 打印交易金额
    print(f""交易金额为：{amount}"")
# 关闭九恒星
xbot_visual.desktop.close(window=""0"")
``` END",{},[]
在帆软BI中，自动创建一个关于上月销售数据的仪表盘并分享给销售团队。,"```python
# 打开帆软BI
process_info=xbot_visual.desktop.launch(process_name=""帆软BI"")
# 点击创建仪表盘按钮
xbot_visual.desktop.click(window=""0"", element=""创建仪表盘按钮"")
# 在数据源选择框中选择上月销售数据源
xbot_visual.desktop.select_by_text(window=""0"", element=""数据源选择框"", text=""上月销售数据源"")
# 在图表类型选择框中选择柱状图
xbot_visual.desktop.select_by_text(window=""0"", element=""图表类型选择框"", text=""柱状图"")
# 点击确认按钮，创建仪表盘
xbot_visual.desktop.click(window=""0"", element=""确认按钮"")
# 点击分享按钮
xbot_visual.desktop.click(window=""0"", element=""分享按钮"")
# 在分享窗口的搜索框中输入销售团队
xbot_visual.desktop.input(window=""0"", element=""分享窗口搜索框"", text=""销售团队"")
# 选择销售团队作为分享对象
xbot_visual.desktop.click(window=""0"", element=""销售团队"")
# 点击确认分享
xbot_visual.desktop.click(window=""0"", element=""确认分享"")
``` END",{},[]
在帆软BI中，自动分析哪个时间段的广告投放效果最佳。,"```python
# 打开帆软BI软件
process_info=xbot_visual.desktop.launch(process_name=""帆软BI"")
# 点击进入广告投放效果分析页面
xbot_visual.desktop.click(window=""0"", element=""广告投放效果分析"")
# 选择时间段1
xbot_visual.desktop.select_by_text(window=""0"", element=""时间段选择框"", text=""时间段1"")
# 点击分析按钮
xbot_visual.desktop.click(window=""0"", element=""分析"")
# 获取时间段1的广告投放效果
time1_result = xbot_visual.desktop.get_attribute(window=""0"", element=""时间段1的广告投放效果"", attribute_name=""text"")
# 选择时间段2
xbot_visual.desktop.select_by_text(window=""0"", element=""时间段选择框"", text=""时间段2"")
# 点击分析按钮
xbot_visual.desktop.click(window=""0"", element=""分析"")
# 获取时间段2的广告投放效果
time2_result = xbot_visual.desktop.get_attribute(window=""0"", element=""时间段2的广告投放效果"", attribute_name=""text"")
# 判断哪个时间段的广告投放效果最佳
if time1_result > time2_result:
    # 打印时间段1的广告投放效果最佳
    print(""时间段1的广告投放效果最佳"")
else:
    # 打印时间段2的广告投放效果最佳
    print(""时间段2的广告投放效果最佳"")
``` END",{},[]
在Notepad++中打开特定代码文件，搜索并高亮所有包含“TODO”的注释行，并将这些注释导出到新的.txt文件中。,"```python
# 打开Notepad++
process_info=xbot_visual.desktop.launch(process_name=""Notepad++"")
# 点击打开文件按钮
xbot_visual.desktop.click(window=""0"", element=""打开文件按钮"")
# 在文件路径输入框中输入特定代码文件的路径
xbot_visual.desktop.input(window=""0"", element=""文件路径输入框"", text=""C:\\path\\to\\codefile.txt"")
# 点击确认打开文件
xbot_visual.desktop.click(window=""0"", element=""确认打开文件按钮"")
# 在搜索框中输入""TODO""
xbot_visual.desktop.input(window=""0"", element=""搜索框"", text=""TODO"")
# 点击搜索按钮
xbot_visual.desktop.click(window=""0"", element=""搜索按钮"")
# 点击高亮所有按钮
xbot_visual.desktop.click(window=""0"", element=""高亮所有按钮"")
# 点击导出到.txt按钮
xbot_visual.desktop.click(window=""0"", element=""导出到.txt按钮"")
# 在导出对话框中输入导出文件的路径
xbot_visual.desktop.input(window=""0"", element=""导出对话框路径输入框"", text=""C:\\path\\to\\export.txt"")
# 点击保存按钮
xbot_visual.desktop.click(window=""0"", element=""保存按钮"")
``` END",{},[]
在Slack中查找所有含有关键词“紧急”的未读消息。,"```python
# 打开Slack软件
process_info=xbot_visual.desktop.launch(process_name=""Slack"")
# 点击进入未读消息列表
xbot_visual.desktop.click(window=""0"", element=""未读消息"")
# 遍历所有消息对象
for message in xbot_visual.desktop.iter_all_elements(window=""0"", element=""消息""):
    # 获取消息对象的文本
    message_text = xbot_visual.desktop.get_attribute(window=""0"", element=message, attribute_name=""text"")
    # 判断消息中是否包含关键词""紧急""
    if ""紧急"" in message_text:
        # 如果包含，打印该消息
        print(message_text)
``` END",{},[]
进入桌面文件夹，打开所有.txt文件，并检查是否含有特定的字符串，例如电子邮件地址。,"```python
# 打开桌面文件夹
xbot_visual.keyboard.send_keys(keys=""#d"")
# 输入文件夹名称
xbot_visual.desktop.input(window=""0"", element=""文件夹名称"", text=""桌面"")
# 按下回车键，进入文件夹
xbot_visual.keyboard.send_keys(keys=""{enter}"")
# 遍历文件夹内的所有.txt文件
for file in xbot_visual.desktop.iter_all_elements(window=""0"", element=""*.txt""):
    # 双击打开文件
    xbot_visual.desktop.click(window=""0"", element=file, clicks=""dbclick"")
    # 在文件中查找特定字符串，例如电子邮件地址
    if xbot_visual.desktop.exist_text(window=""0"", text=""example@example.com""):
        # 打印文件名
        print(xbot_visual.desktop.get_attribute(window=""0"", element=file, attribute_name=""text""))
    # 关闭文件
    xbot_visual.desktop.click(window=""0"", element=""关闭"")
``` END",{'err_funcs': ['xbot_visual.desktop.exist_text']},['err_funcs']
在iTunes中，自动搜索并播放特定艺术家的前五首热门歌曲。,"```python
# 打开iTunes软件
process_info=xbot_visual.desktop.launch(process_name=""iTunes"")
# 在搜索框中输入特定艺术家的名称
xbot_visual.desktop.input(window=""0"", element=""iTunes搜索框"", text=""Taylor Swift"")
# 点击搜索按钮
xbot_visual.desktop.click(window=""0"", element=""iTunes搜索按钮"")
# 等待搜索结果加载完成
xbot_visual.desktop.wait_until_page_loaded(window=""0"", timeout=""5"")
# 遍历搜索结果列表
for song in xbot_visual.desktop.iter_all_elements(window=""0"", element=""iTunes搜索结果列表""):
    # 获取歌曲名称
    song_name = xbot_visual.desktop.get_attribute(window=""0"", element=song, attribute_name=""text"")
    # 判断是否为热门歌曲
    if ""热门"" in song_name:
        # 双击歌曲，播放歌曲
        xbot_visual.desktop.click(window=""0"", element=song, clicks=""dbclick"")
        # 等待歌曲播放一段时间
        xbot_visual.desktop.sleep(secs=""180"")
        # 获取歌曲播放状态
        play_state = xbot_visual.desktop.get_attribute(window=""0"", element=""iTunes播放按钮"", attribute_name=""text"")
        # 如果歌曲正在播放
        if play_state == ""暂停"":
            # 点击播放按钮，暂停歌曲
            xbot_visual.desktop.click(window=""0"", element=""iTunes播放按钮"")
        # 关闭歌曲详情窗口
        xbot_visual.desktop.click(window=""0"", element=""iTunes歌曲详情窗口关闭按钮"")
        # 退出循环
        break
``` END","{'err_funcs': ['xbot_visual.desktop.wait_until_page_loaded', 'xbot_visual.desktop.sleep']}",['err_funcs']
在QuickBooks中，自动打开“收入”报告，并将总收入的数值复制到剪贴板。,"```python
# 打开QuickBooks
process_info=xbot_visual.desktop.launch(process_name=""QuickBooks"")
# 点击进入“收入”报告
xbot_visual.desktop.click(window=""0"", element=""收入报告"")
# 获取总收入的数值
total_income=xbot_visual.desktop.get_attribute(window=""0"", element=""总收入"", attribute_name=""text"")
# 将总收入的数值复制到剪贴板
xbot_visual.desktop.input.keyboard(window=""0"", element=""总收入"", keystrokes=""^(c)"")
``` END",{'err_funcs': ['xbot_visual.desktop.input.keyboard']},['err_funcs']
在Quicken中，自动导航到“投资”选项卡，并将所有股票的当前价格和变动百分比打印出来。,"```python
# 打开Quicken软件
process_info=xbot_visual.desktop.launch(process_name=""Quicken"")
# 点击导航到“投资”选项卡
xbot_visual.desktop.click(window=""0"", element=""投资选项卡"")
# 遍历所有股票对象
for stock in xbot_visual.desktop.iter_all_elements(window=""0"", element=""股票对象""):
    # 获取股票的当前价格
    stock_price = xbot_visual.desktop.get_attribute(window=""0"", element=stock, attribute_name=""text"")
    # 获取股票的变动百分比
    stock_change = xbot_visual.desktop.get_attribute(window=""0"", element=stock, attribute_name=""text"")
    # 打印股票的当前价格和变动百分比
    print(f""股票当前价格：{stock_price}，变动百分比：{stock_change}"")
``` END",{},[]
在Adobe Photoshop中，自动找到最近5个打开过的项目，并将其导出为JPG格式保存到指定文件夹。,"```python
# 打开Adobe Photoshop
process_info=xbot_visual.desktop.launch(process_name=""Adobe Photoshop"")
# 点击文件菜单
xbot_visual.desktop.click(window=""0"", element=""文件菜单"")
# 点击导出子菜单
xbot_visual.desktop.click(window=""0"", element=""导出子菜单"")
# 在导出对话框中，输入保存路径和文件名
xbot_visual.desktop.input(window=""0"", element=""保存路径输入框"", text=""C:\\Export\\project1.jpg"")
# 点击保存按钮
xbot_visual.desktop.click(window=""0"", element=""保存按钮"")
# 循环最近5个打开的项目
for i in range(5):
    # 点击文件菜单
    xbot_visual.desktop.click(window=""0"", element=""文件菜单"")
    # 点击导出子菜单
    xbot_visual.desktop.click(window=""0"", element=""导出子菜单"")
    # 在导出对话框中，输入保存路径和文件名
    xbot_visual.desktop.input(window=""0"", element=""保存路径输入框"", text=""C:\\Export\\project{}.jpg"".format(i+2))
    # 点击保存按钮
    xbot_visual.desktop.click(window=""0"", element=""保存按钮"")
``` END",{},[]
在Steam中，自动找到所有已安装但未更新的游戏，并执行更新。,"```python
# 打开Steam
process_info=xbot_visual.desktop.launch(process_name=""Steam"")
# 点击进入游戏库
xbot_visual.desktop.click(window=""0"", element=""游戏库"")
# 遍历所有已安装但未更新的游戏对象列表
for game in xbot_visual.desktop.iter_all_elements(window=""0"", element=""已安装但未更新的游戏对象""):
    # 点击进入游戏详情页
    xbot_visual.desktop.click(window=""0"", element=game)
    # 点击更新按钮
    xbot_visual.desktop.click(window=""0"", element=""更新按钮"")
    # 关闭游戏详情页
    xbot_visual.desktop.click(window=""0"", element=""关闭按钮"")
``` END",{},[]
在AutoCAD中，找出所有未锁定的图层，然后给这些图层上锁，之后缩小窗口并移到屏幕一角。,"```python
# 打开AutoCAD软件
process_info=xbot_visual.desktop.launch(process_name=""AutoCAD"")
# 点击进入图层管理
xbot_visual.desktop.click(window=""0"", element=""图层管理"")
# 遍历所有图层元素
for layer in xbot_visual.desktop.iter_all_elements(window=""0"", element=""图层元素""):
    # 获取图层名称
    layer_name = xbot_visual.desktop.get_attribute(window=""0"", element=layer, attribute_name=""text"")
    # 判断图层是否已锁定
    if ""已锁定"" in layer_name:
        # 点击图层名称，进入图层属性设置
        xbot_visual.desktop.click(window=""0"", element=layer)
        # 在图层属性设置中，点击锁定按钮，解锁图层
        xbot_visual.desktop.click(window=""0"", element=""锁定按钮"")
# 点击应用更改按钮，保存图层设置
xbot_visual.desktop.click(window=""0"", element=""应用更改按钮"")
# 点击关闭按钮，关闭图层管理窗口
xbot_visual.desktop.click(window=""0"", element=""关闭按钮"")
# 点击最小化按钮，将AutoCAD窗口缩小
xbot_visual.desktop.click(window=""0"", element=""最小化按钮"")
# 将AutoCAD窗口移动到屏幕一角
xbot_visual.desktop.move(window=""0"", x=""0"", y=""0"")
``` END",{},[]
在实体门店的订单处理软件里，自动找出当天有退货请求的订单，然后标记这些订单并移动窗口到屏幕的一边，以便于处理。,"```python
# 打开订单处理软件
process_info=xbot_visual.desktop.launch(process_name=""订单处理软件"")
# 点击进入订单管理模块
xbot_visual.desktop.click(window=""0"", element=""订单管理"")
# 点击进入退货请求模块
xbot_visual.desktop.click(window=""0"", element=""退货请求"")
# 遍历订单对象列表
for order in xbot_visual.desktop.iter_all_elements(window=""0"", element=""订单对象""):
    # 获取订单的日期
    order_date = xbot_visual.desktop.get_attribute(window=""0"", element=order, attribute_name=""text"")
    # 判断订单的日期是否为当天
    if order_date == ""当天"":
        # 获取订单的状态
        order_status = xbot_visual.desktop.get_attribute(window=""0"", element=order, attribute_name=""text"")
        # 判断订单的状态是否为退货请求
        if order_status == ""退货请求"":
            # 标记订单
            xbot_visual.desktop.click(window=""0"", element=""标记订单"")
# 移动窗口到屏幕的一边
xbot_visual.desktop.move_window(window=""0"", x=""0"", y=""0"")
``` END",{'err_funcs': ['xbot_visual.desktop.move_window']},['err_funcs']
在Skype里，自动找到最近5个未接电话，并把这些电话的信息录入到一个记事本里。,"```python
# 打开Skype软件
process_info=xbot_visual.desktop.launch(process_name=""Skype"")
# 点击进入未接电话列表
xbot_visual.desktop.click(window=""0"", element=""未接电话"")
# 遍历未接电话对象列表
for call in xbot_visual.desktop.iter_all_elements(window=""0"", element=""未接电话对象""):
    # 获取电话号码
    phone_number = xbot_visual.desktop.get_attribute(window=""0"", element=call, attribute_name=""text"")
    # 将电话号码写入记事本
    xbot_visual.desktop.input(window=""0"", element=""记事本编辑区"", text=phone_number)
    # 按下回车键
    xbot_visual.keyboard.send_keys(keys=""{enter}"")
``` END",{},[]
在Adobe Photoshop里，逐一保存所有项目，并在操作完成后关闭软件。,"```python
# 打开Adobe Photoshop软件
process_info=xbot_visual.desktop.launch(process_name=""Adobe Photoshop"")
# 遍历所有项目
for project in xbot_visual.desktop.iter_all_elements(window=""0"", element=""所有项目""):
    # 点击项目，打开对应的编辑窗口
    xbot_visual.desktop.click(window=""0"", element=project)
    # 点击保存按钮，保存项目
    xbot_visual.desktop.click(window=""0"", element=""保存按钮"")
    # 在保存对话框中，输入文件名
    xbot_visual.desktop.input(window=""0"", element=""文件名输入框"", text=""文件名"")
    # 点击保存按钮，完成保存
    xbot_visual.desktop.click(window=""0"", element=""保存按钮"")
    # 关闭编辑窗口
    xbot_visual.desktop.click(window=""0"", element=""关闭按钮"")
# 关闭Adobe Photoshop软件
xbot_visual.desktop.close(window=""0"")
``` END",{},[]
在店铺的客服管理软件里，找到所有未回复的客户留言。,"```python
# 打开店铺的客服管理软件
process_info=xbot_visual.desktop.launch(process_name=""店铺的客服管理软件"")
# 点击进入客户留言模块
xbot_visual.desktop.click(window=""0"", element=""客户留言"")
# 遍历所有客户留言对象
for message in xbot_visual.desktop.iter_all_elements(window=""0"", element=""客户留言对象""):
    # 获取客户留言对象的回复状态
    reply_status = xbot_visual.desktop.get_attribute(window=""0"", element=message, attribute_name=""text"")
    # 判断回复状态是否为未回复
    if reply_status == ""未回复"":
        # 点击客户留言对象，进入回复界面
        xbot_visual.desktop.click(window=""0"", element=message)
        # 在回复输入框中输入回复内容
        xbot_visual.desktop.input(window=""0"", element=""回复输入框"", text=""感谢您的留言，我们会尽快处理！"")
        # 点击发送按钮，发送回复
        xbot_visual.desktop.click(window=""0"", element=""发送按钮"")
        # 回退到客户留言列表
        xbot_visual.desktop.back()
# 打印所有未回复的客户留言
xbot_visual.desktop.print_all(window=""0"", element=""客户留言对象"")
``` END","{'err_funcs': ['xbot_visual.desktop.print_all', 'xbot_visual.desktop.back']}",['err_funcs']
将桌面记事本图标放置到屏幕的左上角。,"```python
# 获取桌面记事本图标的位置
notepad_icon_position = xbot_visual.desktop.get_position(window=""0"", element=""桌面记事本图标"")
# 将桌面记事本图标放置到屏幕的左上角
xbot_visual.desktop.move(window=""0"", element=""桌面记事本图标"", x=""0"", y=""0"")
``` END","{'err_funcs': ['xbot_visual.desktop.get_position'], 'extra_args': [""xbot_visual.desktop.move:['element']""]}","['err_funcs', 'extra_args']"
将桌面上所有图标移动到一个D盘中新建的图标文件夹中。,"```python
# 打开资源管理器
xbot_visual.keyboard.send_keys(keys=""#{e}"")
# 在资源管理器地址栏中输入桌面路径
xbot_visual.desktop.input(window=""0"", element=""资源管理器地址栏"", text=""C:\\Users\\User\\Desktop"")
# 按下回车键，打开桌面路径
xbot_visual.keyboard.send_keys(keys=""{enter}"")
# 右键点击桌面，弹出菜单
xbot_visual.desktop.click(window=""0"", element=""桌面"", button=""right"")
# 点击新建菜单
xbot_visual.desktop.click(window=""0"", element=""新建"", clicks=""1"")
# 点击文件夹菜单
xbot_visual.desktop.click(window=""0"", element=""文件夹"", clicks=""1"")
# 输入文件夹名称
xbot_visual.desktop.input(window=""0"", element=""文件夹名称输入框"", text=""图标文件夹"")
# 按下回车键，创建文件夹
xbot_visual.keyboard.send_keys(keys=""{enter}"")
# 遍历桌面上的图标
for icon in xbot_visual.desktop.iter_all_elements(window=""0"", element=""桌面图标""):
    # 拖拽图标到文件夹
    xbot_visual.desktop.drag_to_element(window=""0"", element=icon, target=""图标文件夹"")
``` END",{},[]
双击打开桌面测试文件夹。,"```python
# 双击打开桌面测试文件夹
xbot_visual.desktop.click(window=""0"", element=""桌面测试文件夹"", clicks=""dbclick"")
``` END",{},[]
勾选桌面元素复选框。,"```python
# 打开桌面元素
xbot_visual.desktop.click(window=""0"", element=""桌面元素"")
# 勾选复选框
xbot_visual.desktop.set_checkbox(window=""0"", element=""复选框"", check_state=""check"")
``` END",{},[]
在桌面上的会计软件中，打开“税收报告”模块。在显示的列表中，找到所有与“Q4 2023”相关的条目。每个条目左侧都有一个复选框，选中所有Q4相关条目。点击下方的“生成总结报告”按钮，保存生成的报告为“Q4_2023_Summary.pdf”到桌面。,"```python
# 打开会计软件
process_info=xbot_visual.desktop.launch(process_name=""会计软件"")
# 点击进入税收报告模块
xbot_visual.desktop.click(window=""0"", element=""税收报告"")
# 遍历所有条目对象
for item in xbot_visual.desktop.iter_all_elements(window=""0"", element=""条目""):
    # 获取条目的文本
    item_text = xbot_visual.desktop.get_attribute(window=""0"", element=item, attribute_name=""text"")
    # 判断条目是否与""Q4 2023""相关
    if ""Q4 2023"" in item_text:
        # 选中条目的复选框
        xbot_visual.desktop.set_checkbox(window=""0"", element=""条目复选框"", check_state=""check"")
# 点击生成总结报告按钮
xbot_visual.desktop.click(window=""0"", element=""生成总结报告"")
# 在弹出的保存对话框中，输入文件名为""Q4_2023_Summary.pdf""
xbot_visual.desktop.input(window=""0"", element=""文件名输入框"", text=""Q4_2023_Summary.pdf"")
# 点击保存按钮
xbot_visual.desktop.click(window=""0"", element=""保存"")
# 关闭会计软件
xbot_visual.desktop.close_all()
``` END",{'err_funcs': ['xbot_visual.desktop.close_all']},['err_funcs']
打开下载文件夹，将剪切板内容创建一个txt文件，放到下载文件夹中。,"```python
# 打开下载文件夹
xbot_visual.keyboard.send_keys(keys=""#d"")
# 将剪切板内容创建一个txt文件
xbot_visual.desktop.save_as.save(file_name=""%UserProfile%\\Downloads\\剪切板内容.txt"", folder=""Downloads"")
``` END",{'err_funcs': ['xbot_visual.desktop.save_as.save']},['err_funcs']
"我经常使用桌面上的一个小工具来快速调整音量。工具上有一个滑动条，我希望将这个滑动条从当前位置拖拽到屏幕坐标""(500, 300)""以达到我想要的音量。","```python
# 获取小工具窗口
tool_window = xbot_visual.desktop.get(title=""小工具"")
# 拖拽滑动条到指定位置
xbot_visual.desktop.drag_by(window=tool_window, element=""滑动条"", x=""500"", y=""300"")
``` END",{'err_funcs': ['xbot_visual.desktop.drag_by']},['err_funcs']
"我使用桌面的文件管理器，经常需要将文件从一个文件夹拖到另一个位置。现在我想将某文件自动拖拽到屏幕坐标""(400, 400)""处的另一个文件夹中。","```python
# 获取文件对象
file = xbot_visual.desktop.get(title=""文件"")
# 拖拽文件到指定位置
xbot_visual.desktop.drag_to_point(window=file, element=""文件"", x=""400"", y=""400"")
``` END",{},[]
我希望将桌面上的某个图片文件放在桌面的右下角。,"```python
# 获取桌面上的图片文件
image_file = xbot_visual.desktop.get_attribute(window=""0"", element=""桌面上的图片文件"", attribute_name=""src"")
# 将图片文件拖拽到桌面的右下角
xbot_visual.desktop.drag_to_point(window=""0"", element=""桌面上的图片文件"", x=""1920"", y=""1080"")
``` END",{},[]
在使用Skype时，我想检查是否收到新的未读消息。如果有，我想要自动回复“我现在有点忙，稍后再联系你”。,"```python
# 打开Skype
process_info=xbot_visual.desktop.launch(process_name=""Skype"")
# 检查是否有未读消息
if xbot_visual.desktop.contains_string(window=""0"", element=""未读消息提醒"", str_to_be_checked=""1""):
    # 点击进入消息列表
    xbot_visual.desktop.click(window=""0"", element=""消息列表"")
    # 在输入框中输入回复内容
    xbot_visual.desktop.input(window=""0"", element=""输入框"", text=""我现在有点忙，稍后再联系你"")
    # 点击发送按钮
    xbot_visual.desktop.click(window=""0"", element=""发送按钮"")
    # 打印回复已发送
    print(""回复已发送"")
# 如果没有未读消息
else:
    # 打印没有未读消息
    print(""没有未读消息"")
``` END",{'err_funcs': ['xbot_visual.desktop.contains_string']},['err_funcs']
我想确认Spotify音乐播放器是否处于静音状态，如果是，我想要取消静音。,"```python
# 打开Spotify音乐播放器
process_info=xbot_visual.desktop.launch(process_name=""Spotify"")
# 获取静音按钮的状态
mute_status = xbot_visual.desktop.get_attribute(window=""0"", element=""静音按钮"", attribute_name=""enabled"")
# 如果静音按钮是开启状态
if mute_status == ""true"":
    # 点击静音按钮，取消静音
    xbot_visual.desktop.click(window=""0"", element=""静音按钮"")
``` END",{},[]
在打开Steam游戏平台时，我想确认是否已进入到我的游戏库页面。,"```python
# 打开Steam游戏平台
process_info=xbot_visual.desktop.launch(process_name=""Steam"")
# 点击进入我的游戏库
xbot_visual.desktop.click(window=""0"", element=""我的游戏库"")
# 获取当前激活的窗口
steam_window = xbot_visual.desktop.get_active(window=""Steam"")
# 判断是否已进入到我的游戏库页面
if xbot_visual.desktop.contains_element(window=""0"", element=""我的游戏库"", limit=""1""):
    # 打印已进入到我的游戏库页面
    print(""已进入到我的游戏库页面"")
# 否则
else:
    # 打印未进入到我的游戏库页面
    print(""未进入到我的游戏库页面"")
``` END","{'extra_args': [""xbot_visual.desktop.get_active:['window']"", ""xbot_visual.desktop.contains_element:['limit']""]}",['extra_args']
打开回收站，检查是否有文件。如果有，我想要将所有文件恢复到原来的位置。,"```python
# 打开回收站
xbot_visual.desktop.click(window=""0"", element=""回收站图标"", clicks=""dbclick"")
# 检查是否有文件
if xbot_visual.desktop.contains_element(window=""0"", element=""文件""):
    # 将所有文件恢复到原来的位置
    xbot_visual.desktop.click(window=""0"", element=""恢复所有文件按钮"")
``` END",{},[]
"自动化查找桌面上是否存在一个名为 ""MyApp"" 的应用程序图标，并根据结果执行不同的操作。","```python
# 打开桌面
xbot_visual.desktop.click(window=""0"", element=""桌面"", button=""left"", clicks=""2"")
# 在桌面上查找应用程序图标
if xbot_visual.desktop.exists(window=""0"", element=""MyApp""):
    # 如果存在，打印存在
    print(""存在"")
else:
    # 如果不存在，打印不存在
    print(""不存在"")
``` END","{'extra_args': [""xbot_visual.desktop.exists:['window', 'element']""], 'misss_args': [""xbot_visual.desktop.exists:['title']""]}","['extra_args', 'misss_args']"
判断微信窗口是否存在，如果存在则关闭微信窗口，如果不存在打印未找到微信窗口。,"```python
# 判断微信窗口是否存在
if xbot_visual.desktop.exists(title=""微信""):
    # 如果存在则关闭微信窗口
    xbot_visual.desktop.close(title=""微信"")
else:
    # 如果不存在打印未找到微信窗口
    print(""未找到微信窗口"")
``` END","{'extra_args': [""xbot_visual.desktop.close:['title']""], 'misss_args': [""xbot_visual.desktop.close:['window']""]}","['extra_args', 'misss_args']"
如果存在微信窗口而且有微信消息输入框存在，就把桌面上的example.txt文件拖拽到消息输入框中，同时打印执行情况消息。,"```python
# 拖拽example.txt文件到微信消息输入框
xbot_visual.desktop.drag_to_element(file_path=""C:/Users/Username/Desktop/example.txt"", element=""微信消息输入框"")
# 打印执行情况消息
print(""文件已经拖拽到微信消息输入框"")
``` END","{'extra_args': [""xbot_visual.desktop.drag_to_element:['file_path']""], 'misss_args': [""xbot_visual.desktop.drag_to_element:['window', 'target']""]}","['extra_args', 'misss_args']"
如果存在qq窗口，就把桌面文件夹依次拖拽到qq窗口的文件传输对话框中，同时打印执行情况消息。,"```python
# 拖拽桌面文件夹到qq窗口
xbot_visual.desktop.drag_to_point(window=""0"", element=""桌面文件夹"", x=""100"", y=""100"")
# 点击qq窗口的文件传输对话框
xbot_visual.desktop.click(window=""0"", element=""qq文件传输对话框"")
# 循环qq窗口的文件传输对话框中的文件列表
for file in xbot_visual.desktop.iter_all_elements(window=""0"", element=""qq文件传输对话框文件列表""):
    # 打印文件名称
    print(xbot_visual.desktop.get_attribute(window=""0"", element=file, attribute_name=""text""))
# 打印执行情况
print(""文件已传输"")
``` END",{},[]
我在玩一个游戏，需要把所有小鱼图像拖到屏幕左上角上。,"```python
# 打开游戏
process_info=xbot_visual.desktop.launch(process_name=""游戏"")
# 遍历所有小鱼图像对象
for fish in xbot_visual.desktop.iter_all_elements(window=""0"", element=""小鱼图像""):
    # 拖拽小鱼图像到屏幕左上角
    xbot_visual.desktop.drag_to_point(window=""0"", element=fish, x=""0"", y=""0"")
``` END",{},[]
