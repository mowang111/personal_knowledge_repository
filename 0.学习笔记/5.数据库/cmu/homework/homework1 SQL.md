![schema](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/schema2021.png)

### Q2 [5 POINTS] (Q2_STRING_FUNCTION):

Get all unique `ShipNames` from the Order table that contain a hyphen `'-'`.

**Details:** In addition, get all the characters preceding the (first) hyphen. Return ship names alphabetically. Your first row should look like `Bottom-Dollar Markets|Bottom`

```sql
SELECT DISTINCT ShipName from 'Order'
WHERE ShipName LIKE '%-%'
ORDER BY ShipName;
```

> + 筛选重复数据使用DISTINCT
> + ORDER BY放在最后

### Q3 [5 POINTS] (Q3_NORTHAMERICAN):

Indicate if an order's `ShipCountry` is in North America. For our purposes, this is `'USA', 'Mexico', 'Canada'`

**Details:** You should print the Order `Id`, `ShipCountry`, and another column that is either `'NorthAmerica'` or `'OtherPlace'` depending on the Ship Country.
Order by the primary key (`Id`) ascending and return 20 rows starting from Order Id `15445` Your output should look like `15445|France|OtherPlace` or `15454|Canada|NorthAmerica`

>思考过程
>
>+ 需要知道如何增加一列，通过判断`ShipCountry`来决定这一列的值

```sql
SELECT Id,ShipCountry,
CASE WHEN ShipCOuntry IN ('USA','Mexico','Canada')
THEN 'NorthAmerica'
ELSE 'OtherPlace'
END AS ShipCountryGroup
FROM 'Other'
WHERE Id >= 15445 LIMIT 20；
```

### Q4 [10 POINTS] (Q4_DELAYPERCENT):

For each `Shipper`, find the percentage of orders which are late.

**Details:** An order is considered late if `ShippedDate > RequiredDate`. Print the following format, order by descending precentage, rounded to the nearest hundredths, like `United Package|23.44`

```sql
SELECT CompanyName,ROUND(count(CASE WHEN ShippedDate > RequiredDate THEN 1 ELSE NULL END)*100.0/count(*),2)
AS Percentage
FROM 'Order',Shipper
WHERE 'Order'.ShipVia=Shipper.Id
Group By CompanyName
ORDER BY Percentage DESC;
```

### Q5 [10 POINTS] (Q5_AGGREGATES):

Compute some statistics about categories of products

**Details:** Get the number of products, average unit price (rounded to 2 decimal places), minimum unit price, maximum unit price, and total units on order for categories containing greater than 10 products.
Order by `Category Id`. Your output should look like `Beverages|12|37.98|4.5|263.5|60`

> 思考
>
> + 得到一个种类产品（产品数量超过10）的所有数量，平均价格，最小单价，最大单价，总共单数