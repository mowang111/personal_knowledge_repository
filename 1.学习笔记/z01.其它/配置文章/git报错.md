# [Git报错解决：fatal: unable to access 'https://github.com/.......': OpenSSL SSL_read: Connection was reset, errno 10054](https://www.cnblogs.com/lvhuayan/p/14538106.html)

昨天还可以git push代码到远程仓库，今天git push时报了这个错：fatal: unable to access 'https://github.com/.......': OpenSSL SSL_read: Connection was reset, errno 10054

![img](https://img2020.cnblogs.com/blog/1002261/202103/1002261-20210315155144117-985983733.png)

产生原因：一般是这是因为服务器的SSL证书没有经过第三方机构的签署，所以才报错

参考网上解决办法：解除ssl验证后，再次git即可

git config --global http.sslVerify "false"

![img](https://img2020.cnblogs.com/blog/1002261/202103/1002261-20210315155229411-559867266.png)

