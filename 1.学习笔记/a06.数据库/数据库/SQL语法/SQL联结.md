---
title: SQL联结
date: {{ date }}
top: false
cover: false
password:
toc: true
mathjax: true
summary:
tags: 
- 数据库
- SQL
categories: []
---



# SQL联结

## 创建联结

```sql
select vend_name, prod_name, prod_price
from vendors, products
where vendors.vend_id = products.vend_id
```

注：如果没有where语句，返回的结果就是笛卡儿积

### 内联结

前面的联结称为等值联结（equijoin）,它是基于两个表之间的相等测试，这种联结也称为内联结（inner join）。

上述的联结也可以使用稍微不同的语法，联结条件用特定的on子句而不是where子句给出。

```sql
select vend_name, prod_name, prod_price
from vendors
inner join products on vendors.vend_id = product.vend_id;
```

### 自联结

假如要给与Jim Jones同一公司的所有顾客发送一封信件。这个查询要求首先找出Jim Jones工作的公司，然后找出该公司工作的顾客。

使用子查询的解决方案：

```sql
select cust_id, cust_name, cust_contact
from customers
where cust_name = (
	select cust_name
    from customers
    where cust_contact = 'Jim Jones'
);
```

使用自联结的解决方案：

```sql
select c1.cust_id, c1.cust_name, c1.cust_contact
from customers as c1, customers as c2
where c1.cust_name = c2.cust_name
and c1.cust_contact = 'Jim Jones';
```

### 自然联结

标准联结（内联结）返回所有数据，相同的列甚至多次出现。自然联结排除多次出现，使每一列只返回一次。

一般通过对一个表使用通配符（select *），而对其他表的列使用明确的子集来完成。

### 外联结

外联结与内联结不同的是，外联结包括没有关联行的行。在使用outer join语法时，必须使用right或left关键字指定包括所有行的表（right指出的是outer join 右边的表，left指出的是从from子句左边的表）

下面检索包括没有订单顾客在内的顾客：

```sql
select customers.cust_id, orders.order_num
from custormers
left outer join orders on customers.cust_id = orders.cust_id
```



