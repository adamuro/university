-- Adam Turowski, grupa pga
-- Zadanie 1
SELECT country.name, count(islandin.sea)
FROM country
JOIN geo_sea ON country.code=geo_sea.country
JOIN islandin ON islandin.sea=geo_sea.sea
GROUP BY country.name
ORDER BY count(islandin.sea) DESC, country.name ASC;

-- Zadanie 2
WITH polish AS (
  SELECT c1.*
  FROM country c1
  JOIN ethnicgroup e1 ON c1.code=e1.country
  WHERE e1.name='Polish'
),
countries AS (SELECT DISTINCT polish.code, polish.name, count(ethnicgroup.name)
FROM polish
JOIN ethnicgroup ON polish.code=ethnicgroup.country
GROUP BY polish.name, polish.code
HAVING count(ethnicgroup.name)>=10)
SELECT countries.name, ethnicgroup.percentage FROM countries
JOIN ethnicgroup ON countries.code=ethnicgroup.country
WHERE ethnicgroup.name='Polish';

-- Zadanie 4
SELECT country.name, country.population, ROUND(country.population/sum(city.population) * 100) as percentage
FROM country
JOIN city ON country.code=city.country
GROUP BY country.name, country.population
HAVING country.population*0.75<=sum(city.population)
ORDER BY sum(city.population)/country.population DESC;