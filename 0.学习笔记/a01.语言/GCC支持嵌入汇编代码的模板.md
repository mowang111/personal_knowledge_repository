不同于其它 C 编译器支持嵌入汇编代码的方式，为了优化用户代码，GCC 设计了一种特有的嵌入方式，它规定了汇编代码嵌入的形式和嵌入汇编代码需要由哪几个部分组成，如下面代码所示。
```c
__asm__ __volatile__(代码部分:输出部分列表: 输入部分列表:损坏部分列表);
```
可以看到代码模板从 __asm__ 开始（当然也可以是 asm），紧跟着 __volatile__，然后是跟着一对括号，最后以分号结束。括号里大致分为 4 个部分：
1. 汇编代码部分，这里是实际嵌入的汇编代码。

2. 输出列表部分，让 GCC 能够处理 C 语言左值表达式与汇编代码的结合。

3. 输入列表部分，也是让 GCC 能够处理 C 语言表达式、变量、常量，让它们能够输入到汇编代码中去。

4. 损坏列表部分，告诉 GCC 汇编代码中用到了哪些寄存器，以便 GCC 在汇编代码运行前，生成保存它们的代码，并且在生成的汇编代码运行后，恢复它们（寄存器）的代码。

它们之间用冒号隔开，如果只有汇编代码部分，后面的冒号可以省略。但是有输入列表部分而没有输出列表部分的时候，输出列表部分的冒号就必须要写，否则 GCC 没办法判断，同样的道理对于其它部分也一样。
详情可参阅[GCC 手册](https://www.gnu.org/manual/manual.html)。你可以重点看 GAS 相关的章节。