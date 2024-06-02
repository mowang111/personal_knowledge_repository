在做进程运行轨迹的跟踪与统计实验时，需要编写fprintk函数来打印日志，书上是这样写的：
```c
//fprintk（）代码实现
static char logbuf[1024];
int fprintk(int fd, const char *fmt, ...)
{
	va_list args;
	int count;
	struct file * file;
	struct minode * inode;
	va_start(args, fmt);
	count = vsprintf(logbuf, fmt, args);
	va_end(args);
	if (fd == 3) count = sys_write(fd, logbuf, count);
	return count;
}
```
看上去很有道理，但是调用的时候发现很多问题。
## 坑1：编译器优化
当我`do_exit`函数中调用`fprintk`时，死活打印不出来，我想着可能是fd出了问题，于是简化了一下函数，然后把fd打印出来：
```c
// static char logbuf[1024];
int fprintk(int fd)
{
	printk("--------------------------------------\n");
	printk("fprintk called with fd: %d\n", fd);  // 调试信息
	// va_list args;
	// int count;
	// va_start(args, fmt);
	// count = vsprintf(logbuf, fmt, args);
	// va_end(args);
	// printk("fprintk: formatted string: %s\n", logbuf);  // 调试信息
	// if (fd == 3) {
	// 	count = sys_write(fd, logbuf, count);
	// 	printk("fprintk: written %d bytes to fd %d\n", count, fd);  // 调试信息
	// }
	printk("--------------------------------------\n");
	// return count;
	return 0;
}
```
接着在`/kernel/exit.c`的`do_exit()`函数中添加该函数调用：
```c
int fd = 3;
......
printk("exit fd: %d\n", fd);
// fprintk(fd, "%ld\t%c\t%ld\n", current->pid, 'E', jiffies);
fprintk(fd);
...
```
实际实验中，发现打印出来的fd不是3，而是一个很奇怪的值，就不知道是为什么。经过stackoverflow上的老哥提示，尝试修改编译器优化参数-O为-O0，禁止编译器优化（只针对exit和printk两个文件）
```makefile
kernel.o: $(OBJS)
	$(LD) -m elf_i386 -r -o kernel.o $(OBJS)
	sync

exit.o: exit.c
	$(CC) $(CFLAGS) -O0 -c -o exit.o exit.c

printk.o: printk.c
	$(CC) $(CFLAGS) -O0 -c -o printk.o printk.c

.c.s:
	$(CC) $(CFLAGS) \
	-S -o $*.s $<
.s.o:
	$(AS) -o $*.o $<
.c.o:
	$(CC) $(CFLAGS) \
	-c -o $*.o $<
```
然后打印出的fd终于正确了！
## 坑2: do_exit的特殊
但是还是写入不了退出的进程信息，后来调试发现进程调用`do_exit`前已经把log相关的fd关闭了（之前以为统一在`do_exit`里回收），换成下面的写法，直接通过0号进程找文件指针，跳过`sys_write`，直接使用`file_write`:
```c
static char logbuf[1024];
int fprintk(int fd, const char *fmt, ...)
{
	va_list args;
	int count;
	struct file * file;
	struct minode * inode;
	va_start(args, fmt);
	count = vsprintf(logbuf, fmt, args);
	va_end(args);
	if (!(file=task[0]->filp[fd]))    /* 从进程0的文件描述符表中得到文件句柄 */
        return 0;
	inode = file->f_inode;
	count = file_write(inode,file,logbuf,count);
	return count;
}
```
这下总行了吧？
## 坑3: logbuf在内核数据段
运行后发现log文件内容变成了乱码，？？？我迷惑了，于是跟进`file_write`函数内部查看，发现了这样一行代码：
```c
get_fs_byte(buf++);
```
好像有点熟悉，这不是系统调用那个实验时，从用户空间拿字符的方式吗，猛然想起`logbuf`是在内核数据段的的，需要手动先将`fs`换成`ds`，于是有了以下代码：
```c
static char logbuf[1024];
int fprintk(int fd, const char *fmt, ...)
{
	va_list args;
	int count;
	struct file * file;
	struct minode * inode;
	va_start(args, fmt);
	count = vsprintf(logbuf, fmt, args);
	va_end(args);
	if (!(file=task[0]->filp[fd]))    /* 从进程0的文件描述符表中得到文件句柄 */
        return 0;
	inode = file->f_inode;
	__asm__(
	    "push %%fs\n\t"
	    "push %%ds\n\t"
	    "pop %%fs\n\t"
	    ::);
	count = file_write(inode, file, logbuf, count);
	__asm__(
	    "pop %%fs\n\t"
	    ::);
	return count;
}
```
机智如我！
## 坑4: 
然后内核就莫名其妙了，一闪一闪的。。。
发生了什么？最后没辙，看了下大佬的代码：
```c
#include <linux/sched.h>
#include <sys/stat.h>

static char logbuf[1024];
int fprintk(int fd, const char *fmt, ...)
{
    va_list args;
    int count;
    struct file * file;
    struct m_inode * inode;

    va_start(args, fmt);
    count=vsprintf(logbuf, fmt, args);
    va_end(args);

    if (fd < 3)    /* 如果输出到stdout或stderr，直接调用sys_write即可 */
    {
        __asm__("push %%fs\n\t"
            "push %%ds\n\t"
            "pop %%fs\n\t"
            "pushl %0\n\t"
            "pushl $logbuf\n\t" /* 注意对于Windows环境来说，是_logbuf,下同 */
            "pushl %1\n\t"
            "call sys_write\n\t" /* 注意对于Windows环境来说，是_sys_write,下同 */
            "addl $8,%%esp\n\t"
            "popl %0\n\t"
            "pop %%fs"
            ::"r" (count),"r" (fd):"ax","cx","dx");
    }
    else    /* 假定>=3的描述符都与文件关联。事实上，还存在很多其它情况，这里并没有考虑。*/
    {
        if (!(file=task[0]->filp[fd]))    /* 从进程0的文件描述符表中得到文件句柄 */
            return 0;
        inode=file->f_inode;

        __asm__("push %%fs\n\t"
            "push %%ds\n\t"
            "pop %%fs\n\t"
            "pushl %0\n\t"
            "pushl $logbuf\n\t"
            "pushl %1\n\t"
            "pushl %2\n\t"
            "call file_write\n\t"
            "addl $12,%%esp\n\t"
            "popl %0\n\t"
            "pop %%fs"
            ::"r" (count),"r" (file),"r" (inode):"ax","cx","dx");
    }
    return count;
}
```
仔细看下来，发现本质是一样的啊，只不过他是用汇编实现的`file_write`调用，我是用c实现的而已，为了找出区别，然后我做了以下尝试，将代码一步一步替换成大佬的代码，下面是代码1（大佬的代码称为代码2）：
```c
static char logbuf[1024];
int fprintk(int fd, const char *fmt, ...)
{
	va_list args;
	int count;
	struct file * file;
	struct m_inode * inode;
	va_start(args, fmt);
	count = vsprintf(logbuf, fmt, args);
	va_end(args);
	if (fd == 3) {
		// get file by 1 process
		if (!(file=task[0]->filp[fd]))    /* 从进程0的文件描述符表中得到文件句柄 */
            return 0;
		inode = file->f_inode;
		__asm__("push %%fs\n\t"
				"push %%ds\n\t"
				"pop %%fs\n\t"
				::);
		__asm__("pushl %0\n\t"
				"pushl $logbuf\n\t"
				"pushl %1\n\t"
				"pushl %2\n\t"
				"call file_write\n\t"
				"addl $12,%%esp\n\t"
				"popl %0\n\t"
				"pop %%fs\n\t"
				::"r"(count), "r"(file), "r"(inode):"ax","cx","dx");
		printk("logbuf: %s\n", logbuf);
		printk("write %d bytes\n", count);
	}
	return count;
}
```
到了这一步，只是把一段汇编分成两段来写，但是产生的效果完全不一样：
![[嵌入汇编代码1显示结果.png]]
接着跟踪调试，定位到具体报错代码是在调用`file_write(struct m_inode * inode, struct file * filp, char * buf, int count)`时，执行`bh=bread(inode->i_dev,block)`报错，可以猜测是`inode`的值错了，导致其中存的i节点设备不存在。
那这个值为什么会错呢？接下来，对代码1和代码2分吧进行反汇编调试，涉及`__asm__`相关的代码如下：
```asm 代码1
0x84b3 <fprintk+97>     push   %fs                                        0x84b5 <fprintk+99>     push   %ds                                        0x84b6 <fprintk+100>    pop    %fs                                        0x84b8 <fprintk+102>    mov    0x18(%esp),%edi                            0x84bc <fprintk+106>    mov    0x14(%esp),%esi                            0x84c0 <fprintk+110>    mov    0x10(%esp),%ebx                            0x84c4 <fprintk+114>    push   %edi                                       0x84c5 <fprintk+115>    push   $0x1fb00
0x84ca <fprintk+120>    push   %esi                                       0x84cb <fprintk+121>    push   %ebx                                       0x84cc <fprintk+122>    call   0xde1d <file_write>                        0x84d1 <fprintk+127>    add    $0xc,%esp                                  0x84d4 <fprintk+130>    pop    %edi                                       0x84d5 <fprintk+131>    pop    %fs
```

