#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+5;
int cats[maxn], visited[maxn], counter[maxn], k, result;
vector<int> G[maxn];

void dfs(int a){
	if(G[a].size()==1 && a!=1 && counter[a]<=k)
		result++;
	visited[a] = 1;
	for(int i=0; i<G[a].size(); i++){
		if(visited[G[a][i]]==0){
			if(cats[G[a][i]]==1)
				counter[G[a][i]] = counter[a]+1;
			else
				counter[G[a][i]] = 0;
			if(counter[G[a][i]]<=k)
				dfs(G[a][i]);
		}
	}
}

int main(){
	ios_base::sync_with_stdio(false);
	int n;
	cin>>n>>k;
	for(int i=1; i<=n; i++)
			cin>>cats[i];
	for(int i=0; i<n-1; i++){
		int a, b;
		cin>>a>>b;
		G[a].push_back(b);
		G[b].push_back(a);
	}
	counter[1]+=cats[1];
	dfs(1);
	if(n==1){
		cout<<"1\n";
		return 0;
	}
	//cout<<counter[4]<<" "<<counter[5]<<endl;
	cout<<result<<endl;
}