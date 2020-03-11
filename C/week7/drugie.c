#include<stdio.h>
#define h 10
#define w 10
int result[h][w], temp[h][w];
int rzedy[h], kolumny[w], ilosc_r[h], ilosc_c[w];
int git;

int abs(int a){
	if(a<0)
		return (-1)*a;
	return a;
}

void solve(int sze, int wys){
	if(git)
		return ;
	for(int i=0; i<wys; i++){
		for(int j=0; j<sze; j++)
			printf("%d ", temp[i][j]);
		printf("\n");
	}
	for(int i=0; i<wys; i++){
		for(int j =0;j<sze; j++){
			if(temp[i][j]!=0)
				continue;
			//przypadek kiedy trafiamy na oczywiste 0 w jedna strone
			if(ilosc_r[i] == sze-1){
				if(abs(rzedy[i])>9 || rzedy[i]==0)
					return ;
				temp[i][j] = -rzedy[i];
				kolumny[j] -=rzedy[i];
				rzedy[i] = 0;
				ilosc_r[i]++;
				ilosc_c[j]++;
			}
			else //oczywiste zero w druga strone
			if(ilosc_c[j] == wys-1){
				if(abs(kolumny[j])>9 || kolumny[j]==0)
					return ;
				temp[i][j] = -kolumny[j];
				rzedy[i] -= kolumny[j];
				kolumny[j] = 0;
				ilosc_r[i]++;
				ilosc_c[j]++;			
			}
			else{ //brak oczywistej sytuacji wiec probujemy rozne mozliwosci
				int k = 0;
				for(int l=1; l<=18; l++){
					if(l%2==1){
						k *= -1;
						k++;
					}
					else
						k*=-1;
					rzedy[i] += k;
					kolumny[j] += k;
					temp[i][j] = k;
					ilosc_r[i]++;
					ilosc_c[j]++;
					solve(sze, wys);
					ilosc_r[i]--;
					ilosc_c[j]--;
					temp[i][j] = 0;
					rzedy[i] -= k;
					kolumny[j] -= k;
				}
			}
		}
	}
	//sprawdzmy czy wynik jest ok
	for(int i=0; i<wys; i++){
		int tempik = 0;
		for(int j=0; j<sze; j++)
			tempik +=temp[i][j];
		if(tempik!=0)
			return ;
	}
	for(int i=0; i<sze; i++){
		int tempik = 0;
		for(int j=0; j<wys; j++)
			tempik += temp[j][i];
		if(tempik!=0)
			return ;
	}
	git = 1;
	for(int i=0; i<wys; i++)
		for(int j=0; j<sze; j++){
			result[i][j] = temp[i][j];
		}
	return ; 
}

int main(){
	int sze, wys;
	scanf("%d %d", &sze, &wys);
	int tab[h][w];
	for(int i=0; i<wys; i++)
		for(int j=0; j<sze; j++)
			scanf("%d", &tab[i][j]);
	for(int i=0; i<wys; i++)
		for(int j=0; j<sze; j++)
			temp[i][j]=tab[i][j];	
	//zliczam sumy w wierszach i nie_zera
	for(int i=0; i<wys; i++)
		for(int j=0; j<sze; j++){
			rzedy[i]+=tab[i][j];
			if(tab[i][j]!=0)
				ilosc_r[i]++;
		}
	//zliczam kolumny i nie_zera
	for(int i=0; i<sze; i++)
		for(int j=0; j<wys; j++){
			kolumny[i]+=tab[j][i];
			if(tab[j][i]!=0)
				ilosc_c[i]++;
		}
	solve(sze, wys);
	//wypisz wynik
	if(result[0][0]==0){
		printf("NIE DA SIE\n");
		return 0;
	}
	for(int i=0; i<wys; i++){
		for(int j=0; j<sze; j++)
			printf("%d ", result[i][j]);
		printf("\n");
	}
}