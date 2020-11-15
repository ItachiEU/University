
function MyGenerator(n) {
    return function createGenerator() {
        var _state = 0;
        return {
            next : function() {
                return {
                value : _state,
                done : _state ++ >= n
                }
            }
        }
    }
}

var foo = {
    [Symbol.iterator] : MyGenerator(5)
};
var foo1 = {
   [Symbol.iterator]: MyGenerator(3)
}
var foo2 = {
   [Symbol.iterator]: MyGenerator(10)
}

for ( var f of foo ) {
    console.log(f);
}
for ( var f of foo1 ) {
    console.log(f);
}
for ( var f of foo2 ) {
    console.log(f);
}