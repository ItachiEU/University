#include<bits/stdc++.h>
#define mp make_pair
using namespace std;
const int maxn=4e5+7;
int ojciec[maxn], visited[maxn], t_wej[maxn], low[maxn], kolorki[maxn], used[maxn], obrot[maxn];
int licznik, x, ktory, maksik;
stack <int> stos;
vector<pair<int, int> > edges;
vector<pair<int, int> > G[maxn];
vector<int>new_G[maxn];

inline void dfs(int a){
	visited[a]=1;
	t_wej[a]=licznik++;
	low[a]=t_wej[a];
	stos.push(a);
	for(int i=0; i<G[a].size(); i++){
		if(visited[G[a][i].first]==false)
		{
			ojciec[G[a][i].first]=a;
			dfs(G[a][i].first);
			low[a]=min(low[a], low[G[a][i].first]);
		}
		else
		if(G[a][i].first!=ojciec[a])
		{
			low[a]=min(low[a], t_wej[G[a][i].first]);
		}
	}
	if(low[a] == t_wej[a]){
        int sz = 0, v=0;
        while(v!=a)
        {
            v = stos.top();
            stos.pop();
            sz++;
            
        }
        if(sz>maksik)
        {
            maksik = sz;
           	ktory = a;
        }
    }

}
inline void skladowe(int a){
	kolorki[x]++;
	if(kolorki[x]>maksik){
		maksik=kolorki[x];
		ktory = a;
	}
	//cout<<"x: "<<x<<" w tym: "<<a<<endl;
	visited[a]=x;
	for(int i=0; i<new_G[a].size(); i++){
		if(visited[new_G[a][i]]!=x)
			skladowe(new_G[a][i]);
	}
}
inline void route(int a){
	visited[a]=x;
	//cout<<"ide: "<<a<<endl;
    for(auto u:G[a]){
        if(visited[u.first]!=x){
            //deb2 cout<<"obracam krawedz "<<edges[u.second].first<<" "<<edges[u.second].second<<endl;
            if(edges[u.second].first==a && edges[u.second].second==u.first) obrot[u.second] = 1;
            else obrot[u.second] = 0;
            route(u.first);
        }
        else{
            if(edges[u.second].first==a && edges[u.second].second==u.first) obrot[u.second] = 0;
            else obrot[u.second] = 1;
        }
    }

}
int main(){
	ios_base::sync_with_stdio(false);
	int n, m;
	cin>>n>>m;
	for(int i=0; i<m; i++){
		int a, b;
		cin>>a>>b;
		edges.push_back(mp(a, b));
		G[a].push_back(mp(b,i));
		G[b].push_back(mp(a,i));
	}
	dfs(1);
	for(int i=0; i<edges.size(); i++){
		int a = edges[i].first, b = edges[i].second;
		if((low[a] > t_wej[ojciec[a]] && ojciec[a]==b) || (low[b]>t_wej[ojciec[b]] && ojciec[b]==a))
			continue;
		new_G[edges[i].first].push_back(edges[i].second);
		new_G[edges[i].second].push_back(edges[i].first);
	}
	x=2;
	x++;
	cout<<maksik<<endl;
	route(ktory);
	for(int i=0; i<edges.size(); i++){
		if(obrot[i]!=1){
			cout<<edges[i].first<<" "<<edges[i].second<<endl;
		}
		else
			cout<<edges[i].second<<" "<<edges[i].first<<endl;
	}
}