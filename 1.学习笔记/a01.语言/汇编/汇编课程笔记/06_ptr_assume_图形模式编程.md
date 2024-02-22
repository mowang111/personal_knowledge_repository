```
1. ptr
byte ptr,   word ptr,      dword ptr
(char *)   (short int *)  (long int *)
当目标操作数与源操作数的其中之一有明确的宽度时，另外一方不需要加类型修饰, 例如:
mov ds:[bx], ah; 等价于mov byte ptr ds:[bx],ah
mov ax, ds:[bx+si]
;等价于mov ax, word ptr ds:[bx+si]
当源操作数为常数，目标操作数为变量时，则该变量必须加上类型修饰，例如:
mov ds:[bx], 1; 错误
mov byte ptr ds:[bx], 1; ①正确
mov word ptr ds:[bx], 1; ②正确
mov dword ptr ds:[bx], 1; ③正确
设ds=1000h,  bx=2000h
1000:2000 12h; ① 01h ②->01h ③-> 	01h
1000:2001 34h       34h     	00h			00h
1000:2002 56h       56h     	56h			00h
1000:2003 78h       78h			78h			00h

2. assume的作用
帮助编译器建立段寄存器与段的关联, 当源程序中引用了某个 段内的变量时，编译器会在编译出来的机器码中把变量的段地址替换成关联的段寄存器。
http://10.71.45.100/bhh/assume.asm

3. 图形模式编程
(1) 如何把显卡切换到图形模式: 调用int 10h中断
例如,要切换到分辨率320*200,颜色为256色的图形模式:
mov ah, 0  	; 其中AH=0表示int 10h的子功能号为0
mov al, 13h; 其中AL=13h代表图形模式编号
int 10h     ; int 10h是与显示相关的bios中断
(2) 如何把坐标(x,y)转化成13h模式下的偏移地址
y*320+x
(3) 显卡内存中的一个字节表示一个点
一个点对应一个字节,该字节的值表示该点的颜色，例如:
0=黑 1=蓝 2=绿 3=青 4=红 5=洋红 6=棕 7=白
8=灰 9=亮 A=亮 B=亮 C=亮 D=紫   E=黄 F=亮
        蓝   绿   	青   	红                白
http://10.71.45.100/bhh/block.asm
http://10.71.45.100/bhh/cn.asm
http://10.71.45.100/bhh/cnt.asm
```

