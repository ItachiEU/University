#include<stdio.h>
#include<math.h>
#include<ctype.h>
const int konst = 10;
int ile[129];

int main(){
	char c;
	int total = 0;
	while((c=getchar()) != EOF){
		if(isgraph(c)!=0){
			total++;
			//printf("%d \n", isgraph(c));
			ile[(int)c]++;
		}
	}

	if(total>30)
		total = 30;
	if(total<10)
		total=10;
	for(int i=0; i<=127; i++){
		if(ile[i]>0){
			printf("%c [", (char)i);
			for(int j=0; j<total; j++){
				if(j<(int)round((double)konst*((double)ile[i]/total)))
					printf("*");
					else
					printf(" ");
			}
			printf("]\n");
		}
	}
}