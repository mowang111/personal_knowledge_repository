# 内存
内存，DRAM，动态随机存储器
![[DDR内存逻辑结构连接图.png]]
> 北桥负责与CPU通信，并且连接高速设备（内存/显卡），并且与南桥通信；南桥负责与低速设备（硬盘/USB）通信，时钟/BIOS/系统管理/旧式设备控制，并且与北桥通信。

# Cache
![[Cache结构框架图.png]]
## Cache 内部构成
Cache主要由高速的静态存储器、地址转换模块和Cache行替换模块组成
Cache会把自己的高速静态储存器和内存分成大小相同的行，一行大小通常为32字节或者64字节。Cache和内存交换数据的最小单位是一行，为了方便管理，Cache内部的高速储存器中，多个行又形成一组。
除了正常的数据空间外，Cache行中还有一些标志位，如脏位，回写位，访问位等，这些位会被Cache的替换模块所使用。

## Cache 大致工作流程
1. CPU发出的地址由Cache的地址转换模块分成3段：组号，行号，行内偏移；
2. Cache会根据组号、行号查找高速静态储存器中对应的行。命中即返回，没命中则分配新行访问内存再返回。
3. 没有新行，执行替换算法。
以上逻辑，由Cache硬件独立实现，无需软件操作。

## Cache带来的问题——数据一致性

![[x86CPUcache结构图.png]]
以上双核心CPU，有三级Cache，其中涉及的Cache一致性的问题，主要包括三个方面：
1. 一个CPU核心中的指令Cache和数据Cache的一致性问题
2. 多个CPU核心各自的2级Cache的一致性问题
3. CPU的3级Cache与设备内存，如DMA、网卡帧储存，显存之间的一致性问题。

为了解决这些问题，设计了多种协议，典型的多核心Cache数据同步协议有MESI和MOESI。

## Cache的MESI协议
MESI协议定义了4中基本状态：M、E、S、I，即修改（Modified）、独占（Exclusive）、共享（Shared）和无效（Invalid）。

## 开启Cache
x86 CPU上默认是关闭Cache的，需要在CPU初始化时将其开启。
步骤：将CR0寄存器中CD、NW位同时清0即可。
CD=1表示Cache关闭，NW=1表示CPU不维护内存数据一致性。
```
mov eax, cr0
;开启 CACHE    
btr eax,29 ;CR0.NW=0
btr eax,30  ;CR0.CD=0
mov cr0, eax
```

## 获取内存视图
给出一个物理地址并不能准确定位到内存空间，内存空间只是映射物理地址空间的一个子集，物理地址空间中可能有空洞，有ROM, 内存，显存，I/O寄存器，所以获取内存没有多大用，**关键要获取哪些物理地址空间是可以读写的内存**。

物理地址空间是由北桥芯片控制管理的，但是不需要找北桥芯片要内存的地址空间，在x86平台上，只需要利用BIOS提供的实模式下中断服务。

由于PC机上电后由BIOS执行硬件初始化，中断向量表由BIOS设置的，所以执行中断自然是执行BIOS服务。
```
_getmemmap:
  xor ebx,ebx ;ebx设为0
  mov edi,E80MAP_ADR ;edi设为存放输出结果的1MB内的物理内存地址
loop:
  mov eax,0e820h ;eax必须为0e820h
  mov ecx,20 ;输出结果数据项的大小为20字节：8字节内存基地址，8字节内存长度，4字节内存类型
  mov edx,0534d4150h ;edx必须为0534d4150h
  int 15h ;执行中断
  jc error ;如果flags寄存器的C位置1，则表示出错
  add edi,20;更新下一次输出结果的地址
  cmp ebx,0 ;如ebx为0，则表示循环迭代结束
  jne loop  ;还有结果项，继续迭代
    ret
error:;出错处理
```
上述代码是在迭代中执行中断，每次中断都输出20字节大小数据项，最后会形成一个该数据项的数组，可以用C语言结构表示。
```c
#define RAM_USABLE 1 //可用内存
#define RAM_RESERV 2 //保留内存不可使用
#define RAM_ACPIREC 3 //ACPI表相关的
#define RAM_ACPINVS 4 //ACPI NVS空间
#define RAM_AREACON 5 //包含坏内存
typedef struct s_e820{
    u64_t saddr;    /* 内存开始地址 */
    u64_t lsize;    /* 内存大小 */
    u32_t type;    /* 内存类型 */
}e820map_t;
```