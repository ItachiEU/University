#include<stdio.h>
#define maxn 1003
int h, w;
int G[maxn][maxn];
char input[maxn][maxn];
void readin(){
	scanf("%d %d", &w, &h);
	for(int i=0; i<h; i++){
		for(int j=0; j<w; j++)
			scanf("%c", &input[i][j]);
		getchar();
	}
	for(int i=0; i<h; i++){
		for(int j=0; j<w; j++)
			printf("%c", input[i][j]);
	}
}
void build_s_graph(){

}

int main(){
	readin();
	build_s_graph();
}