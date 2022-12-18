-- Adam Turowski, grupa pga

-- Zadanie 1

SELECT DISTINCT org.name
FROM borders 
JOIN ismember im1 ON (borders.country1=im1.country)
JOIN ismember im2 ON (borders.country2=im2.country)
JOIN organization org ON (im1.organization=org.abbreviation AND im2.organization=org.abbreviation)
JOIN politics p1 ON (borders.country1=p1.country)
JOIN politics p2 ON (borders.country2=p2.country)
WHERE ABS(extract(year FROM p1.independence) - extract(year FROM p2.independence))>580;

-- Zadanie 2

CREATE DOMAIN change_types AS text
CHECK (VALUE IN ('INSERT', 'UPDATE', 'DELETE')) NOT NULL;

CREATE TABLE city_log (
  change_id serial PRIMARY KEY,
  change_type change_types,
  user_id name,
  change_date timestamp DEFAULT NOW(),
  accepted boolean DEFAULT TRUE
);

CREATE SEQUENCE change_number;

SELECT setval('change_number', max(change_id))
FROM city_log;

ALTER TABLE city_log ALTER COLUMN change_id
  SET DEFAULT nextval('change_number');

ALTER SEQUENCE change_number OWNED BY city_log.change_id;

-- Zadanie 3

CREATE OR REPLACE FUNCTION log_city_change() RETURNS TRIGGER AS $X$
  BEGIN
    INSERT INTO city_log(change_type, user_id) VALUES
    (TG_OP, CURRENT_USER);

    RETURN NEW;
  END
$X$ LANGUAGE plpgsql;

CREATE TRIGGER on_city_change AFTER INSERT OR UPDATE ON city
FOR EACH ROW EXECUTE PROCEDURE log_city_change();
