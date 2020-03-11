#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+4, INF=1e9+7;

int t[maxn];

int main(){
	ios_base::sync_with_stdio(false);
	long long int n,a,b;
	cin>>n>>a>>b;
	for(int i=0; i<n; i++){
		cin>>t[i];
		if(a<0)
			t[i]*=-1;
	}
	long long int maxik = -INF, temp=0;
	for(int i=0; i<n; i++){
		temp+=t[i];
		if(temp>maxik)
				maxik = temp;
		if(temp<0){
			temp=0;
		}
		//cout<<i<<" "<<temp<<" "<<maxik<<endl;
	}
	if(a<0)
		cout<<maxik*(-a)+b<<endl;
	else
		cout<<maxik*a+b<<endl;
}