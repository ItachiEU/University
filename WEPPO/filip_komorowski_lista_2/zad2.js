let obj = {}
let b = {
   foo: 'o'
}

obj.foo = 1
obj['fo' + 'o'] = 2
obj['fo o'] = 3
console.log(obj.foo, obj['fo o'])

// [] pozwala nam odwoływać się do wyrażenia oraz do kluczy zawierających w sobie spacje, a . nie

obj[7] = 4
console.log(obj[7])
console.log(Object.keys(obj))

// jesli argumentem jest liczba, jest ona rzutowana na stringa

obj[b] = 3
console.log(obj[b])
console.log(Object.keys(obj))

//jesli argumentem jest objekt, jest on rownie rzutowany do stringa metodą toString()
//programista moze nadpisac funkcje toString danego objektu aby dopasowac ja do swoich potrzeb

let arr = [10, 11, 12, 13]

console.log(arr['1'])
console.log(arr['01'])
//Arrays cannot use strings as element indexes (as in an associative array) but must use integers. Setting or accessing via non-integers using bracket notation (or dot notation) will not set or retrieve an element from the array list itself, but will set or access a variable associated with that array's object property collection
//Using an invalid index number returns undefined.
// jesli ustawimy atrybut length na wartosc wieksza niz faktyczna, zostana do tabliy dodane puste komórki
// jesli zmniejszymy length, elementy zostana usuniete