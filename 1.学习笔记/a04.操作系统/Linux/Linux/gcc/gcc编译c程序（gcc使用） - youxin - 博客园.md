下好下面一段简单的代码：

```
#include<stdio.h>
int main()
{
   printf("linux! hello world");

}
```

用ide写好代码保存为hello.c

用gcc首先要找到该文件。

 linux改变/显示当前工作目录

     cd（Change Directory）

语法：cd \[-L|-P\] \[dir\]

功能：cd(Change Directory),改变当前工作目录。

常见用法：

1.     cd  
切换至用户主目录，环境变量$HOME保存着当前登录用户的主目录，也可以这样用：cd $HOME      

2.     cd ~  
同上。

3. cd ~username  
上面1、2命令仅能够切换到当前登录用户的主目录中，而  
cd ~username可以切换至当前未登录用户username的主目录，其中username为系统中相应的用户名，但只有root用户可以这样做。

4.     cd ..  
切换至当前工作目录的上一层目录，即当前工作目录的父目录。

5.  cd - cd $OLDPWD 这两个命令的作用是一样的，都是切换至前一个工作目录。  

我在root目录下建立一个labs文件下，在labs下又建立了一个folder2文件夹。root/labs/folder2.操作显示如下：

\[root@jszx ~\]# cd   
\[root@jszx ~\]# cd labs/folder2  
\[root@jszx folder2\]# cd  
\[root@jszx ~\]#

注意上面的意思：root＠jszx显示用户，用户名后面的代表当前目录。~代表根目录，

\[root@jszx ~\]# cd labs/folder2  
\[root@jszx folder2\]# cd ..  
\[root@jszx labs\]#  
cd ..返回上一层目录。也可以写作cd ../

参考：

http://www.233.com/linux/fudao/20090802/092631173.html

编译成目标文件

gcc  -o  hello  hello.c

或 gcc hello.c -o hello  

