DROP TABLE IF EXISTS Segment;
DROP type IF EXISTS flight_segment Cascade;

CREATE TABLE IF NOT EXISTS Segment
 (flight_id NUMERIC,
  takeoff_airport_id VARCHAR(3),
  landing_airport_id VARCHAR(3),
  takeoff_time timestamp with time zone,
  landing_time timestamp with time zone,
  CHECK (flight_id IS NOT NULL));

DROP TABLE IF EXISTS AirportLocation CASCADE;
DROP TABLE IF EXISTS CityGeo CASCADE;

CREATE TABLE AirportLocation
 (airport_id VARCHAR(3),
  longitude numeric,
  latitude numeric
 );

 CREATE TABLE CityGeo(
   city_name VARCHAR(50),
   prov VARCHAR(50),
   country VARCHAR(4),
   pt geography
 );

CREATE TYPE flight_segment as (
  flight_id int,
  takeoff_airport_id VARCHAR(3),
  landing_airport_id VARCHAR(3),
  takeoff_time timestamp with time zone
);

INSERT INTO AirportLocation(airport_id, longitude, latitude) SELECT iatacode, longitude, latitude FROM airport;

INSERT INTO CityGeo(city_name, prov, country, pt) SELECT city.name, city.province, city.country, CONCAT('POINT(',longitude,' ',latitude,')')::geography FROM city;

CREATE INDEX airport_index ON AirportLocation using Gist(airport_id);
CREATE INDEX city_geo_index on CityGeo using Gist(city_name);

CREATE OR REPLACE FUNCTION list_flights_helper(id int)
RETURNS SETOF flight_segment AS 
$X$
  DECLARE
  seg1 segment;
  seg2 segment;
  lat1 decimal;
  lat2 decimal;
  lat3 decimal;
  lat4 decimal;
  long1 decimal;
  long2 decimal;
  long3 decimal;
  long4 decimal;

  distance numeric;

  res flight_segment;

  BEGIN

  FOR seg1 IN SELECT * FROM segment WHERE flight_id = id
  LOOP
    FOR seg2 IN SELECT * FROM segment
    LOOP
      SELECT latitude, longitude INTO lat1, long1 FROM AirportLocation WHERE airport_id = seg1.takeoff_airport_id;
      SELECT latitude, longitude INTO lat2, long2 FROM AirportLocation WHERE airport_id = seg1.landing_airport_id;
      SELECT latitude, longitude INTO lat3, long3 FROM AirportLocation WHERE airport_id = seg2.takeoff_airport_id;
      SELECT latitude, longitude INTO lat4, long4 FROM AirportLocation WHERE airport_id = seg2.landing_airport_id;

      SELECT ST_Distance(CONCAT('LINESTRING(',long1,' ',lat1,',',long2,' ',lat2,')')::geography, CONCAT('LINESTRING(',long3,' ',lat3,',',long4,' ',lat4,')')::geography)/1000 into distance;

      IF(distance = 0 AND seg2.flight_id != id) 
      THEN
        SELECT seg2.flight_id, seg2.takeoff_airport_id, seg2.landing_airport_id, seg2.takeoff_time INTO res;
        RETURN NEXT res;
      END IF;
    END LOOP;
  END LOOP;
  END;
$X$ LANGUAGE plpgsql;

CREATE OR REPLACE FUNCTION list_flights(id int) RETURNS SETOF
 flight_segment AS 
 $X$
 BEGIN
  RETURN QUERY SELECT DISTINCT flight_id,takeoff_airport_id,landing_airport_id,takeoff_time 
  FROM list_flights_helper(id) ORDER BY takeoff_time DESC, flight_id ASC;
 END
 $X$ LANGUAGE plpgsql;

CREATE OR REPLACE FUNCTION list_cities_helper(id int, dist int)
RETURNS SETOF CityGeo AS 
$X$
  DECLARE
  seg segment;
  miasto CityGeo;
  distance numeric;
  res CityGeo;
  lat1 decimal;
  lat2 decimal;
  long1 decimal;
  long2 decimal;
  punkcik geography;

  BEGIN

  FOR miasto in SELECT * FROM CityGeo
  LOOP
    FOR seg IN SELECT * FROM segment WHERE flight_id = id
    LOOP
      SELECT latitude, longitude INTO lat1, long1 FROM AirportLocation WHERE airport_id = seg.takeoff_airport_id;
      SELECT latitude, longitude INTO lat2, long2 FROM AirportLocation WHERE airport_id = seg.landing_airport_id;

      SELECT pt INTO punkcik FROM CityGeo where city_name = miasto.city_name and prov = miasto.prov;

      SELECT ST_Distance(CONCAT('LINESTRING(',long1,' ',lat1,',',long2,' ',lat2,')')::geography, punkcik)/1000 into distance;

      IF (distance < dist) THEN
        SELECT miasto.city_name, miasto.prov, miasto.country INTO res;
        RETURN NEXT res;
      END IF;
    END LOOP;
  END LOOP;
  END;
$X$ LANGUAGE plpgsql;

CREATE OR REPLACE FUNCTION list_cities(id int, dist int) RETURNS SETOF
 CityGeo AS 
 $X$
 BEGIN
  RETURN QUERY SELECT DISTINCT city_name, prov, country, 'POINT(1 1)'::geography
  FROM list_cities_helper(id, dist) ORDER BY city_name ASC;
 END
 $X$ LANGUAGE plpgsql;

DROP TYPE IF EXISTS id_dist CASCADE; 

CREATE TYPE id_dist as (
  rid int,
  mdist int,
  takeoff_time timestamp with time zone
);

CREATE OR REPLACE FUNCTION list_city_helper(cname VARCHAR(50), province VARCHAR(50), ctry VARCHAR(4), n int, dist int) RETURNS SETOF id_dist as
$X$
DECLARE 
citypoint geography;
seg segment;
lat1 decimal;
lat2 decimal;
long1 decimal;
long2 decimal;
distance numeric;
res id_dist;

BEGIN
  SELECT pt INTO citypoint FROM CityGeo WHERE CityGeo.city_name = cname AND CityGeo.prov = province AND CityGeo.country = ctry;
  FOR seg IN SELECT * FROM segment 
  LOOP
    SELECT latitude, longitude INTO lat1, long1 FROM AirportLocation WHERE airport_id = seg.takeoff_airport_id;
    SELECT latitude, longitude INTO lat2, long2 FROM AirportLocation WHERE airport_id = seg.landing_airport_id;

    SELECT ST_Distance(CONCAT('LINESTRING(',long1,' ',lat1,',',long2,' ',lat2,')')::geography, citypoint)/1000 into distance;

    IF (distance < dist) THEN
    SELECT seg.flight_id, round(distance), seg.takeoff_time INTO res;
    RETURN NEXT res;
    END IF;

  END LOOP;
END
$X$ LANGUAGE plpgsql;

CREATE OR REPLACE FUNCTION list_city(cname VARCHAR(50), prov VARCHAR(50), country VARCHAR(4), n int, dist int) RETURNS SETOF
id_dist AS 
$X$
BEGIN
  RETURN QUERY SELECT DISTINCT rid, mdist, takeoff_time
  FROM list_city_helper(cname, prov, country, n, dist) ORDER BY takeoff_time DESC, rid ASC LIMIT n;
END
$X$ LANGUAGE plpgsql;

COMMIT;