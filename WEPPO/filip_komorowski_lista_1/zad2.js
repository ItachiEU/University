function numbers() {
  let arr = [];
  for (let i = 1; i <= 100000; i++) {
    let temp = i,
      ok = true;
    let dividers = [];
    while (temp >= 1) {
      dividers.push(temp % 10);
      temp = parseInt(temp / 10);
    }
    temp = i;
    for (let i = 0; i < dividers.length; i++) {
      if (dividers[i] == 0 || temp % dividers[i] != 0) {
        ok = false;
        break;
      }
    }
    if (!ok) continue;
    let sumD = dividers.reduce((a, b) => a + b, 0);
    if (temp % sumD == 0) arr.push(temp);
  }
  return arr;
}

console.log(numbers());
