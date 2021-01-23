 
CREATE TABLE workplace_v2 (
    id BIGSERIAL NOT NULL PRIMARY KEY ,
    nazwa_firmy VARCHAR(50) NOT NULL,
    miasto VARCHAR(50) NOT NULL,
    lokalizacja_biura VARCHAR(100) NOT NULL
);

CREATE TABLE employee_v2 (
    id BIGSERIAL NOT NULL PRIMARY KEY ,
    imie VARCHAR(50) NOT NULL,
    nazwisko VARCHAR(50) NOT NULL,
    plec varchar(10) NOT NULL,
    data_urodzenia DATE NOT NULL,
    email VARCHAR(150),
    pensja NUMERIC(19,2) NOT NULL
);

CREATE TABLE workplaces_employees (
  worklace_id BIGINT NOT NULL,
  employee_id BIGINT NOT NULL,
  PRIMARY KEY (worklace_id, employee_id),
  FOREIGN KEY (worklace_id) REFERENCES workplace_v2(id),
  FOREIGN KEY (employee_id) REFERENCES employee_v2(id)
);

INSERT INTO workplace_v2 (nazwa_firmy, miasto, lokalizacja_biura) VALUES ('Samsung', 'Waszawa', 'plac Europejski 1');
INSERT INTO workplace_v2 (nazwa_firmy, miasto, lokalizacja_biura) VALUES ('Nokia', 'Wrocław', 'Lotnicza 12');
INSERT INTO workplace_v2 (nazwa_firmy, miasto, lokalizacja_biura) VALUES ('Credit Suisse', 'Wrocław', 'Szczytnicka 9');

INSERT INTO employee_v2 (imie, nazwisko, plec, data_urodzenia, email, pensja)
VALUES ('Monika', 'Kaszuba', 'k', '1999-04-05', 'm.kaszuba@o2.pl', 3500);
INSERT INTO employee_v2 (imie, nazwisko, plec, data_urodzenia, email, pensja)
VALUES ('Marek', 'Zdun', 'm', '1985-03-12', 'm.zdum@wp.pl', 5000);
INSERT INTO employee_v2 (imie, nazwisko, plec, data_urodzenia, email, pensja)
VALUES ('Krzysztof', 'Kowalski', 'm', '1989-10-05', 'krzys.kowal@wp.pl', 4250);

INSERT INTO workplaces_employees (worklace_id,employee_id) VALUES (1,3);
INSERT INTO workplaces_employees (worklace_id,employee_id) VALUES (1,2);
INSERT INTO workplaces_employees (worklace_id,employee_id) VALUES (3,3);
INSERT INTO workplaces_employees (worklace_id,employee_id) VALUES (2,1);

SELECT employee_v2.id, employee_v2.imie
FROM employee_v2 INNER JOIN workplaces_employees
ON workplaces_employees.employee_id = employee_v2.id
WHERE workplaces_employees.worklace_id = 1;