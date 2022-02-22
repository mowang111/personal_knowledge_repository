# 1. 字符串操作指令stosb及lodsb

## (1) stosb, stosw, stosd

```
stosb:
stosb的操作过程如下:
es:[di] = AL
di++; DF=1时为di--
rep stosb: 循环CX次stosb
rep stosb的操作过程:
again:
if(cx == 0) goto done;
ES:[DI] = AL
DI++; 当DF=1时, 为DI--
CX--
goto again;
done:

例: 把从地址1000:10A0开始共100h个字节的
内存单元全部填0
mov ax, 1000h
mov es, ax; ES=1000h
mov di, 10A0h                    	mov di,10A0h
mov cx, 100h     mov cx, 80h    	mov cx,40h
cld                cld             	cld
xor al, al       xor ax, ax     	xor eax, eax
rep stosb        rep stosw       	rep stosd
```

## (2) lodsb

```
lodsb的操作过程:
AL=DS:[SI]
SI++;当DF=1时, 为SI--

例: 设DS:SI "##AB#12#XY"
且ES:DI指向一个空的数组, CX=11
通过编程过滤#最后使得ES:DI "AB12XY"
   cld
again:
   lodsb; AL=DS:[SI], SI++
         ; mov al, ds:[si]
         ; inc si
   cmp al, '#'
   je   next
   stosb; ES:[DI]=AL, DI++
         ; mov es:[di], al
         ; inc di
next:
   dec cx
   jnz again
```

# 2. 控制转移指令

## (1) jmp的3种类型

```
①jmp short target			; 短跳
②jmp near ptr target 	; 近跳
③jmp far ptr target  	; 远跳
一般情况下，编译器会自动度量跳跃的距离，因此我们在
写源程序的时候不需要加上short、near ptr、far ptr等类型修饰。即上述三种写法一律可以简化为jmp target。
```

## (2)短跳指令

```
①短跳指令的格式
jmp 偏移地址或标号
以下条件跳转指令也都属于短跳: jc jnc jo jno js jns jz jnz ja jb jae jbe jg jge jl jle jp jnp

②短跳指令的机器码
      地址            机器码   汇编指令  
    1D3E:0090     ...
    1D3E:0100     EB06     jmp  108h
短跳指令的机器码由2字节构成:
第1个字节=EB
第2个字节=
Δ=目标地址-下条指令的偏移地址=108h-102h=06h
    1D3E:0102     B402     mov  ah，2
    1D3E:0104     B241     mov  dl, 41h
    1D3E:0106     CD21     int  21h
  1D3E:0108     B44C     mov  ah，4Ch
    1D3E:010A     CD21     int  21h
   例:自我移动的代码 http://10.71.45.100/bhh/movcode.asm
   例: 修改printf让它做加法运算http://10.71.45.100/bhh/printf.c

③ 短跳太远跳不过去的解决办法
cmp ax, bx
je  equal; jump out of range
jne not_equal
jmp equal; 近跳
not_equal:
...; 假定这里省略指令的机器码总长度超过7Fh字节
equal:
...
```

## (3)近跳指令

```
①近跳指令的3种格式
jmp 偏移地址或标号; 如jmp 1000h
jmp 16位寄存器		; 如jmp bx
jmp 16位变量  		; 如jmp word ptr [addr]

②近跳指令的机器码
  地址        机器码      汇编指令    
1D3E:0100   E9FD1E      jmp  2000h
近跳指令的第1个字节=E9
第2个字节=Δ=目标地址-下条指令的偏移地址
=2000h-103h=1EFDh
1D3E:0103   B44C         mov  ah，4Ch
1D3E:0105   CD21         int  21h
...
1D3E:2000   ...

byte ptr ; 1字节
word ptr ; 2字节
dword ptr; 4字节(32位整数或float类型小数)
fword ptr; 6字节(4字节偏移地址+2字节段地址)
qword ptr; 8字节(64位整数或double类型小数)
tbyte ptr; 10字节(long double类型的80位小数)
short     用来修饰一个短的标号
near ptr 用来修饰一个近的标号
far ptr  用来修饰一个远的标号
```

## (4)远跳指令

```
①远跳指令的2种格式
jmp 段地址:偏移地址
jmp dword ptr 32位变量
②远跳指令的机器码
jmp 1234h:5678h; 机器码为0EAh,78h,56h,34h,12h
远跳到某个常数地址时,在源程序中不能直接用jmp指令，而应该改用机器码0EAh定义，如:
db 0EAh
dw 5678h
dw 1234h
上述3行定义合在一起表示jmp 1234h:5678h

例: jmp dword ptr 32位变量 的用法
data segment
addr dw 0000h, 0FFFFh 
;或写成addr dd 0FFFF0000h
data ends
code segment
assume cs:code, ds:data
main:
mov ax, data
mov ds, ax
jmp dword ptr [addr] 
;相当于jmp FFFF:0000
code ends
end main
 例: 演示短跳、近跳、远跳 http://10.71.45.100/bhh/jmp.asm
```

# 3. 循环指令：LOOP

```
loop  dest的操作过程:
CX = CX - 1   	; 循环次数减1
if(CX != 0)   	; 若CX不等于0，则
    goto  dest 	; 跳转至dest

例: 求1+2+3的和
mov ax, 0
mov cx, 3
next:
add ax, cx; ax +3, +2, +1
loop next; cx=2, 1, 0
           ; dec cx
           ; jnz next
done:
mov ax, 0
mov cx, 0
jcxz done  这条指令可以防止cx为0时进入循环
next:
add ax, cx
loop next; 循环10000h次
done:
```

# 4. call, ret指令

## (1) 汇编语言中的三种参数传递方式

```
① 寄存器传递
f:
   add ax, ax; ax=2*ax
   ret        ; 返回时ax就是函数值
main:
   mov ax, 3; ax就是f()的参数
   call f
next:
   mov ah, 4Ch
   int 21h


② 变量传递
f:
   mov ax, var
   add ax, ax; ax就是函数值
   ret
main:
   mov var, 3; var是一个16位的变量, 用作参数
   call f

在汇编语言中，用db、dw等关键词定义的变量均为全局变量。在堆栈中定义的变量才是局部变量。
③ 堆栈传递
f:
   push bp
   mov bp, sp
   mov ax, [bp+4]; 从堆栈中取得参数
   add ax, ax
   pop bp
   ret
main:
   mov ax, 3
   push ax; 参数压入到堆栈
   call f
   add sp, 2
```

## (2) C语言函数调用y=f(2,3)求两数之和转化成汇编语言

```
f:
   push bp;(4)
   mov bp, sp
   mov ax, [bp+4]
   add ax, [bp+6]
   pop bp; (5)
   ret; (6)
main:
   mov ax, 3
   push ax; (1)
   mov ax, 2
   push ax; (2)
   call f; (3)
here:
   add sp, 4;(7)
上述程序运行过程中的堆栈布局如下:
ss:1FF8 old bp <- bp (4)
ss:1FFA here <- (3)(5)
ss:1FFC 02   <- (2)(6)
ss:1FFE 03   <- (1)
ss:2000 ??   <- (7)

参数个数可变的函数例子: myprintf.c
http://10.71.45.100/bhh/myprintf.c

```

