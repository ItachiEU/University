#include<stdio.h>

int main(){
	int a;
	int temp =0, maks = 1, last=0, pierwszy = 0;
	while((a=getchar())!= EOF){
		for(int i=7; i>=0; i--){
			//printf("%d", temp);
			if(pierwszy==0){
				if(a & (1<<i)){
					last = 1;
					temp = 1;
				}
				else
					last = 0;
				pierwszy = 1;
				continue;
			}
			//printf("%d", a & (1<<i));
			if(a & (1<<i)){
				if(last==0 && temp>0){
					temp++;
					if(temp>maks)
						maks =temp;
					last = 1;
				}
				else{
					temp = 1;
					last = 1;
					continue;
				}
			}
			else
				if(last==1){
					last = 0;
					temp++;
					if(temp>maks)
						maks = temp;
				}
				else{
					temp = 0;
					last = 0;
					continue;
				}
		}
		//printf("\n");
	}
	printf("%d\n", maks);
}