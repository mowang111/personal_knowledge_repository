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
仔细看下来，发现本质是一样的啊，只不过他是用汇编实现的`file`