生成的目标文件名(不是object，而是可执行文件）通过 **\-o** 选项指定的。该选项通常作为命令行中的最后一个参数。如果被省略，输出文件默认为 ‘a.out’。

**注意到**如果当前目录中与可执行文件重名的文件已经存在，它将被覆盖。

选项 **\-Wall** 开启编译器几乎所有常用的警告──**强烈建议你始终使用该选项**。编译器有很多其他的警告选项，但 **\-Wall** 是最常用的。默认情况下GCC 不会产生任何警告信息。当编写 C 或 C++ 程序时编译器警告非常有助于检测程序存在的问题。 **注意如果有用到math.h库等非gcc默认调用的标准库，请使用-lm参数**

本例中，编译器使用了 _\-Wall_ 选项而没产生任何警告，因为示例程序是完全合法的。

选项 ""-g"" 表示在生成的目标文件中带调试信息，调试信息可以在程序异常中止产生core后，帮助分析错误产生的源头，包括产生错误的文件名和行号等非常多有用的信息。

要运行该程序，输入可执行文件的路径如下：

$ ./hello  
Hello, world!

这将可执行文件载入内存，并使 CPU 开始执行其包含的指令。 路径 **./** 指代当前目录（不能省略），因此 **./hello** 载入并执行当前目录下的可执行文件 ‘hello’。

\# gcc -o hello hello.c

\# ./hello  

linux! hello world

开启warning.

如上所述，当用 C 或 C++ 编程时，编译器警告是非常重要的助手。为了说明这一点，下面的例子包含一个微妙的错误：为一个整数值错误地指定了一浮点数控制符‘%f’。

```
#include <stdio.h>

 int main (void)  
{  
    printf ("Two plus two is %f\\n", 4);  
    return 0;  
}


```

一眼看去该错误并不明显，但是它可被编译器捕捉到，只要启用了警告选项 **\-Wall**。

编译上面的程序‘bad.c’，将得到如下的消息：

$ gcc -Wall -o bad bad.c  
main.c: 在函数‘main’中:  
main.c:5: 警告： 格式‘%f’需要类型‘double’，但实参 2 的类型为‘int’


这表明文件 ‘bad.c’第 6 行中的格式字符串用法不正确。GCC 的消息总是具有下面的格式 _文件名:行号:消息_。编译器对错误与警告区别对待，前者将阻止编译，后者表明可能存在的问题但并不阻止程序编译。

本例中，对整数值来说，正确的格式控制符应该是 **%d**。

如果不启用 **\-Wall**，程序表面看起来编译正常，但是会产生不正确的结果：

$ gcc bad.c -o bad  
$ ./bad  
Two plus two is 0.000000

显而易见，开发程序时不检查警告是非常危险的。如果有函数使用不当，将可能导致程序崩溃或产生错误的结果。开启编译器警告选项 **\-Wall** 可捕捉 C 编程时的多数常见错误。

多个源文件生成可执行程序

即使多个源码文件被编译，GCC编译器也会自动进行链接操作。例如：下面的代码保存在名为 hellomain.c 的文件中并调用一个名为 sayhello()的函数：

/\* hellomain.c \*/  
void sayhello(void);  
int main(int argc,char \*argv\[\])  
{  
sayhello();  
return 0;  
}

以下代码保存在名为 sayhello.c 的文件中并定义了 sayhello() 函数：
```c
/\* sayhello.c \*/  
#include <stdio.h>  
void sayhello()  
{  
printf("hello, ubuntu\\n");/\*这里有个小错误，是中文输入法造成的引号使gcc报错\*/  
}
```
下面的命令将两个文件分别编译为对象文件且将其链接为可执行程序 hello，并删除对象文件：

$ gcc \-Wall hellomain.c sayhello.c -o helloubuntu

gcc ./helloubuntu

输出了 hello,ubuntu

包含头文件

在 linux 下开发软件时，完全不使用第三方函数库的情况是比较少见的，通常来讲都需要借助一个或多个函数库的支持才能够完成相应的功能。从程序员的角度看，函数库实际上就是一些头文件（ .h ）和库文件（ .so 或者 .a ）的集合。虽然 Linux 下的大多数函数都默认将头文件放到/usr/include/ 目录下，而库文件则放到 /usr/lib/ 目录下，但并不是所有的情况都是这样。正因如此， GCC 在编译时必须有自己的办法来查找所需要的头文件和库文件。 GCC 采用搜索目录的办法来查找所需要的文件， \-I 选项可以向 GCC 的头文件搜索路径中添加新的目录。例如，如果在/home/justin/include/ 目录下有编译时所需要的头文件，为了让 GCC 能够顺利地找到它们，就可以使用 \-I 选项：

**\# gcc foo.c -I /home/justin/include -o foo**

在root/header下建立了一个文件header.h
```c
#include<stdio.h>  
void sayhello()  
{  
  printf("hello ubuntu\\n");  
}

在root/labs建立了一个c文件headerTest.c：

#include"header.h"  
int main(int argc,char\* argv\[\])  
{  
   sayhello();  
return 0;  
}
```

编译如下：

\[root@jszx labs\]# gcc -I /root/header headerTest.c -o headerTestResult  
在包含自 headerTest.c：1 的文件中:  
/root/header/header.h:5:2: 警告：文件未以空白行结束  
headerTest.c:6:2: 警告：文件未以空白行结束  
\[root@jszx labs\]# ./headerTestResult  
hello ubuntu  
 正确输出了结果。

头文件和源文件会单独存放在不同的目录中。例如，假设存放源文件的子目录名为./src，而包含文件则放在层次的其他目录下，如./inc。当我们在./src 目录下进行编译工作时，如何告诉GCC到哪里找头文件呢？方法如下所示： $ gcc test.c –I../inc -o test \[喝小酒的网摘\]http://blog.const.net.cn/a/17086.htm  
上面的命令告诉GCC包含文件存放在./inc 目录下，在当前目录的上一级。  
如果在编译时需要 的包含文件存 放在多个目录下，可以使用多个-I 来指定各个目录：  
$ gcc test.c –I../inc –I../../inc2 -o test 

这里指出了另一个包含子目录inc2，较之前目录它还要在再上两级才能找到。

\[喝小酒的网摘\]http://blog.const.net.cn/a/17086.htm

 一个困惑我的问题：

```
例如：  
//test.h  
int fun ();

//test.c  
int fun () {   
 //\*\*\*\*  
}

//main.c  
#include <stdio.h>  
#include "test.h"

int main ()  
{  
fun ();  
return 0;  
}  
如果直接这样用gcc -Wall main.c 编译就会显示：undefine reference to "fun"。  
如果在main.c中包含上test.c文件就没问题。但这种事情不会出现在VC之上。  
用什么办法才能只需要包含头文件即可编译呢？


```

```
你这样的命令test.o没有链接进去啊，把test.c加在后面
```

回答

没有，一般的办法是用makefile，把需要编译的参数，文件都包含在里面，在VC里其实也是这样的，不过VC里面自动生成了makefile

上面这个问题：还可以这么做，即使main.c不包含test文件，我们编译的时候gcc -o x main.c test.c这样也行。

参考：

[http://www.cnblogs.com/azraelly/archive/2012/07/07/2580839.html](http://www.cnblogs.com/azraelly/archive/2012/07/07/2580839.html)

[http://blog.renren.com/share/241565115/1819139547](http://blog.renren.com/share/241565115/1819139547)

[http://blog.csdn.net/sustzombie/article/details/5470425](http://blog.csdn.net/sustzombie/article/details/5470425)

http://blog.csdn.net/sustzombie/article/details/5470425

 http://www.jhmcu.com/index.php/on-the-learning-experiences-of-computer-language/  
[http://blog.csdn.net/jk198310/article/details/16982735](http://blog.csdn.net/jk198310/article/details/16982735)