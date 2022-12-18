-- Adam Turowski, grupa pga

-- Zadanie 0
CREATE TABLE sunken_city (LIKE city);
ALTER TABLE sunken_city ADD COLUMN sinking_date date;

-- Zadanie 1
CREATE TABLE sea_level (level int);
INSERT INTO sea_level (level) VALUES (0);

CREATE OR REPLACE FUNCTION sea_level(int) RETURNS VOID
AS $X$
BEGIN
  INSERT INTO sunken_city
    SELECT 
      c.name, c.country, c.province, c.population, c.latitude, c.longitude, c.elevation, CURRENT_DATE
    FROM city c
    WHERE c.elevation < $1;

  DELETE FROM airport
  WHERE elevation < $1;

  DELETE FROM city
  WHERE elevation < $1;

  UPDATE airport
  SET city = NULL
  WHERE (city, country, province) IN 
    (SELECT sc.name, sc.country, sc.province
     FROM sunken_city sc);

  UPDATE sea_level
  SET level = $1;
END
$X$ LANGUAGE plpgsql;

-- Po wywołaniu sea_level(100) z bazy usunięte zostaną wszystkie miasta i lotniska
-- o elewacji < 100, można się o tym przekonać wykonując zapytanie
-- SELECT * FROM city/airport WHERE elevation < 101;
-- Poprawne działanie drugiej części funkcji testowałem wykonując zapytanie
-- SELECT city, province, country FROM airport WHERE elevation < 105;
-- Widać wtedy, że rzeczywiście niektóre miasta zostały usunięte.