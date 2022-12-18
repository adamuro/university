-- Adam Turowski, grupa pga
-- Zadanie 1
CREATE VIEW SeaAirports
  (iatacode, name, city, province, country, sea)
AS
SELECT city.elevation, airport.iatacode, airport.name, city.name AS city, city.province, city.country, sea.name AS seaname
FROM airport JOIN city ON airport.city=city.name AND airport.country=city.country AND airport.province=city.province
JOIN located ON airport.city=located.city AND airport.country=located.country AND airport.province=located.province
JOIN sea ON located.sea=sea.name
WHERE city.elevation>200;

-- Zadanie 3
INSERT INTO countrypops
  (country, year, population)
SELECT country.code, 2021, country.population
FROM country;

-- Zadanie 4
ALTER TABLE country ADD COLUMN popPeakCount bigint;
ALTER TABLE country ADD COLUMN popPeakYear smallint;

UPDATE country c SET(popPeakCount, popPeakYear) = 
  (SELECT cp.population, cp.year
   FROM countrypops cp
   WHERE c.code=cp.country
   ORDER BY cp.population DESC, cp.year ASC
   LIMIT 1);

