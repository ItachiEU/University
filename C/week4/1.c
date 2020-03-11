#include<stdio.h>
#include<ctype.h>

int main(){
	char a;
	int po_kropce=-1, po_przecinku=-1;
	while((a=getchar()) != EOF){
		if(isalpha(a)!=0 && po_kropce==1){
			putchar(toupper(a));
			po_kropce = -1;
			po_przecinku=-1;
		}
		else
		if(isalpha(a)!=0 && po_kropce==-1){
			putchar(a);
		}
		else
		if(a=='.'){
			po_kropce = 1;
			putchar(a);
			putchar(' ');
		}
		else
		if(a==','){
			putchar(a);
			putchar(' ');
		}
		else
		if(po_kropce==-1 && isalpha(a)==0){
			putchar(a);
		}
		else
		if((po_kropce == 1 || po_przecinku ==1 )&& a==' '){
			continue;
		}
	}
}