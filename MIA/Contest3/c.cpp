#include<bits/stdc++.h>
#define mp make_pair
using namespace std;
int n, m, x, y;
const long long int INF=1e18+3;
const int maxn=1e3+7;
vector<pair<int, int> > G_init[maxn], G_final[maxn];
priority_queue<pair<int, int> > q;
long long int dist_max[maxn], cost[maxn], d[maxn][maxn], d_final[maxn];

void input(){
	cin>>n>>m>>x>>y;
	for(int i=0; i<m; i++){
		int a, b ,c;
		cin>>a>>b>>c;
		G_init[a].push_back(mp(b,c));
		G_init[b].push_back(mp(a,c));
	}
	for(int i=1; i<=n; i++)
		cin>>dist_max[i]>>cost[i];
	fill(d_final, d_final+n+2,INF);
	for(int i=1; i<=n; i++)
		fill(d[i], d[i]+n+2, INF);
}
void init_dijkstra(int a){
	d[a][a]=0;
	q.push(mp(0,a));
	while(!q.empty()){
		pair<int, int> P=q.top();
        P.first = -P.first;
        q.pop();
        for(int i=0; i<G_init[P.second].size(); i++)
        {
            int v=G_init[P.second][i].first;
            if(d[a][v]>d[a][P.second] + G_init[P.second][i].second)
            {
                d[a][v]=d[a][P.second] + G_init[P.second][i].second;
                q.push(mp(-d[a][v],v));
            }
        } 
	}
}
void build_new_graph(int v){
	for(int i=1; i<=n; i++){
		if(d[v][i]<=dist_max[v] && i!=v)
			G_final[v].push_back(mp(i, cost[v]));
	}
}
void final_dijkstra(int a){
	d_final[a]=0;
	q.push(mp(0,a));
	while(!q.empty()){
		pair<int, int> P=q.top();
        P.first = -P.first;
        q.pop();
        for(int i=0; i<G_final[P.second].size(); i++)
        {
            int v=G_final[P.second][i].first;
            if(d_final[v]>d_final[P.second] + G_final[P.second][i].second)
            {
                d_final[v]=d_final[P.second] + G_final[P.second][i].second;
                q.push(mp(-d_final[v],v));
            }
        } 
	}
}
int main(){
	ios_base::sync_with_stdio(false);
	input();
	for(int i=1; i<=n; i++)
		init_dijkstra(i);
	for(int i=1; i<=n; i++)
		build_new_graph(i);
	final_dijkstra(x);
	if(d_final[y]==INF)
		cout<<"-1\n";
	else
		cout<<d_final[y];
}