#include<bits/stdc++.h>
using namespace std;
const int maxn=1e3+5;
int parent[maxn];
vector<int> G[maxn];

int main(){
	ios_base::sync_with_stdio(false);
	int n;
	cin>>n;
	for(int i=1; i<=n-1; i++){
		int a;
		cin>>a;
		parent[i+1] = a;
		G[a].push_back(i+1);
		G[i+1].push_back(a);
	}
	for(int i=1; i<=n; i++){
		if(G[i].size()>1){
			int licznik = 0;
			for(int j=0; j<G[i].size(); j++){
				if(G[G[i][j]].size()==1)
					licznik++;
			}
			if(licznik<3){
				cout<<"No\n";
				return 0;
			}
		}
	}
	cout<<"Yes\n";
}