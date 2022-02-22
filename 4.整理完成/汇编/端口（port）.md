**CPU <->端口(port) **<->**I/O设备**
**端口编号就是端口地址。端口地址的范围是：**
**[0000h, 0FFFFh]，共65536个端口。**
**对端口操作使用指令in与out实现。**
# 通过60h号端口，CPU与键盘之间可以建立通讯。
**in al, 60h; 从端口60h读取一个字节并存放到AL中**
**例如: [http://10.71.45.100/bhh/key.asm](http://10.71.45.100/bhh/key.asm)**
** **
# 70h及71h端口与芯片cmos内部的时钟有关。
**其中cmos中的地址4、2、0中分别保存了当前的时、分、秒，并且格式均为BCD码。**
**mov al, 2**
**out 70h, al**
**in al, 71h; 读取cmos中2号单元的值**
** **
**mov al, 4**
**out 70h, al**
**mov al, 23h**
**out 71h, al; 把cmos4号单元即小时的值改成23点**
** **
**例如: [http://10.71.45.100/bhh/readtime.asm](http://10.71.45.100/bhh/readtime.asm)**
** **
**以读取键盘为例, 以下为从高层到低层的编程方式排序:**
**dos       高 mov ah, 1; int 21h 功能弱,但编程简单**
**bios     中 mov ah, 0; int 16h**
**in/out   低 in al, 60h; 功能强, 但编程麻烦**
** **
**例如: [http://10.71.45.100/bhh/music.asm](http://10.71.45.100/bhh/music.asm)**
