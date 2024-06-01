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
看上去很有道理，

