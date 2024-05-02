---
title: mysql一行记录是如何存储的？
date: {{ date }}
top: false
cover: false
password:
toc: true
mathjax: true
summary:
tags:
- mysql
- 数据库
categories: []
---

本文引用自[小林MySQL 一行记录是怎么存储的？](https://xiaolincoding.com/mysql/base/row_format.html#%E6%80%BB%E7%BB%93）

# MySql一行记录是如何存储的？

mysql数据库文件的存放在那个目录？

```sql
mysql> SHOW VARIABLES LIKE 'datadir';
+---------------+-----------------+
| Variable_name | Value           |
+---------------+-----------------+
| datadir       | /var/lib/mysql/ |
+---------------+-----------------+
1 row in set (0.00 sec)
```

我们每创建一个 database（数据库） 都会在 /var/lib/mysql/ 目录里面创建一个以 database 为名的目录，然后保存表结构和表数据的文件都会存放在这个目录里。

假设这里有一个名为 my_test 的 database，该 database 里有一张名为 t_order 数据库表。

进入 /var/lib/mysql/my_test 目录，看看里面有什么文件

```shell
[root@xiaolin ~]#ls /var/lib/mysql/my_test
db.opt  
t_order.frm  
t_order.ibd
```

+ db.opt，用来存储当前数据库的默认字符集和字符校验规则
+ t_order.frm，t_order的**表结构**会保存在这个文件。在 MySQL 中建立一张表都会生成一个.frm 文件，该文件是用来保存每个表的元数据信息的，主要包含表结构定义。
+ t_order.ibd，t_order的**表数据**会保存在这个文件。表数据既可以存在共享表空间文件（文件名：ibdata1）里，也可以存放在独占表空间文件（文件名：表名字.ibd）。这个行为是由参数 innodb_file_per_table 控制的，若设置了参数 innodb_file_per_table 为 1，则会将存储的数据、索引等信息单独存储在一个独占表空间，从 MySQL 5.6.6 版本开始，它的默认值就是 1 了，因此从这个版本之后， MySQL 中每一张表的数据都存放在一个独立的 .ibd 文件。

## 表空间的文件结构是怎样的？

表空间由段（segment）、区（extent）、页（page）、行（row）组成。

![img](https://cdn.xiaolincoding.com/gh/xiaolincoder/mysql/row_format/表空间结构.drawio.png)

+ 行（row）
  + 数据库表中的记录都是按行（row）进行存放的，每行记录根据不同的行格式，有不同的存储结构。
+ 页（page）
  + 记录时按照行来存储的，但是数据库的读取并不以【行】为单位，否则一次读取（也就是一次IO操作）只能处理一行数据，效率低
  + InnoDB的数据时按照【页】为单位来读写的
  + 默认每个页的大小为16KB，也就是最多能保证16KB的连续存储空间。
  + 页的类型有很多，常见的有数据页、undo日志页、溢出页等等。数据表中的行记录使用【数据页】来管理的。
+ 区（extent）
  + InnoDB存储引擎使用B+树来组织数据的，B+树种每一层都是通过双向链表连接起来的，如果是以页为单位来分配存储空间，那么链表种相邻的两个页之间的物理位置并不是连续的，可能离的非常远，那么磁盘查询时就会有大量的随机I/O，随机I/O是非常慢的。
  + 在表种数据量大的时候，为某个索引分配空间的时候就不再按照页为单位分配了，而是按照区（extent）为单位进行分配。每个区的大小为1MB，对于16KB的页来说，连续64页会被划为一个区，这样就使得链表种相邻的页的物理位置也相邻，就能用顺序I/O了。
+ 段（segment）
  + 表空间是由各个段（segment）组成的，段是由多个区（extent）组成的。段一般分为数据段、索引段和回滚段等
    + 索引段：存放B+树的非叶子节点的区的集合；
    + 数据段：存放B+树的叶子节点的区的集合
    + 回滚段：存放的是回滚数据的区的集合，事务隔离种，有提到MVCC利用回滚段实现了多版本查询数据。



## InnoDB行格式有哪些？

行格式（row_format），就是一条记录的存储结构

InnoDB提供了4种行格式，分别是Redundant、Compact、Dynamic和Compressed行格式

- Redundant 是很古老的行格式了， MySQL 5.0 版本之前用的行格式，现在基本没人用了。
- 由于 Redundant 不是一种紧凑的行格式，所以 MySQL 5.0 之后引入了 Compact 行记录存储方式，Compact 是一种紧凑的行格式，设计的初衷就是为了让一个数据页中可以存放更多的行记录，从 MySQL 5.1 版本之后，行格式默认设置成 Compact。
- Dynamic 和 Compressed 两个都是紧凑的行格式，它们的行格式都和 Compact 差不多，因为都是基于 Compact 改进一点东西。从 MySQL5.7 版本之后，默认使用 Dynamic 行格式。

重点介绍Compact行格式

### COMPACT行格式

![image-20230325211542129](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20230325211542129.png)

一条完整的记录分为「记录的额外信息」和「记录的真实数据」两个部分。

#### 记录的额外信息

记录的额外信息包括3个部分：变长字段长度列表、NULL值列表、记录头信息

1. 变长字段长度列表

   varchar(n)和char(n)的区别就是varchar是变长的，char是定长的，变长字段实际存储的数据长度是不固定的

   所以，在存储数据的时候，也要把数据占用的大小存起来，存到【变长字段长度列表】里，读取数据的时候才能根据这个【变长字段长度列表】去读取对应的长度。其他TEXT、BLOB等变长字段也是这样实现的。

   ```sql
   create table `t_user`(
   	`id` int(11) not null,
       `name` varchar(20) default null,
       `phone` varchar(20) default null,
       `age` int(11) default null,
       primary key(`id`) using btree
   ) engine = InnoDB default character set = ascii row_format = compact;
   ```

   ![img](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/t_test.png)

   + 第一条记录

     + name列的值为a, 真实数据占用的字节数是1字节，十六进制0x01;
     + phone列的值为123，真实占用的字节数是3字节，十六进制0x03;
     + age 列和 id 列不是变长字段，所以这里不用管。

     这些变长字段的真实数据占用的字节数会按照列的顺序**逆序存放**（等下会说为什么要这么设计），所以「变长字段长度列表」里的内容是「 03 01」，而不是 「01 03」。

     ![image-20230325212823590](C:\Users\11547\AppData\Roaming\Typora\typora-user-images\image-20230325212823590.png)

   + 同样的道理，我们也可以得出**第二条记录**的行格式中，「变长字段长度列表」里的内容是「 04 02」，如下图：

     ![image-20230325212912410](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20230325212912410.png)

   + **第三条记录**中 phone 列的值是 NULL，**NULL 是不会存放在行格式中记录的真实数据部分里的**，所以「变长字段长度列表」里不需要保存值为 NULL 的变长字段的长度。

     ![img](https://cdn.xiaolincoding.com/gh/xiaolincoder/mysql/row_format/变长字段长度列表3.png)

   > 为什么【变长字段长度列表】的信息要按照逆序存放？
   >
   > 这个设计是有想法的，主要是因为「记录头信息」中指向下一个记录的指针，指向的是下一条记录的「记录头信息」和「真实数据」之间的位置，这样的好处是向左读就是记录头信息，向右读就是真实数据，比较方便。
   >
   > 「变长字段长度列表」中的信息之所以要逆序存放，是因为这样可以**使得位置靠前的记录的真实数据和数据对应的字段长度信息可以同时在一个 CPU Cache Line 中，这样就可以提高 CPU Cache 的命中率**。
   >
   > 同样的道理， NULL 值列表的信息也需要逆序存放。

   > 变长字段字节数列表不是必须的
   >
   > 当数据表没有变长字段的时候，比如全部都是int类型的字段，这时候表里的行格式就不会有【变长字段长度列表】了

2. NULL值列表

   表中的某些列可能会存储 NULL 值，如果把这些 NULL 值都放到记录的真实数据中会比较浪费空间，所以 Compact 行格式把这些值为 NULL 的列存储到 NULL值列表中。

   如果存在允许 NULL 值的列，则每个列对应一个二进制位（bit），二进制位按照列的顺序逆序排列。

   + 二进制位的值为1时，代表该列的值为NULL。
   + 二进制位的值为0时，代表该列的值不为NULL。

   另外，NULL 值列表必须用整数个字节的位表示（1字节8位），如果使用的二进制位个数不足整数个字节，则在字节的高位补 `0`。

3. 记录头信息

   记录头信息包含的内容较多，这里列举几个比较重要的：

   + delete_mask ：标识此条数据是否被删除。从这里可以知道，我们执行 detele 删除记录的时候，并不会真正的删除记录，只是将这个记录的 delete_mask 标记为 1。
   + next_record：下一条记录的位置。从这里可以知道，记录与记录之间是通过链表组织的。在前面我也提到了，指向的是下一条记录的「记录头信息」和「真实数据」之间的位置，这样的好处是向左读就是记录头信息，向右读就是真实数据，比较方便。
   + recore_type: 表示当前记录的类型，0表示普通记录，1表示B+树非叶子节点记录，2表示最小记录，3表示最大记录

#### 记录的真实数据

记录真实数据部分除了我们自己定义的字段，还有三个隐藏字段，分别是：row_id、trx_id、roll_pointer

![image-20230325220045192](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20230325220045192.png)

+ row_id

  如果我们建表的时候指定了主键或者唯一约束列，那么就没有row_id隐藏字段了。如果既没有指定主键，又没有唯一约束，那么InnoDB就会为记录添加row_id隐藏字段。row_id不是必需的，占用6个字节。

+ trx_id

  事务id，表示这个数据是由哪个事务生成的。trx_id是必需的，占用6个字节。

+ roll_pointer

  这条记录上一个版本的指针。roll_pointer是必需的，占用7个字节。



### varchar(n)中n最大取值是多少？

**MySQL规定除了TEXT、BLOBs这种大对象类型之外，其他所有的列（不包括隐藏列和记录头信息）占用的字节长度加起来不能超过65535个字节。**

也就是说，一行记录除了TEXT、BLOBs类型的列，限制最大为65535字节

varchar(n) 字段类型的 n 代表的是最多存储的字符数量，并不是字节大小哦。

要算 varchar(n) 最大能允许存储的字节数，还要看数据库表的字符集，因为字符集代表着，1个字符要占用多少字节，比如 ascii 字符集， 1 个字符占用 1 字节，那么 varchar(100) 意味着最大能允许存储 100 字节的数据。

#### 单字段情况

```sql
CREATE TABLE test ( 
`name` VARCHAR(65535)  NULL
) ENGINE = InnoDB DEFAULT CHARACTER SET = ascii ROW_FORMAT = COMPACT;
```

![image-20230325220811376](C:\Users\11547\AppData\Roaming\Typora\typora-user-images\image-20230325220811376.png)

**一行数据的最大字节数是65535（不包含TEXT、BLOBs这种大对象类型）,其中包含了storage overhead;**

这个 storage overhead 是什么呢？其实就是「变长字段长度列表」和 「NULL 值列表」，也就是说**一行数据的最大字节数 65535，其实是包含「变长字段长度列表」和 「NULL 值列表」所占用的字节数的**。所以， 我们在算 varchar(n) 中 n 最大值时，需要减去 storage overhead 占用的字节数。

这是因为我们存储字段类型为 varchar(n) 的数据时，其实分成了三个部分来存储：

+ 真实数据
+ 真实数据占用的字节数
+ NULL 标识，如果不允许为NULL，这部分不需要

「变长字段长度列表」所占用的字节数 = 所有「变长字段长度」占用的字节数之和。

所以，我们要先知道每个变长字段的「变长字段长度」需要用多少字节表示？具体情况分为：

条件一：如果变长字段允许存储的最大字节数小于等于 255 字节，就会用 1 字节表示「变长字段长度」；
条件二：如果变长字段允许存储的最大字节数大于 255 字节，就会用 2 字节表示「变长字段长度」；
我们这里字段类型是 varchar(65535) ，字符集是 ascii，所以代表着变长字段允许存储的最大字节数是 65535，符合条件二，所以会用 2 字节来表示「变长字段长度」。

因为我们这个案例是只有 1 个变长字段，所以「变长字段长度列表」= 1 个「变长字段长度」占用的字节数，也就是 2 字节。

因为我们在算 varchar(n) 中 n 最大值时，需要减去 「变长字段长度列表」和 「NULL 值列表」所占用的字节数的。所以，在数据库表只有一个 varchar(n) 字段且字符集是 ascii 的情况下，varchar(n) 中 n 最大值 = 65535 - 2 - 1 = 65532。

当然，我上面这个例子是针对字符集为 ascii 情况，如果采用的是 UTF-8，varchar(n) 最多能存储的数据计算方式就不一样了：

- 在 UTF-8 字符集下，一个字符最多需要三个字节，varchar(n) 的 n 最大取值就是 65532/3 = 21844。

#### 多字段情况

**如果有多个字段的话，要保证所有字段的长度 + 变长字段字节数列表所占用的字节数 + NULL值列表所占用的字节数 <= 65535**。



### 行溢出后，MySQL是怎么处理的？

MySQL中磁盘和内存交互的基本单位是页，一个页的大小一般是16KB，也就是16384字节，而一个varchar(n)类型的列最多可以存储65532字节，一些大对象如TEXT、BLOB可能存储更多的数据，这时一个页可能就存不了一条记录。这个时候就会发生**行溢出，多的数据就会存到另外的【溢出页】中**

如果一个数据页存不了一条记录，InnoDB 存储引擎会自动将溢出的数据存放到「溢出页」中。在一般情况下，InnoDB 的数据都是存放在 「数据页」中。但是当发生行溢出时，溢出的数据会存放到「溢出页」中。

当发生行溢出时，在记录的真实数据处只会保存该列的一部分数据，而把剩余的数据放在「溢出页」中，然后真实数据处用 20 字节存储指向溢出页的地址，从而可以找到剩余数据所在的页。大致如下图所示。

![image-20230325221530708](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20230325221530708.png)

Compressed 和 Dynamic 这两个行格式和 Compact 非常类似，主要的区别在于处理行溢出数据时有些区别。

这两种格式采用完全的行溢出方式，记录的真实数据处不会存储该列的一部分数据，只存储 20 个字节的指针来指向溢出页。而实际的数据都存储在溢出页中，看起来就像下面这样：

![image-20230325221615807](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20230325221615807.png)

## 总结

1. MySQL的NULL值是如何存放的？

   MySQL的Compact行格式中会用【NULL值列表】来标记值为NULL的列，NULL值并不会存储在行格式中的真实数据部分

   NULL值列表会占用1字节空间，当表中所有字段都定义成NOT NULL，行格式中就不会有NULL值列表，这样可节省1字节的空间

2. MySQL如何知道varchar(n)实际占用的数据大小？

   MySQL的Compact行格式中会用【变长字段长度列表】存储变长字段实际占用的数据大小

3. varchar(n)中n最大取值为多少？

   一行记录最大能存储65535字节的数据，但是这个是包含【变长字段字节数列表所占用的字节数】和【NULL值列表所占用的字节数】。所以我们在计算varchar(n)的最大值时，需要减去这两个列表所占用的字节数。

   如果一张表只有一个 varchar(n) 字段，且允许为 NULL，字符集为 ascii。varchar(n) 中 n 最大取值为 65532。

   计算公式：65535 - 变长字段字节数列表所占用的字节数 - NULL值列表所占用的字节数 = 65535 - 2 - 1 = 65532。

   如果有多个字段的话，要保证所有字段的长度 + 变长字段字节数列表所占用的字节数 + NULL值列表所占用的字节数 <= 65535。

4.行溢出后，MySQL是如何处理的？

​	如果一个数据页存不了一条记录，InnoDB 存储引擎会自动将溢出的数据存放到「溢出页」中。

​	Compact 行格式针对行溢出的处理是这样的：当发生行溢出时，在记录的真实数据处只会保存该列的一部分数	据，而把剩余的数据放在「溢出页」中，然后真实数据处用 20 字节存储指向溢出页的地址，从而可以找到剩余	数据所在的页。

​	Compressed 和 Dynamic 这两种格式采用完全的行溢出方式，记录的真实数据处不会存储该列的一部分数据，	只存储 20 个字节的指针来指向溢出页。而实际的数据都存储在溢出页中。

