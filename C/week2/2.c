#include<stdio.h>
#include<math.h>
#define MAX(x, y) (((x) > (y)) ? (x) : (y))

int pierwsze[1005];

void sito()
{
	for (int i=2; i*i<=1004; i++){														
        if(pierwsze[i] == 0)				
			for (int j = i*i ; j<=1004; j+=i) 
           	 pierwsze[j] = 1;			
    }
}

int liczba_b(int m, int n){
	int res = 0;
	for(int i=2; i<1001; i++){
		if(pierwsze[i]==0){
			if(n%i != m%i){
				res = i;
				break;
			}
		}
	}
	return res;
}

int main(){
	sito();
	//int m, n;
	//scanf("%d %d", &m, &n);
	//printf("%d", liczba_b(3,9));
	double maks = 0;
	int wynik1 =0, wynik2=0;
	for(int i=3; i<=1000; i++){
		for(int j=3; j<=1000; j++){
			int p = liczba_b(i, j);
			if(p/log10((double)(MAX(i,j)))>maks){
				maks = p/log10((double)(MAX(i,j)));
				wynik1 = i;
				wynik2 = j;
			}

		}
	}
	printf("%d %d\n", wynik1, wynik2);
}