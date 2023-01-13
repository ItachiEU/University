import { List } from './List.js';
import { Product } from './Product.js';

let l = new List();
let p = new Product('test', 5, new Date().toString(), 'true', 13);
let s = new Product('test2', 6, new Date('2022-11-19').toString(), 'true', 9);
let r = new Product('test3', 3, new Date().toString(), 'true', 7);

let [id1, id2, id3] = [l.addProduct(p), l.addProduct(s), l.addProduct(r)];

// console.log(l.content());

// l.removeProduct(id);

// console.log(l.content());

// id = l.addProduct(p);

// console.log(l.content())

// l.editProduct(id, 'count', '15');
// l.editProduct(id, 'name', 'Test edit name');
// l.editProduct(id, 'purchaseDate', 'Sun Nov 20 2022 06:47:53 GMT-0500 (Eastern Standard Time)');
// l.editProduct(id, 'status', 'True');
// l.editProduct(id, 'price', '15.4');
// console.log(l.content());


// console.log(l.content());

// l.swapProducts(0, 2);
// console.log(l.content());
// console.log(l.getProductsForToday());

console.log(l.getExpenseSummaryForDate(new Date()));

function cb(product) {
   product.price *= -1.0;
}

// function cb(product) {
//    product.name = 'MASS MODIFICATION'
// }

l.massEditProducts([id1, id3], cb);

console.log(l.content())