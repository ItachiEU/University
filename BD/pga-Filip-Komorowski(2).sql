-- Filip Komorowski, grupa pga

-- Zadanie 1
CREATE VIEW SeaAirports(iatacode, name, city, province, country, sea) AS
SELECT DISTINCT iatacode, Airport.name, Airport.city, Airport.province, Airport.country, sea FROM City JOIN Airport ON(City.name = Airport.city AND Airport.country = city.country) JOIN located ON(located.city = City.name AND located.province = airport.province) WHERE city.elevation > 200 AND located.sea IS NOT NULL;

-- Zadanie 2

ALTER TABLE city DROP CONSTRAINT citykey;

ALTER TABLE city ADD COLUMN id SERIAL;
ALTER TABLE city ADD CONSTRAINT pk_city
    PRIMARY KEY(id);

ALTER TABLE airport ADD COLUMN CityId int;

UPDATE airport SET CityId = cit.id
FROM city cit JOIN airport air ON(cit.name = air.city) WHERE air.city = airport.city;

ALTER TABLE airport ADD CONSTRAINT fk_airport
    FOREIGN KEY (CityId) REFERENCES city(id) DEFERRABLE;

INSERT INTO airport(iatacode,name,country,city,province,latitude,longitude,
elevation, CityId)
SELECT 'IEG', 'Babimost', country, name, province,
 latitude, longitude, elevation, id
FROM city WHERE name = 'Zielona Góra';

-- Zadanie 3

INSERT INTO CountryPops(country, year, population) SELECT country.code, extract(year FROM current_date), country.population FROM country;

-- Zadanie 4

ALTER TABLE Country ADD COLUMN popPeakCount numeric;
ALTER TABLE Country ADD COLUMN popPeakYear numeric;

UPDATE Country SET popPeakCount = (SELECT max(population) FROM countrypops WHERE Country.code = countrypops.country);
UPDATE Country SET popPeakYear = (SELECT MIN(year) FROM countrypops WHERE Country.popPeakCount = countrypops.population);
