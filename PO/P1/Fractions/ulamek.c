#include "ulamek.h"

void show(Ulamek* a){
	printf("%d/%d\n", a->licznik, a->mianownik);
}


int NWD(int a, int b){
	if (a == 0) 
        return b; 
    return NWD(b % a, a); 
}

void skracanie(Ulamek *a){
	int temp = NWD(a->licznik, a->mianownik);
	a->licznik /= temp;
	a->mianownik /= temp;
}
void set_up(Ulamek* a, int licznik, int mianownik){
	a->licznik = licznik;
	a->mianownik = mianownik;
	skracanie(a);
	if(a->mianownik < 0){
		a->licznik *= -1;
		a->mianownik *=-1;
	}
}
Ulamek* dodaj(Ulamek *a, Ulamek *b){

	Ulamek *result = malloc(sizeof(Ulamek));
	
	set_up(result, a->licznik*b->mianownik+b->licznik*a->mianownik, a->mianownik*b->mianownik);
	skracanie(result);

	return result;
}
Ulamek* odejmij(Ulamek *a, Ulamek *b){

	Ulamek *result = malloc(sizeof(Ulamek));
	
	set_up(result, a->licznik*b->mianownik-b->licznik*a->mianownik, a->mianownik*b->mianownik);
	skracanie(result);

	return result;
}
void dodaj_drugi(Ulamek *a, Ulamek *b){
	Ulamek temp = *a;
	temp.licznik = a->licznik*b->mianownik + b->licznik*a->mianownik;
	temp.mianownik = a->mianownik*b->mianownik;
	*b = temp;
	skracanie(b);
}
void odejmij_drugi(Ulamek *a, Ulamek *b){
	Ulamek temp = *a;
	temp.licznik = a->licznik*b->mianownik - b->licznik*a->mianownik;
	temp.mianownik = a->mianownik*b->mianownik;
	*b = temp;
	skracanie(b);
}

Ulamek* pomnoz(Ulamek*a, Ulamek* b){
	Ulamek* result = malloc(sizeof(Ulamek));

	set_up(result, a->licznik*b->licznik, a->mianownik*b->mianownik);
	skracanie(result);
	return result;
}
void pomnoz_drugi(Ulamek* a, Ulamek* b){
	Ulamek temp = *a;
	temp.licznik = a->licznik*b->licznik;
	temp.mianownik = a->mianownik*b->mianownik;
	*b = temp;
	skracanie(b);
}
Ulamek* podziel(Ulamek*a, Ulamek* b){
	Ulamek* result = malloc(sizeof(Ulamek));

	set_up(result, a->licznik*b->mianownik, a->mianownik*b->licznik);
	skracanie(result);
	return result;
}
void podziel_drugi(Ulamek* a, Ulamek* b){
	Ulamek temp = *a;
	temp.licznik = a->licznik*b->mianownik;
	temp.mianownik = a->mianownik*b->licznik;
	*b = temp;
	skracanie(b);
}
