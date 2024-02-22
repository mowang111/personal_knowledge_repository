linux秉持一切皆文件的理念，两个主机建立socket连接时，可以把socket也看作一个文件，发送数据就往这个文件中写入数据，相对应地，接收数据就是从这个文件中读数据。

文件描述符（file descriptor）是操作系统内核为了高效管理已被打开的文件所创建的索引，用于指代被打开的文件

在Linux中，每个进行都有一个文件描述符表，比如一个bash进程，这个文件描述符表是一个指针数组，系统默认初始化了数组的前3位，0指向标准的输入流（一般指键盘），1指向标准的输出流（一般指显示器），2指向标准的错误流（一般也指显示器）。

# Linux实验
1、查看当前bash的文件描述符

```bash
ls -l /proc/$$/fd
复制代码
```

![image.png](https://p3-juejin.byteimg.com/tos-cn-i-k3u1fbpfcp/7bc285103b2944a080259a42630c445f~tplv-k3u1fbpfcp-zoom-in-crop-mark:4536:0:0:0.image) 命令中的 `$$` 表示当前bash的进程id号 可以看到当前进程中有0,1,2三个文件描述符，代表标准输入、标准输出、错误输出的入口，这里的255是bash独有的，可以不用管
  
2、在linux中与`www.baidu.com`建立socket连接
```bash
exec 6<>/dev/tcp/www.baidu.com/80
复制代码
```

-   6是文件描述符，数字任意，不能与存在的数字重复（0,1,2,255）
-   <> 是重定向，< 表示是输入流，> 表示输出流，意思是`/dev/tcp/www.baidu.com/80`这个文件的文件描述符重定向到6（或者是这个文件的输入输出流执行文件描述符6），根据文件描述符6可以得到这个文件的输入输出流


3、查看socket连接

```bash
ls -l /proc/$$/fd   
复制代码
```
这里还是查看进程中的文件描述符，因为socket也是一个文件 ![image.png](https://p3-juejin.byteimg.com/tos-cn-i-k3u1fbpfcp/4558b681f38140c4a7a25c912ac48f87~tplv-k3u1fbpfcp-zoom-in-crop-mark:4536:0:0:0.image) 可以看到文件描述符6指向了一个socket，说明与百度的socket建立成功
  

4、往socket中发请求头，获取百度首页html
```bash
echo -e 'GET / HTTP/1.0\n'  1>& 6
复制代码
```

-   echo 是在控制台输出的命令，-e 表示字符串中的 \n 自动转为换行
-   `1> 6` 是控制台的输出重定向到文件描述符6，就是往百度发数据
-   `1>& 6`因为 > 的后面跟的是文件描述符，所以 > 后要加 &

5、查看返回的数据

```bash
cat 0<& 6
复制代码
```

-   cat是查看文件内容的命令
-   `cat 0<& 6` 表示文件描述符 6 的内容（socket 读缓冲区中的内容）输入到 cat 的标准输入中，这样就能查看到百度发过来的内容了

![image.png](https://p3-juejin.byteimg.com/tos-cn-i-k3u1fbpfcp/50ad98870cdc4566bc1a06280d2048b6~tplv-k3u1fbpfcp-zoom-in-crop-mark:4536:0:0:0.image) 但是并没有返回数据，因为我们操作的时间太长了，socket连接上却并没有发送任何数据，服务器那么超时断开了连接，所以我们只要把上面的步骤操作快点，就可以获取内容了 ![image.png](https://p3-juejin.byteimg.com/tos-cn-i-k3u1fbpfcp/c21d50c95f374592a919aeec9a52027f~tplv-k3u1fbpfcp-zoom-in-crop-mark:4536:0:0:0.image) 这样就得到百度的数据了