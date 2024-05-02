---
title: SQL用法
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

# SQL用法

+ sql取出某一列中数量最多的元素
  + 先group by 这一列，然后order by 这一列 desc limit 1;