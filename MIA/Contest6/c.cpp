#include<bits/stdc++.h>
using namespace std;

const int MOD = 1e9+7, maxn =5e3+6;

int dp[maxn][maxn];

int main(){
	ios_base::sync_with_stdio(false);
	int result = 0;
	string a, b;
	cin>>a>>b;
	for(int i=0; i<a.size(); i++)
		for(int j=0; j<b.size(); j++){
			dp[i+1][j+1] = dp[i+1][j] % MOD;
			if(a[i] == b[j])
				dp[i+1][j+1] += (dp[i][j]+1)%MOD;
			dp[i+1][j+1] %=MOD;
		}
	for (int i = 0; i<a.size(); i++)
		result = (result + dp[i + 1][b.size()])%MOD;
  	cout<<result<<endl;
}