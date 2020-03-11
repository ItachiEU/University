#include<bits/stdc++.h>
using namespace std;
const int maxn=5e3+5;
long long int input[maxn], dp[maxn][maxn];
long long int sumy[maxn];
int main(){
	ios_base::sync_with_stdio(false);
	int n, m, k;
	cin>>n>>m>>k;
	for(int i=0; i<n; i++)
			cin>>input[i];
	sumy[1]=input[0];
	for(int i=2; i<=n; i++)
		sumy[i]=sumy[i-1]+input[i-1];
	long long int result = 0;
	for(int i = 1; i <= n; ++i){
        if(m > i) continue;
        long long int temp = sumy[i] - sumy[i - m];
        for(int j = 1; j <= k; ++j){
            if(j*m <= i) {
                dp[i][j] = dp[i-m][j-1] + temp;
                for(int q = 0; q <= m; ++q){
                    dp[i][j] = max(dp[i][j], dp[i-q][j]);
                }
            }
        }
    }
    cout << dp[n][k];
}