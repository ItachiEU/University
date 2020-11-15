function sum() {
   return Array.from(arguments).reduce((prev, curr) => prev + curr, 0);
}

console.log(sum(1, 2, 3, 4));