# Native badcase分析

![image-20230914103224323](https://raw.githubusercontent.com/mowang111/image-hosting/master/img/image-20230914103224323.png)

## 函数名错误

1. 有些函数名直接改成他喜欢的函数名

![image-20230914104735106](C:\Users\11547\AppData\Roaming\Typora\typora-user-images\image-20230914104735106.png)

2. 乱编函数

   	1. 函数 xbot_visual.win32.window.bring_window_to_front 未定义', '函数 xbot_visual.wait 未定义'、

   	1. 

![image-20230914105243878](https://raw.githubusercontent.com/mowang111/image-hosting/master/img/image-20230914105243878.png)

​			

xbot_visual.win32.element.close_win_element 未定义（他想用这个关闭文件选择框这个元素，本来应该用点击这个指令)

3. 



## 参数错误

1. input_win_element 缺失参数: {'append', 'contains_hotkey'}",

3. click_win_element 缺失参数: {'button'}
4. get_win_element_screenshot 有多余的参数: {'save_as'}"
5. get_win_element_screenshot 缺失参数: {'folder_path'}
6. close_window,activate_window有多余的参数: {'window_title'}"
7. click_win_element 有多余的参数: {'y', 'x'}"
8. xbot_visual.win32.element.input_win_element 缺失参数: {'contains_hotkey'}