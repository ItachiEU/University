#include<stdio.h>

int used[1000005];

int indicator;
_Bool check(long long int x){
	indicator++;
	long long int temp = 0, val = x;
	while(used[val]!=indicator){
		used[val] = indicator;
		//printf("Start: %lld\n", val);
		while(val>=1){
			long long int potega = (val%10)*(val%10);
			temp+= potega;
			val/=10;
			//printf("%lld\n", potega);
		}

		if(temp == 1){
			return 1;
		}
		val = temp;
		temp = 0;
	}
	return 0;
}

int main(){
	long long int n;
	scanf("%lld", &n);
	for(long long int i=n; i<n+10; i++){
		if(check(i) == 1){
				printf("%lld", i);
				return 0;
		}
	}
	printf("BRAK\n");
}