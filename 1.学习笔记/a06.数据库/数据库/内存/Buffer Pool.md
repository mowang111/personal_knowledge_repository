---
title: Buffer pool
date: {{ date }}
top: false
cover: false
password:
toc: true
mathjax: true
summary:
tags: 
- 数据库
- mysql
categories: []
---

引用自(小林揭开 Buffer Pool 的面纱)[https://xiaolincoding.com/mysql/buffer_pool/buffer_pool.html#%E4%B8%BA%E4%BB%80%E4%B9%88%E8%A6%81%E6%9C%89-buffer-pool]

## Buffer pool

虽然说 MySQL 的数据是存储在磁盘里的，但是也不能每次都从磁盘里面读取数据，这样性能是极差的。

要想提升查询性能，加个缓存就行了嘛。所以，当数据从磁盘中取出后，缓存内存中，下次查询同样的数据的时候，直接从内存中读取。

为此，Innodb 存储引擎设计了一个**缓冲池（\*Buffer Pool\*）**，来提高数据库的读写性能。

![image-20230326224319547](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20230326224319547.png)

有了缓冲池后：

+ 当读取数据时，如果数据存在于Buffer Pool中，客户端就会直接读取Buffer Pool 中的数据，否则再去磁盘中读取。
+ 当修改数据时，首先是修改Buffer Pool 中数据所在的页，然后将其页设置为脏页，最后由后台线程将脏页写入到磁盘。

## Buffer Pool有多大?

Buffer Pool是在MySQL启动的时候，向操作系统申请的一片连续的内存空间，默认配置下Buffer Pool只有128MB。

可以通过调整`innodb_buffer_pool_size`参数来设置Buffer Pool的大小，一般建议设置成可用物理内存的60%~80%

## Buffer Pool 缓存什么？

InnoDB会把存储的数据划分为若干个【页】，以页作为磁盘和内存交互的基本单位，一个页的默认大小为16KB。因此，Buffer Pool同样需要按【页】来划分。

在MySQL启动的时候，**InnoDB会为Buffer Pool申请一篇连续的内存空间，然后按照默认的16KB大小划分成一个个页，Buffer Pool 中的页就叫做缓存页。**此时，这些缓存也都是空闲的，之后随着程序的运行，才会有磁盘上的页被缓存到Buffer Pool中。

Buffer Pool 中除了缓存【索引页】和【数据页】，还包括了undo页，插入缓存、自适应哈希索引、锁信息等。

![image-20230327142306681](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20230327142306681.png)

为了更好的管理这些在Buffer Pool中的缓存页，InnoDB为每一个缓存页都创建了一个**控制块**，控制块信息包括【缓存页的表空间、页号、缓存地址、链表节点】等等。

控制块也是占用内存空间的，它是放在Buffer Pool的最前面，接着才是缓存页：

![image-20230327142550106](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20230327142550106.png)

上图中，控制块和缓存页中的中间部分称为碎片空间。

### 为什么会有碎片空间？

你想想啊，每一个控制块都对应一个缓存页，那在分配足够多的控制块和缓存页后，可能剩余的那点儿空间不够一对控制块和缓存页的大小，自然就用不到喽，这个用不到的那点儿内存空间就被称为碎片了。

当然，如果你把 Buffer Pool 的大小设置的刚刚好的话，也可能不会产生碎片。

### 查询一条记录，就只需要缓冲一条记录吗？

不是。当我们查询一条记录的时候，InnoDB是会把整个页的数据加载到Buffer Pool 中，因为通过索引只能定位到磁盘中的页，而不能定位到页中的一条记录，将页加载到Buffer Pool中后，再通过页里的页目录去定位到某条具体的记录。

## 如何管理Buffer Pool?

### 如何管理空闲页？

Buffer Pool是一片连续的内存空间，当MySQL运行一段时间后，这片连续的内存空间中的缓存页既有空闲的，也有被使用的。

当我们从磁盘读取数据的时候，为了快速找到空闲的缓存页，可以使用链表结构，将空闲缓存页的【控制块】作为链表的节点，这个链表称为**Free链表（空闲链表）**。

![image-20230327143446027](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20230327143446027.png)

Free链表上除了控制块，还有一个头节点，该头节点中包含了链表的头节点地址，尾节点地址，以及当前链表中节点的数量等信息。

Free链表节点是一个一个控制块，而每个控制块包含着对应缓存页的地址，所以相当于Free链表节点都对应一个空闲的缓存页。

有了Free链表之后，每当需要从磁盘中加载一个页到Buffer Pool中时，就从Free链表中取一个空闲的缓存页，并且把该缓存页对应的控制块的信息填上，然后把该缓存页对应的控制块从Free链表上移除。

### 如何管理脏页？

设计Buffer Pool除了能提高读性能，还能提高写性能，也就是更新数据的时候，不需要每次都要写入磁盘，而是将Buffer Pool对应的缓存页标记为【脏页】,然后再由后台线程将脏页写入到磁盘。

为了快速知道哪些缓存页是脏的，于是设计出【Flush链表】，和Free链表类似，链表的节点也是控制块，区别在于Flush链表的元素都是脏页。

![image-20230327144101488](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20230327144101488.png)

### 如何提高缓存命中率？

最容易想到的就是 LRU（Least recently used）算法。

该算法的思路是，链表头部的节点是最近使用的，而链表末尾的节点是最久没被使用的。那么，当空间不够了，就淘汰最久没被使用的节点，从而腾出空间。

简单的 LRU 算法的实现思路是这样的：

- 当访问的页在 Buffer Pool 里，就直接把该页对应的 LRU 链表节点移动到链表的头部。
- 当访问的页不在 Buffer Pool 里，除了要把页放入到 LRU 链表的头部，还要淘汰 LRU 链表末尾的节点。

到这里我们可以知道，Buffer Pool 里有三种页和链表来管理数据。

![image-20230327144430307](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20230327144430307.png)

图中：

- Free Page（空闲页），表示此页未被使用，位于 Free 链表；
- Clean Page（干净页），表示此页已被使用，但是页面未发生修改，位于LRU 链表。
- Dirty Page（脏页），表示此页「已被使用」且「已经被修改」，其数据和磁盘上的数据已经不一致。当脏页上的数据写入磁盘后，内存数据和磁盘数据一致，那么该页就变成了干净页。脏页同时存在于 LRU 链表和 Flush 链表。

简单的LRU算法并没有被MySQL使用，因为简单的LRU算法无法避免下面两个问题：

+ 预读失效

  + MySQL的预读机制。程序是由空间局部性的，靠近当前被访问数据的数据，在未来很大概率会被访问到。所以MySQL在加载数据页时，会提前把它相邻的数据页一并加载进来，目的是为了减少磁盘IO。但**可能这些被提前加载进来的数据页并没有被访问到，相当于这个预读是白做了，这就是预读失效。**如果使用简单的LRU算法，就会把预读页放到LRU链表头部，而当Buffer Pool空间不够的时候，还需要把末尾的页淘汰掉。如果这些预读页一直不被访问到，不会访问的预读页却占用了LRU链表前排的位置，而末尾淘汰的页，可能是频繁访问的页，这样就大大降低了缓存命中率。

  + 如何解决预读失效而导致的缓存命中率降低的问题？

    + 最好就是让预读的页停留在Buffer Pool里的时间要尽可能短，让真正被访问的页才能移动到LRU链表的头部，从而保证真正被读取的热数据留在Buffer Pool里的时间尽可能长。

    + **MySQL改进了LRU算法，将LRU划分了2个区域：old区域和young区域。**young区域在LRU链表的前半部分，old区域则是在链表的后半部分。

      ![image-20230327145437308](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20230327145437308.png)

      old 区域占整个 LRU 链表长度的比例可以通过 `innodb_old_blocks_pct` 参数来设置，默认是 37，代表整个 LRU 链表中 young 区域与 old 区域比例是 63:37。

      **划分为两个区域后，预读的页就只需要加入old区域的头部，当页被真正访问的时候，才将页插入young区域的头部。**如果预读的页一直没有被访问，就会从old区域移除，这样就不会影响young区域中的热点数据。

+ Buffer Pool污染

  + 当**某个SQL语句扫描了大量的数据**时，在Buffer Pool空间比较有限的情况下，可能会将**Buffer Pool里的所有页都替换出去，导致大量的热数据被淘汰**，等这些热数据又被再次访问的时候，由于缓存未命中，就会产生大量的磁盘IO，MySQL性能就会急剧下降，这个过程被称为**Buffer Pool污染**。

  + 注意，Buffer Pool污染并不是查询语句查询出了大量的数据才出现的问题，即使查询出来的结果集很小，也会造成Buffer Pool污染。

    + 比如在一个数据量非常大的表，执行了以下语句：

      ```sql
      select * from t_user where name like "%xiaolin%";
      ```

      可能这个查询出来的结果就几条记录，但是由于这条语句会发生索引失效，所以这个查询过程是全表扫描的，接着会发生如下过程：

      + 从磁盘读到的页加入到LRU链表的old区域头部；
      + 当从页里读取行记录的时候，也就是页被访问的时候，就要将该页放到young区域头部；
      + 接下来拿行记录的name字段和字符串xiaolin进行模糊匹配，如果符合条件，就加入到结果集里。
      + 如此往复，直到扫描完表中的所有记录

  + 如何解决Buffer Pool污染而导致的缓存命中率下降的问题？

    + LRU链表中young区域就是热点数据，只要我们提高进入young区域的门槛，就能有效保证young区域里的热点数据不会被替换掉
    + MySQL是这样做的，进入到young区域条件增加了一个停留在old区域的时间判断。
      + 具体是这样的，在对某个处在old区域的缓存页进行第一次访问时，就在它对应的控制块中记录下来这个访问的时间
        + 如果后续的访问时间与第一次访问的时间在某个时间间隔内，那么该缓存页就不会被从old区域移动到young区域的头部
        + 如果后续的访问时间与第一次访问的时间不在某个时间间隔内，那么该缓存页移动到young区域的头部。
        + 这个时间间隔是由`innodb_old_blocks_time`控制的，默认是1000ms
      + **只有同时满足【被访问】与【在old区域停留时间超过1秒】两个条件，才会被插入到young区域头部。**
    + 另外，MySQL对young区域做了一个优化，为了防止young区域节点频繁移动到头部。young区域前面1/4被访问不会移动到链表头部，只有后面的3/4被访问才会

### 脏页什么时候会被输入磁盘？

引入了Buffer Pool后，当修改数据时，首先是修改Buffer Pool中数据所在页，然后将其页设置为脏页，但是磁盘中还是原数据。

因此，脏页需要被刷入到磁盘，保证缓存和磁盘的数据一致，但是若每次修改数都刷入磁盘，则性能会很差，所以一般都会在一定时机进行批量刷盘。

如果在脏页还没有来得及刷入磁盘时，MySQL宕机了，不就丢失数据了？

InnoDB的更新操作采用的是Write Ahead Log策略，即先写入日志，再写入磁盘，通过redo log日志让MySQL拥有了崩溃恢复能力。

下面几种情况会触发脏页的刷新：

+ 当redo log日志满了的情况下，会主动触发脏页刷新到磁盘；
+ Buffer Pool空间不足时，需要将一部分数据页淘汰掉，如果淘汰的是脏页，需要先将脏页同步到磁盘；
+ MySQL认为空闲时，后台线程会定期将适量的脏页刷入到磁盘
+ MySQL正常关闭之前，会把所有的脏页刷入到磁盘

在我们开启了慢 SQL 监控后，如果你发现**「偶尔」会出现一些用时稍长的 SQL**，这可能是因为脏页在刷新到磁盘时可能会给数据库带来性能开销，导致数据库操作抖动。

如果间断出现这种现象，就需要调大 Buffer Pool 空间或 redo log 日志的大小。



## 总结

InnoDB存储引擎设置了一个缓冲池（Buffer Pool），来提高数据库的读写性能。

Buffer Pool以页为单位缓冲数据，可以通过`innodb_buffer_pool_size`参数调整缓冲池的大小，默认是128M。

InnoDB通过三种链表来管理缓存页：

+ Free List（空闲页链表），管理空闲页
+ Flush List（脏页链表），管理脏页
+ LRU List，管理脏页+干净页，将最近且经常查询的数据缓存在其中，而不常查询的数据就淘汰出去。

InnoDB对LRU做了一些优化，我们熟悉的LRU算法通常将最近查询的数据放到LRU链表的头部，而InnoDB做了2点优化：

+ 将LRU链表分为young和old区域，加入缓冲池的页，优先插入old区域；页被访问时，才会进入young区域，目的是解决预读失效的问题。
+ 当【页被访问】且【 old 区域停留时间超过 `innodb_old_blocks_time` 阈值（默认为1秒）】时，才会将页插入到young区域，否则还是插入到old区域，目的是为了解决批量数据访问，大量热数据淘汰的问题。

可以通过调整 `innodb_old_blocks_pct` 参数，设置 young 区域和 old 区域比例。

在开启了慢 SQL 监控后，如果你发现「偶尔」会出现一些用时稍长的 SQL，这可因为脏页在刷新到磁盘时导致数据库性能抖动。如果在很短的时间出现这种现象，就需要调大 Buffer Pool 空间或 redo log 日志的大小。
