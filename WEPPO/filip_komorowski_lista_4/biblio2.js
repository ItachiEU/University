module.exports = { func_2 };
let a = require('./biblio1.js');
function func_2(n) {
 if ( n > 0 ) {
 console.log( `biblio2: ${n}`);
 a.func_1(n-1);
 }
} 