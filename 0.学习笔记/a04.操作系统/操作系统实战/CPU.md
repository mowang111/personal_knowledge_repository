# CPU

CPU的工作模式：实模式、保护模式、长模式

## 实模式

运行真实的指令，对指令的动作不做区分，直接执行指令的真实功能；发往内存的地址都是真实的，对任何地址不加限制地发往内存

### 实模式寄存器

表中每个寄存器都是16位的

![img](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/f837811192730cc9c152afbcccf4eff8.jpeg)

### 实模式下访问内存

![img](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/14633ea933972e19f3439eb6aeab3d13.jpg)

DOS下的Hello World程序，工作在实模式下的汇编代码，共16位：
```
data SEGMENT ;定义一个数据段存放Hello World!
    hello  DB 'Hello World!$' ;注意要以$结束
data ENDS
code SEGMENT ;定义一个代码段存放程序指令
    ASSUME CS:CODE,DS:DATA ;告诉汇编程序，DS指向数据段，CS指向代码段
start:
    MOV AX,data  ;将data段首地址赋值给AX                
    MOV DS,AX    ;将AX赋值给DS，使DS指向data段
    LEA DX,hello ;使DX指向hello首地址,LEA为取地址指令
    MOV AH,09h   ;给AH设置参数09H，AH是AX高8位，AL是AX低8位，其它类似
    INT 21h      ;执行DOS中断输出DS指向的DX指向的字符串hello
    MOV AX,4C00h ;给AX设置参数4C00h
    INT 21h      ;调用4C00h号功能，结束程序
code ENDS
END start
```

### 实模式中断
硬件中断：中断控制器发送一个电子信号，CPU对该信号作出应答，随后中断控制器将中断号发给CPU
软件中断：INT指令+中断号

为了实现中断，需要在内存放一个中断向量表，这个表的地址和长度由CPU的特定寄存器IDTR指向。实模式下，表中的一个条目由代码段地址和段内偏移组成 
> 他这个中断表地址就是指向中断表开始的地址（从下往上看），中断表的长度就指向了中断表的末尾
![image.png](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/20221225150628.png)


## 保护模式
基于更高计算量和更大内存容量的需求，需要解决寻址问题，16位寄存器最多只能表示$2^{16}$个地址，所以CPU的寄存器和运算单元都要扩展为32位
同时要解决实模式场景下的问题，需要CPU对指令加以区分的执行，对访问的地址加以限制
基于这些原因，CPU实现保护模式
### 保护模式寄存器
保护模式相比于实模式，增加了一些控制寄存器和段寄存器，扩展通用寄存器的位宽，所有通用寄存器都是32位的，还可以单独使用低16位，这个低16位又可以拆分成两个8位寄存器
![image.png](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/20221225154550.png)
## 保护模式特权级
为了区分哪些指令（如in、out、cli）和哪些资源（如寄存器、I/O端口、内存地址）可以被访问，CPU实现了特权级
特权级分为 4 级，R0~R3，每个特权级执行指令的数量不同，R0 可以执行所有指令，R1、R2、R3 依次递减，它们只能执行上一级指令数量的子集。而内存的访问则是靠后面所说的段描述符和特权级相互配合去实现的。如下图
![image.png](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/20221225155006.png)
## 保护模式段描述符
目前为止，内存还是分段模型，要对内存进行保护，就可以转换成对段的保护
由于 CPU 的扩展导致了 32 位的段基地址和段内偏移，还有一些其它信息，所以 16 位的段寄存器肯定放不下。放不下就要找内存借空间，然后把描述一个段的信息封装成特定格式的段描述符，放在内存中，其格式如下。
![image.png](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/20221225155505.png)
一个段描述符有 64 位 8 字节数据，里面包含了段基地址、段长度、段权限、段类型（可以是系统段、代码段、数据段）、段是否可读写，可执行等。虽然数据分布有点乱，这是由于历史原因造成的。
多个段描述符在内存中形成全局段描述符表，该表的基地址和长度由 CPU 和 GDTR 寄存器指示。如下图所示。
![image.png](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/20221225160358.png)
段寄存器中不再存放段基地址，而是具体段描述符的索引，访问一个内存地址时，段寄存器中的索引首先会结合 GDTR 寄存器找到内存中的段描述符，再根据其中的段信息判断能不能访问成功。
### 保护模式段选择子
CS、DS、ES、SS、FS、GS这些段寄存器，里面存放的不只是内存段的描述符索引，而是由影子寄存器、段描述符索引、描述符表索引、权限级别组成。
![image.png](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/20221225160942.png)
#### 影子寄存器
影子寄存器是靠硬件来操作的，对系统程序员不可见，是硬件为了减少性能损耗而设计的一个段描述符的高速缓存，不然每次内存访问都要去内存中查表，那性能损失是巨大的，影子寄存器也正好是 64 位，里面存放了 8 字节段描述符数据。
通常情况下，CS 和 SS 中 RPL 就组成了 CPL（当前权限级别），所以常常是 RPL=CPL，进而 CPL 就表示发起访问者要以什么权限去访问目标段，当 CPL 大于目标段 DPL 时，则 CPU 禁止访问，只有 CPL 小于等于目标段 DPL 时才能访问。

