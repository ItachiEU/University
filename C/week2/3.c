#include<stdio.h>
#include<math.h>
#include<limits.h>

int liczba1, liczba2;
long long int s;
int check(int temp){
	int sumka = 1;
	for(int i=2; i*i<=temp; i++){
		if(temp%i==0){
			//printf("%d ", i);
			sumka+=i;
			if(i*i!=temp)
				sumka+=temp/i;
		}
	}
	int kandydat = sumka;
	int 	sumka2 = 1;
	for(int i=2; i*i<=kandydat; i++){
		if(kandydat%i==0){
			//printf("%d ", i);
			sumka2+=i;
			if(i*i!=kandydat)
				sumka2+=kandydat/i;
		}
	}
	if(sumka2 == temp && kandydat != temp && temp > s && kandydat > s){
		if(temp < kandydat){
			liczba1 = temp;
			liczba2 = kandydat;
		}
		else{
			liczba1 = kandydat;
			liczba2 = temp;
		}
		return 1;
	}
	else
		return -1;
}

int main(){
	scanf("%lld", &s);
	if(s>=100000000){
		printf("BRAK\n");
		return 0;
	}
	for(int i=s+1; i<INT_MAX; i++){
		int res = check(i);
		if(res == 1){
			printf("%d %d\n", liczba1, liczba2);
			return 0;
		}
	}
	printf("BRAK\n");
}