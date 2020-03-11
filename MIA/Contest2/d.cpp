#include<bits/stdc++.h>
using namespace std;
#define mp make_pair
const int maxn=1e6+5;
const long long int INF=1e18+7;
long long int visited[maxn], flagged[maxn], d[maxn];
vector<long long int> path;
vector<pair<long long int, long long int> > G[maxn];
priority_queue<pair<long long int, long long int> > q;

void dijkstra(long long int u, long long int n){
	for(long long int i=0; i<n; i++)
			d[i] = INF;
	d[u]=0;
	q.push(mp(0,u));
	while(!q.empty()){
		pair<long long int, long long int> k = q.top();
		q.pop();
		for(int i=0; i<G[k.second].size(); i++){
			long long int x = G[k.second][i].first;	
			if(d[x]>-k.first+G[k.second][i].second){
				d[x]=G[k.second][i].second-k.first;
				q.push(mp(-d[x], x));
			}
		}
	}
}

int dfs(int a){
	if(visited[1]==0)
		path.push_back(a);
	visited[a]=1;
	for(int i=0; i<G[a].size(); i++)
		if(visited[G[a][i].first]!=1 && G[a][i].first!=flagged[a])
			dfs(G[a][i].first);
	if(visited[1]!=1)
		path.pop_back();
}

int main(){
	ios_base::sync_with_stdio(false);
	long long int n, m;
	cin>>n>>m;
	for(int i=0; i<m; i++){
		long long int a, b, c;
		cin>>a>>b>>c;
		G[a].push_back(mp(b,c));
		G[b].push_back(mp(a,c));
	}
	//dijkstra magic
	dijkstra(1, n);
	for(int i=0; i<n; i++){
		for(int j=0; j<G[i].size(); j++){
			if(d[i]==d[G[i][j].first]+G[i][j].second)
				flagged[i] = G[i][j].first;
		}
	}
	dfs(0);
	if(visited[1]==0){
		cout<<"impossible\n";
		return 0;
	}
	cout<<path.size()<<endl;
	for(int i=0; i<path.size(); i++)
		cout<<path[i]<<" ";
}