var fs = require('fs');
var https = require('https'); 

https.createServer((req, res) => {
   res.setHeader('Content-type', 'text/html; charset=utf-8');
   res.setHeader('Content-Disposition', 'attachment; filename="test.txt"');
   res.end(`hello there ${new Date()}`);
}).listen(5000);

console.log('started')