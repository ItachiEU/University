#include<stdio.h>
#include<string.h>
#define PRINTBIN(napis) \
			do{   \
					int k = 0;\
					int temp = 0, git = 1;\
					for(int i=0; #napis[i]; i++){\
						if(strlen(#napis)%8!=0 && git){\
							while((strlen(#napis)+k)%8!=0){\
								k++;\
							}\
							git =0;\
						}\
						if(k%8==0){\
							printf("%c", temp);\
							k = 0;\
							temp = 0;\
						}\
						if(#napis[i]=='1')\
							temp += (1<<(7-k));\
						k++;\
					}\
					if(k%8!=0){\
						printf("%c", temp);\
					}\
					printf("\n");\
			 }while(0);\

int main(){
	for (int i = 0; i < 10; i++)
		if (i%2){
			PRINTBIN(111010001011010010100100001010); 
		}
		else{
			PRINTBIN(1010);
		}
}