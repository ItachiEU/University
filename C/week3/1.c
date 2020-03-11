#include<stdio.h>
#include<string.h>
char input[10005];
char stack[10005];
int indicator;

int main(){
	scanf("%[^\n]s", input);
	stack[0] = input[0];
	for(int i=1; i<strlen(input); i++){
		//printf("%c ", input[i]);
		if(input[i] == '(' || input[i] == '[' || input[i] == '{'){
			indicator++;
			stack[indicator] = input[i];
		}
		if((input[i]==')' || input[i] ==']'|| input[i]=='}') && indicator==-1){
			printf("niepoprawny 1\n");
			return 0;
		}
		if(input[i] == ')'){
			if(stack[indicator]=='('){
			indicator--;
			continue;
			}
			else{
				printf("niepoprawny 2\n");
				return 0;
			}
		}
		if(input[i] == ']'){
			if(stack[indicator]=='['){
			indicator--;
			continue;
			}
			else{
				printf("niepoprawny 3\n");
				return 0;
			}
		}
		if(input[i] == '}'){
			if(stack[indicator]=='{'){
			indicator--;
			continue;
			}
			else{
				printf("niepoprawny 4\n");
				return 0;
			}
		}
	}
	//printf("%d\n", indicator);
	if(indicator==-1)
	printf("poprawny\n");
	else
	printf("niepoprawny\n");

}