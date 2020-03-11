#include<stdio.h>
#include<stdbool.h>
#include<string.h>

char result[100000];
int pointer = -1, res_point = 0;

int main(){
	char a;
	bool prev_nawias = false, prev_close = false;
	while((a=getchar()) != EOF && a!='\n'){
		if(a == ' ')
			continue;
		if(a == '('){
			prev_nawias = true;
			pointer++;
		}
		else{
			if(pointer == -1){
				result[res_point++] = a;
				continue;
			}
			if(a == ')'){
				//printf("%d\n", res_point);
				if(result[res_point-2]==',')
					res_point-=2;
				result[res_point++] = ')';
				prev_close = true;
				pointer--;
				continue;
			}
			if(prev_close && pointer>=0){
				result[res_point++] = ',';
				result[res_point++] = ' ';
				prev_close = false;
			}
			if(prev_nawias){
				while(a!= ' ' && a!=')'){
					result[res_point++] = a;
					a = getchar();
				}
				result[res_point++] = '(';
				prev_nawias = false;
				if(a == ')'){
					if(result[res_point-2]==',')
						res_point-=2;
					result[res_point++] = ')';
					prev_close = true;
				}
				continue;
			}
			while(a!=' ' && a!=')' && a!=EOF){
				result[res_point++] = a;
				a = getchar();
			}
			if(a == EOF)
				break;
			if(a!=')'){
				result[res_point++] = ',';
				result[res_point++] = ' ';
			}
			else{
				result[res_point++] = ')';
				prev_close = true;
			}
		}
	}
	for(int i=0; i<res_point; i++)
		printf("%c", result[i]);
}