python多线程端口扫描器。

输出示例：

![python多线程端口扫描器 输出示例](https://raw.githubusercontent.com/mowang111/image-hosting/master/others/python多线程端口扫描器 输出示例.1ug02otwbf40.png)

Github
------

此端口扫描器的源码，文档及详细调用方法见[Github PythonPortScanner by Yaokai](https://github.com/YaokaiYang-assaultmaster/Python-Port-Scanner-Module)。

* * *

背景
--

有时候，在进行网络相关的研究的时候，我们需要执行一些有目的的参数测量。而端口扫描就是其中比较普遍也比较重要的一项。所谓的端口扫描，就是指通过TCP握手或者别的方式来判别一个给定主机上的某些端口是否处理开放，或者说监听的状态。现有的使用比较广泛的端口扫描工具是nmap。毋庸置疑，nmap是一款非常强大且易于使用的软件。但nmap是一款运行于terminal中的软件，有时在别的代码中调用并不是很方便，甚至没有相应的库。另外，nmap依赖的其他库较多，在较老的系统中可能无法使用较新的nmap，这样会造成扫描的不便。另外，nmap在扫描时需要root权限。基于这个原因，我用python2.7自带的库开发了一款高效的多线程端口扫描器来满足使用需要。

具体实现
----

### I. 利用TCP握手连接扫描一个给定的`(ip,port)`地址对

为了实现端口扫描，我们首先明白如何使用`python socket`与给定的`(ip, port)`进行TCP握手。为了完成TCP握手，我们需要先初始化一个TCP socket。在`python`中新建一个TCP socket的代码如下：

```python
TCP_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM) #(1)
TCP_sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEPORT, 1) #(2)
TCP_sock.settimeout(delay) #(3)
```

其中`(1)`是初始化socket的代码，`socket.AF_INTE`参数表示`IPv4 socket`，`socket.SOCK_STREAM`参数表示`TCP socket`。<font color='red'>这样我们就初始化了一个使用`IPv4，TCP`协议的socket。</font> `(2)`使用了`socket.setsockopt()`来设置socket的另一些参数。`socket.SOL_SOCKET`指定当前socket将使用`setsockopt()`中后面的参数。`socket.SO_REUSEPORT`表明当前socket使用了可复用端口的设置。`socket.SO_REUSEPORT`具体含义可以参考[我的另一篇文章](http://blog.csdn.net/yaokai_assultmaster/article/details/68951150)。 `(3)`将socket的连接超时时间设置为`delay`变量所对应的时间（以秒为单位）。这么做是为了防止我们在一个连接上等待太久。 了解了如何新建一个socket，我们就可以开始对给定的`(ip,port)`对进行TCP连接。代码如下：

```python
try:
    result = TCP_sock.connect_ex((ip, int(port_number)))

    # If the TCP handshake is successful, the port is OPEN. Otherwise it is CLOSE
    if result == 0:
        output[port_number] = 'OPEN'
    else:
        output[port_number] = 'CLOSE'

        TCP_sock.close()

except socket.error as e:
    output[port_number] = 'CLOSE'
    pass
```

因为这是一个I/O操作，为了处理可能出现的异常，我们需要在`try,except`块处理这部分操作。其次，我们根据`socket.connect_ex()`方法连接目标地址，通过该方法返回的状态代码来判断连接是否成功。该方法返回`0`代表连接成功。所以当返回值为`0`的时候将当前端口记录为打开状态。反之记录为关闭。另外，当连接操作出现异常的时候，我们也将端口记录为关闭状态，因为其并不能被成功连接（可能因为防火墙或者数据包被过滤等原因）。 需要注意的是，在连接完成后我们一定要调用`socket.close()`方法来关闭与远程端口之间的TCP连接。否则的话我们的扫描操作可能会引起所谓的TCP连接悬挂问题（Hanging TCP connection）。

总结起来，TCP握手扫描的整体代码如下：

```python
"""
Perform status checking for a given port on a given ip address using TCP handshake

Keyword arguments:
ip -- the ip address that is being scanned
port_number -- the port that is going to be checked
delay -- the time in seconds that a TCP socket waits until timeout
output -- a dict() that stores result pairs in {port, status} style (status = 'OPEN' or 'CLOSE')
"""
def __TCP_connect(ip, port_number, delay, output):
    # Initilize the TCP socket object
    TCP_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    TCP_sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEPORT, 1)
    TCP_sock.settimeout(delay)

    try:
        result = TCP_sock.connect_ex((ip, int(port_number)))

        # If the TCP handshake is successful, the port is OPEN. Otherwise it is CLOSE
        if result == 0:
            output[port_number] = 'OPEN'
        else:
            output[port_number] = 'CLOSE'

        TCP_sock.close()

    except socket.error as e:

        output[port_number] = 'CLOSE'
        pass
```

### II. 多线程扫描端口

单线程扫描虽然逻辑简单，但无疑是及其低效的。因为在扫描过程中要进行大量的数据包的发送和接受，所以这是一个I/O密集型的操作。如果只是用单线程进行扫描的话，程序会在等待回复的过程中浪费大量的时间。因此多线程的操作是很有必要的。这里，一个很自然的思路就是为每一个端口单独开一个线程进行扫描。 在这里我们将需要扫描的端口列表定为从Nmap中得到的前1000个使用频率最高的端口：

```python
__port_list = [1,3,6,9,13,17,19,20,21,22,23,24,25,30,32,37,42,49,53,70,79,80,81,82,83,84,88,89,99,106,109,110,113,119,125,135,139,143,146,161,163,179,199,211,222,254,255,259,264,280,301,306,311,340,366,389,406,416,425,427,443,444,458,464,481,497,500,512,513,514,524,541,543,544,548,554,563,...]
```

完整的端口表见[top 1K commonly used ports](https://github.com/YaokaiYang-assaultmaster/PythonPortScanner/blob/master/PortScanner/portlists/top1KPorts) 对于一个给定的ip地址，扫描的过程是这样的： 1. 取出一个端口 2. 新建一条线程，利用`__TCP_connect()`函数对该`(ip,port)`进行连接操作。 3. 调用`thread.start()`和`thread.join()`方法，使扫描的子线程开始工作并且命令主线程等待子线程死亡后再结束。 4. 重复这个过程直到所有的端口都被扫描过。 根据以上思路，多线程扫描的代码如下：

```python
"""
Open multiple threads to perform port scanning

Keyword arguments:
ip -- the ip address that is being scanned
delay -- the time in seconds that a TCP socket waits until timeout
output -- a dict() that stores result pairs in {port, status} style (status = 'OPEN' or 'CLOSE')
"""
def __scan_ports_helper(ip, delay, output):

    '''
    Multithreading port scanning
    '''

    port_index = 0

    while port_index < len(__port_list):

        # Ensure that the number of cocurrently running threads does not exceed the thread limit
        while threading.activeCount() < __thread_limit and port_index < len(__port_list):

            # Start threads
            thread = threading.Thread(target = __TCP_connect, args = (ip, __port_list[port_index], delay, output))
            thread.start()
            # lock the thread until all threads complete
            thread.join()
            port_index = port_index + 1
```

其中\_\_thread\_limit参数是用来限制线程数目的。output是一个字典，以`(port: status)`的形式保存了扫描的结果。 `thread.join()`保证了主线程只有在所有子线程都结束之后才会继续执行，从而确保了我们一定会扫描全部的端口。

### III. 多线程扫描多个网站

在多线程扫描端口的同时，如果我们能够多线程扫描多个网站，那么扫描的效率还将进一步提高。为了达到这个目的，我们需要另一个线程去管理一个网站对应的对其端口进行扫描的所有子线程。 除此之外，在这种情况下，**我们必须删去`__scan_ports_helper()`中的`thread.join()`。否则主线程就会被端口扫描子线程阻塞，我们也就无法多线程扫描多个网站了。**  在不使用`join()`的情况下，我们如何确保一个网站的扫描线程只有在完成对其全部端口的扫描之后才会返回呢？这里我使用的方法是检测`output`字典的长度。因为在全部扫描完成后，`output`的长度一定与`__port_list`的长度一致。 改变后的代码如下：

```python
def __scan_ports_helper(ip, delay, output):

    '''
    Multithreading port scanning
    '''

    port_index = 0

    while port_index < len(__port_list):

        # Ensure that the number of cocurrently running threads does not exceed the thread limit
        while threading.activeCount() < __thread_limit and port_index < len(__port_list):

            # Start threads
            thread = threading.Thread(target = __TCP_connect, args = (ip, __port_list[port_index], delay, output))
            thread.start()
            port_index = port_index + 1

    while (len(output) < len(self.target_ports)):
        continue
```

根据以上扫描线程的代码，端口扫描的管理线程的代码如下所示：

```python
"""
Controller of the __scan_ports_helper() function

Keyword arguments:
ip -- the ip address that is being scanned
delay -- the time in seconds that a TCP socket waits until timeout
"""        

def __scan_ports(websites, output_ip, delay):

    scan_result = {}

    for website in websites:
        website = str(website)
        scan_result[website] = {}

        thread = threading.Thread(target = __scan_ports_helper, args = (ip, delay, scan_result[website]))
        thread.start()
        # lock the script until all threads complete
        thread.join()

    return scan_result
```

至此，我们就完成了一个多线程端口扫描器的全部代码。

### IV. 总结！利用这些代码扫描给定网站并输出结果

处于输出方便的考虑，我并没有使用多线程扫描多个网站，同时对每个网站多线程扫描多个端口的方法。在这个例子中只进行了多线程扫描端口，但同时只扫描一个网站的操作。整合起来的代码如下：

```python
import sys
import subprocess
import socket
import threading
import time

class PortScanner:

    # default ports to be scanned
    # or put any ports you want to scan here!
    __port_list = [1,3,6,9,13,17,19,20,21,22,23,24,25,30,32,37,42,49,53,70,79,80,81,82,83,84,88,89,99,106,109,110,113,119,125,135,139,143,146,161,163,179,199,211,222,254,255,259,264,280,301,306,311,340,366,389,406,416,425,427,443,444,458,464,481,497,500,512,513,514,524,541,543,544,548,554,563]
    # default thread number limit
    __thread_limit = 1000
    # default connection timeout time inseconds
    __delay = 10


    """
    Constructor of a PortScanner object

    Keyword arguments:
    target_ports -- the list of ports that is going to be scanned (default self.__port_list)
    """
    def __init__(self, target_ports = None):
        # If target ports not given in the arguments, use default ports
        # If target ports is given in the arguments, use given port lists
        if target_ports is None:
            self.target_ports = self.__port_list
        else:
            self.target_ports = target_ports


    """
    Return the usage information for invalid input host name. 
    """
    def __usage(self):
        print('python Port Scanner v0.1')
        print('please make sure the input host name is in the form of "something.com" or "http://something.com!"\n')


    """
    This is the function need to be called to perform port scanning

    Keyword arguments:
    host_name -- the hostname that is going to be scanned
    message -- the message that is going to be included in the scanning packets, in order to prevent
        ethical problem (default: '')
    """
    def scan(self, host_name, message = ''):

        if 'http://' in host_name or 'https://' in host_name:
            host_name = host_name[host_name.find('://') + 3 : ]

        print('*' * 60 + '\n')
        print('start scanning website: ' + str(host_name))

        try:
            server_ip = socket.gethostbyname(str(host_name))
            print('server ip is: ' + str(server_ip))

        except socket.error as e:
            # If the DNS resolution of a website cannot be finished, abort that website.

            #print(e)
            print('hostname %s unknown!!!' % host_name)

            self.__usage()

            return {}

            # May need to return specificed values to the DB in the future

        start_time = time.time()
        output = self.__scan_ports(server_ip, self.__delay, message)
        stop_time = time.time()

        print('host %s scanned in  %f seconds' %(host_name, stop_time - start_time))

        print('finish scanning!\n')

        return output


    """
    Set the maximum number of thread for port scanning

    Keyword argument:
    num -- the maximum number of thread running concurrently (default 1000)
    """
    def set_thread_limit(self, num):
        num = int(num)

        if num <= 0 or num > 50000:

            print('Warning: Invalid thread number limit! Please make sure the thread limit is within the range of (1, 50,000)!')
            print('The scanning process will use default thread limit!')

            return

        self.__thread_limit = num


    """
    Set the time out delay for port scanning in seconds

    Keyword argument:
    delay -- the time in seconds that a TCP socket waits until timeout (default 10)
    """
    def set_delay(self, delay):

        delay = int(delay)
        if delay <= 0 or delay > 100:

            print('Warning: Invalid delay value! Please make sure the input delay is within the range of (1, 100)')
            print('The scanning process will use the default delay time')

            return 

        self.__delay = delay


    """
    Print out the list of ports being scanned
    """
    def show_target_ports(self):
        print ('Current port list is:')
        print (self.target_ports)


    """
    Print out the delay in seconds that a TCP socket waits until timeout
    """
    def show_delay(self):
        print ('Current timeout delay is :%d' %(int(self.__delay)))


    """
    Open multiple threads to perform port scanning

    Keyword arguments:
    ip -- the ip address that is being scanned
    delay -- the time in seconds that a TCP socket waits until timeout
    output -- a dict() that stores result pairs in {port, status} style (status = 'OPEN' or 'CLOSE')
    message -- the message that is going to be included in the scanning packets, in order to prevent
        ethical problem (default: '')
    """
    def __scan_ports_helper(self, ip, delay, output, message):

        '''
        Multithreading port scanning
        '''

        port_index = 0

        while port_index < len(self.target_ports):

            # Ensure that the number of cocurrently running threads does not exceed the thread limit
            while threading.activeCount() < self.__thread_limit and port_index < len(self.target_ports):

                # Start threads
                thread = threading.Thread(target = self.__TCP_connect, args = (ip, self.target_ports[port_index], delay, output, message))
                thread.start()
                port_index = port_index + 1


    """
    Controller of the __scan_ports_helper() function

    Keyword arguments:
    ip -- the ip address that is being scanned
    delay -- the time in seconds that a TCP socket waits until timeout
    message -- the message that is going to be included in the scanning packets, in order to prevent
        ethical problem (default: '')
    """        
    def __scan_ports(self, ip, delay, message):

        output = {}

        thread = threading.Thread(target = self.__scan_ports_helper, args = (ip, delay, output, message))
        thread.start()

        # Wait until all port scanning threads finished
        while (len(output) < len(self.target_ports)):
            continue

        # Print openning ports from small to large
        for port in self.target_ports:
            if output[port] == 'OPEN':
                print(str(port) + ': ' + output[port] + '\n')

        return output



    """
    Perform status checking for a given port on a given ip address using TCP handshake

    Keyword arguments:
    ip -- the ip address that is being scanned
    port_number -- the port that is going to be checked
    delay -- the time in seconds that a TCP socket waits until timeout
    output -- a dict() that stores result pairs in {port, status} style (status = 'OPEN' or 'CLOSE')
    message -- the message that is going to be included in the scanning packets, in order to prevent
        ethical problem (default: '')
    """
    def __TCP_connect(self, ip, port_number, delay, output, message):
        # Initilize the TCP socket object
        TCP_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        TCP_sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEPORT, 1)
        TCP_sock.settimeout(delay)


        # Initilize a UDP socket to send scanning alert message if there exists an non-empty message
        if message != '':
            UDP_sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
            UDP_sock.sendto(str(message), (ip, int(port_number)))

        try:
            result = TCP_sock.connect_ex((ip, int(port_number)))
            if message != '':
                TCP_sock.sendall(str(message))

            # If the TCP handshake is successful, the port is OPEN. Otherwise it is CLOSE
            if result == 0:
                output[port_number] = 'OPEN'
            else:
                output[port_number] = 'CLOSE'

            TCP_sock.close()

        except socket.error as e:

            output[port_number] = 'CLOSE'
            pass
```