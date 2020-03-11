#include<bits/stdc++.h>
using namespace std;
const int maxn=1e3+5;
char t[maxn][maxn];
int visited[maxn];
vector<int> G[maxn], sequence;

int dfs(int a){
	visited[a] = 1;
	for(int i=0; i<G[a].size(); i++)
		if(visited[G[a][i]]==0)
			dfs(G[a][i]);
	sequence.push_back(a);
}

int main(){
	ios_base::sync_with_stdio(false);
	int n;
	cin>>n;
	for(int i=0; i<n; i++)
		for(int j=0; j<n; j++){
			cin>>t[i][j];
			if(t[i][j]=='1')
				G[i].push_back(j);
		}
	dfs(0);
	if(sequence.size() < n)
		cout<<"impossible\n";
	else
		for(int i=0; i<sequence.size(); i++)
			cout<<sequence[i]<<" ";
}