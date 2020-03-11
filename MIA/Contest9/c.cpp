#include<bits/stdc++.h>
using namespace std;

int main(){
	int n,x,r=0;
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>x;
		r^=x&1^1;
		cout<<2-r<<"\n";
	}
}