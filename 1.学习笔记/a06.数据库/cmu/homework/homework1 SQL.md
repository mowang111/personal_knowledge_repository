![schema](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/schema2021.png)

### Q2 [5 POINTS] (Q2_STRING_FUNCTION):

Get all unique `ShipNames` from the Order table that contain a hyphen `'-'`.

**Details:** In addition, get all the characters preceding the (first) hyphen. Return ship names alphabetically. Your first row should look like `Bottom-Dollar Markets|Bottom`

```sql
SELECT DISTINCT ShipName, substr(ShipName, 0, instr(ShipName, '-')) as PreHyphen
FROM 'Order'
WHERE ShipName LIKE '%-%'
ORDER BY ShipName ASC;
```

> + 筛选重复数据使用DISTINCT
> + ORDER BY放在最后
> + SUBSTR(*string*, *start*, *length*)
> + INSTR(*string1*, *string2*)

### Q3 [5 POINTS] (Q3_NORTHAMERICAN):

Indicate if an order's `ShipCountry` is in North America. For our purposes, this is `'USA', 'Mexico', 'Canada'`

**Details:** You should print the Order `Id`, `ShipCountry`, and another column that is either `'NorthAmerica'` or `'OtherPlace'` depending on the Ship Country.
Order by the primary key (`Id`) ascending and return 20 rows starting from Order Id `15445` Your output should look like `15445|France|OtherPlace` or `15454|Canada|NorthAmerica`

>思考过程
>
>+ 需要知道如何增加一列，通过判断`ShipCountry`来决定这一列的值

```sql
SELECT Id, ShipCountry, 
       CASE 
              WHEN ShipCountry IN ('USA', 'Mexico','Canada')
              THEN 'NorthAmerica'
              ELSE 'OtherPlace'
       END
FROM 'Order'
WHERE Id >= 15445
ORDER BY Id ASC
LIMIT 20;
```

### Q4 [10 POINTS] (Q4_DELAYPERCENT):

For each `Shipper`, find the percentage of orders which are late.

**Details:** An order is considered late if `ShippedDate > RequiredDate`. Print the following format, order by descending precentage, rounded to the nearest hundredths, like `United Package|23.44`

```sql
SELECT CompanyName, round(delaycnt * 100.0 / cnt, 2) AS pct
FROM (
      SELECT ShipVia, COUNT(*) AS cnt 
      FROM 'Order'
      GROUP BY ShipVia
     ) AS totalCnt
INNER JOIN (
            SELECT ShipVia, COUNT(*) AS delaycnt 
            FROM 'Order'
            WHERE ShippedDate > RequiredDate 
            GROUP BY ShipVia
           ) AS delayCnt
          ON totalCnt.ShipVia = delayCnt.ShipVia
INNER JOIN Shipper on totalCnt.ShipVia = Shipper.Id
ORDER BY pct DESC;
```

### Q5 [10 POINTS] (Q5_AGGREGATES):

Compute some statistics about categories of products

**Details:** Get the number of products, average unit price (rounded to 2 decimal places), minimum unit price, maximum unit price, and total units on order for categories containing greater than 10 products.
Order by `Category Id`. Your output should look like `Beverages|12|37.98|4.5|263.5|60`

> 思考
>
> + 得到一个种类产品（产品数量超过10）的所有数量，平均价格，最小单价，最大单价，总共单数
> + 通过Product可以找出所有产品数量超过10的种类id CategoryId
> + 再通过Category找到种类名称

```sql
SELECT CategoryName
    , COUNT(*) AS ProductnumofCate
    , ROUND(AVG(UnitPrice),2) AS UnitPriceAVG
    , MIN(UnitPrice) AS MinUnitPrice
    , MAX(UnitPrice) AS MAXUnitPrice
    , SUM(UnitsOnOrder) AS TotalUnitsOnOrder
from Product
INNER JOIN Category ON Category.Id = Product.CategoryId
GROUP BY CategoryId
HAVING ProductnumofCate > 10
ORDER BY CategoryId
```

### Q6 [10 POINTS] (Q6_DISCONTINUED):

For each of the 8 discontinued products in the database, which customer made the first ever order for the product? Output the customer's `CompanyName` and `ContactName`

**Details:** Print the following format, order by `ProductName` alphabetically: `Alice Mutton|Consolidated Holdings|Elizabeth Brown`

