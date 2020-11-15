var o = {
   p: 7,
   f: function () {
      return 1;
   },
   get bar() {
      return this.p;
   },
   set bar(x) {
      this.p = x;
   }
}
//Trying it out:
console.log(o.bar);

o.bar = 3;

console.log(o.bar);

//nowe pole

o.nowe_pole = 5;
o.nowa_metoda = function () {
   return "nowa metoda";
}


//Wlasciwosci musza byc dadane ta metoda
Object.defineProperty(o, "nowa_wlasciwosc", {
   get: function () { return value },
   set: function (x) { value = x }
});
o.nowa_wlasciwosc = 5;
console.log(o.nowa_wlasciwosc)
console.log(o);