### 保护模式平坦模型
分段模型有很多缺陷，这在后面课程讲内存管理时有详细介绍，其实现代操作系统都会使用分页模型（这点在后面讲 MMU 那节课再探讨）。

但是 x86 CPU 并不能直接使用分页模型，而是要在分段模型的前提下，根据需要决定是否要开启分页。因为这是硬件的规定，程序员是无法改变的。但是我们可以简化设计，来使分段成为一种“虚设”，这就是保护模式的平坦模型。

根据前面的描述，我们发现 CPU32 位的寄存器最多只能产生 4GB 大小的地址，而一个段长度也只能是 4GB，所以我们把所有段的基地址设为 0，段的长度设为 0xFFFFF，段长度的粒度设为 4KB，这样所有的段都指向同一个（（段的长度 +1）* 粒度 - 1）字节大小的地址空间。

下面我们还是看一看前面 Hello OS 中段描述符表，如下所示
```
GDT_START:
knull_dsc: dq 0
;第一个段描述符CPU硬件规定必须为0
kcode_dsc: dq 0x00cf9e000000ffff
;段基地址=0，段长度=0xfffff
;G=1,D/B=1,L=0,AVL=0 
;P=1,DPL=0,S=1
;T=1,C=1,R=1,A=0
kdata_dsc: dq 0x00cf92000000ffff
;段基地址=0，段长度=0xfffff
;G=1,D/B=1,L=0,AVL=0 
;P=1,DPL=0,S=1
;T=0,C=0,R=1,A=0
GDT_END:
GDT_PTR:
GDTLEN  dw GDT_END-GDT_START-1
GDTBASE  dd GDT_START
```

### 保护模式中断

实模式下CPU不需要做权限检查，处理中断时可以直接把中断向量表中的值装载到CS:IP寄存器即可
而保护模式下，中断需要做权限检查以及特权级的切换，所以需要扩展中断向量表中的信息，即每个中断用一个中断门描述符来表示，简称中断门，其格式如下：
![image.png](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/20230101162927.png)

同样地，保护模式要实现中断，也必须在内存中有一个中断向量表，通用是由IDTR寄存器指向，只不过中断向量表中的条目变成了中断门描述符：
![image.png](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/20230101162942.png)
产生中断后，CPU首先会检查中断号是否大于最后一个中断门描述符，x86 CPU最大支持256个中断源（即中断号：0~255）然后检查描述符类型（是否时中断门或者陷阱门）、是否为系统描述符、是不是存在于内存中。

最后做权限检查，如果CPL小于等于中断门的DPL,并且CPU大于等于中断门中的段选择子所指向的段描述符的DPL,就指向段描述符的DPL。

进一步的，CPL等于中断门中的段选择子指向段描述符的DPL，则为同级权限不进行栈切换，否则进行栈切换。如果要进行栈切换，还需要从TSS(任务状态段，Task-state segment )[[任务状态段TSS(Task-state segment)]]中加载具体权限的SS、ESP,当然也要对SS中段选择子指向的段描述符进行检查。

做完这一系列检查之后，CPU才会加载中断门描述符中目标代码段选择子到CS寄存器中，把目标代码段偏移加载到EIP寄存器中。

### 切换到保护模式

x86 CPU在第一次加电和每次reset后，都会自动进入实模式，要想进入保护模式，就需要程序员写代码实现从实模式切换到保护模式。

第一步，准备全局段描述符表。
```
GDT_START:
knull_dsc: dq 0
kcode_dsc: dq 0x00cf9e000000ffff
kdata_dsc: dq 0x00cf92000000ffff
GDT_END:
GDT_PTR:
GDTLEN dw GDT_END-GDT_START-1
GDTBASE dd GDT_START
```

第二步，加载设置GDTR寄存器，使之指向全局段描述符表。
```
lgdt [GDT_PTR]
```

第三步，设置CR0寄存器，开启保护模式
```
;开启 PE
mov eax, cr0                 ; mov dst, src
bts eax, 0                   ; CR0.PE = 1
mov cr0, eax
```

第四步，进行长跳转，加载CS段寄存器，即段选择子
```
jmp dword 0x8 :_32bits_mode ;_32bits_mode为32为代码标号即段偏移
```

为什么要进行长跳转？因为我们无法直接或间接mov一个数据到CS寄存器中，因为刚刚开启保护模式时，CS的影子寄存器还是实模式下的值，所以需要告诉CPU加载新的段信息。

接下来，CPU发现了CRO寄存器第0位的值是1，就会按GDTR的指示找到全局描述符表，然后根据索引值8，把新的段描述符信息加载到CS影子寄存器，当然这里的前提是进行一系列合法的检查。

到此位置，CPU真正进入了保护模式，CPU也有了32位的处理能力

## 长模式

长模式又名 AMD64，因为这个标准是 AMD 公司最早定义的，它使 CPU 在现有的基础上有了 64 位的处理能力，既能完成 64 位的数据运算，也能寻址 64 位的地址空间。这在大型计算机上犹为重要，因为它们的物理内存通常有几百 GB。

