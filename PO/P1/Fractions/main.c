#include "ulamek.h"

int main(){
	Ulamek *a, *b;
	a = malloc(sizeof(Ulamek));
	b = malloc(sizeof(Ulamek));
	set_up(a, 2, 4);
	set_up(b, 2, 6);

	Ulamek *result = dodaj(a, b);
	show(result);

	result = odejmij(a, b);
	show(result);

	show(b);

	dodaj_drugi(result, b);
	show(b);

	show(pomnoz(result, b));

	show(a);

	pomnoz_drugi(a,b);

	show(b);

	show(podziel(a, b));

	podziel_drugi(a, b);

	show(b);
	free(a);
	free(b);
	free(result);
}