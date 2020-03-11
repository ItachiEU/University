#include<stdio.h>
#include<string.h>
#include<math.h>

int tab[1025][1025];
int wejscie[1048581];
char input[3];

int main(){
	int licznik = 0,suma=0, rozmiar, last=0;
	scanf("%s", input);
	if(input[0]=='P' && input[1]=='1'){
		int n, m;
		scanf("%d %d", &n, &m);
		for(int i=0; i<n; i++)
			for(int j=0; j<m; j++)
				scanf("%d", &tab[i][j]);	
	}
	else{
		scanf("%d", &rozmiar);
		while(scanf("%d", &wejscie[licznik++]) != EOF){
			//suma+=wejscie[licznik-1];
		}
	}
	int linie = 2*rozmiar-1, mid_point = linie/2+1, items=0, indx = 0;
	if(input[1]=='R'){
		int temp=0;
		for(int i=0; i<licznik-1; i++){
			for(int j=last; j<last+wejscie[i]; j++){
				if(i%2==1)
					tab[(int)(j/rozmiar)][j%rozmiar]=1;
				temp=j;
			}
			if(wejscie[i]!=0)
				last = temp+1;
		}
	}
	else
	if(input[1]=='S'){
		int temp = 0;
		for(int i=0; i<licznik-1; i++){
			for(int j=last; j<last+wejscie[i]; j++){
				if(i%2==1){
					if((int)(j/rozmiar)%2==0)
						tab[(int)(j/rozmiar)][j%rozmiar]=1;
				else
					tab[(int)(j/rozmiar)][rozmiar-1-(j%rozmiar)]=1;
				}
				temp=j;
			}
			if(wejscie[i]!=0)
				last = temp+1;
		}
	}
	else
	if(input[1]=='D'){
		for(int i=1; i<=linie; i++){
			int row, column;
			if(i<=mid_point){
				items++;
				if(i%2==0){
					for(int j=0; j<items; j++){
						row = (i-j)-1;
						column=j;
						if(wejscie[indx]<=0)
							indx++;
						wejscie[indx]--;
						if(indx%2==1)
							tab[column][row]=1;
					}
				}
				else{
					for(int j=items-1; j>=0; j--){
						row = (i-j)-1;
						column=j;
						if(wejscie[indx]<=0)
							indx++;
						wejscie[indx]--;
						if(indx%2==1)
							tab[column][row]=1;
					}
				}
			}
			else{
				items--;
				if(i%2==0){
					for(int j=0; j<items; j++){
						row = (rozmiar-1)-j;
						column = (i-rozmiar)+j;
						if(wejscie[indx]<=0)
							indx++;
						wejscie[indx]--;
						if(indx%2==1)
							tab[column][row]=1;
					}
				}
				else{
					for(int j=items-1; j>=0; j--){
						row = (rozmiar-1)-j;
						column = (i-rozmiar)+j;
						if(wejscie[indx]<=0)
							indx++;
						wejscie[indx]--;
						if(indx%2==1)
							tab[column][row]=1;
					}
				}
			}
		}
	}
	int regular = 1, snake = 1, diagonal = 1;
	diagonal = 1;
	snake = 1;
	int curr=0;
	for(int i=0; i<rozmiar; i++){
		for(int j=0; j<rozmiar; j++){
			if(tab[i][j]!=curr){
				curr=tab[i][j];
				regular++;
			}
		}
	}
	curr=0;
	for(int i=0; i<rozmiar; i++){
		if(i%2==0)
			for(int j=0; j<rozmiar; j++){
				if(tab[i][j]!=curr){
					curr=tab[i][j];
					snake++;
				}
			}
		else
			for(int j=rozmiar-1; j>=0; j--){
				if(tab[i][j]!=curr){
					curr=tab[i][j];
					snake++;
				}
			}
	}
	curr = 0;
	linie = 2*rozmiar-1, mid_point = linie/2+1, items=0, indx = 0;
	for(int i=1; i<=linie; i++){
		int row, column;
		if(i<=mid_point){
			items++;
			if(i%2==0){
				for(int j=0; j<items; j++){
					row = (i-j)-1;
					column=j;
					if(tab[column][row]!=curr){
						curr=tab[column][row];
						diagonal++;
					}
				}
			}
			else{
				for(int j=items-1; j>=0; j--){
					row = (i-j)-1;
					column=j;
					if(tab[column][row]!=curr){
						curr=tab[column][row];
						diagonal++;
					}
				}
			}
		}
		else{
			items--;
			if(i%2==0){
				for(int j=0; j<items; j++){
					row = (rozmiar-1)-j;
					column = (i-rozmiar)+j;
					if(tab[column][row]!=curr){
						curr=tab[column][row];
						diagonal++;
					}					
				}
			}
			else{
				for(int j=items-1; j>=0; j--){
					row = (rozmiar-1)-j;
					column = (i-rozmiar)+j;
					if(tab[column][row]!=curr){
						curr=tab[column][row];
						diagonal++;
					}
				}
			}
		}
	}
	/*for(int i=0; i<rozmiar; i++){
		for(int j=0; j<rozmiar; j++){
			printf("%d", tab[i][j]);
		}
		printf("\n");
	}*/
	printf("%d %d %d", regular, snake, diagonal);
}