### 长模式寄存器

长模式相比于保护模式，增加了一些通用寄存器，并扩展通用寄存器的位宽，所有的通用寄存器都是 64 位，还可以单独使用低 32 位。

这个低 32 位可以拆分成一个低 16 位寄存器，低 16 位又可以拆分成两个 8 位寄存器，如下表。
![image.png](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/20230102125731.png)

### 长模式段描述符
长模式依然具备保护模式绝大多数特性，如特权级和权限检查。相同的部分就不再重述了，这里只会说明长模式和保护模式下的差异。
下面我们来看看长模式下段描述的格式，如下图所示。
![image.png](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/20230102125941.png)
在长模式下，CPU 不再对段基址和段长度进行检查，只对 DPL 进行相关的检查，这个检查流程和保护模式下一样。

当描述符中的 L=1，D/B=0 时，就是 64 位代码段，DPL 还是 0~3 的特权级。然后有多个段描述在内存中形成一个全局段描述符表，同样由 CPU 的 GDTR 寄存器指向。

下面我们来写一个长模式下的段描述符表，加深一下理解，如下所示.
```
ex64_GDT:
null_dsc:  dq 0
;第一个段描述符CPU硬件规定必须为0
c64_dsc:dq 0x0020980000000000  ;64位代码段
;无效位填0
;D/B=0,L=1,AVL=0 
;P=1,DPL=0,S=1
;T=1,C=0,R=0,A=0
d64_dsc:dq 0x0000920000000000  ;64位数据段
;无效位填0
;P=1,DPL=0,S=1
;T=0,C/E=0,R/W=1,A=0
eGdtLen   equ $ - null_dsc  ;GDT长度
eGdtPtr:dw eGdtLen - 1  ;GDT界限
     dq ex64_GDT
```

### 长模式中断
保护模式下为了实现对中断进行权限检查，实现了中断门描述符，在中断门描述符中存放了对应的段选择子和其段内偏移，还有 DPL 权限，如果权限检查通过，则用对应的段选择子和其段内偏移装载 CS:EIP 寄存器。
如果你还记得中断门描述符，就会发现其中的段内偏移只有 32 位，但是长模式支持 64 位内存寻址，所以要对中断门描述符进行修改和扩展，下面我们就来看看长模式下的中断门描述符的格式，如下图所示。
![image.png](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/20230102130223.png)
结合上图，我们可以看出长模式下中断门描述符的格式变化。
首先为了支持 64 位寻址中断门描述符在原有基础上增加 8 字节，用于存放目标段偏移的高 32 位值。其次，目标代码段选择子对应的代码段描述符必须是 64 位的代码段。最后其中的 IST 是 64 位 TSS 中的 IST 指针，因为我们不使用这个特性，所以不作详细介绍。
长模式也同样在内存中有一个中断门描述符表，只不过表中的条目（如上图所示）是 16 字节大小，最多支持 256 个中断源，对中断的响应和相关权限的检查和保护模式一样，这里不再赘述。

### 切换到长模式
可以从实模式直接切换到长模式，也可以从保护模式切换长模式。

第一步，准备长模式全局段描述符
```
ex64_GDT:
null_dsc:  dq 0
;第一个段描述符CPU硬件规定必须为0
c64_dsc:dq 0x0020980000000000  ;64位代码段
d64_dsc:dq 0x0000920000000000  ;64位数据段
eGdtLen   equ $ - null_dsc  ;GDT长度
eGdtPtr:dw eGdtLen - 1  ;GDT界限
     dq ex64_GDT
```

第二步，准备长模式下的MMU页表，这是为了开启分页模式，切换到长模式必须要开启分页，长模式下已经不对段基址和段长度进行检查了，那么内存地址空间就得不到保护了
而长模式下内存地址空间的保护交给了MMU,MMU依赖页表对地址进行转换，页表有特定的格式存放在内存中，其地址由CPU的CR3寄存器指向。
```
mov eax, cr4
bts eax, 5   ;CR4.PAE = 1
mov cr4, eax ;开启 PAE
mov eax, PAGE_TLB_BADR ;页表物理地址
mov cr3, eax
```

第三步，加载GDTR寄存器，使之指向全局段描述符
```
lgdt [eGdtPtr]
```

第四步，开启长模式，要同时开启保护模式和分页模式，在实现长模式时定义了MSR寄存器，需要用专用的指令rdmsr、wrmsr进行读写， IA32_EFER寄存器的地址位0xC0000080,它的第8位决定了是否开启长模式
```
;开启 64位长模式
mov ecx, IA32_EFER
rdmsr
bts eax, 8 ;IA32_EFER.LME =1
wrmsr
;开启 保护模式和分页模式
mov eax, cr0
bts eax, 0 ;CR0.PE =1
bts eax, 31
mov cr0, eax
```

第五步，进行跳转，加载CS段寄存器，刷新其影子寄存器
```
jmp 08:entry64 ;entry64为程序标号即64位偏移地址
```
切换到长模式和切换保护模式的流程差不多，只是需要准备的段描述符有所区别，还有就是要注意同时开启保护模式和分页模式。原因在上面已经说明了。