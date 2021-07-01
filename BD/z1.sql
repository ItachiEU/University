-- Filip Komorowksi, grupa pga
-- Zadanie 1

SELECT DISTINCT city.* 
FROM city JOIN airport ON (city.name = airport.city)

WHERE city.country = 'PL' AND city.elevation < '100'
ORDER BY name;


--- Zadanie 2

SELECT DISTINCT sea.name, sea.area FROM sea JOIN river ON(sea.name = river.sea) JOIN geo_river ON (river.name = geo_river.river)

WHERE river.length > 800 AND geo_river.country = 'F'
ORDER BY sea.area DESC;
