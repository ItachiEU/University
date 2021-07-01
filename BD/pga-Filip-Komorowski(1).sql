-- Filip Komorowksi, grupa pga

-- Zadanie 1

SELECT DISTINCT country.name, count(DISTINCT islandin.island)

FROM country JOIN geo_sea ON(country.code = geo_sea.country) JOIN sea ON(geo_sea.sea = sea.name) LEFT JOIN islandIn ON(sea.name = islandIn.sea)

GROUP BY country.name 

ORDER BY 2 DESC, 1 ASC;

-- Zadanie 2

WITH polacy AS (

SELECT DISTINCT country.name as cn, percentage as procentPolakow

FROM country JOIN ethnicgroup ON (country.code = ethnicgroup.country)

WHERE ethnicgroup.name = 'Polish'

)

SELECT DISTINCT country.name, procentPolakow 

FROM country JOIN ethnicgroup ON (country.code = ethnicgroup.country) JOIN polacy ON (country.name = cn)

GROUP BY country.name, procentPolakow HAVING COUNT(DISTINCT ethnicgroup.name) >= 10; 

-- Zadanie 3

CREATE TEMP TABLE new_borders AS(
(SELECT country1 AS c2, country2 AS c1 FROM borders)
UNION
(SELECT country2 AS c2, country1 AS c1 FROM borders) 
);

WITH RECURSIVE Path(a,b) AS (
(SELECT c1, c2 FROM new_borders)
UNION (SELECT b.c1, p.b FROM new_borders b JOIN Path p ON (b.c2 = p.a)))

SELECT country 
FROM Path p JOIN country ON (p.a = country.code)
WHERE p.b = 'PL'
ORDER BY country.name;


-- Zadanie 4

SELECT country.name, ROUND((SUM(city.population) / country.population) * 100) as procent

FROM country JOIN city ON (country.code = city.country)

GROUP BY country.name, country.population

HAVING (SUM(city.population)/ country.population) * 100 > 75

ORDER BY procent DESC;

