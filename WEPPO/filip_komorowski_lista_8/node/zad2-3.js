const { Client } = require('pg');
const client = new Client({
    user: "postgres",
    password: "postgres",
    host: "localhost",
    port: 5432,
    database: "test"
});

//Zadanka 2 i 3

async function getData(){  
    try{
        var {rows} = await client.query("SELECT * FROM person_v2");
        await console.table(rows);
    } catch(err){
        console.error(err);
    }
};

async function insertData(){
    const query = {
        values: ['Monika', 'Baran','k','1986-03-12', 'monika.baran@gmail.com'],
        text: "INSERT INTO person_v2 (imie, nazwisko, plec, data_urodzenia, email) VALUES($1, $2, $3, $4, $5) RETURNING id"
    }
    try{
        var result = await client.query(query);
        var newId = result.rows[0].id;
        console.log(`New id is: ${newId}`);
    }catch(err){
        console.error(err);
    }
}

async function deleteData(){
    var idNumber = 7;
    try{
        await client.query(`DELETE FROM person_v2 WHERE id = ${idNumber}`);
        console.log(`Deleted second number ${idNumber} successfuly`);
    }catch(err){
        console.log(err);
    }   
}

async function updateData(){
    try{
        await client.query(`UPDATE person_v2 SET email = 'maria.polak@o2.pl' WHERE nazwisko = 'Polak'`);
        console.log(`Updated successfuly`);
    }catch(err){
        console.log(err);
    }   
}

async function main(){
    try{
        await client.connect()
        console.log("Connected successfuly");
        await getData();
        await insertData();
        await deleteData();
        await updateData();
        await getData();
    }finally{
        await client.end();
        console.log("Disconnected successfuly");
    }
};

main();