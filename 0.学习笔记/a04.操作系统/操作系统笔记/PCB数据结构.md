struct task_struct { 
long state //任务的运行状态(-1 不可运行,0 可运行(就绪),>0 已停止)。
long counter // 任务运行时间计数(递减)(滴答数),运行时间片。 
long priority // 运行优先数。任务开始运行时 counter=priority, 越大运行越长。
 long signal // 信号。是位图,每个比特位代表一种信号,信号值=位偏移值+1。
 struct sigaction sigaction[32] // 信号执行属性结构,对应信号将要执行的操作和标志信息。
 long blocked // 进程信号屏蔽码(对应信号位图)。
 int exit_code // 任务执行停止的退出码,其父进程会取。
 // 代码段地址。
 unsigned long start_code unsigned long end_code // 代码长度(字节数)。
 unsigned long end_data // 代码长度 + 数据长度(字节数)。
 unsigned long brk // 总长度(字节数)。
 unsigned long start_stack // 堆栈段地址。
 long pid // 进程标识号(进程号)。
 long father // 父进程号。
 long pgrp // 父进程组号。
 long session // 会话号。
 long leader // 会话首领。
 unsigned short uid // 用户标识号(用户 id)。
 unsigned short euid // 有效用户 id。
 unsigned short suid // 保存的用户 id。
 unsigned short gid // 组标识号(组 id)。
 unsigned short egid // 有效组 id。
 unsigned short sgid // 保存的组 id。
 long alarm // 报警定时值(滴答数)。
 long utime // 用户态运行时间(滴答数)。
 long stime // 系统态运行时间(滴答数)。
 long cutime // 子进程用户态运行时间。
 long cstime // 子进程系统态运行时间。
 long start_time // 进程开始运行时刻。
 unsigned short used_math // 标志:是否使用了协处理器。
 int tty // 进程使用 tty 的子设备号。-1 表示没有使用。
 unsigned short umask // 文件创建属性屏蔽位。
 struct m_inode * pwd // 当前工作目录 i 节点结构。
 struct m_inode * root // 根目录 i 节点结构。
 struct m_inode * executable // 执行文件 i 节点结构。
 unsigned long close_on_exec // 执行时关闭文件句柄位图标志。
(参见 include/fcntl.h) struct file * filp[NR_OPEN] // 文件结构指针表,最多 32 项。
表项号即是文件描述符的值。
 struct desc_struct ldt[3] // 任务局部描述符表。
0-空,1-代码段 cs,2-数据和堆栈段 ds&ss。
 struct tss_struct tss // 进程的任务状态段信息结构。 };

其中的 m_inode数据结构如下

struct m_inode { unsigned short i_mode; unsigned short i_uid; unsigned long i_size; unsigned long i_mtime; unsigned char i_gid; unsigned char i_nlinks; unsigned short i_zone[9]; /* these are in memory also */ struct task_struct * i_wait; unsigned long i_atime; unsigned long i_ctime; unsigned short i_dev; unsigned short i_num; unsigned short i_count; unsigned char i_lock; unsigned char i_dirt; unsigned char i_pipe; unsigned char i_mount; unsigned char i_seek; unsigned char i_update; };

```c
struct task_struct {
/* these are hardcoded - don't touch */
	long state;	/* -1 unrunnable, 0 runnable, >0 stopped */
	long counter;
	long priority;
	long signal;
	struct sigaction sigaction[32];
	long blocked;	/* bitmap of masked signals */
/* various fields */
	int exit_code;
	unsigned long start_code,end_code,end_data,brk,start_stack;
	long pid,father,pgrp,session,leader;
	unsigned short uid,euid,suid;
	unsigned short gid,egid,sgid;
	long alarm;
	long utime,stime,cutime,cstime,start_time;
	unsigned short used_math;
/* file system info */
	int tty;		/* -1 if no tty, so it must be signed */
	unsigned short umask;
	struct m_inode * pwd;
	struct m_inode * root;
	struct m_inode * executable;
	unsigned long close_on_exec;
	struct file * filp[NR_OPEN];
/* ldt for this task 0 - zero 1 - cs 2 - ds&ss */
	struct desc_struct ldt[3];
/* tss for this task */
	struct tss_struct tss;
};
```

