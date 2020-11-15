function fib(n) {
    let memo = {0: 0, 1: 1};
    function helper(m) {
        if (typeof memo[m] == 'undefined') {
            memo[m] = helper(m-1) + helper(m-2);
        }
        return memo[m]
    }
    return helper(n) 
}

function regularFib(n) {
    if(n == 0) return 0;
    if(n == 1) return 1;
    return regularFib(n - 1) + regularFib(n - 2);
}

function countTime(n) {
    console.time("fib1");
    console.log('Regular fibonacci: ')
    console.log(n, ' -> ', regularFib(n))
    console.timeEnd("fib1");

    console.log()
    console.time("fib2");
    console.log('Improved fibonacci: ')
    console.log(n, ' -> ', fib(n))
    console.timeEnd("fib2");
}

countTime(35)