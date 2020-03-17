#include "drzewo.h"

void tree_traverse(Node* start){
	if(start != NULL){
		//Ustawiamy wysokosc
		//Lecimy dalej
		if(start->left != NULL){
			tree_traverse(start->left);
			start->left->wysokosc = start->wysokosc + 1;
		}
		if(start->right != NULL){
			tree_traverse(start->right);
			start->right->wysokosc = start->wysokosc + 1;
		}
		//Wracając z rekurencji ustawiamy wysokosc poddrzew
		if(start->right != NULL && start->left != NULL){
			start->wysokosc = start->right->wysokosc >= start->left->wysokosc ? start->right->wysokosc : start->left->wysokosc;	
			start->balans = start->left->wysokosc - start->right->wysokosc;
		}
		if(start->right != NULL && start->left == NULL)
			start->balans = -start->right->wysokosc;
		if(start->right == NULL && start->left != NULL)
			start->balans = start->left->wysokosc;
	}
}
void wyznacz_balanse(Drzewo T){
	Node* start = T;
	if(start !=NULL){
		start->wysokosc = 0;
		tree_traverse(start);
	}
}
int main(){
	Drzewo siema;
	siema = malloc(sizeof(Node));
	siema->balans = 17;
	wyznacz_balanse(siema);
	printf("%d - Hello World!", siema->balans);
	free(siema);
	return 0;
}
