/**
 * Creates a new Product
 * @class
 * @param {string} name - Self explanatory
 * @param {number} count - how many are available
 * @param {Date} purchase_date - by this time the product should have been sold
 * @param {string} status - is sold
 * @param {number} [price=undefined] - product's price
 * 
*/
export function Product(name, count, purchaseDate, status, price = undefined) {
   this.setName = function(name) {
      this.name = name;
   }
   this.setCount = function (count) {
      this.count = parseInt(count);
   }
   this.setPurchaseDate = function (purchaseDate) {
      this.purchaseDate = Date.parse(purchaseDate)
   }
   this.setStatus = function (status) {
      this.status = JSON.parse(status.toLowerCase());
   }
   this.setPrice = function (price) {
      if(this.status == true)
         this.price = parseFloat(price);
      else
         throw "Can't set price to unsold item"
   }
   this.setters = {
      "name": this.setName.bind(this),
      "count": this.setCount.bind(this),
      "purchaseDate": this.setPurchaseDate.bind(this),
      "price": this.setPrice.bind(this),
      "status": this.setStatus.bind(this)
   }
   this.setName(name);
   this.setCount(count);
   this.setPurchaseDate(purchaseDate);
   this.setStatus(status);
   if (price != undefined)
      this.setPrice(price);
   return this;
}