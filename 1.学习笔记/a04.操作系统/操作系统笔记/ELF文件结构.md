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

`/usr/include/elf.h`中存放了ELF文件头结构及相关常识
```c
typedef struct
{
  unsigned char e_ident[EI_NIDENT];     /* Magic number and other info */
  Elf64_Half    e_type;                 /* Object file type */
  Elf64_Half    e_machine;              /* Architecture */
  Elf64_Word    e_version;              /* Object file version */
  Elf64_Addr    e_entry;                /* Entry point virtual address */
  Elf64_Off     e_phoff;                /* Program header table file offset */
  Elf64_Off     e_shoff;                /* Section header table file offset */
  Elf64_Word    e_flags;                /* Processor-specific flags */
  Elf64_Half    e_ehsize;               /* ELF header size in bytes */
  Elf64_Half    e_phentsize;            /* Program header table entry size */
  Elf64_Half    e_phnum;                /* Program header table entry count */
  Elf64_Half    e_shentsize;            /* Section header table entry size */
  Elf64_Half    e_shnum;                /* Section header table entry count */
  Elf64_Half    e_shstrndx;             /* Section header string table index */
} Elf64_Ehdr;
```
## 段表

## 重定位表
`.rela.text`段，链接器在处理目标文件时，需要对目标文件中的某些部位进行重定位，即代码段和数据段中哪些对绝对地址的引用的位置。比如对`printf`对调用。

## 字符串表
`.strtab`段或`.shstrtab`段，分别是字符串表和段表字符串表

## 符号表
![[符号表.png]]
+ 符号名 st_name
+ 符号值 st_value
+ 符号大小 st_size
+ 符号类型及绑定信息 st_info
	+ 符号绑定信息![[符号绑定信息.png]]
	+ 符号类型
+ 符号所在段 st_shndx