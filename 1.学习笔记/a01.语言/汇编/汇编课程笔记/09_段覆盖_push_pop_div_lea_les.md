```

1. 32位间接寻址方式
(1) 32位比16位多了以下这种寻址方式:
[寄存器+寄存器*n+常数]
其中n=2、4、8。
例如:
mov eax, [ebx + esi*4]
设ebx是数组a的首地址, 下标i用esi表示
则上述语句相当于C语言的: eax = a[i];

mov eax, [ebx+esi*4+6]

VC里面要查看当前C代码对应的机器语言，可以在按F10开始调试后选菜单:
View->Debug Windows->Disassembly
TC里面要查看当前C代码对应的机器语言:
先把ary.c(http://10.71.45.100/bhh/ary.c)拷到dosbox86\tc,
集成环境中选菜单File->Dos Shell->
cd \tc
tc
File->Load->ary.c
Compile->Compile
Compile->Link
File->Quit
td ary.exe
View->CPU

这种寻址方式的应用:
long a[10]={...};
int i, n=10, sum=0;
for(i=0; i<n; i++)
   sum += a[i];
设ebx=&a[0], esi=0, eax=0, 则上述C代码可转化
成以下汇编代码:
again:
add eax, [ebx+esi*4]
add esi, 1
cmp esi, 10
jb again

(2) 32位寻址方式里面，对[]中的两个寄存器几乎不加限制例如:
ebx, ebp, esi, edi, 
eax, ecx, edx, esp都可以放到[]里面;
mov eax, [ebx+ebx*4]; 两个寄存器可以任意组合

2. 段覆盖(segment overriding)
通过在操作数前添加一个段前缀(segment prefix)如CS:、DS:、ES:、SS:来强制改变操作数的段址，这就是段覆盖。
段地址的隐含:
mov ax, [bx]
mov ax, [si]
mov ax, [di+2]
mov ax, [bx+si]
mov ax, [bx+di+2]
mov ax, [1000h]
上述指令的源操作数都省略了段地址ds。

[bp], [bp+2], [bp+si+2], [bp+di-1]
等价于
ss:[bp], ss:[bp+2], ss:[bp+si+2], ss:[bp+di-1]
当[]中包含有寄存器bp时，该变量的段地址一定是ss。
例如:
mov ax, [bp+2] 相当于
mov ax, ss:[bp+2]


默认的段地址是可以改变的, 例如:
mov ax, ds:[bp+2]
这条指令的源操作数段地址从默认的ss改成了ds。
同理,
mov ax, [bx+si+2]改成mov ax, cs:[bx+si+2]的话,
默认段地址就从ds变成了cs。

3．通用数据传送指令：MOV，PUSH，POP，XCHG
mov byte ptr ds:[bx], byte ptr es:[di]
错误原因:两个操作数不能同时为内存变量
以下为正确写法:
mov al, es:[di]
mov ds:[bx], al
 push、pop遵循先进后出(FILO)规则,例如:
 
 32位push、pop过程演示:
http://10.71.45.100/bhh/stk1.txt 代码
http://10.71.45.100/bhh/stk2.txt 堆栈布局
push/pop后面也可以跟变量,例如:
push word ptr ds:[bx+2]
pop word ptr es:[di]
8086中, push不能跟常数, 但80386及以后的cpu允许push一个常数。
push/pop后面不能跟一个8位的寄存器或变量:
push ah; 语法错误 push byte ptr ds:[bx]
pop al;语法错误   pop byte ptr es:[di]

mov ax, 1
mov bx, 2
xchg ax, bx; 则ax=2, bx=1
xchg ax, ds:[bx]

4. 除法指令: div
(1) 16位除以8位得8位
ax / 除数 = AL..AH
例如: div bh
设AX=123h, BH=10h
div bh; AL=12h, AH=03h
(2) 32位除以16位得16位
dx:ax / 除数 = ax..dx
例如: div bx
设dx=123h, ax=4567h, bx=1000h
div bx	; 1234567h/1000h
       	; AX=1234h, DX=0567h
(3) 64位除以32位得32位
edx:eax / 除数 = eax..edx
例如: div ebx
假定要把一个32位整数如7FFF FFFFh转化成十进制格式
则一定要采用(3)这种除法以防止发生除法溢出。
代码: http://10.71.45.100/bhh/val2decy.asm
5．地址传送指令：LEA, LDS, LES
(1) lea  dest, src  
load effective address=取变量的偏移地址
lea dx, ds:[1000h] ; DX=1000h
mov dx, 1000h; 上述lea指令的效果等同于mov指令

lea dx, abc ; 效果等价于以下指令
mov dx, offset abc
设abc的偏移地址=1000h
则lea dx, abc编译成:
lea dx, [1000h]
而mov dx, offset abc编译成:
mov dx, 1000h
          
mov dx, offset ds:[bx+si+3]; 语法错误
lea dx, ds:[bx+si+3]; dx=bx+si+3
mov dx, bx+si+3; 错误
mov dx, 1+2+3; 正确用法,因为右侧是常数表达式
mov dx, ((1*2+3) shl 2) xor 5; 正确

mov dx, bx; \
add dx, si;  | 效果等同于上述lea指令
add dx, 3 ; /

lea eax, [eax+eax*4]; EAX=EAX*5 用lea做乘法
lea eax, [eax+eax*2]; EAX=EAX*3

(2) 远指针(far pointer)
16位汇编中，远指针是指16位段地址:16位偏移地址;
32位汇编中，远指针是指16位段地址:32位偏移地址。
48位的远指针在汇编语言中有一个类型修饰词:
fword ptr
近指针(near pointer)：偏移地址就是近指针
16位汇编中，近指针是指16位的偏移地址；
32位汇编中，近指针是指32位的偏移地址；

远指针(far pointer)包括段地址及偏移地址两个部分；
近指针(near pointer)只包括偏移地址，不包含段地址。
                 12345678h
假定把一个远指针1234h:5678h存放到地址1000:0000中，则内存布局如下：  &p=1000:0000
1000:0000 78h  
1000:0001 56h  
1000:0002 34h  
1000:0003 12h  
设ds=1000h, bx=0
mov di, ds:[bx]; di=5678h
mov es, ds:[bx+2]; es=1234h
les di, dword ptr ds:[bx]
mov al, es:[di]; AL=byte ptr 1234:[5678]

假定把一个48位的远指针001B:12345678存放到地址1000:0000中，则内存布局如下：
1000:0000 78h  
1000:0001 56h  
1000:0002 34h  
1000:0003 12h  
1000:0004 1Bh
1000:0005 00h
假定要把1000:0000中存放的48位远指针取出来，存放到es:edi中，则
mov ax, 1000h
mov ds, ax
mov edi, dword ptr ds:[0]
mov es, word ptr ds:[4]

les edi, fword ptr ds:[0000h]
; es=001Bh, edi=12345678h


远指针的汇编语言例子:
http://10.71.45.100/bhh/les.asm
近指针的汇编语言例子:
http://10.71.45.100/bhh/nearptr.asm
远指针的C语言例子:
http://10.71.45.100/bhh/farptr.c
```

