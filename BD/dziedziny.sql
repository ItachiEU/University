CREATE DOMAIN semestry AS varchar(10)
NOT NULL
CHECK (VALUE IN ('zimowy', 'letni'));

INSERT INTO test VALUES('czerwony');

SELECT * FROM test;

CREATE SEQUENCE numer_semestru;
SELECT setval('numer_semestru',max(semestr_id)) FROM semestr;
ALTER TABLE semestr ALTER COLUMN semestr_id SET DEFAULT nextval('numer_semestru');
ALTER SEQUENCE numer_semestru OWNED BY semestr.semestr_id;

ALTER TABLE semestr ADD COLUMN semestr semestry DEFAULT 'zimowy';

UPDATE semestr SET semestr='letni' WHERE nazwa LIKE '%letni%';

UPDATE semestr SET rok = substring( nazwa FROM position('/' IN nazwa)-4 FOR 9);
ALTER TABLE semestr ALTER COLUMN semestr DROP DEFAULT;

ALTER TABLE semestr ALTER COLUMN semestr SET DEFAULT
 CASE WHEN extract(month FROM current_date) BETWEEN 1 AND 6
   THEN 'letni' ELSE 'zimowy'
 END;

ALTER TABLE semestr ALTER COLUMN rok SET DEFAULT
 CASE WHEN extract(month FROM current_date) BETWEEN 1 AND 6
   THEN extract(year FROM current_date)-1||'/'||extract(year FROM current_date)
   ELSE extract(year FROM current_date)||'/'||extract(year FROM current_date)+1
 END;
 
 
INSERT INTO semestr(semestr,rok) VALUES ('zimowy','2018/2019'), ('letni','2018/2019');


CREATE SEQUENCE numer_przedmiot_semestr;
SELECT setval('numer_przedmiot_semestr',max(kod_przed_sem)) FROM przedmiot_semestr;
ALTER TABLE przedmiot_semestr

   ALTER COLUMN kod_przed_sem

   SET DEFAULT nextval('numer_przedmiot_semestr');
ALTER SEQUENCE numer_przedmiot_semestr

   OWNED BY przedmiot_semestr.kod_przed_sem;
   
INSERT INTO przedmiot_semestr    

   (semestr_id,kod_przed,strona_domowa, angielski)

   SELECT s1.semestr_id, p.kod_przed, strona_domowa, angielski
  FROM semestr s1,

        przedmiot p JOIN

        przedmiot_semestr ps USING(kod_przed) JOIN

        semestr s USING(semestr_id)

   WHERE rodzaj IN ('p', 'o') AND

         s.rok='2016/2017' AND

         s.semestr=s1.semestr AND

         s1.rok='2018/2019';   