```asm 代码2
0x84b3 <fprintk+97>     mov    0x18(%esp),%edi                  
0x84b7 <fprintk+101>    mov    0x14(%esp),%esi                 
0x84bb <fprintk+105>    mov    0x10(%esp),%ebx                  
0x84bf <fprintk+109>    push   %fs                       
0x84c1 <fprintk+111>    push   %ds                          
0x84c2 <fprintk+112>    pop    %fs                 
0x84c4 <fprintk+114>    push   %edi
0x84c5 <fprintk+115>    push   $0x1fb00        
0x84ca <fprintk+120>    push   %esi                 
0x84cb <fprintk+121>    push   %ebx                
0x84cc <fprintk+122>    call   0xde1d <file_write>
0x84d1 <fprintk+127>    add    $0xc,%esp
0x84d4 <fprintk+130>    pop    %edi
0x84d5 <fprintk+131>    pop    %fs
```

可以看出两者的区别仅在于这六行代码的顺序不同，这个很好理解，`__asm__`嵌入汇编前会做一些处理。
```asm
0x84b3 <fprintk+97>     push   %fs                                        0x84b5 <fprintk+99>     push   %ds                                        0x84b6 <fprintk+100>    pop    %fs
0x84b8 <fprintk+102>    mov    0x18(%esp),%edi                            0x84bc <fprintk+106>    mov    0x14(%esp),%esi                            0x84c0 <fprintk+110>    mov    0x10(%esp),%ebx
```
前面三行是自己写的，后面三行是将count,file,inode三个变量的值保存到寄存器中，函数中的局部变量保存在堆栈中，故它们三个都是通过esp寄存器加上一定的偏移找到，而push指令会导致esp寄存器中的值增加，相应的偏移量确没有改变，导致上述三个变量的值错了，编译器无法识别嵌入汇编中的push指令对esp寄存器的影响，所以这种嵌入汇编还是尽量写到一起。


