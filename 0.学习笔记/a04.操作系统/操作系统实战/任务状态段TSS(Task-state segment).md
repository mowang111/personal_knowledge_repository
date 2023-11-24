> 任务状态段TSS（Task-state segment）是一块104字节的内存，用于存储大部分寄存器的值。CPU中无进程和线程的概念（这是操作系统的概念），CPU中只有任务概念（任务对应操作系统的线程）。1个CPU核只有一个TR寄存器，存储了当前TSS。

### CPU怎么找到TSS

前面已经知道，CPU可以通过 gdtr 寄存器来知道 GDT表在哪里，通过 idtr 寄存器知道 idt 表在哪里。实际上，CPU是通过 tr 寄存器来确定 TSS 的位置的。和 gdtr，idtr 这些不同的是，tr 寄存器是段寄存器，之前已经知道的段寄存器有 cs, ds, es, ss, fs, gs 。也知道段寄存器有96位，还做过实验验证。tr 寄存器中存放的就是描述了TSS段的相关信息，比如TSS段的基址，大小和属性。可以通过 ltr指令跟上TSS段描述符的选择子来加载TSS段。该指令是特权指令，只能在特权级为0的情况下使用。

### TSS 段描述符
![[TSS段描述符.webp]]
当S=0, TYPE=1001或者TYPE=1011的时候，表示这是一个TSS段描述符。当TSS段没被加载进 tr 寄存器时，TYPE=1001，一旦TSS被加载进 tr 寄存器，TYPE就变成了1011.

### TSS、TSS段描述符、TR寄存器三者之间的关系

一定要理解：TSS、TSS段描述符、TR寄存器三者之间的关系。  
TSS是任务段（共104字节内存），TSS描述符存储在GDT表中，TR在GDT表中查出来的TSS段描述符。  
到哪找TSS？答：TR寄存器  
TR寄存器里面的值是什么？答：GDT表里面的TSS段描述符  
怎么访问TR寄存器（从TR寄存器里面取值，给TR寄存器赋值）？答：LTR和STR指令

TR.BASE：记录了当前TSS在哪里  
TR.LIMIT：记录了这个TSS有多大

TSS104字节都保存了什么？可以解析成下面一个结构体：

```html
typedef struct TSS {
    DWORD link; // 保存前一个 TSS 段选择子，使用 call 指令切换寄存器的时候由CPU填写。
    // 这 6 个值是固定不变的，用于提权，CPU 切换栈的时候用
    DWORD esp0; // 保存 0 环栈指针
    DWORD ss0;  // 保存 0 环栈段选择子
    DWORD esp1; // 保存 1 环栈指针
    DWORD ss1;  // 保存 1 环栈段选择子
    DWORD esp2; // 保存 2 环栈指针
    DWORD ss2;  // 保存 2 环栈段选择子
    // 下面这些都是用来做切换寄存器值用的，切换寄存器的时候由CPU自动填写。
    DWORD cr3; 
    DWORD eip;  
    DWORD eflags;
    DWORD eax;
    DWORD ecx;
    DWORD edx;
    DWORD ebx;
    DWORD esp;
    DWORD ebp;
    DWORD esi;
    DWORD edi;
    DWORD es;
    DWORD cs;
    DWORD ss;
    DWORD ds;
    DWORD fs;
    DWORD gs;
    DWORD ldt_selector;//ldt段选择子,用于换ldtr寄存器，一个TSS对应一个LDT表，就算你有100个任务，那么ldtr寄存器里面存储的也是当前ldt表，也就是任务切换时，LDT表会切换，但GDT表不会切换
    // 这个暂时忽略
    DWORD io_map;
} TSS;
```

说明：  
为什么没有ss3和esp3？因为3环不需要切换堆栈。

### TSS的用途

(1)保存0环、1环和2环的栈段选择子和栈顶指针，在跨段提权的时候，需要切换栈，CPU会通过 tr 寄存器找到 TSS，取出其中的 SS0 和 ESP0 复制到 ss 和 esp 寄存器中。这只是 TSS 的一个用途，也是现代 Windows 操作系统使用到的功能。  
(2)一次性切换一堆寄存器，可以通过 call/jmp + TSS段选择子指令一次性把这些值加载到 CPU 对应的寄存器中。同时，旧值将保存在旧的 TSS 中。GDT 表中可以存放多个TSS描述符，这意味着内存中可以存在多份不同的TSS。总有一个 TSS 是在当前使用中的，也就是 tr 寄存器指向的那个 TSS。当使用 call/jmp + TSS段选择子的时候，CPU做了以下几件事情。  
a.把当前所有寄存器（TSS结构中有的那些寄存器）的值填写到当前 tr 段寄存器指向的 TSS 中  
b.把新的 TSS 段选择子指向的段描述符加载到 tr 段寄存器中  
c.把新的 TSS 段中的值覆盖到当前所有寄存器（TSS结构中有的那些寄存器）中

### TR寄存器操作指令

LTR 指令是0环指令，格式如下：

```html
mov ax,SelectorTSS
ltr ax
```

执行该指令，从GDT表取TSS描述符填充TR寄存器，但并不会修改其他寄存器。执行指令后，TSS描述符TYPE域低2位会置1.

STR 指令只会读取 TR 的16位选择子部分，该指令没有特权要求。指令格式如下：

```html
str ax
```

### 总结

任务门在IDT表，描述符在GDT表。

如果采用分页机制，那么由线性地址空间到物理地址空间的映射由包含页目录表起始物理地址的控制寄存器CR3确定。所以，与特定任务相关的虚拟地址空间到物理地址空间的映射由LDTR和CR3确定。

虽然 Intel 设计的初衷是用TSS来做任务切换，然而，在现代操作系统中（无论是 Windows 还是 Linux），都没有使用这种方式来执行任务切换，而是自己实现了线程。主要原因是这种切换速度非常慢，一条指令要消耗200多个时钟周期。至于现代操作系统如何进行线程或进程的切换，确实是用到了 TSS，但却不是靠切换call/jmp TSS 来切换任务。
