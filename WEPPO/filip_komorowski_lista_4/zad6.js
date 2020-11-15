const readline = require('readline');
const fs = require('fs');

const rl = readline.createInterface({
  input: fs.createReadStream('logi.txt'),
  crlfDelay: Infinity
});


var data = {};
rl.on('line', (line) => {
    const ip = line.split(' ')[1];
    if (data[ip] !== undefined)
        data[ip]++;
    else
        data[ip] = 1;
}).on('close',() => {
    var res = [];
    for (var ip in data) {
        res.push([ip, data[ip]]);
    }
    
    res.sort(function(a, b) {
        return b[1] - a[1];
    });   

    [0,1,2].forEach((ip)=> console.log(res[ip][0], data[res[ip][0]]))
})