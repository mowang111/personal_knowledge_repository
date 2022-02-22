# 换码指令：XLAT (translate) 也称查表指令

```
在xlat执行前必须让ds:bx指向表, al必须赋值为
数组的下标; 执行xlat后, AL=ds:[bx+AL]
char t[]="0123456789ABCDEF";
char i;
i = 10;
i = t[i]; 最后i='A'

设ds=数组t的段地址
mov bx, offset t; BX=表的首地址
mov al, 10; AL为下标
xlat; 结果AL='A'
xlat指令要求DS:BX指向数组，AL=数组下标。
执行指令后, AL=数组元素
例子: http://10.71.45.100/bhh/xlat.asm
例子: http://10.71.45.100/bhh/xlat_sub.asm
```

# 算数指令

## 加法指令:add,inc,adc
## 减法指令:sub,sbb,dec,neg,cmp 
### (1) sub dest,src;
### (2) sbb dest,src;带借位减
```
;求56781234h-1111FFFFh的差
mov ax,1234h
sub ax,0FFFFh;CF=1
mov dx,5678
sbb dx,1111h;DX=5678h-11111h-CF
```
### (3) dec op;自减
### (4) neg op;求相反数

- op: reg, mem; 
- 会影响CF,ZF,SF等[标志位](https://www.yuque.com/mowang-6fbjm/gkuveu/qqtmrl#3V3Eh)
```
mov ax,1
neg ax;AX=-1=0FFFFh

mov ax,0FFFEh
neg ax;AX=2,CF=1,SF=0,ZF=0

neg ax ≡ (not ax) +1
-x ≡ ～x + 1
```
### (5) cmp ; 仅影响标志位状态

- ja, jb, jae, jbe 非符号数相关跳转指令
   - jb: CF==1 
   - ja: CF==0且ZF==0
- jg, jl, jge, jle 符号数比较相关跳转指令
   - jg: SF==OF且ZF==0
   - jge: SF==OF
   - jl: SF!=OF 不需要考虑ZF
```
mov ax, 3
mov bx, 2
cmp ax, bx; AX-BX=1, SF=0, OF=0 -> AX > BX
mov ah, 7Fh
mov bh, 80h
cmp ah, bh; AH-BH=0FFh, SF=1, OF=1 -> AX>BX
mov ax, 2
mov bx, 3
cmp ax, bx; AX-BX=FFFFh, SF=1, OF=0 -> AX<BX
mov ah, 80h
mov bh, 7Fh
cmp ah, bh; AH-BH=1, SF=0, OF=1 -> AX<BX
```
## 乘法指令：MUL, IMUL

```
AX=AL*src
DX:AX=AX:src
```



## 除法指令：DIV, IDIV

```
① 16位AX / 8位  = 8位AL(商)..8位AH(余数)
② 32位DX:AX / 16位 = 16位AX .. 16位DX
③ 64位EDX:EAX/32位=32位EAX .. 32位EDX
```



#### 除法溢出
(1) 除法溢出的两种情形:
①
```
mov ax, 1234h
mov bh, 0
div bh; 此时因为除以0, 所以会发生除法溢出
```


②
```
mov ax, 123h
mov bh, 1
div bh; 此时由于商无法保存到AL中, 因此也会发生溢出。
```

(2) 除法溢出时会发生什么?
```
mov ax, 123h
mov bh, 1
;除法溢出时会在此处插入int 00h并执行
;在dos系统下, int 00h会显示溢出信息并终止程序运行
div bh; 此处发生除法溢出
mov ah, 4Ch; \ 这2条指令将不可能被执行到
int 21h     ; /
```
(3)除法溢出的处理
```
code segment
assume cs:code
old_00h dw 0,0
int_00h:
  mov ch,10h
  iret; interrupt return 中断返回
  		; iret会执行以下动作：pop ip,pop cs,popf
main:
	push cs 
  pop ds
  xor ax,ax
  mov es,ax
  mov bx,0
  mov ax,es:[bx];偏移地址
  mov dx,es:[bx+2];段地址
  mov old_00h[0],ax
  mov old_00h[2],dx
  mov word ptr es:[bx],offset int_00h
  mov es:[bx+2],cs
  mov ax,123h
  mov ch,1
  ;插入指令int 00h并执行
  ;pushf, push cs, push offset back
  ;jmp dword ptr 0:[0]
back:
  div ch;发生除法溢出
  mov ax,old_00h[0]
  mov dx,o;d_00h[2]
  mov es:[bx],ax
  mov es:[bx+2],dx
  mov ah,4Ch
  int 21h
code ends
end main
```
## 小数运算
### 小数变量
```
pi dd 3.14; 32位小数,相当于float
r  dq  3.14159; 64位小数, 相当于double
							; q:quadruple 4倍的
s  dt  3.14159265; 80位小数, 相当于long double
```
### 小数运算
fadd, fsub, fmul, fdiv 由浮点处理器负责执行, 用法请参考主页intel指令集
### 小数寄存器
CPU内部一共有8个小数寄存器，分别叫做st(0)、st(1)、…、st(7)，其中st(0)简称st这8个寄存器的宽度均达到80位，相当于C语言中的long double类型。
```
;Turbo Debugger跟踪时，
;点菜单View->Numeric Processor查看小数堆栈
data segment
abc dd 3.14
xyz dd 2.0
result dd 0
data ends
code segment
assume cs:code, ds:data
main:
   mov ax, data
   mov ds, ax
   fld abc; 把3.14载入到小数堆栈 abc->st(0)
   fld xyz; 把2.0载入到小数堆栈 st(0)下沉到st(1) xyz->st(0)
   				;fild xyz;(xyz为整数2)
   fmul st, st(1); 两数相乘
   fstp result; 保存结果到result，并弹出
   fstp st      ; 弹出小数堆栈中残余的值
   mov ah, 4Ch
   int 21h
code ends
end main
```
# 逻辑运算与移位指令
## (1) 逻辑运算指令：AND，OR，XOR，NOT，TEST
```
mov ax, 9234h
test ax, 8000h; ZF=0, AX=9234h
jnz msb_is_one; most significant bit最高位
;test和and的关系相当于cmp和sub的关系。
```
判断某个寄存器是否为0的几种方法:
```
test cl, cl
or cl, cl
and cl, cl
or cl, 0
cmp cl, 0
```
上述每条指令后面都可以跟jz或jnz来判断CL是否为0。


## (2) 移位指令:shl, shr, sal, sar, rol,ror, rcl, rcr
rcl: rotate through carry left 带进位循环左移
rcr: rotate through carry right带进位循环右移

```
mov ah, 0B6h
stc; CF=1
rcl ah, 1; CF=1 AH=1011 0110 移位前
; CF=1 AH=0110 1101 移位后
mov ah, 0B6h
stc; CF=1
rcr ah, 1; AH=1011 0110  CF=1移位前
; AH=1101 1011  CF=0移位后
```
例如: 要把1234ABCDh逻辑左移3位, 结果保存在dx:ax
解法1:
```
mov dx, 1234h
mov ax, 0ABCDh
mov cl, 3
shl dx, cl
mov bx, ax
shl ax, cl
mov cl, 13
shr bx, cl
or dx, bx
```
解法2:
```
mov dx, 1234h
mov ax, 0ABCDh
mov cx, 3
next:
shl ax, 1
rcl dx, 1
dec cx
jnz next
```
sal: shift arithmetic left  算术左移
sar: shift arithmetic right 算术右移
sal及sar是针对符号数的移位运算, 对负数右移的时候
要在左边补1, 对正数右移的时候左边补0, 无论对正数还是负数左移右边都补0。显然sal≡shl。
shl及shr是针对非符号数的移位运算,无论左移还是
右移, 空缺的部分永远补0。
shl, shr, rol, ror, rcl, rcr最后移出去的那一位一定在CF中。


假定要把AX中的16位值转化成二进制输出:
解法1:
```
mov cx, 16
next:
shl ax, 1
jc is_1
is_0:
mov dl, '0'
jmp output
is_1:
mov dl, '1'
output:
push ax
mov ah, 2
int 21h
pop ax
dec cx
jnz next
```
解法2:
```
mov cx, 16
next:
shl ax, 1
mov dl, '0'
adc dl, 0
output:
push ax
mov ah, 2
int 21h
pop ax
dec cx
jnz next
```
C语言有2个库函数用来做循环左移及右移:
```c
unsigned int _rotl(unsigned int x, int n)
unsigned int _rotr(unsigned int x, int n)
unsigned int _rotl(unsigned int x, int n)
{
return x << n  | x >> sizeof(x)*8-n;
}
```
# 字符串操作指令
## 字符串传送（move string）
## 字符串比较（compare string）

> repe cmpsb 结束时且在ZF=0的情况下，SI与DI指向的并不是首个不相等的字符，而是首个不相等的字符后的那个字符，因为repe cmpsb总是为下次比较做好判断后才判断本次比较是否相等

## 字符串扫描（scan string）:scasb,scasw
```
scasb:
	cmp al,es:[di]
  di++;当DF=1时，为di--
  
repne scasb:
next:
	if(cx==0) goto done;
  cmp al,es:[di]
  		di++;当DF=1时，为di--
      cx--
  je done
  goto next
done:
```
例子: 假定从地址1000:2000开始存放一个字符串，请计算该字符串的长度并存放到CX中。假定字符串以ASCII码0结束，字符串长度不包括0。
```
mov ax, 1000h
mov es, ax
mov di, 2000h; ES:DI目标串
mov cx, 0FFFFh; CX=最多找FFFF次
mov al, 0; AL=待找的字符
cld       ; DF=0，表示正方向
repne scasb; again:
not cx      ; 相当于cx=FFFF-cx
dec cx
;上述两条指令也可以替换成以下两条指令:
;inc cx
;not cx
```
repe scasb
假定从地址1000:0000起存放以下字符串：
"###ABC"，现要求跳过前面的#，把后面剩余的
全部字符复制到2000:0000中。
假定es=1000h, di=0, cx=7, 则

```
mov al, '#'
cld
repe scasb
dec di; ES:DI->"ABC"
inc cx; CX=4
push es
pop ds; DS=ES
push di
pop si; SI=DI
mov ax, 2000h
mov es, ax
mov di, 0
rep movsb
```



## 存入字符串（store string）
## 从字符串取（load string）