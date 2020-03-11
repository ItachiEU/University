#include<stdio.h>

int main(){
	int m, n, t;
	scanf("%d %d %d", &m, &n, &t);
	for(int i=0; i<m; i++){
		int ile = i%t;
		int hasze = t - ile,licznik=0;
		for(int j=0; j<n; j++){
			if(licznik<hasze)
				printf("#");
			else
				printf(" ");
			licznik++;
			if(licznik==t)
				licznik=0;
		}
		printf("\n");
	}
}