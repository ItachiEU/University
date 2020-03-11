#include<stdio.h>
int tab[21], git, n;
char result[21], temp[21];

void solve(int poz, int res, char znak, char tempik[]){
	if(git==1)
		return ;
	tempik[poz] = znak;
	if(znak == '*')
		res = res * tab[poz+1];
	if(znak == '-')
		res = res - tab[poz+1];
	if(znak == '+')
		res = res + tab[poz+1];
	if(znak == '/')
		res = res / tab[poz+1];
	if(poz == n-2 && res == 1){
		for(int i=0; i<n-1; i++)
			result[i] = tempik[i];
		git = 1;
		return ;
	}
	if(poz>=n-2)
		return;
	if(znak!='*')
		solve(poz+1, res, '*', tempik);
	if(znak!='+')
		solve(poz+1, res, '+', tempik);
	if(znak!='-')
		solve(poz+1, res, '-', tempik);
	if(znak!='/')
		solve(poz+1, res, '/', tempik);
}

int main(){
	scanf("%d", &n);
	for(int i=0; i<n; i++)
		scanf("%d", &tab[i]);
	solve(0,tab[0], '+', temp);
	solve(0,tab[0], '-', temp);
	solve(0,tab[0], '*', temp);
	solve(0,tab[0], '/',temp);
	if(result[0] == NULL){
		printf("NIE DA SIE\n");
		return 0;
	}
	for(int i=0; i<n; i++){
		if(i==n-1){
			printf("%d ", tab[i]);
			break;
		}
		else{
			printf("%d ", tab[i]);
			printf("%c ", result[i]);
		}
	}
}