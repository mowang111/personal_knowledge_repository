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
当我`do_exit`函数中调用`fprintk`时，死活打印不出来，后来调试发现进程调用`do_exit`前已经把log相关的fd关闭了，没辙，换成下面的写法，直接用0号进程的
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
	count = 
	return count;
}
```
