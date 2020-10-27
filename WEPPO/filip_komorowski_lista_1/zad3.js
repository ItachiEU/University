function primes() {
  let arr = [2];
  for (let i = 3; i <= 100000; i++) {
    let ok = true;
    for (let j = 2; j < i; j++) {
      if (i % j == 0) {
        ok = false;
        break;
      }
    }
    if (ok) arr.push(i);
  }
  return arr;
}

console.log(primes());
