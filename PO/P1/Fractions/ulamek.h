#ifndef ULAMEK_H
#define ULAMEK_H

#include<stdio.h>
#include<stdlib.h>

typedef struct {
	int licznik;
	int mianownik;
} Ulamek;

void set_up(Ulamek* a, int licznik, int mianownik);

int NWD(int a, int b);

Ulamek* dodaj(Ulamek *a, Ulamek *b);
void dodaj_drugi(Ulamek* a, Ulamek* b);

Ulamek* odejmij(Ulamek *a, Ulamek *b);
void odejmij_drugi(Ulamek* a, Ulamek* b);

Ulamek* pomnoz(Ulamek*a, Ulamek* b);
void pomnoz_drugi(Ulamek* a, Ulamek* b);

Ulamek* podziel(Ulamek*a, Ulamek* b);
void podziel_drugi(Ulamek* a, Ulamek* b);

void show(Ulamek* a);

#endif