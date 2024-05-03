```
1. 32位系统下的远指针
mov eax, ds:[ebx]; 这里的ebx表示32位偏移地址
在32位系统下，由于偏移地址的范围是[0, 232-1]，即可以在段地址不变只变化偏移地址的情况下可以访问4G空间，所以段寄存器cs=ds=es=ss并且是不变的。因此在C语言中，平时接触到指针均为近指针。
char *p;
short int *q;
long int *r;
double *s;
对上述变量求sizeof(),则sizoef(p)、sizeof(q)、sizeof(r)、sizeof(s)均等于4。
32位汇编中，远指针是指16位段地址+32位偏移地址。
若变量p定义成48位的远指针，则它的类型修饰为:
fword ptr
例如:
main:
   jmp begin
p 	dd 12345678h; p里面存放了一个48位的远指针
  	dw 18h       ; 18h:12345678h
	begin:
   les ebx, fword ptr cs:[p]; es=18h
                                 ; ebx=12345678h
   jmp fword ptr cs:[p]; jmp 18h:12345678h
在32位系统下，16位的段地址不再通过后面补一个十六进制的0来得到段首地址，而是要通过查表得到段首地址。
这里提到的表称为全局描述符表(Global Descriptor Table)，简称gdt表。gdt表其实是一个数组，该数组的首地址存放在gdtr寄存器内，数组中每个元素的宽度均为8字节。
设gdt表首地址为t，从地址t开始存放以下数据:
t+0   	xx,xx,xx,xx,xx,xx,xx,xx
t+8    	xx,xx,xx,xx,xx,xx,xx,xx
t+10h 	xx,xx,00h,00h,00h,xx,xx,80h
t+18h 	xx,xx,40h,30h,20h,xx,xx,10h
把段地址18h与t相加得到gdt表内第3个元素的偏移,
再取出t+18h指向的元素的值(共8字节), 其中第2、3、4、7个字节逆向排列得到段首地址=10203040h。把段首地址与偏移地址12345678h相加就得到了物理地址:
18h:12345678h = 10203040h + 12345678h
   逻辑地址                 物理地址
8字节中余下的4个xx计32位，其中20位用来表示段长度(长度单位可以是字节也可以是页，其中1页=4K)，剩余的12位中有一部分位用来表示段的ring级别(0、1、2、3共4级)及权限(读Read、写Write、执行eXecute)。
系统代码与用户代码用ring分级: 其中系统代码是ring0，而用户代码是ring3。ring级别保存在cs低2位中。当用户代码要访问某个段如18h时，cpu会检查用户代码的(cs & 0x0003)是否小于等于18h对应段描述中的ring级别，若条件为真则允许访问，否则拒绝访问。
保护模式(段有权限)  实模式(段无权限)

2. PUSHF，POPF
把标志寄存器FL压入堆栈/弹出堆栈
不能写成push FL  ,  pop FL
寄存器FL及IP在编程时都是不能直接引用的:
mov ip, ax;\
mov ax, ip; \ 都是错误的
mov bx, fl; /
mov fl, bx;/
如何间接改变ip:
cs:0123 jmp 1000h; ip=1000h
...
cs:1000 call 1234h; ip=1234h
cs:1003 mov ah, 4Ch
cs:1005 int 21h
cs:1234 ...
cs:1235 ret; ip=1003h
标志寄FL
stc指令可以使CF=1;
clc指令可以使CF=0;
cld指令可以使DF=0;
std指令可以使DF=1;
cli指令可以使IF=0;
sti指令可以使IF=1;
要让 TF=1
ODIT SZ xAxPxC
pushf
pop ax; AX=FL
or ax, 100h; 1 0000 0000B
push ax
popf; FL=AX


sub ax, ax; ZF=1
or ax, 1; ZF=0
但并不存在指令clt、stt来改变TF的值。要改变TF的值必须通常pushf和popf实现:
pushf
pop ax; AX=FL
or ax, 100000000B; 或or ax, 100h
push ax
popf; FL=AX, 其中第8位即TF=1
...
pushf
pop ax; AX=FL
and ax, not 100000000B; 或and ax, 0FEFFh
push ax
popf; FL=AX, 其中第8位即TF=0
在常数表达式中除了+ - * /运算符外，还可以使用not, or, and, xor等运算符。
pushf/popf配合起来除了可以刻意改变FL中的某些位外，也可以用来保护/恢复FL的值:
pushf; 保护FL的当前值
...
popf; 恢复FL的值
在32位系统中, EFL是一个32位寄存器, 对应的指令是pushfd和popfd; 若在32位系统中使用pushf/popf则控制的仅是EFL的低16位即FL。

3．符号扩充指令：CBW, CWD, CDQ
cbw:convert byte to word
cwd:convert word to double word
cdq:convert double word to quadruple word
mov al, 0FEh
cbw; 把AL扩充成AX, AX=0FFFEh
mov ax, 8000h
cwd; 把AX扩充成DX:AX, DX=FFFFh, AX=8000h
mov eax, 0ABCD1234h
cdq; 把EAX扩充成EDX:EAX
    ; EDX=0FFFFFFFFh, EAX=0ABCD1234h

零扩充指令: movzx
movzx ax, al; zx:zero extension
movzx eax, al;
movzx ebx, cx;

新的符号扩充指令: movsx
movsx ax, al; sx:sign extension符号扩充
; 效果等同于cbw

4. 乘法指令: mul
8位乘法: 被乘数一定是AL, 乘积一定是AX
例如mul bh表示AX=AL*BH
16位乘法: 被乘数一定是AX, 乘积一定是DX:AX
例如mul bx表示DX:AX=AX*BX
32位乘法: 被乘数一定是EAX, 乘积一定是EDX:EAX
例如mul ebx表示EDX:EAX=EAX*EBX
利用乘法指令把十进制字符串转化成32位整数的例子:
http://10.71.45.100/bhh/dec2v32.asm
利用乘法指令把十进制字符串转化成16位整数的例子:
http://10.71.45.100/bhh/dec2v16.asm
```

