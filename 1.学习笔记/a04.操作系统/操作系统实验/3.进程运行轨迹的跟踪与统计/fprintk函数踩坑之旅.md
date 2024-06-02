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
	if (!(file=task[0]->filp[fd]))    /* 从进程0的文件描述符表中得到文件句柄 */
        return 0;
	inode = file->f_inode;
	count = file_write(inode,file,logbuf,count);
	return count;
}
```
这下总行了吧？
## 坑3:

