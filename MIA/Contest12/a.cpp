#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e3+5;
int x;
bool git;
vector<pair<int, int> > G[maxn];
int visited[maxn];

void dfs(int start, int end, int color){
	visited[start] = x;
	if(start == end){
		git = true;
		return ;
	}
	for(int i=0; i<G[start].size(); i++){
		if(visited[G[start][i].first] !=x && G[start][i].second == color){
			//cout<<"tu ide: "<<G[start][i].first<<" taki kolor: "<<color<<endl;
			dfs(G[start][i].first, end, color);
		}
	}
}

int main(){
	ios_base::sync_with_stdio(false);
	int n, m, q;
	cin>>n>>m;
	for(int i=0; i<m; i++){
		int a, b, c;
		cin>>a>>b>>c;
		G[a].push_back(make_pair(b, c));
		G[b].push_back(make_pair(a, c));
	}
	cin>>q;
	while(q--){
		int a, b, res = 0;
		cin>>a>>b;
		for(int i=1; i<=100; i++){
			x++;
			git = false;
			dfs(a, b, i);
			if(git)
				res++;
		}
		cout<<res<<endl;
	}
}