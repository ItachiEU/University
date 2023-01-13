import { v4 } from 'uuid';

/**
 * Creates a new list of Products
 * @class
*/
export function List() {
   this.content = function(){
      return this.list;
   }

   /**  @type {Array.Product}*/
   this.list = [];

   /**
    * Adds a product to the list
    * @param {Product} product 
    * @returns {string}
   */
   this.addProduct = function (product) {
      product.id = v4();
      this.list.push(product);
      return product.id;
   };

   /**
    * Removes a product with given ID
    * @param {string} id 
   */
   this.removeProduct = function(id) {
      let index = this.list.map(e => e.id).indexOf(id);
      if (index == -1)
         return;
      this.list.splice(index, 1);      
   }

   /**
    * Edits a product with given id
    * @param {string} id 
    * @param {string} paramName
    * @param {string} newValue
   */
   this.editProduct = function(id, paramName, newValue) {
      let index = this.list.map(e => e.id).indexOf(id);
      if (index == -1)
         return;
      
      if (Object.keys(this.list[index].setters).includes(paramName)) {
         this.list[index].setters[paramName](newValue);
      }
      else {
         this.list[index][paramName] = newValue;
      }
   }

   /**
    * Swaps two products on given indices
    * @param {number} index1 
    * @param {number} index2 
    */
   this.swapProducts = function (index1, index2) {
      if (index1 < 0 || index1 >= this.list.length)
         return;
      if (index2 < 0 || index2 >= this.list.length)
         return;
      let p = this.list[index1];
      this.list[index1] = this.list[index2];
      this.list[index2] = p;
   }

   
   /**
    * Filters products that should be sold today
    * @returns {Products[]} - products that should be sold on this date
    */
   this.getProductsForToday = function(){
      let date = new Date();
      let [day, month, year] = [date.getDate(), date.getMonth(), date.getFullYear()];
      return this.list.filter(el => {
         let t = new Date(el.purchaseDate);
         return t.getFullYear() == year && t.getMonth() == month && t.getDate() == day;
      })
   }

   /**
    * Returns some of all prices of products sold on given date
    * @param {Date} date 
    * @returns {number}
    */
   this.getExpenseSummaryForDate = function (date) {
      let [day, month, year] = [date.getDate(), date.getMonth(), date.getFullYear()];
      let soldProductsFromDate = this.list.filter(el => {
         let t = new Date(el.purchaseDate);
         return t.getFullYear() == year && t.getMonth() == month && t.getDate() == day;
      }).filter(el => el.status);

      let result = -1;
      result = soldProductsFromDate.reduce((accumulator, currentValue) => {
         if (currentValue.price != undefined)
            return accumulator + currentValue.price * currentValue.count;
         else
            throw 'Undefined price';
      }, 0);
      return result;         
   }

   /**
    * Performs the action defined in callback on products with ids 
    * specified in the listOfIDs
    * @param {String[]} listOfIDs 
    * @param {callback} callback - accepts single Product and modifies it in place
    */
   this.massEditProducts = function (listOfIDs, callback) {
      this.list.filter(el => listOfIDs.includes(el.id)).map(callback);
   }
}

