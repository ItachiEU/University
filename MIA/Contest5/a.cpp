#include<bits/stdc++.h>
using namespace std;
unordered_map<long long int, long long int> mapa;

void dodaj(long long int a, long long int b, long long int val){
	while(a!=b){
		if(a>b){
			mapa[a]+=val;
			a/=2;
		}
		else{
			mapa[b]+=val;
			b/=2;
		}
	}
}
long long int ile(long long int a, long long int b){
	long long int res =0;
	while(a!=b){
		if(a>b){
			res+=mapa[a];
			a/=2;
		}else{
			res+=mapa[b];
			b/=2;
		}
	}
	return res;
}

int main(){
	ios_base::sync_with_stdio(false);
	long long int q;
	cin>>q;
	while(q--){
		long long int t;
		cin>>t;
		if(t==1){
			long long int a, b, c;
			cin>>a>>b>>c;
			dodaj(a, b, c);
		}
		else
		if(t==2){
			long long int a, b;
			cin>>a>>b;
			cout<<ile(a, b)<<endl;
		}
	}
}	