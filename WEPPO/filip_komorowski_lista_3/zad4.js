function createFs(n) {
    var fs = []; //poprawna wersja z var

    var nested = function nested(i) {
        fs[i] = function () {
            return i;
        };
    };

    for (var i = 0; i < n; i++) {
        nested(i);
    };
    return fs;
}

var myfs = createFs(10);
console.log( myfs[0]() ); 
console.log( myfs[2]() );
console.log( myfs[7]() );