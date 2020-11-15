let fs = require('fs');
let util = require('util')

fs.readFile('test.txt', 'utf-8', (err, data) => {
   if (err)
      throw err;
   //console.log(data);
   console.log('success1')
})


var readFilePromise = util.promisify(fs.readFile);

readFilePromise('test.txt', 'utf-8')
   .then((data) => {
      //console.log(data);
      console.log('success2')
   })
   .catch((err) => {
      throw err;
   })

async function callRF() {
   const data = await readFilePromise('test.txt', 'utf-8');
   console.log(data)
}


callRF();