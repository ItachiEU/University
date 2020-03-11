#include<stdio.h>
#include<string.h>
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define maxn 1027

char tab[2];
int input[maxn][maxn];
int dp_lewo[maxn], dp_prawo[maxn], dp[maxn][maxn], temp[maxn];

void first_row(int n){
	for(int i=0; i<n; i++){
		if(i==0)
			dp_prawo[i]=1;
		else
			if(input[0][i]!=input[0][i-1])
				dp_prawo[i]=dp_prawo[i-1]+1;
			else
				dp_prawo[i]=1;
	}
	for(int i=n-1; i>=0; i--){
		if(i==n-1)
			dp_lewo[i]=1;
		else
			if(input[0][i]!=input[0][i+1])
				dp_lewo[i]=dp_lewo[i+1]+1;
			else
				dp_lewo[i]=1;
	}
	for(int i=0; i<n; i++)
		dp[0][i] = MAX(dp_lewo[i], dp_prawo[i]);
}
int update_lewo(int level, int poz){
	if(MAX(dp_lewo[poz], dp_prawo[poz])<=dp[level-1][poz]+1)
		temp[poz] = dp[level-1][poz]+1;
	else
		return 0;
	//printf("wchodze: %d %d\n", level, poz);
	for(int i=poz-1; i>=0; i--){
		if(input[level][i]!=input[level][i+1] && temp[poz]+poz-i>dp[level][i])
			temp[i] = temp[poz]+poz-i;
		else
		if(input[level][i]==input[level][i+1])
			break;
	}
	for(int i=0; i<=poz; i++)
		if(temp[i]>dp[level][i]){
			dp[level][i]=temp[i];
		}
	return 1;
}
void update_prawo(int level, int poz, int n){
	for(int i=poz+1; i<n; i++){
		if(input[level][i]!=input[level][i-1] && temp[poz]+i-poz>dp[level][i])
			temp[i] = temp[poz]+i-poz;
		else
		if(input[level][i]==input[level][i-1])
			break;
	}
	for(int i=poz+1; i<n; i++)
		if(temp[i]>dp[level][i]){
			dp[level][i]=temp[i];
		}
}
void wylicz_dp(int n){
	//dla kazdego rzedu:
	for(int j=1; j<n; j++){
		for(int i=0; i<n; i++){
			if(i==0)
				dp_prawo[i]=1;
			else
				if(input[j][i]!=input[j][i-1])
					dp_prawo[i]=dp_prawo[i-1]+1;
				else
					dp_prawo[i]=1;
		}
		for(int i=n-1; i>=0; i--){
			if(i==n-1)
				dp_lewo[i]=1;
			else
				if(input[j][i]!=input[j][i+1])
					dp_lewo[i]=dp_lewo[i+1]+1;
				else
					dp_lewo[i]=1;
		}		
		for(int i=0; i<n; i++)
			dp[j][i] = MAX(dp_lewo[i], dp_prawo[i]);
	//sprawdzenie czy z gory i pojscie w boki
		for(int i=0; i<n; i++){
			if(input[j][i]!=input[j-1][i]){
				if(update_lewo(j, i))
					update_prawo(j,i,n);
			}
		}
		for(int i=0; i<n; i++)
			temp[i]=0;
	}
}
long long int result(int n){
	long long int maks = 0;
	for(int i=0; i<n; i++)
		for(int j=0; j<n; j++)
			if(dp[i][j]>maks)
				maks = dp[i][j];
	return maks;
}
int main(){
	scanf("%s", tab);
	int n, m;
	scanf("%d %d", &n, &m);
	for(int i=0; i<n; i++)
		for(int j=0; j<m; j++)
			scanf("%d", &input[i][j]);
	//pierwszy wiersz
	first_row(n);
	wylicz_dp(n);
	printf("%lld\n",  result(n));
},