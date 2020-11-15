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


function* take(it, top) {
    var i = 0;
    while (i < top) {
        i += 1;
        yield it.next().value;
    }
}

for (let i of take(fib1(), 10)) {
   console.log(i);
}