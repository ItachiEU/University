CREATE SEQUENCE person_id_seq;
CREATE TABLE person_v1 (
    id INT DEFAULT NEXTVAL('person_id_seq'),
    imie VARCHAR(50) NOT NULL,
    nazwisko VARCHAR(50) NOT NULL,
    plec varchar(10) NOT NULL,
    data_urodzenia DATE NOT NULL,
    email VARCHAR(150)
);

INSERT INTO person_v1 (imie, nazwisko, plec, data_urodzenia) VALUES (
    'Julia', 'Kowalska','k','1998-04-05');
INSERT INTO person_v1 (imie, nazwisko, plec, data_urodzenia) VALUES (
    'Stefan', 'Kowalski','m','1986-03-12');

/* if no DEFAULT NEXTVAL()*/
INSERT INTO person_v1 VALUES (nextval('serial'), 'Julia', 'Kowalska','k','1998-04-05');

SELECT * FROM person_v1;

CREATE TABLE person_v2 (
    id BIGSERIAL NOT NULL PRIMARY KEY ,
    imie VARCHAR(50) NOT NULL,
    nazwisko VARCHAR(50) NOT NULL,
    plec varchar(10) NOT NULL,
    data_urodzenia DATE NOT NULL,
    email VARCHAR(150)
);

INSERT INTO person_v2 (imie, nazwisko, plec, data_urodzenia) VALUES (
    'Katarzyna', 'Kowalska','k','1999-04-05');
INSERT INTO person_v2 (imie, nazwisko, plec, data_urodzenia, email) VALUES (
    'Krzysztof', 'Borowski','m','1986-03-12', 'kbr@gmail.com');

SELECT * FROM person_v2;