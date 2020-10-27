function fib_iter(n) {
  let last = 1,
    b4last = 1;
  for (let i = 3; i <= n; i++) {
    let temp = last;
    last = last + b4last;
    b4last = temp;
  }
  return last;
}

function fib_rec(n) {
  if (n == 0) return 0;
  if (n == 1) return 1;
  return fib_rec(n - 1) + fib_rec(n - 2);
}

for (let i = 10; i < 50; i++) {
  console.log("n: ", i);
  console.time("iteracyjny");
  fib_iter(i);
  console.timeEnd("iteracyjny");
  console.time("recursive");
  fib_rec(i);
  console.timeEnd("recursive");
}

//node.js -> Rekurencyjny do n = 40 jeszcze jakos sobie radzi, potem czasy zaczynaja przekraczac sekunde co przestaje miec sens

//Przy testowaniu w przegladarce chrome czasy są minimalnie większe

//Przy testowaniu w przeglądarce opera, wyniki są najgorsze, ale roznice nadal minimalne
