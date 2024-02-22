```

                MBR分析及修改
            
                        Written by Black White
                        iceman@zju.edu.cn
                        June 8, 2021.

1. 计算机启动过程
(1) 计算机从ROM启动, 执行的第1条指令的地址为:
FFFF:0000

(2) ROM启动过程中会读取硬盘的0道/0头/1扇区到
0000:7C00, 再执行一条远跳指令:
jmp 0000:7C00

(3) 步骤(2)的代码会搜索活动分区设为C:, 并读取
C:的第1个扇区(0道/1头/1扇区)到0000:7C00, 再执
行一条远跳指令:
jmp 0000:7C00

(4) 步骤(3)的代码会搜索C:\io.sys(DOS)或
c:\ntldr(XP)并读取该文件内容到内存中,再
执行一条远跳指令跳到文件内容中


2. 读取硬盘的扇区或者系统文件的内容都需要调用
bios的中断: int 13h
mov ah, 2; 2表示读扇区
mov al, 扇区数; 1
mov dl, 80h; 80h表示第1个物理硬盘, 81h是第2个物理硬盘
mov dh, 磁头号; 0 (base 0)
mov cl, 扇区号; 1 (base 1), 其中CL的高2位表示磁道高2位
mov ch, 磁道号; 0 (base 0)
mov bx, seg buf
mov es, bx
mov bx, offset buf
int 13h

3. 道、头、扇的递增顺序
      10位    8位    1~3Fh(6位)
disk[磁道号][磁头号][扇区号]
       0       0       3Fh
       0       1       01h
       0     0FFh      3Fh
       1       0       01h
      3FFh
最大的硬盘扇区数= 400h*100h*3Fh 大约8G

4. 如何读容量超过8G的硬盘扇区
int 13h/AH=42h可以读取更大容量的硬盘(超过8G)
mov ah, 42h
mov dl, 80h
mov si, seg para
mov ds, si
mov si, offset para
int 13h

para:
10h;\ sizeof(para)=0010h
00h;/
01h;\ 要读的扇区数=1
00h;/
78h;\
56h; \buf的地址=1234h:5678h
34h; /
12h;/
00h, 00h, 00h, 00h, 00h, 00h, 00h, 00h; 起始逻辑扇区号(即LBA)=0
只用扇区号不用道/头/扇的扇区表示方法称为LBA(logical block addressing)

假定1条磁道有100h个磁头, 1个磁头有3Fh个扇区
则C/H/S可以按以下公式转化成LBA:
LBA = (C*100h+H)*3Fh + S - 1

C:cylinder柱面
H:head磁头
S:sector扇区

5. 如何跟踪MBR(master boot record)即0道/0头/1扇区的引导过程
bochsdbg.exe -> Load -> dos.bxrc -> Start
Bochs Enhanced Debugger窗口->输入以下命令: 
   pb 0x7C00
此命令表示对物理地址0x7C00设置一个硬件执行断点;
点continue按钮或输入命令c让rom程序继续运行
过一会cpu会停在0000:7C00处, 按F8单步跟踪

200h字节的0道/0头/1扇区内容中, 偏移+1BE处是分区表
在bochs中输入以下命令可以保存0:600~0:800这段内存
到文件mboot.dat中:
writemem "mboot.dat" 0x600 0x200

6. 分区信息结构
C:盘的16字节分区信息如下:
            ;分区标识可参考datarecovery.com/rd/hexadecimal-flags-for-partition-type
            +--分区标识(06=FAT16, 07=NTFS or exFAT, 0B=FAT32, 05=扩展分区)
            |  +--C盘最后扇区的磁头号=0F
            |  |  +---扇区号
            |  |  |  +--磁道号
            |  |  |  |
DL DH CL CH v  v  v  v
80 01 01 00 06 0F 3F 50 3F 00 00 00 B1 3E 01 00
-- -- -- --             =========== ===========
^  ^  ^  ^              C盘的起始   C盘的总共
|  |  |  |              逻辑扇区号  扇区数
|  |  |  +--磁道号=0    (base 0)
|  |  +---扇区号=1
|  +--C盘首扇区的磁头号=1
+---活动分区必须=80h; 00h表示数据分区

7. 如何修改MBR(master boot record)即0道/0头/1扇区实现启动时验证密码?
先把第5节中保存的mboot.dat做个备份设为mboot0.dat, 再用QV打开mboot.dat, 
按几次回车直到看到汇编代码;
光标移到地址10h处, 按Tab键跳到汇编指令一栏, 输入:
   call E0
F5输入E0定位到地址E0处
Tab键跳到汇编指令栏, 输入以下代码:
   push si                   
   mov di,7D20               
   mov ah,00                 
   int 16                    
   cmp al,0D                 
   jz EF               
   stosb      
   jmp E4              
   mov al,00                 
   stosb
   mov si,7D06               
   mov cx,6               
   mov di,7D20               
   repe cmpsb
   jz 101               
   jmp FF              
   mov di,0600               
   pop si                    
   ret                       
按Tab跳回机器码一栏, 按Alt+F9保存
光标移到地址106处, 按两次回车, 切换到十六进制、ASCII字符对照模式,
按Tab键跳到字符一栏, 输入:
   123456
这6个字符就是密码。
按Tab键跳回16进制一栏, 按Alt+F9保存。
用QV打开Bochs文件夹里面的dos.img, 在文件内容的最开始处(地址0)按Ins
标记块首, 按朝下键, 移动光标到地址1FF处, 再按一次Ins键;
按Shift+F3, 输入mboot.dat, 用mboot.dat中的内容覆盖dos.img的最开始
200h字节, 按Alt+F9保存。
重新在Bochs里面打开dos.bxrc, 对修改过的mboot进行调试。
调试完毕后, 用QV打开dos.img, 用Ins键选上地址0到地址1FF之间的字节,
按Shift+F3输入mboot0.dat恢复mbr, 按Alt+F9保存。

```

