```
0. 先找到d:\tc\turboc.cfg, 点右键用editplus打开
把它的内容改成如下所示:
   -ID:\TC\INCLUDE
   -LD:\TC\LIB
改完后保存。(这一步修改是为了防止tcc编译时报找不到
头文件及库文件错, 以后不需要再做)

1. 先用editplus打开hexfile.c, ctrl+F搜索"char2hex", 
找到该函数的定义, 用#if 0及#endif把该函数括起来, 达
到注释掉该函数的效果;

2. 在hexfile.c的typedef语句后面补充以下一句:
extern void char2hex(byte xx, byte s[]);
表示该函数的函数体定义在外面, 不在当前.c内;

3. 在d:\masm里面新建一个汇编源程序myf.asm
代码如下:
public _char2hex
_DATA	segment word public 'DATA'
t db "0123456789ABCDEF"
_DATA ends

_TEXT segment byte public 'CODE'
assume cs:_TEXT, ds:_DATA
_char2hex:
   push bp
   mov bp, sp
   push bx
   push di
   mov ax, [bp+4]; ax = xx = 0xAF
   mov di, [bp+6]; di->s[0]
   mov bx, offset t
   mov cl, 4
   shr ax, cl; AX=000A
   and al, 0Fh; AL=000A
   xlat
   mov [di], al; s[0]=AL='A'
   mov ax, [bp+4]
   and al, 0Fh; AL=0Fh
   xlat
   mov [di+1], al; s[1]=AL='F'
   pop di
   pop bx
   pop bp
   ret   
_TEXT ends
end

4. 用以下命令把myf.asm编译成myf.obj (/ml表示编译时保留大小写):
masm /ml myf;

5. 用以下命令把myf.obj拷到\tc中:
copy myf.obj \tc

6. 用以下命令把hexfile.c及myf.obj编译成hexfile.exe (-v 表示编译时加入调试信息):
tcc -v hexfile.c myf.obj

7. 用以下命令对hexfile.exe进行调试:
td hexfile.exe
在TD中找到调用char2hex()的语句, 并在此语句处按F2设断点
TD->Run->Run
会触发断点, 按Alt+V->CPU切换到汇编模式, 再F7跟踪进入即
可对char2hex进行调试;


```

