#include<stdio.h>
#include<string.h>

char task[15], key[257], input[257];
char alfabet[65]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',' ',','};
char mapa[64][64];
char result[256];
int permutacja[64];
int main(){
	for(int i=0; i<64;i++)
		for(int j=0; j<64; j++)
			mapa[i][j]=alfabet[(j+i)%64];
	scanf("%s", task);
	int a;
	for(int i=0; i<64; i++){
		scanf("%d", &a);
		permutacja[i]=a;
	}
	getchar();
	scanf("%[^\n]s", key);
	getchar();
	int mod = strlen(key);
	scanf("%[^\n]s", input);
	//for(int i=0; i<strlen(input); i++)
	//	printf("%c", input[i]);
	//printf("\n");
	int index_key, index_txt, index_res=-1;
	for(int j=0; j<(int)strlen(input); j++){
		index_key = -1;
		index_txt = -1;
		index_res++;
		for(int i=0; i<64; i++){
			if(alfabet[i]==key[j%mod]){
				index_key = i;
				break;
			}
		}
		for(int i=0; i<64; i++){
			if(alfabet[i]==input[j]){
				index_txt = i;
				break;
			}
		}
		if(index_key == -1 || index_txt==-1){
			printf("UNSUPPORTED_ALPHABET\n");
			return 0;
		}
		index_key = permutacja[index_key];
		if(task[0] == 'd')
			index_key = (64 - index_key)%64;

		result[index_res]=mapa[index_key][index_txt];
	}
	for(int i=0; i<index_res+1; i++)
		printf("%c", result[i]);
}