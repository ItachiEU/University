#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+7;
const long long int MOD = 1e9+7;
long long int result[maxn];
int main(){
	ios_base::sync_with_stdio(false);
	int n;
	cin>>n;
 	result[1]=1;
 	result[2]=3;
 	for(int i=3; i<n+2; i++)
 		result[i]=(result[i-1]+result[i-2]+2)%MOD;
 	cout<<result[n];
}