module.exports = { func_1 };

let b = require('./biblio2.js');

function func_1(n) {
 if ( n > 0 ) {
 console.log( `biblio1: ${n}`);
 b.func_2(n-1);
 }
} 