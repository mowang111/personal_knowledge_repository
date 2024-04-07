```
邮箱: iceman@zju.edu.cn
主页: 10.71.45.100/bhh

一、学习目的
1. 帮助我们深入理解其它计算机语言
2. 培养调试(debug)技能
    不仅要调试有源代码的程序，还要学习
调试没有源代码的exe程序。
    exe里面没有机器码，调试器可以把机器
码翻译成汇编语言。
3. 逆向工程: 读懂没有源代码的exe程序，提取
程序中的算法，修改exe程序; 挖掘exe里
面的漏洞，从而进行黑客攻击。
4. 混合语言编程

二、sum.exe的调试
主页中按ctrl+f输入sum.zip,下载并解压缩,里面包含sum.exe。
用OllyDbg打开sum.exe。
OD代码窗分成三栏: 地址、机器码、汇编指令
F8 单步执行(step over)
F2 设置断点
寄存器(register)可以理解成cpu内部的全局变量

三、password.exe的破解
主页中按ctrl+f输入password.rar搜索,下载并解压缩，里面包含password.exe。
主页提供的xp虚拟机中已包含接下去演示过程中要用到的工具: OllyDbg、010editor、QuickView。
其中OllyDbg是一个32位调试器;010Editor可以以16进制格式查看或修改exe的内容，但是它没有反汇编功能即不能把16进制机器码翻译成汇编代码; QuickView既可以以16进制格式也可以以汇编语言格式查看、修改exe。
用OD打开password.exe
不停按F8跟踪到以下地址处:
+401244 E8B7FDFFFF  call   00401000
此时再按F8无法继续，因为任务栏的控制台窗口要求用户输入。此时随便输入"asdfg"并回车, OD会停在以下地址处:
+401249  83C40C  add   esp, 0xC
   观察控制台窗口, 发现已经输出"Incorrect password"，由此可以推断401000这个函数对我们输入的内容"asdfg"进行了比较。因此需要重新跟踪password.exe并跟踪进入401000。先在+401244处按F2设断点, 再点菜单"调试->重新开始"从头开始跟踪, 点三角形的Run按钮, 自动断在+401244处，按F7单步步入(trace into)，来到以下地址处:
+401000 55   push    ebp
   此处正是main()的首地址。F8执行到以下地址:
+40100B E81E010000   call    0040112E
   F8执行上述call会发现控制台窗口输出"Please input your password:"，可见上述call是调用了一个字符串输出函数如puts()。
   再F8跟踪到以下地址:
+401017  E8C8000000   call    004010E4
   会发现控制台窗口等待用户输入，由此推断上述call是调用了一个字符串输入函数如gets()。
   F8继续跟踪到以下地址:
+401028 E833000000   call    00401060
   这条call指令实际是调用了strcmp()函数。该call指令上方有2条push指令, 其中push 40604C是第2个参数(指向标准答案"123456")，而push ecx则是第1个参数(指向用户输入的字符串"asdfg")，F8执行完上述call后, 函数strcmp()的返回值会自动保存在寄存器EAX中。观察EAX的值为1，由此可以推断这两个字符串不相等。接下去会执行以下代码:
+401030  85C0   test    eax, eax
+401032  750F   jnz     00401043
   test指令的含义是做eax & eax的运算, 运算结果反映在寄存器窗口中的Z标志位上, Z=0表示运算结果非零。jnz指令表示jump if not zero, 它根据z=0作出跳转到401043的动作。在+401032处按F8会来到此处:
+401043  6864604000  push    00406064
+401048  E8E1000000  call    0040112E
   这两条指令相当于调用了函数puts("Incorrect password"), 其中406064是函数的参数, 它指向"Incorrect password"。
至此, 我们已经跟踪到了正确答案为"123456"。
接下去讲解如何通过修改程序使其在我们乱输一个密码的情况下也能够输出"Password is OK!"。
+401032 75 0F jnz 401034
要把上述指令改成nop nop有两种方法:
(1)代码窗中选中这条指令输入nop
(2)数据窗中按ctrl+g输入401032定位到此指令，
选中75输入90 90
要把改过的内容恢复原样，只要选中再按alt+backspace。
把+401032处的jnz改成nop nop仅仅是对内存中的程序的修改, password.exe的文件内容并不会发生改变。要修改password.exe需要使用QuickView。
先关闭OD以便结束password.exe的运行。
选中password.exe->右键->QuickView就可以用QuickView打开password.exe进行修改。
qv打开exe后默认以16进制模式呈现文件内容，用户可以按enter切换到汇编模式或文本模式。汇编模式下按F2可以进行16位汇编与32位汇编的切换。
F7输入75 0F 68 54 60搜索16进制机器码
找到75 0F后在机器码一栏直接输入90 90完成修改；也可以按Tab键跳到汇编语言一栏再输入nop nop完成修改。万一改坏可以按F3恢复。
按Alt+F9保存修改结果。
按Esc退出QV。

regtest破解
http://10.71.45.100/bhh/regtest.rar
regtest.rar解压缩后，里面有一个reg.exe,
用od打开它进行调试:
在windows平台，用C或C++编程时会调用两类函数:
(1) 库函数: gets puts scanf printf strcmp
这些函数经过编译后，函数名会消失，变成函数的地址;
(2) Windows系统内核的函数: MessageBoxA, 
GetCommandLineA, LoadLibrary, GetProcAddress
象MessageBox这种跟字符串相关的函数通常有2个版本:
①ansi: MessageBoxA
字符串"abc"用ansi格式表示为:0x61,0x62,0x63,0x00
②unicode: MessageBoxW
字符串"abc"用unicode格式表示为:
0x61,0x00, 0x62,0x00, 0x63,0x00, 0x00,0x00
系统内核的函数又叫做api(application program interface)。
编译的时候，源代码中的MessageBox会被替换成
MessageBoxA。也就是说，在源代码中要调用ansi版本的函数，既可以写成MessageBox也可以写成MessageBoxA。
(sn ^ 1999AA98) == 特征码 
sn = 特征码 ^ 1999AA98 = 3BF1EED4 =
1005711060

当某个exe里面调用了这些函数时，这些函数的函数体并不会编译进入exe里面，而是独立存在于操作系统内核中，并且它们的地址在系统启动后是固定的。
在od的代码窗中按ctrl+g并输入MessageBoxA就可以定位到该函数的首地址处，此处按F2设一个断点。
接下去点run按钮让reg.exe运行。
输入注册码1234点确定后，会断在刚才所设断点上，
此时可以观察到寄存器eip刚好等于断点地址，因为eip
表示当前将要执行的指令的地址。
一直按F8单步走到retn处(有些win10的电脑可能会在到达retn前调用MessageBoxExA处卡住,原因是看不到那个弹框或点不掉那个弹框,此时建议不要F8步过而是在retn处再设一个断点,再点run按钮运行)，再按F8就会回到调用者那里。
现在来到此处:
0040C85A   pop     esi
0040C85B   retn    0xC
按两次F8把函数40C82C走完
结果来到此处:
004013F0  mov     ecx, [ebp-0xC]
按PgUp可以看到以下可疑指令:
004013D1  mov     eax, [esi+0x60]
004013D4  mov     ecx, [esi+0x5C]
004013D7  xor     eax, 0x1999AA98
004013DC  cmp     eax, ecx
004013DE  je      short 00401401
注意C语言的异或运算^在汇编语言里是: xor
接下去在地址4013D1处设断点, F8单步两次并观察eax及ecx的值，可以发现eax是我们乱输的注册码1234，而ecx就是信息码。根据上述程序片断，可以整理出以下结论:
(sn ^ 0x1999AA98) == 特征码 
sn = 特征码 ^ 0x1999AA98 = 1005708783
```

