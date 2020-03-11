#include<stdio.h>
#define maxn 1000
#define INF 1000000000
int tab[maxn], dp[210001][52];

int main() 
{ 
    int n, sum = 25000;
    scanf("%d", &n);
    for(int i=0; i<n; i++) scanf("%d", &tab[i]);
    for(int i=0; i<=200000; i++)
        for(int j=0; j<=51; j++)
            dp[i][j] = -INF;
    dp[25000][0] = 0;
    for(int k=0; k<n; k++)
      for(int j=50; j>=0; j--)
             for(int i=0; i<=50000; i++)
                if(dp[i][j]!=-INF)
                    if(i+tab[k]>0 && dp[i+tab[k]][j+1]==-INF)
                        dp[i+tab[k]][j+1]=i;
    int gdzie = -1;
    for(int j=50; j>=0; j--)
        if(dp[sum][j]!=-INF){
            printf("%d\n", j);
            gdzie = j;
            break;
        }
    for(int j=gdzie; j>0; j--){
        int el = sum - dp[sum][j];
        sum = dp[sum][j];
        printf("%d ", el);
    }
} 