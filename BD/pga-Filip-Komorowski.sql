-- Filip Komorowski, grupa pga

-- Zadanie 0

CREATE TABLE sunken_city(LIKE city);

ALTER TABLE sunken_city ADD COLUMN sinking_date date;

-- Zadanie 1
-- Testowanie:
-- To zadanie testowałem na miastach z elevation < 1, było ich 18 i po wywowałaniu funkcji wszystkie przeniosły się do sunken_city, last_level poprawnie ustawił sie na 1 dodatkowo przetesowałem czy wszystkie lotniska miast z sunken_city zostały usunięte i tak było.
-- Dodatkowo znalazłem miasto Sevilla, które ma elevation 12 a jego lotnisko(iatacode: SVQ) 34 i sprawdziłem, że city ustawione jest na NULL po wykonaniu SELECT sea_level(13);

-- SELECT airport.iatacode, airport.name, airport.city, city.elevation, airport.elevation FROM city JOIN airport ON (city.name=airport.name) WHERE (city.elevation < airport.elevation); <- tak znalazłem Sevilla
-- SELECT airport.* FROM airport WHERE airport.iatacode = 'SVQ'; <-- jest ok

CREATE OR REPLACE FUNCTION sea_level(level int)
RETURNS VOID
AS $X$

DECLARE miasto city;

BEGIN
	-- Do zadania drugiego tu trzymam ostatni level z wywołania funkcji
	DROP TABLE IF EXISTS last_level; -- Uznałem, ze łatwiej zawsze tworzyc od nowa niż wyszukiwać konkretnej wartości do updateowania
	CREATE TABLE last_level(level INT);
	INSERT INTO last_level(level) VALUES(level);
	
	DELETE FROM airport WHERE elevation < level;
	
	FOR miasto IN SELECT * FROM city
	LOOP
		IF (miasto.elevation < level) AND EXISTS(SELECT city FROM city JOIN airport ON(city.name = airport.city AND city.country = airport.country) WHERE city.name = miasto.name AND city.country = miasto.country)
		THEN
		 	UPDATE airport SET city = NULL WHERE city = miasto.name AND country = miasto.country;
		END IF; 
		IF (miasto.elevation < level)
		THEN 
			INSERT INTO sunken_city(name,country,province, population, latitude, longitude, elevation, sinking_date)
			VALUES(miasto.name, miasto.country, miasto.province, miasto.population, miasto.latitude, miasto.longitude, miasto.elevation, current_date);
			DELETE FROM city WHERE city.name = miasto.name AND city.country = miasto.country;
		END IF;
	END LOOP;
END

$X$ LANGUAGE plpgsql;

-- Zadanie 2

CREATE OR REPLACE FUNCTION insert_city()
    RETURNS TRIGGER AS $X$
    DECLARE llevel INT;
    BEGIN
    SELECT level INTO llevel FROM last_level;
    IF (NEW.elevation >= llevel) 
    	THEN RETURN NEW;
    ELSE 
    	INSERT INTO sunken_city(name,country,province,population,latitude,
        longitude,elevation,sinking_date)
        VALUES(NEW.name,NEW.country,NEW.province,NEW.population,
        NEW.latitude,NEW.longitude,NEW.elevation,current_date); 
    END IF;
    RETURN NULL;
    END
    $X$ LANGUAGE plpgsql;

CREATE OR REPLACE FUNCTION update_city()
    RETURNS TRIGGER AS $X$
    DECLARE llevel INT;
    BEGIN
    SELECT level INTO llevel FROM last_level;
    IF (NEW.elevation >= llevel) 
    	THEN RETURN NEW;
    ELSE 
    	DELETE FROM city WHERE name = OLD.name AND country = OLD.country;
    	INSERT INTO sunken_city(name,country,province,population,latitude,
        longitude,elevation,sinking_date)
        VALUES(NEW.name,NEW.country,NEW.province,NEW.population,
        NEW.latitude,NEW.longitude,NEW.elevation,current_date); 
    END IF;
    RETURN NULL;
    END
    $X$ LANGUAGE plpgsql;

CREATE TRIGGER on_city_insert BEFORE INSERT ON city
FOR EACH ROW EXECUTE PROCEDURE insert_city();

CREATE TRIGGER on_city_update BEFORE UPDATE ON city
FOR EACH ROW EXECUTE PROCEDURE update_city();

--Testowanie:
-- Po tym jak testowałem pierwsze zadanie z level 13, sprobowałem dodac do tabeli city testowe miasto z elevation 10
-- INSERT INTO city(name,country,province, population, latitude, longitude, elevation) VALUES ('test', 'te', 'test', 100, 100, 100, 10);
-- Poniższe zapytanie zwraca 0 wierszy więc jest ok
-- SELECT * FROM city where city.name = 'test'; 

-- Jeszcze pozostało przetestować update
-- SELECT city.* FROM city WHERE city.name = 'Paris'; <-- Jest w city, elevation = 28
-- UPDATE city SET elevation = 10 WHERE name = 'Paris'; <-- feedback : UPDATE 0
-- SELECT city.* FROM city WHERE city.name = 'Paris'; <-- teraz zwraca 0 wierszy
-- Pozostaje sprawdzic czy poprawnie przeniosło do sunken city:
-- SELECT sunken_city.* FROM sunken_city WHERE sunken_city.name = 'Paris'; <- jest ok
