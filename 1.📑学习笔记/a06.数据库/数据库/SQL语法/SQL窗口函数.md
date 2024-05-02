---
title: SQL窗口函数
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

# SQL窗口函数

SQL窗口函数（Window Functions）是一种高级SQL技术，它可以对结果集中的行进行聚合计算，同时保留原始结果集中的行。窗口函数可以在SELECT语句中使用，使用OVER子句定义窗口（Window），并使用PARTITION BY子句对结果集进行分许，以便在每个分组内进行聚合计算。

窗口函数可以用于执行许多复杂的查询和分析操作，如计算移动平均值、累计总和、排名和百分位数等。窗口函数与GROUP BY子句不同，它不会对结果进行聚合，而是对每个行进行计算，并将计算结果添加到结果集的每个行中。

常见的SQL窗口函数包括：
+ ROW_NUMBER()：为每一行返回一个唯一的整数值
+ RANK()：计算每一行在分组中的排名
+ DENSE_RANK()：与RANK()类似，但是不会跳过相同的排名。
+ SUM()、AVG()、MAX()、MIN()：计算指定列在每个窗口中的聚合值。

示例：使用窗口函数计算每个城市的平均工资和排名：
```sql
SELECT 
	city, AVG(salary) OVER (PARTITION BY city) AS avg_salary,
	RANK() OVER (PARTITION BY city ORDER BY AVG(salary) DESC) AS rank
FROM
	employee;
```

https://leetcode.cn/problems/game-play-analysis-ii/description/

https://leetcode.cn/problems/investments-in-2016/description/?favorite=qgq7m9e