-- 1

select TOP 10
c.CustomerId 'CustomerID',
(select SUM(od.UnitPrice * od.Quantity) from OrderDetails od where od.OrderId = o.OrderId) vanzari
from Orders o
where o.OrderDate >= '01-08-2015' and o.OrderDate < '01-02-2016' -- depending on how date is formatted, this might require changes, note < first day of fabruary 2016
group by c.CustomerId
order by vanzari des

-- Should output something like:

-- CustomerID, vanzari
-- 1, 789
-- 2, 678
-- 3, 567
-- 4, 456

-- For other details like name, an easy join with Customers should do the job

-- Ok so this is not very clear
-- best selled product should be only one, adding best selled product for each client
-- I am assuming it's the product bought the most by each client from the top 10 list

select TOP 1 pd.ProductId ProductId, SUM(od.UnitPrice * od.Quantity) total from OrderDetails od where od.OrderId = o.OrderId group by od.ProductId order by total desc


select TOP 10
c.CustomerId 'CustomerID',
(select SUM(od.UnitPrice * od.Quantity) from OrderDetails od where od.OrderId = o.OrderId) vanzari,
(   -- inline on 25, formatted here for better visibility
    select TOP 1 pd.ProductId ProductId
    from OrderDetails od
    where od.OrderId = o.OrderId
    group by od.ProductId
    order by SUM(od.UnitPrice * od.Quantity) desc
) MostSold
from Orders o
where o.OrderDate >= '01-08-2015' and o.OrderDate < '01-02-2016' -- depending on how date is formatted, this might require changes, note < first day of fabruary 2016
group by c.CustomerId
order by vanzari des

-- PS: Without any db to run the queries on, I doubt they are going to work out of box, normally I would go step by step, query by query till I get to the result I want