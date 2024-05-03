---
title: 子网掩码&wireshark小实验
date: {{ date }}
top: false
cover: false
password:
toc: true
mathjax: true
summary:
tags: [计算机网络, wireshark] 
categories: []

---

# 子网掩码&wireshark小实验

## 实验环境搭建

主机是win11，虚拟机ubuntu（使用桥接模式）

参考https://www.cnblogs.com/heruiguo/p/11132887.html安装回环适配器，将虚拟机桥接到这个适配器

虚拟机的ip地址设置为192.168.1.100，子网掩码配置成255.255.255.0，主机回环适配器的ip地址设置为192.168.1.137，子网掩码配置成255.255.255.224

![image-20230812165521573](C:\Users\11547\AppData\Roaming\Typora\typora-user-images\image-20230812165521573.png)

备注：Ubuntu22配置ip

```bash
sudo vim /etc/netplan/01-network-manager-all.yaml
sudo netplan apply
```

```bash
# Let NetworkManager manage all devices on this system
# network:
  #version: 2
  # renderer: NetworkManager
  #
network:
  ethernets:
    enp0s3:
      dhcp4: no
      dhcp6: no
      addresses:
        - 192.168.1.100/24
      routes:
        - to: default
          via: 192.168.1.137
      nameservers:
        addresses:
          - 114.114.114.114
  version: 2
  renderer: networkd
```



## 实验

主机ping虚拟机

![image-20230812165611865](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20230812165611865.png)

虚拟机ping主机

