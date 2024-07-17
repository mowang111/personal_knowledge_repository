示例代码
```c
int printf(const char *format, ...);

int global_init_var = 84;
int global_uninit_var;

void func1(int i){
    printf("%d\n", i);
}

int main(void){
    static int static_var = 85;
    static int static_var2;
    int a = 1;
    int b;

    func1(static_var + static_var2 + a + b);

    return a;
}
```


![[objdump-h.png]]
+ .text 代码段
+ .data 数据段
	+ 保存了初始化了的全局静态变量和局部静态变量
	+ global_init_var，static_var
+ bss段
	+ 
+ .rodata 只读数据段
	+ 保存了字符串常量 `%d\n`
+ 注释信息段
+ 堆栈提示段