const { Client } = require('pg');
const client = new Client({
    user: "postgres",
    password: "postgres",
    host: "localhost",
    port: 5432,
    database: "test"
});

// Zadanko 4 i 5

async function insertOneToMany(){
    var workplaceId;
    const wrokpalce = {
        values: ['Amazon', 'Wrocław', 'Kaszubska 16'],
        text: "INSERT INTO workplace_v1 (nazwa_firmy, miasto, lokalizacja_biura) VALUES ($1, $2, $3) RETURNING id"
    }
    const employee = {
        values: ['Tomasz', 'Kot','m','1991-12-12','t.kot91@gmail.com', 5000],
        text: "INSERT INTO employee_v1 (imie, nazwisko, plec, data_urodzenia, email, pensja, workplace_id) VALUES ($1, $2, $3, $4, $5, $6, $7) RETURNING *"
    }
    try{
        var workResult = await client.query(wrokpalce);
        workplaceId = workResult.rows[0].id;
        console.log(`New workplace is: ${workplaceId}`);
        employee.values.push(workplaceId);
        var employeeResult = await client.query(employee);
        console.log(`New emloyee is:`);
        console.log(JSON.stringify(employeeResult.rows[0], null, 2));
    }catch(err){
        console.error(err);
    }
};

async function insertManyToMany(){
    var workplaceId;
    const wrokpalce = {
        values: ['Google', 'Warszawa', 'Emilii Plater 53'],
        text: "INSERT INTO workplace_v2 (nazwa_firmy, miasto, lokalizacja_biura) VALUES ($1, $2, $3) RETURNING id"
    }
    const employee = {
        values: ['Zuzanna', 'Broniarek','m','1997-11-05','zuzanna.bron@gmail.com', 12500],
        text: "INSERT INTO employee_v2 (imie, nazwisko, plec, data_urodzenia, email, pensja) VALUES ($1, $2, $3, $4, $5, $6) RETURNING id"
    }
    const relation = {
        values: [],
        text: "INSERT INTO workplaces_employees (worklace_id,employee_id) VALUES ($1,$2)"
    }
    try{
        var workResult = await client.query(wrokpalce);
        workplaceId = workResult.rows[0].id;
        relation.values.push(workplaceId);
        console.log(`New workplace is: ${workplaceId}`);
        var employeeResult = await client.query(employee);
        employeeId = employeeResult.rows[0].id;
        relation.values.push(employeeId);
        console.log(`New emloyee is: ${employeeId}`);
        await client.query(relation);
        console.log(`New relation between workplace ${workplaceId} and employee ${employeeId}`)
    }catch(err){
        console.error(err);
    }
};

async function main2(){
    try{
        await client.connect()
        console.log("Connected successfuly");
        await insertOneToMany();
        await insertManyToMany();
    }finally{
        await client.end();
        console.log("Disconnected successfuly");
    }
};

main2();