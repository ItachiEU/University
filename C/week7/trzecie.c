#include<stdio.h>
struct bloczek{
	int h;
	int w;
	char tab[10][10];
};

struct bloczek tablica[8];
int n,t, m, blocks;
void input(){
	scanf("%d %d %d", &n, &m, &blocks);
	for(int i=0; i<blocks;i++){
		int h, w;
		struct bloczek temp;
		scanf("%d %d", &w, &h);
		getchar();
		temp.h = h;
		temp.w = w;
		char tempik[h][w];
		for(int j=0; j<h; j++){
			for(int k=0; k<w; k++)
				scanf("%c", &tempik[j][k]);
			getchar();
		}
		for(int j=0; j<10; j++)
			for(int k=0; k<10; k++)
				if(j<h && k<w)
					temp.tab[j][k]=tempik[j][k];
				else
					temp.tab[j][k]='.';
		tablica[i] = temp;
	}
	scanf("%d", &t);
}
void solve(){
	int ciag[10];
	for(int i=0; i<blocks; i++)
		scanf("%d", &ciag[i]);

}
int main(){
	input();
	while(t--){
		solve();
	}
}