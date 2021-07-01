-- Filip Komorowski, grupa pga

-- Zadanie 1

CREATE TEMP TABLE temp AS
SELECT country1, country2, independenceDate1, independenceDate2
FROM (SELECT country1, country2, p1.independence as independenceDate1, p2.independence as independenceDate2
FROM borders JOIN Politics p1 ON(p1.country = country1)
JOIN Politics p2 ON(p2.country = country2)
WHERE p1.independence IS NOT NULL AND p2.independence IS NOT NULL) AS helper 
WHERE abs(extract(year FROM helper.independenceDate1) - extract(year FROM helper.independenceDate2)) > 580;


SELECT DISTINCT memb.organization FROM isMember memb JOIN temp ON(memb.country = temp.country1)
WHERE temp.country2 IN (SELECT country FROM isMember WHERE isMember.organization = memb.organization);

-- Zadanie 2

CREATE TABLE city_log(change_id serial PRIMARY KEY,
 change_type text, 
 user_id text, 
 change_date timestamp, 
 change_accepted boolean default true);


-- Zadanie 3

CREATE OR REPLACE FUNCTION update_city_log()
    RETURNS TRIGGER AS $X$
    BEGIN
	INSERT INTO city_log(change_type, user_id, change_date, change_accepted)
	VALUES('update', current_user, current_date, true);
	RETURN NEW;
	END
    $X$ LANGUAGE plpgsql; 

CREATE OR REPLACE FUNCTION insert_city_log()
    RETURNS TRIGGER AS $X$
    BEGIN
	INSERT INTO city_log(change_type, user_id, change_date, change_accepted)
	VALUES('insert', current_user, current_date, true);
	RETURN NEW;
	END
    $X$ LANGUAGE plpgsql;
    
CREATE OR REPLACE FUNCTION delete_city_log()
    RETURNS TRIGGER AS $X$
    BEGIN
	INSERT INTO city_log(change_type, user_id, change_date, change_accepted)
	VALUES('delete', current_user, current_date, true);
	RETURN OLD;
	END
    $X$ LANGUAGE plpgsql;

CREATE TRIGGER on_city_update BEFORE UPDATE ON city
FOR EACH ROW EXECUTE PROCEDURE update_city_log();

CREATE TRIGGER on_city_insert_nowy BEFORE INSERT ON city
FOR EACH ROW EXECUTE PROCEDURE insert_city_log();

CREATE TRIGGER on_city_delete BEFORE DELETE ON city
FOR EACH ROW EXECUTE PROCEDURE delete_city_log();


--testy

--INSERT INTO city VALUES('test2', 'test', 'test', 10, 10, 10, 10);
--DELETE FROM city WHERE city.name = 'test2';
--UPDATE city SET name = 'test2' WHERE name ='test_update';
--UPDATE city SET name = 'test_update' WHERE name ='test2';


-- Zadanie 4

CREATE OR REPLACE FUNCTION update_city_log()
    RETURNS TRIGGER AS $X$
    BEGIN
    IF ((SELECT count(*) FROM (SELECT * FROM city_log ORDER BY change_id DESC LIMIT 10) as temp 
    WHERE user_id=current_user) < 10)
    THEN
       	INSERT INTO city_log(change_type, user_id, change_date, change_accepted)
        VALUES('update', current_user, current_date, true);
        RETURN NEW;
    ELSE
        INSERT INTO city_log(change_type, user_id, change_date, change_accepted)
        VALUES('update', current_user, current_date, false);
        RETURN NULL;
    END IF;
	END
    $X$ LANGUAGE plpgsql;
    

CREATE OR REPLACE FUNCTION insert_city_log()
    RETURNS TRIGGER AS $X$
    BEGIN
    IF ((SELECT count(*) FROM (SELECT * FROM city_log ORDER BY change_id DESC LIMIT 10) as temp
    WHERE user_id=current_user) < 10)
    THEN
       	INSERT INTO city_log(change_type, user_id, change_date, change_accepted)
        VALUES('insert', current_user, current_date, true);
        RETURN NEW;
    ELSE
        INSERT INTO city_log(change_type, user_id, change_date, change_accepted)
        VALUES('insert', current_user, current_date, false);
        RETURN NULL;
    END IF;
    END
    $X$ LANGUAGE plpgsql;
    
CREATE OR REPLACE FUNCTION delete_city_log()
    RETURNS TRIGGER AS $X$
    BEGIN
	IF ((SELECT count(*) FROM (SELECT * FROM city_log ORDER BY change_id DESC LIMIT 10) as temp
	WHERE user_id=current_user) < 10) 
	THEN
       	INSERT INTO city_log(change_type, user_id, change_date, change_accepted)
        VALUES('delete', current_user, current_date, true);
        RETURN OLD;
    ELSE
        INSERT INTO city_log(change_type, user_id, change_date, change_accepted)
        VALUES('delete', current_user, current_date, false);
        RETURN NULL;
    END IF;
	END
    $X$ LANGUAGE plpgsql;
