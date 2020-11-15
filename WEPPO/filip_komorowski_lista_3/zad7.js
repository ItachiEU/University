function fib() {
    var cur = 1;
    var prev = -1;

    return {
        next: function () {
            var temp = prev;
            prev = cur;
            cur += temp;
            return { value: cur, done: false }
        }
    }

}

function *fib1(){
    var cur = 1;
    var prev = -1;
    while(true){
        var temp = prev;
        prev = cur;
        cur += temp;
        yield cur;
    }
}


var _it = fib();
var __i = 0;
for (var _result; _result = _it.next(), !_result.done;) {
    console.log(_result.value);
    __i += 1;
    if (__i > 10)
        break;
}
__i=0
for(var i of fib1()){
    console.log(i);
    __i += 1;
    if (__i > 10)
        break;
}