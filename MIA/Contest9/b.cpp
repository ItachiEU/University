#include<bits/stdc++.h>
using namespace std;

long long int solve(long long int a){
	if(a%4==0)
		return 0;
	if(a%4==1)
		return a-1;
	if(a%4==2)
		return 1;
	if(a%4==3)
		return a;
}

int main(){
	ios_base::sync_with_stdio(false);
	int t;
	long long int res = 0;
	cin>>t;
	while(t--){
		long long int x, m;
		cin>>x>>m;
		res ^= solve(x)^solve(x+m);
	}
	cout<<(res ? "tolik" : "bolik")<<endl;
}