const libraryStore = [];

String.prototype.capitalize = function() {
  return this.length === 0 ? '' : this[0].toUpperCase() + this.slice(1)
}

const capitalize = (str) => {
   return str.length === 0 ? '' : str[0].toUpperCase() + str.slice(1);
}

function capitalizeSentence(str) {
   return str.split(' ').map(capitalize).join(' ');
}

console.log(capitalizeSentence('alice')) // 'Alice'
console.log(capitalizeSentence('alice in Wonderland')) // 'Alice In Wonderland'

class Media {

  constructor(props) {
    this._title = capitalizeSentence(props.title);
    this._ratings = [];
    this._available = true;
  }
   
  getTitle() {
     return this._title;
  }
   
  getRatings() {
     return this._ratings;
  }
   
  getAvailable() {
     return this._available;
  }

  addRating(rating) {
     this._ratings.push(rating);
  }

  orderMedia (){
    return new Promise((resolve, reject) => {
      if (this._available) {
        setTimeout(function () {
          this._available = false;
          resolve();
        }, 1000)
        return;
      }

      reject("Not available")
    })
  }

  returnMedia(){
    return new Promise((resolve, reject) => {
      if (!this._available) {
        setTimeout(function () {
          this._available = true;
          resolve();
        }, 1000)
        return;
      }

      reject("Already returned")
    })
  }
}

const media = new Media({title: 'alice in wonderland'})
console.log(media.getTitle()) // 'Alice In Wonderland'
console.log(media.getRatings()) // []
console.log(media.getAvailable()) // true


media.addRating(9)
media.addRating(8.5)
console.log(media.getRatings()) // [9, 8.5]

media.title = "not alice"
media.ratings = [1, 1]
media.available = false
console.log(media.getTitle())
console.log(media.getRatings())
console.log(media.getAvailable())

async function test() {
  await media.orderMedia().catch(e =>console.log(e))
  console.log(media.getAvailable()) // false

  await media.returnMedia().catch(e =>console.log(e))
  console.log(media.getAvailable()) // true
}
test()

class Book {
  constructor(props) {
    this.title = capitalizeSentence(props.title);
    this.author = capitalizeSentence(props.author);
    this.pages = props.pages;
    this.ratings = [];
    this.available = true;
  }

  orderBook() {
    return new Promise((resolve, reject) => {
      if (this.available) {
        setTimeout(function() {
          this.available = false;
          resolve();
        }, 1000)
        return;
      }

      reject("Not available")
    })
  }

  returnBook() {
    return new Promise((resolve, reject) => {
      if (!this.available) {
        setTimeout(function() {
          this.available = true;
          resolve();
        }, 1000)
        return;
      }

      reject("Already returned")
    })
  }
}

const addToLibrary = (props) => {
  switch(props.type) {
    case "book": 
      const media = new Book(props)
      libraryStore.push(media)
      return media;
    case "movie": 
      const media = new Movie(props)
      libraryStore.push(media)
      return media;
    default: 
      const media = new Media(props);
      libraryStore.push(media)
      return media;
  }
}

function order(title) {
  for (let i = 0; i < libraryStore.length; i++) {
    if (libraryStore[i].title === title) {
      libraryStore[i].orderMedia().then(
        console.log("Order completed!")
      ).catch((e) => {
        console.log("Sorry! " + e)
      })
    }
  }
}