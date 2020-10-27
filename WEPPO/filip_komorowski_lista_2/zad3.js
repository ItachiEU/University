console.log( (![]+[])[+[]] + (![]+[])[+!+[]] + ([![]]+[][[]])[+!+[]+[+[]]] + (![]+[])[!+[]+!+[]] );

// pierwszy fragment wylicza się do false[0] czyli f
//f
// drugi fragment -> +!+[] wylicza sie do negacja z 0 czyli true + 0 czyli 1, czyli false[1] czyli 'a'
//fa
//trzeci fragment -> [![]]+[][[]] wylicza się do false + undefined czyli falseundefined, +!+[]+[+[]] wylicz się do 1 + '0 czyli '10', wiec mamy falseundefined[10] -> i
//fai
//czwarty fragment -> analogicznie jak w drogim mamy false[!+[]+!+[]], czyli false[2] czyli 'l'
//Otrzymujemy -> 'fail'
