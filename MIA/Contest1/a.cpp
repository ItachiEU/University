#include<bits/stdc++.h>
using namespace std;
const int maxn=1e3+4;
int t[maxn];
int main(){
	ios_base::sync_with_stdio(false);
	int n;
	cin>>n;
	for(int i=0; i<n; i++)
		cin>>t[i];
	int result=0;
	for(int i=n-1; i>=0; i--)
		for(int j=i-1; j>=0; j--)
				if(t[i]<t[j])
					result++;
	cout<<result<<endl;
}