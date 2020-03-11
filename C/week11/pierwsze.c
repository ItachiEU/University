#include<stdio.h>
#include<stdlib.h>

int MAX(int a, int b){
	if(a>b)
		return a;
	return b;
}
int MIN(int a, int b){
	if(a<b)
		return a;
	return b;
}


int main(int argc, char *argv[]){
	FILE *fp1, *fp2;

	fp1=fopen(argv[0], "rb");	
	fp2=fopen(argv[1], "rb+");
	
	char* buffer1;
	char* buffer2;
	fseek (fp1 , 0 , SEEK_END);
	int size1 = ftell(fp1);
	rewind (fp1);
	fseek (fp2, 0, SEEK_END);
 	int size2 = ftell(fp2);
	rewind (fp2);

	buffer1 = (char*) malloc (sizeof(char)*size1);
	buffer2 = (char*) malloc (sizeof(char)*size2);

	fread(buffer1,1, size1,fp1);
	rewind(fp1);
	fread(buffer2,1, size2,fp2);
	rewind(fp2);
	for(int i=0; i<MAX(size1, size2); i++){
		if(size1 == MAX(size1, size2)){
			//klucz wiekszy
			//printf("halo\n");
			buffer2[i%size2] = (buffer1[i] ^ buffer2[i%size2]);
		}
		if(size2 == MAX(size1, size2)){
			//printf("halo2\n");
			//plik wiekszy
			buffer2[i] = (buffer1[i%size1] ^ buffer2[i]);
		}
	}
	fwrite(buffer2, sizeof(char), size2, fp2);
	fclose(fp1);
	fclose(fp2);
	free(buffer1);
	free(buffer2);
}