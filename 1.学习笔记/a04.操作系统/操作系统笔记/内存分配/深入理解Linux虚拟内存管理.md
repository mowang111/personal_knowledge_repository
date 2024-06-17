---
title: 深入理解Linux虚拟内存管理
date: {{ date }}
top: false
cover: false
password:
toc: true
mathjax: true
summary:
tags: 
- 操作系统
- 内存管理
categories: [操作系统]
---

本文引用自[小林深入理解 Linux 虚拟内存管理](https://xiaolincoding.com/os/3_memory/linux_mem.html#_4-6-%E6%B7%B1%E5%85%A5%E7%90%86%E8%A7%A3-linux-%E8%99%9A%E6%8B%9F%E5%86%85%E5%AD%98%E7%AE%A1%E7%90%86)

# 深入理解Linux虚拟内存管理

![image-20230328112622015](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20230328112622015.png)

## 什么是虚拟内存地址？

以Inter Core i7处理器为例，64位虚拟地址的格式位：全局目录页（9位）+ 上层页目录项（9位）+ 中间页目录项（9位）+ 页表项（12位）。共48位组成的虚拟内存地址。

![image-20230328194549817](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20230328194549817.png)

32位虚拟内存地址的格式为：页目录项（10位）+ 页表项（10位）+页内偏移（12位）。共32位组成的虚拟地址。

![image-20230328194710702](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20230328194710702.png)

> 进程虚拟内存空间中的每一个字节都有与其对应的虚拟内存地址，一个虚拟内存地址表示进程虚拟内存空间中的一个特定的字节。

## 为什么要用虚拟内存地址？

防止多进程运行时造成的内存地址冲突

## 进程虚拟内存空间

![image-20230328195335934](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20230328195335934.png)

+ 用于存放进程程序二进制文件中的机器指令的代码段
+ 用于存放全局变量和静态变量的数据段和BSS段
+ 用于再程序运行过程中动态申请内存的堆
+ 用于存放动态链接库以及内存映射区域的文件映射与匿名映射区
+ 用于存放函数调用过程中的局部变量和函数参数的栈



## Linux进程虚拟内存空间

### 32位机器上进程虚拟内存空间分布

在32位机器上，指针的寻址范围是2^32，所能表达的虚拟内存空间为4GB。所以在32位机器上进程的虚拟内存地址范围为0x0000 0000 - 0xFFFF FFFF。

其中用户态虚拟内存空间为3GB，虚拟内存地址范围为：0x0000 0000 - 0xC000 0000；

内核态虚拟内存地址空间为1GB，虚拟内存地址范围为：0xC000 0000 - 0xFFFF FFFF;

![image-20230328201000789](C:\Users\11547\AppData\Roaming\Typora\typora-user-images\image-20230328201000789.png)

用户态虚拟内存空间中的代码段并不是从0x00000000地址开始的，而是从0x0804 8000地址开始的。

0x0000 0000 到0x0804 8000这段虚拟内存地址是一段不可访问的保留区，因为在大多数操作系统中，数值较小的地址通常被认为不是一个合法的地址，这块小地方是不允许访问的。比如在C语言中我们通常会将一些无效的指针设置为NULL，指向这块不允许访问的地址。

保留区的上面就是代码段和数据段，它们是从程序的二进制文件中直接加载进内存中的，BSS段中的数据也存在与二进制文件中，因为内核直到这些数据是没有初值的，所以在二进制文件中只会记录BSS段的大小，加载进内存时会生成一段0填充的内存空间。

紧挨着BSS段的上面就是经常使用的堆空间，其地址增长方向为从低地址到高地址增长。

内核中使用start_brk标识堆的起始位置，brk标识堆当前的结束位置。当堆申请新的内存空间时，只需要将brk指针增加对应的大小，回收地址时减少对应的大小即可。比如当我们通过malloc向内核申请很小的一块内存时（128K之内），就是通过改变brk位置实现的。

堆空间的上面是一段待分配区域，用于扩展堆空间使用。

接下来就是文件映射与匿名映射区域。进程运行时所依赖的动态链接库中的代码段，数据段，BSS段就加载在这里。还有我们调用mmap映射出来的一段虚拟内存空间也保存在这个区域。注意：在文件映射与匿名映射区的地址增长方向时从高地址向低地址增长。

接下来时栈空间，在这里会保存函数运行过程所需要的局部变量以及函数参数等调用信息。栈空间中的地址增长方向是从高地址向低地址增长。每次进程申请新的栈空间时，其地址时在减少的。

在内核中使用start_stack标识栈的起始位置，RSP寄存器中保存栈顶指针stack pointer，RBP寄存器中保存的时栈基地址。

在栈空间的下边也有一段待分配区域用于扩展栈空间，在栈空间的上边就是内核空间了，进程虽然可以看到这段内核空间地址，但是就是不能访问。

### 64位机器上进程虚拟内存空间分布

可以通过`cat /proc/pid/maps` 或者`pmap pid`来查看某个进程的实际虚拟内存布局

虚拟内存地址范围为：0x0000 0000 0000 0000 0000 - 0xFFFF FFFF FFFF FFFF 。

事实上在目前的 64 位系统下只使用了 48 位来描述虚拟内存空间，寻址范围为 2^48 ，所能表达的虚拟内存空间为 256TB。

其中低128T表示用户态虚拟内存空间，虚拟内存地址范围为：0x0000 0000 0000 0000 - 0x0000 7FFF FFFF F000

高128T表示内核态虚拟内存空间，虚拟内存地址范围为：0xFFFF 8000 0000 0000 - 0xFFFF FFFF FFFF FFFF

这样一来就在用户态虚拟内存空间与内核态虚拟内存空间之间形成了一段0x0000 7FFF FFFF F000 - 0xFFFF 8000 0000 0000 的地址空洞，我们把这个空洞叫做canonical address空洞。

![image-20230328204632265](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20230328204632265.png)

我们都知道在 64 位机器上的指针寻址范围为 2^64，但是在实际使用中我们只使用了其中的低 48 位来表示虚拟内存地址，那么这多出的高 16 位就形成了这个地址空洞。

注意到：低128T的用户态地址空间：0x0000 0000 0000 0000 - 0x0000 7FFF FFFF F000范围中，所以虚拟内存地址的高16位全部为0。

如果一个虚拟地址的高16位全部为0，那么我们就可以直接判断出这是一个用户空间的虚拟内存地址。

同样，在高128T的内核态虚拟内存空间：0xFFFF 8000 0000 0000 - 0xFFFF FFFF FFFF FFFF 范围中，所以虚拟内存地址的高16位全部为1.

也就是说内核态的虚拟内存地址的高16位全部为1，如果一个试图访问内核的虚拟地址的高16位不全为1，则可以快速判断这个访问时非法的。

> 这个高 16 位的空闲地址被称为 canonical 。如果虚拟内存地址中的高 16 位全部为 0 （表示用户空间虚拟内存地址）或者全部为 1 （表示内核空间虚拟内存地址），这种地址的形式我们叫做 canonical form，对应的地址我们称作 canonical address 。
>
> 那么处于 canonical address 空洞 ：0x0000 7FFF FFFF F000 - 0xFFFF 8000 0000 0000 范围内的地址的高 16 位 不全为 0 也不全为 1 。如果某个虚拟地址落在这段 canonical address 空洞区域中，那就是既不在用户空间，也不在内核空间，肯定是非法访问了。
>
> 未来我们也可以利用这块 canonical address 空洞，来扩展虚拟内存地址的范围，比如扩展到 56 位。

64位Linux系统下的真实虚拟内存空间布局情况：

![image-20230328212444082](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20230328212444082.png)

上图所示，64位系统中的虚拟内存布局和32位系统中的虚拟内存布局大体一致，主要不同有三点：

1. 由高16位空闲地址造成的canonical address空洞。在这段范围内的虚拟内存地址是不合法的，因为它的高16位既不全为0也不全为1，不是一个canonical address，所以称之为canonical address空洞。
2. 在代码段和数据段中间还有一段不可以读写的保护段，它的作用是防止程序在读写数据段的的时候越界访问到代码段，这个保护段可以让越界行为直接崩溃，防止它继续往下运行。
3. 用户态虚拟内存空间与内核态虚拟内存空间分别占用128T，其中低128T分配给用户虚拟内存空间，高128T分配给内核态虚拟内存空间。



## 进程虚拟内存空间的管理

介绍虚拟内存空间管理，离不开进程在内核中的描述符task_struct结构

```c++
struct task_struct {
    //进程id
    pid_t	pid;
    //用于标识线程所属的线程组ID
    pit_t	tgid;
    //进程打开的文件信息
    struct files_struct	*files;
    //内存描述符表示进程虚拟地址空间
    struct mm_struct	*mm;

    ............省略............
}
```

在进程描述符task_struct结构中，有一个专门描述进程虚拟地址空间的内存描述符mm_struct结构，这个结构体包含了前面介绍的进程虚拟内存空间的全部信息。

每个进程都有一个唯一的mm_struct结构体，也就是每个进程的虚拟地址空间都是独立，互不干扰的。

当我们调用fork()函数创建进程的时候，表示进程地址空间的时候，表示进程地址空间的mm_struct结构会随着进程描述符task_struct的创建而创建。

```c
long _do_fork(unsigned long clone_flags,
             unsigned long stack_start,
             unsigned long stack_size,
             int __user *parent_tidptr,
             int __user *child_tidptr,
             unsigned long tls)
{
    ............省略...........
        struct pid *pid;
    	struct task_struct *p;
    ............省略............
    //为进程创建task_struct结构，用父进程的资源填充task_struct信息
    p = copy_process(clone_flags, stack_start, stack_size,
                    child_tidptr, NULL, trace, tls, NUMA_NO_NOED);
    
   .............省略............
    
}
```

> `__user` 是一种特殊的内核宏，表示该指针指向用户空间（user space），而不是内核空间（kernel space）。在 Linux 内核中，`__user` 可以用于标记函数参数、结构体字段和变量等，以表明它们来自用户空间，这可以帮助内核检测和避免安全漏洞。
>
> 在这个例子中，`__user` 标记用于表示 `parent_tidptr` 参数是指向用户空间的指针，它指向一个整数变量，用于返回父进程的线程 ID。由于该参数来自用户空间，内核需要通过一些额外的步骤才能在内核空间中使用它。



随后会在copy_process函数总创建task_struct结构，并拷贝父进程相关资源到新进程的task_struct结构里，其中就包括拷贝父进程的虚拟内存空间mm_struct结构。**这里可以看出子进程在新创建出来之后它的虚拟内存空间是和父进程的虚拟内存空间一模一样，直接拷贝过来。**

```c
static __latent_entropy struct task_struct *copy_process(
						unsigned long clone_flags,
						unsigned long stack_start,
						unsigned long stack_size,
						int __user *child_tidptr,
						struct pid *pid,
						int trace,
						unsigned long tls,
						int node){
    struct task_struct *p;
    //创建 task_struct 结构
    p = dup_task_struct(current, node);
    ............初始化子进程...............
    ............开始继承拷贝父进程资源........
    //继承父进程打开的文件描述符
    retval = copy_files(clone_flags, p);
    //继承父进程所属的文件系统
    retval =  copy_fs(clone_flags, p);
    //继承父进程注册的信号以及信号处理函数
    retval = copy_sighand(clone_flags, p);
    retval = copy_signal(clone_flags, p);
    //继承父进程的虚拟内存空间
    retval = copy_mm(clone_flags, p);
    //继承父进程的namespaces
    retval = copy_namespaces(clone_flags, p);
    //继承父进程的IO信息
    retval = copy_io(clone_flags, p);
    
 	............省略............
    //分配 CPU
    retval = sched_fork(clone_flags, p);
    //分配pid
    pid = alloc_pid(p->nsproxy->pid_ns_for_children);
    
    ............省略.............
    
}
```

这里重点关注copy_mm函数，正是在这里完成了子进程虚拟空间mm_struct结构的创建以及初始化。

```c
static int copy_mm(unsigned long clone_flags, struct task_strct *tsk){
    struct mm_struct *mm, *olmm;
    int retval;
    .................省略..................
        
    
    tsk->mm = NULL;
    tsk->active_mm = NULL;
    //获取父进程虚拟内存空间
    oldmm = current->mm;
    if(!oldmm) return 0;

    .................省略..................
    //通过vfork或者clone系统调用创建出的子进程（线程）和父进程共享虚拟地址空间
    if(clone_flags & CLONE_VM){
        //增加父进程虚拟地址空间的引用计数
        mmget(oldmm);
        //直接将父进程的虚拟内存空间赋值给子进程（线程）
        //线程共享其所属进程的虚拟内存空间
        mm = oldmm;
        goto good_mm;
    }
    
    retval = -ENOMEM;
   	//如果是fork系统调用创建出的子进程，则将父进程的虚拟内存空间以及相关页表拷贝到子进程的mm_struct结构
    mm = dup_mm(tsk);
    if(!mm) goto fail_nomem;
    
good_mm:
    //将拷贝出来的父进程虚拟内存空间mm_struct赋值给子进程
    tsk->mm = mm;
    tsk->active_mm = mm;
    return 0;
    
    .................省略..................
}
```

由于本小节中我们举的示例是通过 fork() 函数创建子进程的情形，所以这里大家先占时忽略 `if (clone_flags & CLONE_VM)` 这个条件判断逻辑，我们先跳过往后看~~

copy_mm函数首先会将父进程的虚拟内存空间current->mm赋值给指针oldmm，然后通过 dup_mm 函数将父进程的虚拟内存空间以及**相关页表**拷贝到子进程的 mm_struct 结构中。最后将拷贝出来的 mm_struct 赋值给子进程的 task_struct 结构。

> 通过 fork() 函数创建出的子进程，它的虚拟内存空间以及相关页表相当于父进程虚拟内存空间的一份拷贝，直接从父进程中拷贝到子进程中。

而当我们通过 vfork 或者 clone 系统调用创建出的子进程，首先会设置 CLONE_VM 标识，这样来到 copy_mm 函数中就会进入 `if (clone_flags & CLONE_VM)` 条件中，在这个分支中会将父进程的虚拟内存空间以及相关页表直接赋值给子进程。这样一来父进程和子进程的虚拟内存空间就变成共享的了。也就是说父子进程之间使用的虚拟内存空间是一样的，并不是一份拷贝。

子进程共享了父进程的虚拟内存空间，这样子进程就变成了我们熟悉的线程，**是否共享地址空间几乎是进程和线程之间的本质区别。Linux 内核并不区别对待它们，线程对于内核来说仅仅是一个共享特定资源的进程而已**。

内核线程和用户态线程的区别就是内核线程没有相关的内存描述符 mm_struct ，内核线程对应的 task_struct 结构中的 mm 域指向 Null，所以内核线程之间调度是不涉及地址空间切换的。

当一个内核线程被调度时，它会发现自己的虚拟地址空间为 Null，虽然它不会访问用户态的内存，但是它会访问内核内存，聪明的内核会将调度之前的上一个用户态进程的虚拟内存空间 mm_struct 直接赋值给内核线程，因为内核线程不会访问用户空间的内存，它仅仅只会访问内核空间的内存，所以直接复用上一个用户态进程的虚拟地址空间就可以避免为内核线程分配 mm_struct 和相关页表的开销，以及避免内核线程之间调度时地址空间的切换开销。

> 父进程与子进程的区别，进程与线程的区别，以及内核线程与用户态线程的区别其实都是围绕着这个 mm_struct 展开的。

现在我们知道了表示进程虚拟内存空间的 mm_struct 结构是如何被创建出来的相关背景，那么接下来我就带大家深入 mm_struct 结构内部，来看一下内核如何通过这么一个 mm_struct 结构体来管理进程的虚拟内存空间的。

### 内核如何划分用户态和内核态虚拟内存空间

用户态的地址空间和内核态的地址空间在内核中是如何被划分的呢？

这就用到了进程的内存描述符mm_struct结构体中的task_size变量，task_size定义了用户态地址空间与内核态地址空间之间的分界线。

```c
struct mm_struct {
    unsigned long task_size;	/* size of task vm space */
}
```

我们知道在 32 位系统中用户态虚拟内存空间为 3 GB，虚拟内存地址范围为：0x0000 0000 - 0xC000 000 。

内核态虚拟内存空间为 1 GB，虚拟内存地址范围为：0xC000 000 - 0xFFFF FFFF。

**32位系统中用户地址空间和内核地址空间的分界线再0xC000 000地址处，那么自然进程的mm_struct结构中的task_size为0xC000 000。**

我们来看下内核在 `/arch/x86/include/asm/page_32_types.h` 文件中关于 TASK_SIZE 的定义

```c
/*
 * User space process size: 3GB (default).
 */
#define TASK_SIZE		__PAGE_OFFSET
```

如下图所示：__PAGE_OFFSET 的值在 32 位系统下为 0xC000 000。

![image-20230328223810875](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20230328223810875.png)

而在 64 位系统中，只使用了其中的低 48 位来表示虚拟内存地址。其中用户态虚拟内存空间为低 128 T，虚拟内存地址范围为：0x0000 0000 0000 0000 - 0x0000 7FFF FFFF F000 。

内核态虚拟内存空间为高 128 T，虚拟内存地址范围为：0xFFFF 8000 0000 0000 - 0xFFFF FFFF FFFF FFFF 。

64 位系统中用户地址空间和内核地址空间的分界线在 0x0000 7FFF FFFF F000 地址处，那么自然进程的 mm_struct 结构中的 task_size 为 0x0000 7FFF FFFF F000 。

我们来看下内核在 `/arch/x86/include/asm/page_64_types.h` 文件中关于 TASK_SIZE 的定义。

```c
#define TASK_SIZE		(test_thread_flag(TIF_ADDR32) ? \
					IA32_PAGE_OFFSET : TASK_SIZE_MAX)

#define TASK_SIZE_MAX		task_size_max()

#define task_size_max()		((_AC(1,UL) << __VIRTUAL_MASK_SHIFT) - PAGE_SIZE)

#define __VIRTUAL_MASK_SHIFT	47
```

我们来看下在 64 位系统中内核如何来计算 TASK_SIZE，在 task_size_max() 的计算逻辑中 1 左移 47 位得到的地址是 0x0000800000000000，然后减去一个 PAGE_SIZE （默认为 4K），就是 0x00007FFFFFFFF000，共 128T。所以在 64 位系统中的 TASK_SIZE 为 0x00007FFFFFFFF000 。

> 这里我们可以看出，64 位虚拟内存空间的布局是和物理内存页 page 的大小有关的，物理内存页 page 默认大小 PAGE_SIZE 为 4K。

PAGE_SIZE 定义在 `/arch/x86/include/asm/page_types.h`文件中：

```c
/* PAGE_SHIFT determines the page size */
#define PAGE_SHIFT		12
#define PAGE_SIZE		(_AC(1,UL) << PAGE_SHIFT)
```

而内核空间的起始地址是 0xFFFF 8000 0000 0000 。在 0x00007FFFFFFFF000 - 0xFFFF 8000 0000 0000 之间的内存区域就是我们在 《4.2 64 位机器上进程虚拟内存空间分布》小节中介绍的 canonical address 空洞。

### 内核如何布局进程虚拟内存空间

![image-20230328224234099](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20230328224234099.png)

前面提到，内核中采用了一个叫做内存描述符的mm_struct结构体来表示进程虚拟内存空间的全部信息。

```c
struct mm_struct {
    unsigned long task_size;    /* size of task vm space */
    unsigned long start_code, end_code, start_data, end_data;
    unsigned long start_brk, brk, start_stack;
    unsigned long arg_start, arg_end, env_start, env_end;
    unsigned long mmap_base;  /* base of mmap area */
    unsigned long total_vm;    /* Total pages mapped */
    unsigned long locked_vm;  /* Pages that have PG_mlocked set */
    unsigned long pinned_vm;  /* Refcount permanently increased */
    unsigned long data_vm;    /* VM_WRITE & ~VM_SHARED & ~VM_STACK */
    unsigned long exec_vm;    /* VM_EXEC & ~VM_WRITE & ~VM_STACK */
    unsigned long stack_vm;    /* VM_STACK */

       ...... 省略 ........
}
```

内核中用mm_struct结构体中的上述属性来定义上图中虚拟内存空间里的不同内存区域

+ start_code 和 end_code 定义代码段的起始和结束位置，程序编译后的二进制文件中的机器码被加载进内存之后就存放在这里。
+ start_data 和 end_data 定义数据段的起始和结束位置，二进制文件中存放的全局变量和静态变量被加载进内存中就存放在这里。
+ 后面紧挨着的是 BSS 段，用于存放未被初始化的全局变量和静态变量，这些变量在加载进内存时会生成一段 0 填充的内存区域 （BSS 段）， BSS 段的大小是固定的，
+ 下面就是 OS 堆了，在堆中内存地址的增长方向是由低地址向高地址增长， start_brk 定义堆的起始位置，brk 定义堆当前的结束位置。
+ 接下来就是内存映射区，在内存映射区内存地址的增长方向是由高地址向低地址增长，mmap_base 定义内存映射区的起始地址。进程运行时所依赖的动态链接库中的代码段，数据段，BSS 段以及我们调用 mmap 映射出来的一段虚拟内存空间就保存在这个区域。
+ start_stack 是栈的起始位置在 RBP 寄存器中存储，栈的结束位置也就是栈顶指针 stack pointer 在 RSP 寄存器中存储。在栈中内存地址的增长方向也是由高地址向低地址增长。
+ arg_start 和 arg_end 是参数列表的位置， env_start 和 env_end 是环境变量的位置。它们都位于栈中的最高地址处。

![image-20230328225022733](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20230328225022733.png)

**在 mm_struct 结构体中除了上述用于划分虚拟内存区域的变量之外，还定义了一些虚拟内存与物理内存映射内容相关的统计变量，操作系统会把物理内存划分成一页一页的区域来进行管理，所以物理内存到虚拟内存之间的映射也是按照【页】为单位进行的。**这部分内容我会在后续的文章中详细介绍，大家这里只需要有个概念就行。

+ mm_struct 结构体中的 total_vm 表示在进程虚拟内存空间中总共与物理内存映射的页的总数。

> 注意映射这个概念，它表示只是将虚拟内存与物理内存建立关联关系，并不代表真正的分配物理内存。

+ 当内存吃紧的时候，有些页可以换出到硬盘上，而有些页因为比较重要，不能换出。locked_vm 就是被锁定不能换出的内存页总数，pinned_vm 表示既不能换出，也不能移动的内存页总数。
+ data_vm 表示数据段中映射的内存页数目，exec_vm 是代码段中存放可执行文件的内存页数目，stack_vm 是栈中所映射的内存页数目，这些变量均是表示进程虚拟内存空间中的虚拟内存使用情况。



### 内核如何管理虚拟内存区域

我们知道内核是通过一个 mm_struct 结构的内存描述符来表示进程的虚拟内存空间的，并通过 task_size 域来划分用户态虚拟内存空间和内核态虚拟内存空间。

划分出的这些虚拟内存空间里边又包含了许多特定的虚拟内存区域，比如：代码段，数据段，堆，内存映射区，栈。那么这些虚拟内存区域在内核中又是如何表示的呢？

这里就引入一个新的结构体vm_area_struct,正是这个结构体描述了这些虚拟内存区域VMA（virtual memory area）。

```c
struct vm_area_struct {

	unsigned long vm_start;		/* Our start address within vm_mm. */
	unsigned long vm_end;		/* The first byte after our end address
					   within vm_mm. */
	/*
	 * Access permissions of this VMA.
	 */
	pgprot_t vm_page_prot;
	unsigned long vm_flags;	

	struct anon_vma *anon_vma;	/* Serialized by page_table_lock */
    struct file * vm_file;		/* File we map to (can be NULL). */
	unsigned long vm_pgoff;		/* Offset (within vm_file) in PAGE_SIZE
					   units */	
	void * vm_private_data;		/* was vm_pte (shared mem) */
	/* Function pointers to deal with this struct. */
	const struct vm_operations_struct *vm_ops;
}
```

每个 vm_area_struct 结构对应于虚拟内存空间中的唯一虚拟内存区域 VMA，vm_start 指向了这块虚拟内存区域的起始地址（最低地址），vm_start 本身包含在这块虚拟内存区域内。vm_end 指向了这块虚拟内存区域的结束地址（最高地址），而 vm_end 本身包含在这块虚拟内存区域之外，所以 vm_area_struct 结构描述的是 [vm_start，vm_end) 这样一段左闭右开的虚拟内存区域。

![image-20230328225546692](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20230328225546692.png)

VM_SHARD 用于指定这块虚拟内存区域映射的物理内存是否可以在多进程之间共享，以便完成进程间通讯。

> 设置这个值即为 mmap 的共享映射，不设置的话则为私有映射。这个等后面我们讲到 mmap 的相关实现时还会再次提起。



### 定义虚拟内存区域的访问权限和行为规范

vm_page_prot 和 vm_flags 都是用来标记 vm_area_struct 结构表示的这块虚拟内存区域的访问权限和行为规范。

内核会将整块物理内存划分为一页一页大小的区域，以页为单位来管理这些物理内存，每页大小默认 4K 。而虚拟内存最终也是要和物理内存一一映射起来的，所以在虚拟内存空间中也有虚拟页的概念与之对应，虚拟内存中的虚拟页映射到物理内存中的物理页。无论是在虚拟内存空间中还是在物理内存中，内核管理内存的最小单位都是页。

**vm_page_prot 偏向于定义底层内存管理架构中页这一级别的访问控制权限**，它可以直接应用在底层页表中，它是一个具体的概念。

虚拟内存区域 VMA 由许多的虚拟页 (page) 组成，每个虚拟页需要经过页表的转换才能找到对应的物理页面。页表中关于内存页的访问权限就是由 vm_page_prot 决定的。

**vm_flags 则偏向于定于整个虚拟内存区域的访问权限以及行为规范。**描述的是虚拟内存区域中的整体信息，而不是虚拟内存区域中具体的某个独立页面。它是一个抽象的概念。可以通过 `vma->vm_page_prot = vm_get_page_prot(vma->vm_flags)` 实现到具体页面访问权限 vm_page_prot 的转换。

下面我列举一些常用到的 vm_flags 方便大家有一个直观的感受：

![image-20230328230209359](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20230328230209359.png)

+ VM_READ，VM_WRITE，VM_EXEC 定义了虚拟内存区域是否可以被读取，写入，执行等权限

​	比如代码段这块内存区域的权限是可读，可执行，但是不可写。数据段具有可读可写的权限但是不可执行。堆	则具有可读可写，可执行的权限（Java 中的字节码存储在堆中，所以需要可执行权限），栈一般是可读可写	的权限，一般很少有可执行权限。而文件映射与匿名映射区存放了共享链接库，所以也需要可执行的权限。

![image-20230328230340131](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20230328230340131.png)

+ VM_SHARD 用于指定这块虚拟内存区域映射的物理内存是否可以在多进程之间共享，以便完成进程间通讯。

> 设置这个值即为 mmap 的共享映射，不设置的话则为私有映射。这个等后面我们讲到 mmap 的相关实现时还会再次提起。

+ VM_IO 的设置表示这块虚拟内存区域可以映射至设备 IO 空间中。通常在设备驱动程序执行 mmap 进行 IO 空间映射时才会被设置。
+ VM_RESERVED 的设置表示在内存紧张的时候，这块虚拟内存区域非常重要，不能被换出到磁盘中。
+ VM_SEQ_READ 的设置用来暗示内核，应用程序对这块虚拟内存区域的读取是会采用顺序读的方式进行，内核会根据实际情况决定预读后续的内存页数，以便加快下次顺序访问速度。
+ VM_RAND_READ 的设置会暗示内核，应用程序会对这块虚拟内存区域进行随机读取，内核则会根据实际情况减少预读的内存页数甚至停止预读。
+ 我们可以通过 posix_fadvise，madvise 系统调用来暗示内核是否对相关内存区域进行顺序读取或者随机读取。相关的详细内容，大家可以看下我上篇文章 [《从 Linux 内核角度探秘 JDK NIO 文件读写本质》 (opens new window)](https://mp.weixin.qq.com/s?__biz=Mzg2MzU3Mjc3Ng==&mid=2247486623&idx=1&sn=0cafed9e89b60d678d8c88dc7689abda&chksm=ce77cad8f90043ceaaca732aaaa7cb692c1d23eeb6c07de84f0ad690ab92d758945807239cee&token=1276722624&lang=zh_CN#rd)中的第 9 小节文件页预读部分。

通过一系列介绍，我们可以看到vm_flags就是定义整个虚拟内存区域的访问权限以及行为规范，而内存区域中内存的最小单位为页（4K）,虚拟内存区域中包含了很多这样的虚拟页，对于虚拟内存区域VMA设置的访问权限也会全部复制到区域中包含的内存页中。

### 关联内存映射中的映射关系

vm_area_struct接下来的三个属性**anon_vma，vm_file，vm_pgoff**分别和虚拟内存映射相关，**虚拟内存区域可以映射到物理内存上，也可以映射到文件中，映射到物理内存上我们称之为匿名映射，映射到文件上称之为文件映射**。

那么这个映射关系在内核中该如何表示呢？这就用到了 vm_area_struct 结构体中的上述三个属性。

![image-20230329104412269](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20230329104412269.png)

当我们调用malloc申请内存的适合，如果申请的是小块内存（低于128K）则会使用do_brk()系统调用通过调整堆中的brk指针大小来增加或者回收堆内存。

如果申请的是比较大块的内存（超过128K）,则会调用mmap在上图虚拟内存空间中的文件映射与匿名映射区创建出一块VMA内存区域（这里是匿名映射）。这块匿名映射区域就用struct anon_vma结构表示

当调用mmap进行文件映射时，vm_file属性就用来关联被映射的文件。这样一来虚拟内存区域就与映射文件关联了起来。vm_pgoff则表示映射进虚拟内存中的文件内容，在文件中的偏移。

> 当然在匿名映射中，vm_area_struct 结构中的 vm_file 就为 null，vm_pgoff 也就没有了意义。

vmf_private_data则用于存储VMA中的私有数据。具体的存储内容和内存映射的类型有关，暂不展开讨论。



### 针对虚拟内存区域的相关操作

struct vm_area_struct 结构中还有一个vm_ops用来指向针对虚拟内存区域VMA的相关操作的函数指针。

```c
struct vm_operatirons_struct {
    void (*open)(struct vm_area_struct *area);
    void (*close)(struct vm_area_struct *area);
    vm_fault_t (*fault)(struct vm_fault *vmf);
    vm_fault_t (*page_mkwrite)(struct vm_fault *vmf);
    ....... 省略 .......
}
```

+ 当指定的虚拟内存区域被加入到进程虚拟内存空间中时，open函数会被调用
+ 当虚拟内存区域VMA从进程虚拟内存空间中被删除时，close函数会被调用
+ 当进程访问虚拟内存时，访问的页面不在物理内存中，可能时未分配物理内存也可能时被置换到磁盘中，这时就会产生缺页异常，fault函数就会被调用。
+ 当一个只读页面将要变成可写时，page_mkwrite函数会被调用

struct vm_operations_struct 结构中定义的都是对虚拟内存区域 VMA 的相关操作函数指针。



### 虚拟内存区域在内核中是如何被组织的

我们继续来到 struct vm_area_struct 结构中，来看一下与组织结构相关的一些属性：

```c
struct vm_area_struct {
    
    struct vm_area_struct *vm_next, *vm_prev;
	struct rb_node vm_rb;
    struct list_head anon_vma_chain; 
	struct mm_struct *vm_mm;	/* The address space we belong to. */

	unsigned long vm_start;		/* Our start address within vm_mm. */
	unsigned long vm_end;		/* The first byte after our end address
					   within vm_mm. */
	/*
	 * Access permissions of this VMA.
	 */
	pgprot_t vm_page_prot;
	unsigned long vm_flags;	

	struct anon_vma *anon_vma;	/* Serialized by page_table_lock */
    struct file * vm_file;		/* File we map to (can be NULL). */
	unsigned long vm_pgoff;		/* Offset (within vm_file) in PAGE_SIZE
					   units */	
	void * vm_private_data;		/* was vm_pte (shared mem) */
	/* Function pointers to deal with this struct. */
	const struct vm_operations_struct *vm_ops;
}
```

在内核中其实是通过一个struct vm_area_struct结构的双向链表将虚拟内存空间中的这些虚拟内存区域VMA串联起来的。

vm_area_struct 结构中的 vm_next ，vm_prev 指针分别指向 VMA 节点所在双向链表中的后继节点和前驱节点，内核中的这个 VMA 双向链表是有顺序的，所有 VMA 节点按照低地址到高地址的增长方向排序。

双向链表中的最后一个 VMA 节点的 vm_next 指针指向 NULL，双向链表的头指针存储在内存描述符 struct mm_struct 结构中的 mmap 中，正是这个 mmap 串联起了整个虚拟内存空间中的虚拟内存区域。

```c
struct mm_struct {
    struct vm_area_struct *mmap;		/* list of VMAs */
}
```

![image-20230329120151586](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20230329120151586.png)

我们可以通过 `cat /proc/pid/maps` 或者`pmap pid`查看进程的虚拟内存空间布局以及其中包含的所有内存区域。这两个命令背后的实现原理就是通过变量内核中这个vm_area_struct双向链表获取的。



内核中关于这些虚拟内存区域的操作除了遍历之外还有许多需要根据特定虚拟内存地址在虚拟内存空间中查找特定的虚拟内存区域。

尤其在进程虚拟内存空间中包含的内存区域 VMA 比较多的情况下，使用红黑树查找特定虚拟内存区域的时间复杂度是 O( logN ) ，可以显著减少查找所需的时间。

所以在内核中，同样的内存区域 vm_area_struct 会有两种组织形式，一种是双向链表用于高效的遍历，另一种就是红黑树用于高效的查找。

每个 VMA 区域都是红黑树中的一个节点，通过 struct vm_area_struct 结构中的 vm_rb 将自己连接到红黑树中。

而红黑树中的根节点存储在内存描述符 struct mm_struct 中的 mm_rb 中：

```c
struct mm_struct {
     struct rb_root mm_rb;
}
```

![image-20230329121644995](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20230329121644995.png)

## 程序编译后的二进制文件如何映射到虚拟内存空间中

进程的虚拟内存空间mm_struct以及这些虚拟内存区域vm_area_struct是如何被创建并初始化的？

程序代码编译之后会生成一个ELF格式的二进制文件，这个二进制文件中包含了程序运行时所需要的元信息，比如程序的机器码，程序中的全局变量以及静态变量等。

这个ELF格式的二进制文件中的布局和我们前面讲的虚拟内存空间中的布局类似，也是一段一段的，每一段包含了不同的元数据。

> 磁盘文件中的段叫做Section，内存中的段叫做Segment，也就是内存区域

磁盘文件中的这些Section会在进程运行之前加载到内存中并映射到内存中的Segment。通常是多个Section映射到一个Segment。

比如磁盘文件中的.text，.rodata等一些只读的Section，会被映射到内存的一个只读可执行的Segment里（代码段）。而.data，.bss等一些可读写的Section，则会被映射到内存中的一个具有读写权限的Segment（数据段，BSS段）。

那么这些 ELF 格式的二进制文件中的 Section 是如何加载并映射进虚拟内存空间的呢？

内核中完成这个映射过程的函数是load_elf_binary，这个函数的作用很大，加载内核的是它，启动第一个用户态进程init的是它，fork完了之后，调用exec运行一个二进制程序的也是它。当exec运行一个二进制程序的时候，除了解析ELF的格式之外，另一个重要的事情就是建立上述提到的内存映射。

```c
static int load_elf_binary(struct linux_binprm *bprm){
    ...........省略..........
    //设置虚拟内存空间中的内存映射区域起始地址mmap_base
    setup_new_exec(bprm);
    
    ...........省略..........
    //创建并初始化栈对应的vm_area_struct结构
    //设置mm->start_stack就是栈的起始地址也就是栈底，并将mm->arg_start是指向栈底的
    retval = setup_arg_pages(bprm, randomize_stack_top(STACK_TOP),
                            executable_stack);
    ...........省略..........
    //将二进制文件中的代码部分映射到虚拟空间中
    error = elf_map(bprm->file, load_bias + vaddr, elf_ppnt, 
                   elf_prot, elf_flags, total_size);
    ...........省略..........
    //创建并初始化堆对应的vm_area_struct结构
    //设置current->mm->start_brk = current->mm->brk, 设置堆的起始地址 start_brk, 结束地址brk,起初两者相等表示堆是空的
    retval = set_brk(elf_bss, elf_brk, bss_prot);
     ...........省略..........
   	// 将进程依赖的动态链接库 .so 文件映射到虚拟内存空间中的内存映射区域
    elf_entry = load_elf_interp(&loc->interp_elf_ex,
                               interpreter,
                               &interp_map_addr,
                               load_bias, interp_elf_phdata);
    //初始化内存描述符mm_struct
    current->mm->end_code = end_code;
    current->mm->start_code = start_code;
    current->mm->start_data = start_data;
    current->mm->end_data = end_data;
    current->mm->start_stack = bprm->p;
    ...........省略..........
}
```

+ setup_new_exec 设置虚拟内存空间中的内存映射区域起始地址mmap_base
+ setup_arg_pages创建并初始化栈对应的vm_area_struct结构。置mm->start_stack 就是栈的起始地址也就是栈底，并将 mm->arg_start 是指向栈底的。
+ elf_map 将 ELF 格式的二进制文件中.text ，.data，.bss 部分映射到虚拟内存空间中的代码段，数据段，BSS 段中。
+ set_brk 创建并初始化堆对应的的 vm_area_struct 结构，设置 current->mm->start_brk = current->mm->brk，设置堆的起始地址 start_brk，结束地址 brk。 起初两者相等表示堆是空的。
+ load_elf_interp 将进程依赖的动态链接库 .so 文件映射到虚拟内存空间中的内存映射区域
+ 初始化内存描述符 mm_struct



## 内核虚拟内存空间

在我们已经知道了进程虚拟内存空间在内核中的布局以及管理，那么内核态的虚拟内存空间又是什么样子的呢？

![image-20230329144846947](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20230329144846947.png)

不同进程之间的虚拟内存空间是相互隔离的，彼此之间相互独立，相互感知不到其他进程的存在。使得进程以为自己拥有所有的内存资源。

而内核态虚拟内存空间是所有进程共享的，不同进程进入内核态之后看到的虚拟内存空间全部是一样的。

> 这里我和大家澄清一个经常被误解的概念：由于内核会涉及到物理内存的管理，所以很多人会想当然地认为只要进入了内核态就开始使用物理地址了，这就大错特错了，千万不要这样理解，进程进入内核态之后使用的仍然是虚拟内存地址，只不过在内核中使用的虚拟内存地址被限制在了内核态虚拟内存空间范围中

### 32位体系内核虚拟内存空间布局

在 32 位体系结构下进程用户态虚拟内存空间为 3 GB，虚拟内存地址范围为：0x0000 0000 - 0xC000 000 。内核态虚拟内存空间为 1 GB，虚拟内存地址范围为：0xC000 000 - 0xFFFF FFFF。

本小节我们主要关注 0xC000 000 - 0xFFFF FFFF 这段虚拟内存地址区域也就是内核虚拟内存空间的布局情况。

#### 直接映射区

在总共大小 1G 的内核虚拟内存空间中，位于最前边有一块 896M 大小的区域，我们称之为直接映射区或者线性映射区，地址范围为 3G -- 3G + 896m 。

之所以这块 896M 大小的区域称为直接映射区或者线性映射区，是因为 3G -- 3G + 896m 这块 896M 大小的虚拟内存会直接映射到 0 - 896M 这块 896M 大小的物理内存上，**这块区域中的虚拟内存地址直接减去 0xC000 0000 (3G) 就得到了物理内存地址**。所以我们称这块区域为直接映射区。

> 我们假设现在机器上的物理内存为 4G 大小

![image-20230329145210097](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20230329145210097.png)

> 虽然这块区域中的虚拟地址是直接映射到物理地址上，但是内核在访问这段区域的时候还是走的虚拟内存地址，内核也会为这块空间建立映射页表。

**在这段 896M 大小的物理内存中，前 1M 已经在系统启动的时候被系统占用，1M 之后的物理内存存放的是内核代码段，数据段，BSS 段（这些信息起初存放在 ELF格式的二进制文件中，在系统启动的时候被加载进内存）。**

> 我们可以通过 `cat /proc/iomem` 命令查看具体物理内存布局情况。

当我们使用 fork 系统调用创建进程的时候，内核会创建一系列进程相关的描述符，比如之前提到的进程的核心数据结构 task_struct，进程的内存空间描述符 mm_struct，以及虚拟内存区域描述符 vm_area_struct 等。

这些进程相关的数据结构也会存放在物理内存前 896M 的这段区域中，当然也会被直接映射至内核态虚拟内存空间中的 3G -- 3G + 896m 这段直接映射区域中。

**内核栈**

当进程被创建完毕之后，在内核运行的过程中，会涉及内核栈的分配，内核会为每个进程分配一个固定大小的内核栈（一般是两个页大小，依赖具体的体系结构），每个进程的整个调用链必须放在自己的内核栈中，内核栈也是分配在直接映射区。

与进程用户空间中的栈不同的是，内核栈容量小而且是固定的，用户空间中的栈容量大而且可以动态扩展。内核栈的溢出危害非常巨大，它会直接悄无声息的覆盖相邻内存区域中的数据，破坏数据。

**直接映射区域功能划分**

我们都知道内核对物理内存的管理都是以页为最小单位来管理的，每页默认 4K 大小，理想状况下任何种类的数据页都可以存放在任何页框中，没有什么限制。比如：存放内核数据，用户数据，缓冲磁盘数据等。

但是实际的计算机体系结构受到硬件方面的限制制约，间接导致限制了页框的使用方式。

比如在 X86 体系结构下，ISA 总线的 DMA （直接内存存取）控制器，只能对内存的前16M 进行寻址，这就导致了 ISA 设备不能在整个 32 位地址空间中执行 DMA，只能使用物理内存的前 16M 进行 DMA 操作。

**因此直接映射区的前 16M 专门让内核用来为 DMA 分配内存，这块 16M 大小的内存区域我们称之为 ZONE_DMA。**

**而直接映射区中剩下的部分也就是从 16M 到 896M（不包含 896M）这段区域，我们称之为 ZONE_NORMAL。**从字面意义上我们可以了解到，这块区域包含的就是正常的页框（使用没有任何限制）。

![image-20230329145819396](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20230329145819396.png)

> 注意这里的 ZONE_DMA 和 ZONE_NORMAL 是内核针对物理内存区域的划分。

#### ZONE_HIGHMEM 高端内存

而物理内存 896M 以上的区域被内核划分为 ZONE_HIGHMEM 区域，我们称之为高端内存。

本例中我们的物理内存假设为 4G，高端内存区域为 4G - 896M = 3200M，那么这块 3200M 大小的 ZONE_HIGHMEM 区域该如何映射到内核虚拟内存空间中呢？

由于内核虚拟内存空间中的前 896M 虚拟内存已经被直接映射区所占用，而在 32 体系结构下内核虚拟内存空间总共也就 1G 的大小，这样一来内核剩余可用的虚拟内存空间就变为了 1G - 896M = 128M。

**显然物理内存中 3200M 大小的 ZONE_HIGHMEM 区域无法继续通过直接映射的方式映射到这 128M 大小的虚拟内存空间中。**

这样一来物理内存中的 ZONE_HIGHMEM 区域就只能采用动态映射的方式映射到 128M 大小的内核虚拟内存空间中，也就是说只能动态的一部分一部分的分批映射，先映射正在使用的这部分，使用完毕解除映射，接着映射其他部分。

![image-20230329150151627](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20230329150151627.png)

内核虚拟内存空间中的 3G + 896M 这块地址在内核中定义为 high_memory，high_memory 往上有一段 8M 大小的内存空洞。空洞范围为：high_memory 到 VMALLOC_START 。

VMALLOC_START 定义在内核源码 `/arch/x86/include/asm/pgtable_32_areas.h` 文件中：

```c
#define VMALLOC_OFFSET	(8 * 1024 * 1024)

#define VMALLOC_START	((unsigned long)high_memory + VMALLOC_OFFSET)
```



#### vmalloc动态映射区

接下来 VMALLOC_START 到 VMALLOC_END 之间的这块区域成为动态映射区。采用动态映射的方式映射物理内存中的高端内存。

```c
#ifdef CONFIG_HIGHMEM
# define VMALLOC_END	(PKMAP_BASE - 2 * PAGE_SIZE)
#else
# define VMALLOC_END	(LDT_BASE_ADDR - 2 * PAGE_SIZE)
#endif
```

![image-20230329150343934](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20230329150343934.png)

和用户态进程使用 malloc 申请内存一样，在这块动态映射区内核是使用 vmalloc 进行内存分配。由于之前介绍的动态映射的原因，vmalloc 分配的内存在虚拟内存上是连续的，但是物理内存是不连续的。通过页表来建立物理内存与虚拟内存之间的映射关系，从而可以将不连续的物理内存映射到连续的虚拟内存上。

> 由于 vmalloc 获得的物理内存页是不连续的，因此它只能将这些物理内存页一个一个地进行映射，在性能开销上会比直接映射大得多。



#### 永久映射区

![image-20230329150456125](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20230329150456125.png)

而在 PKMAP_BASE 到 FIXADDR_START 之间的这段空间称为永久映射区。在内核的这段虚拟地址空间中允许建立与物理高端内存的长期映射关系。比如内核通过 alloc_pages() 函数在物理内存的高端内存中申请获取到的物理内存页，这些物理内存页可以通过调用 kmap 映射到永久映射区中。

> LAST_PKMAP 表示永久映射区可以映射的页数限制。

```c
#define PKMAP_BASE		\
	((LDT_BASE_ADDR - PAGE_SIZE) & PMD_MASK)

#define LAST_PKMAP 1024
```



#### 固定映射区

![image-20230329150612762](C:\Users\11547\AppData\Roaming\Typora\typora-user-images\image-20230329150612762.png)

内核虚拟内存空间中的下一个区域为固定映射区，区域范围为：FIXADDR_START 到 FIXADDR_TOP。

FIXADDR_START 和 FIXADDR_TOP 定义在内核源码 /arch/x86/include/asm/fixmap.h 文件中：

```c
#define FIXADDR_START		(FIXADDR_TOP - FIXADDR_SIZE)

extern unsigned long __FIXADDR_TOP; // 0xFFFF F000
#define FIXADDR_TOP	((unsigned long)__FIXADDR_TOP)
```

在内核虚拟内存空间的直接映射区中，直接映射区中的虚拟内存地址与物理内存前 896M 的空间的映射关系都是预设好的，一比一映射。

在固定映射区中的虚拟内存地址可以自由映射到物理内存的高端地址上，但是与动态映射区以及永久映射区不同的是，在固定映射区中虚拟地址是固定的，而被映射的物理地址是可以改变的。也就是说，有些虚拟地址在编译的时候就固定下来了，是在内核启动过程中被确定的，而这些虚拟地址对应的物理地址不是固定的。**采用固定虚拟地址的好处是它相当于一个指针常量（常量的值在编译时确定），指向物理地址，如果虚拟地址不固定，则相当于一个指针变量。**

那为什么会有固定映射这个概念呢 ? 比如：在内核的启动过程中，有些模块需要使用虚拟内存并映射到指定的物理地址上，而且这些模块也没有办法等待完整的内存管理模块初始化之后再进行地址映射。因此，内核固定分配了一些虚拟地址，这些地址有固定的用途，使用该地址的模块在初始化的时候，将这些固定分配的虚拟地址映射到指定的物理地址上去。



#### 临时映射区

在内核虚拟内存空间中的最后一块区域为临时映射区，那么这块临时映射区是用来干什么的呢？

![image-20230329151011003](C:\Users\11547\AppData\Roaming\Typora\typora-user-images\image-20230329151011003.png)

> 先跳过，还看不懂。。。



### 64位体系内核虚拟内存空间布局

内核虚拟内存空间在 32 位体系下只有 1G 大小，实在太小了，因此需要精细化的管理，于是按照功能分类划分除了很多内核虚拟内存区域，这样就显得非常复杂。

到了 64 位体系下，内核虚拟内存空间的布局和管理就变得容易多了，因为进程虚拟内存空间和内核虚拟内存空间各自占用 128T 的虚拟内存，实在是太大了，我们可以在这里边随意翱翔，随意挥霍。

因此在 64 位体系下的内核虚拟内存空间与物理内存的映射就变得非常简单，由于虚拟内存空间足够的大，即便是内核要访问全部的物理内存，直接映射就可以了，不在需要用到《7.1.2 ZONE_HIGHMEM 高端内存》小节中介绍的高端内存那种动态映射方式。

![image-20230329151414936](C:\Users\11547\AppData\Roaming\Typora\typora-user-images\image-20230329151414936.png)

在 64 位系统中，只使用了其中的低 48 位来表示虚拟内存地址。其中用户态虚拟内存空间为低 128 T，虚拟内存地址范围为：0x0000 0000 0000 0000 - 0x0000 7FFF FFFF F000 。

内核态虚拟内存空间为高 128 T，虚拟内存地址范围为：0xFFFF 8000 0000 0000 - 0xFFFF FFFF FFFF FFFF 。

本小节我们主要关注 0xFFFF 8000 0000 0000 - 0xFFFF FFFF FFFF FFFF 这段内核虚拟内存空间的布局情况。

![image-20230329151440021](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20230329151440021.png)

64 位内核虚拟内存空间从 0xFFFF 8000 0000 0000 开始到 0xFFFF 8800 0000 0000 这段地址空间是一个 8T 大小的内存空洞区域。

紧着着 8T 大小的内存空洞下一个区域就是 64T 大小的直接映射区。这个区域中的虚拟内存地址减去 PAGE_OFFSET 就直接得到了物理内存地址。

PAGE_OFFSET 变量定义在 /arch/x86/include/asm/page_64_types.h 文件中：

```c
#define __PAGE_OFFSET_BASE      _AC(0xffff880000000000, UL)
#define __PAGE_OFFSET           __PAGE_OFFSET_BASE
```

从图中 VMALLOC_START 到 VMALLOC_END 的这段区域是 32T 大小的 vmalloc 映射区，这里类似用户空间中的堆，内核在这里使用 vmalloc 系统调用申请内存。

VMALLOC_START 和 VMALLOC_END 变量定义在 `/arch/x86/include/asm/pgtable_64_types.h` 文件中：

```c
#define __VMALLOC_BASE_L4	0xffffc90000000000UL

#define VMEMMAP_START		__VMEMMAP_BASE_L4

#define VMALLOC_END		(VMALLOC_START + (VMALLOC_SIZE_TB << 40) - 1)
```

从 VMEMMAP_START 开始是 1T 大小的虚拟内存映射区，用于存放物理页面的描述符 struct page 结构用来表示物理内存页。

VMEMMAP_START 变量定义在 `/arch/x86/include/asm/pgtable_64_types.h` 文件中：

```
#define __VMEMMAP_BASE_L4	0xffffea0000000000UL

# define VMEMMAP_START		__VMEMMAP_BASE_L4
```

从 __START_KERNEL_map 开始是大小为 512M 的区域用于存放内核代码段、全局变量、BSS 等。这里对应到物理内存开始的位置，减去 __START_KERNEL_map 就能得到物理内存的地址。这里和直接映射区有点像，但是不矛盾，因为直接映射区之前有 8T 的空洞区域，早就过了内核代码在物理内存中加载的位置。

__START_KERNEL_map 变量定义在 `/arch/x86/include/asm/page_64_types.h` 文件中：

```c
#define __START_KERNEL_map  _AC(0xffffffff80000000, UL)
```

![image-20230329151818818](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20230329151818818.png)

## 到底什么是物理内存地址？

聊完了虚拟内存，我们接着聊一下物理内存，我们平时所称的内存也叫随机访问存储器（ random-access memory ）也叫 RAM 。而 RAM 分为两类：

+ 一类是静态 RAM（ `SRAM` ），这类 SRAM 用于 CPU 高速缓存 L1Cache，L2Cache，L3Cache。其特点是访问速度快，访问速度为 1 - 30 个时钟周期，但是容量小，造价高。

![image-20230329151909363](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20230329151909363.png)

+ 另一类则是动态 RAM ( `DRAM` )，这类 DRAM 用于我们常说的主存上，其特点的是访问速度慢（相对高速缓存），访问速度为 50 - 200 个时钟周期，但是容量大，造价便宜些（相对高速缓存）

内存由一个一个的存储器模块（memory module）组成，它们插在主板的扩展槽上。常见的存储器模块通常以 64 位为单位（ 8 个字节）传输数据到存储控制器上或者从存储控制器传出数据。

![image-20230329152001613](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20230329152001613.png)

如图所示内存条上黑色的元器件就是存储器模块（memory module）。多个存储器模块连接到存储控制器上，就聚合成了主存。

![image-20230329152016354](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20230329152016354.png)

而 DRAM 芯片就包装在存储器模块中，每个存储器模块中包含 8 个 DRAM 芯片，依次编号为 0 - 7 。

![image-20230329152042266](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20230329152042266.png)

而每一个 DRAM 芯片的存储结构是一个二维矩阵，二维矩阵中存储的元素我们称为超单元（supercell），每个 supercell 大小为一个字节（8 bit）。每个 supercell 都由一个坐标地址（i，j）。

> i 表示二维矩阵中的行地址，在计算机中行地址称为 RAS (row access strobe，行访问选通脉冲)。 j 表示二维矩阵中的列地址，在计算机中列地址称为 CAS (column access strobe,列访问选通脉冲)。

下图中的 supercell 的 RAS = 2，CAS = 2。

![image-20230329152140690](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20230329152140690.png)

DRAM 芯片中的信息通过引脚流入流出 DRAM 芯片。每个引脚携带 1 bit的信号。

图中 DRAM 芯片包含了两个地址引脚( addr )，因为我们要通过 RAS，CAS 来定位要获取的 supercell 。还有 8 个数据引脚（data），因为 DRAM 芯片的 IO 单位为一个字节（8 bit），所以需要 8 个 data 引脚从 DRAM 芯片传入传出数据。

> 注意这里只是为了解释地址引脚和数据引脚的概念，实际硬件中的引脚数量是不一定的。

### DRAM芯片的访问

### CPU如何读写主存

### CPU从主存读取数据过程

### 如何根据物理内存地址从主存中读取数据

### CPU 向内存写入数据过程
