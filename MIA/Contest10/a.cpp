#include<bits/stdc++.h>
using namespace std;

int main(){
	ios_base::sync_with_stdio(false);
	int n, m;
	cin>>n>>m;
	int ile = n/m;
	int rest = n - ile*m, k =0;
	for(int i=0; i<m; i++){
		if(k<rest)
			cout<<ile+1<<" ";
		else
			cout<<ile<<" ";
		k++;
	}
}