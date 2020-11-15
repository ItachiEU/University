function forEach(tab, f) {
    for (let i = 0; i < tab.length; i++) {
        f(tab[i]);
    }
}

function filter(tab, f) {
    var ans = []
    for (let i = 0; i < tab.length; i++) {
        if (f(tab[i])) {
            ans.push(tab[i]);
        }
    }
    return ans;
}

function map(tab, f) {
    for (let i = 0; i < tab.length; i++) {
        tab[i] = f(tab[i]);
    }
    return tab;
}


let list = [1, 2, 3, 4, 5]
map(list, (a) => a * a);
forEach(list, (elem) => console.log(`${elem}`))
console.log('Nieparzyste: ', filter(list, (i) => i % 2 == 1));