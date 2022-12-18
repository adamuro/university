-- Adam Turowski, grupa pga
-- Zadanie 1
SELECT city.*
FROM city 
JOIN airport ON airport.city=city.name AND airport.country=city.country AND airport.province=city.province
JOIN country ON airport.country=country.code
WHERE country.name='Poland' AND city.elevation<100
ORDER BY city.name;

-- Zadanie 2
SELECT DISTINCT sea.name, sea.area
FROM sea
JOIN river ON sea.name=river.sea
JOIN geo_river ON geo_river.river=river.name
WHERE geo_river.country='F' AND river.length>800
ORDER BY sea.area DESC;