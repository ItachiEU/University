CREATE TABLE workplace_v1 (
    id BIGSERIAL NOT NULL PRIMARY KEY ,
    nazwa_firmy VARCHAR(50) NOT NULL,
    miasto VARCHAR(50) NOT NULL,
    lokalizacja_biura VARCHAR(100) NOT NULL
);

CREATE TABLE employee_v1 (
    id BIGSERIAL NOT NULL PRIMARY KEY ,
    imie VARCHAR(50) NOT NULL,
    nazwisko VARCHAR(50) NOT NULL,
    plec varchar(10) NOT NULL,
    data_urodzenia DATE NOT NULL,
    email VARCHAR(150),
    pensja NUMERIC(19,2) NOT NULL,
    workplace_id BIGINT,
    FOREIGN KEY (workplace_id) REFERENCES workplace_v1(id)
);

INSERT INTO workplace_v1 (nazwa_firmy, miasto, lokalizacja_biura) VALUES ('Samsung', 'Waszawa', 'plac Europejski 1');
INSERT INTO workplace_v1 (nazwa_firmy, miasto, lokalizacja_biura) VALUES ('Nokia', 'Wrocław', 'Lotnicza 12');
INSERT INTO workplace_v1 (nazwa_firmy, miasto, lokalizacja_biura) VALUES ('Credit Suisse', 'Wrocław', 'Szczytnicka 9');

INSERT INTO employee_v1 (imie, nazwisko, plec, data_urodzenia, email, pensja, workplace_id)
VALUES ('Monika', 'Kaszuba', 'k', '1999-04-05', 'm.kaszuba@o2.pl', 3500, 1);
INSERT INTO employee_v1 (imie, nazwisko, plec, data_urodzenia, email, pensja, workplace_id)
VALUES ('Marek', 'Zdun', 'm', '1985-03-12', 'm.zdum@wp.pl', 5000, 3);
INSERT INTO employee_v1 (imie, nazwisko, plec, data_urodzenia, email, pensja, workplace_id)
VALUES ('Krzysztof', 'Kowalski', 'm', '1989-10-05', 'krzys.kowal@wp.pl', 4250, 1);
