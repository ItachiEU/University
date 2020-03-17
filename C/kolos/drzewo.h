#ifndef DRZEWO_H
#define DRZEWO_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
	double unknown;
	int wysokosc;
	int balans;
	struct Node* left;
	struct Node* right;
} Node;
typedef Node* Drzewo;


void tree_travers(Node* start);
void wyznacz_balanse(Drzewo T);

#endif
