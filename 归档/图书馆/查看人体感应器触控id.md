## 登录一体机

默认的地址是192.168.0.15

不是该地址，需要登陆路由器查看主机ip

通过mobaXterm输入命令登陆一体机

```
telnet 192.168.0.15
用户名：root
```

![image-20220601104806773](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20220601104806773.png)

## 运行smartlib程序

```
systemctl stop smartlib #关闭后台运行的smartlib程序
cd /opt/smartlib #进入smartlib目录
./smartlib #临时运行smartlib程序
systemctl start smartlib #打开后台运行的smartlib程序
```

![image-20220601104945950](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20220601104945950.png)

触控id:50

关闭smartlib程序：Ctrl + C