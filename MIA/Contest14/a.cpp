#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e6+5;
int tab[maxn];

int main(){
	ios_base::sync_with_stdio(false);

	int n, size = 0, last = -1, maxsz=-1;
	cin>>n;

	for(int i=0; i<n; i++){
		int t, m;
		cin>>t>>m;
		tab[t] = m;
	}

	for(int i = 1; i<=1000000; i++){
		size = max(size-1, 0);
		size += tab[i];
		if(size > 0)
			last = i+1;
		if(size > maxsz)
			maxsz = size;
	}
	if(size > 0)
		last += size-1;
	cout<<last<<" "<<maxsz<<endl;
}