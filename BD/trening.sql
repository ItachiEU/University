SELECT DISTINCT 
u.nazwisko,pierwszy_zapis(u.kod_uz,s.semestr_id) 
FROM uzytkownik u JOIN wybor w USING(kod_uz) 
    JOIN grupa g USING(kod_grupy)
    JOIN przedmiot_semestr ps USING(kod_przed_sem)
    JOIN semestr s USING(semestr_id)
WHERE s.nazwa='Semestr zimowy 2016/2017' AND

      u.nazwisko LIKE 'A%'
ORDER BY 2; 



CREATE FUNCTION pierwszy_zapis(int,int)

     RETURNS wybor.data%TYPE 

AS $X$
    SELECT min(data)
    FROM wybor
         JOIN grupa USING(kod_grupy)
         JOIN przedmiot_semestr USING(kod_przed_sem)
    WHERE wybor.kod_uz=$1 AND semestr_id=$2;
$X$ LANGUAGE SQL STABLE;

CREATE OR REPLACE FUNCTION przydziel_praktyki() RETURNS VOID

AS $X$
DECLARE osoba student;
       ofertap int;
BEGIN
  FOR osoba IN
      SELECT *

      FROM student

      WHERE kod_uz NOT IN
           (SELECT student FROM praktyki)

            AND semestr BETWEEN 6 AND 10
 LOOP
    SELECT max(kod_oferty) INTO ofertap

    FROM oferta_praktyki
   WHERE liczba_miejsc>0;
   

    IF (ofertap IS NULL) THEN EXIT; END IF;
   

    UPDATE oferta_praktyki
    SET liczba_miejsc=liczba_miejsc-1
   WHERE kod_oferty=ofertap;
   

    INSERT INTO praktyki(student,oferta)

    VALUES(osoba.kod_uz,ofertap);
 END LOOP;
END
$X$ LANGUAGE plpgsql;
