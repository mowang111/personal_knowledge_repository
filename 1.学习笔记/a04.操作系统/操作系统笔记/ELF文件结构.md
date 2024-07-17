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
	+ 为未初始化的全局变量和局部静态变量预留了空间（涉及强符号和弱符号的区别）
+ .rodata 只读数据段
	+ 保存了字符串常量 `%d\n`
+ .comment 注释信息段
	+ 存放编译器版本信息
+ .note.GNU-stack 堆栈提示段
![[ELF常见段.png]]
![[readelf-h.png]]