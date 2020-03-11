#include<bits/stdc++.h>
#define mp make_pair
using namespace std;
const int maxn=1e5+7;
vector<pair<int, int> > query, input;
int visited[maxn], d[maxn], ancestor[maxn][19], values[maxn], final_values[maxn];
vector<int> G[maxn];
queue<int>q;
void BFS(int a)
{
    q.push(a);

    while(!q.empty())
    {
        int v=q.front();
        q.pop();
        visited[v]=1;
        for(int i=0; i<G[v].size(); i++)
        {
            if(visited[G[v][i]]==0)
            {
                q.push(G[v][i]);
                d[G[v][i]]=d[v]+1;
                ancestor[G[v][i]][0]=v;
            }
        }
    }
}
void make_ancestor(int n)
{
    for(int k=1; k<19; k++)
        for(int i=1; i<=n; i++)
        {
            ancestor[i][k]=ancestor[ancestor[i][k-1]][k-1];
        }
}
int lca(int a, int b)
{
    if(d[a]>d[b]) swap(a, b);
    for(int k=18; k>=0; k--)
    {
        if(d[ancestor[b][k]]>=d[a])
            b=ancestor[b][k];
    }
    if(a==b)
    return a;
    for(int k=18; k>=0; k--)
    {
        if(ancestor[a][k]!=ancestor[b][k])
        {
            a = ancestor[a][k];
            b = ancestor[b][k];
        }
    }
    return ancestor[a][0];
}
void dfs(int a){
	visited[a]=2;
	for(int i=0; i<G[a].size(); i++){
		if(visited[G[a][i]]!=2)
			dfs(G[a][i]);
	}
	for(int i=0; i<G[a].size(); i++){
		if(G[a][i]!=ancestor[a][0])
			final_values[a]+=final_values[G[a][i]];
	}
	final_values[a]+=values[a];
}
int main(){
	ios_base::sync_with_stdio(false);
	int n, m;
	cin>>n;
	for(int i=0; i<n-1;i++){
		int a, b;
		cin>>a>>b;
		input.push_back(mp(a, b));
		G[a].push_back(b);
		G[b].push_back(a);
	}
	cin>>m;	
	for(int i=0; i<m; i++){
		int a, b;
		cin>>a>>b;
		query.push_back(mp(a,b));
	}
	d[1]=0;
    visited[1]=1;
    ancestor[1][0]=1;
    BFS(1);
    make_ancestor(n);
    for(int i=0; i<query.size(); i++){
    	values[query[i].first]++;
    	values[query[i].second]++;
    //	cout<<"lca: "<<lca(query[i].first, query[i].second)<<endl;
    	values[lca(query[i].first, query[i].second)]-=2;
    }	
    dfs(1);
   // for(int i=1; i<=n; i++)
    //	cout<<i<<": "<<final_values[i]<<endl;
    for(int i=0; i<n-1; i++){
    	if(d[input[i].first]>d[input[i].second])
    	cout<<final_values[input[i].first]<<" ";
    	else
    	cout<<final_values[input[i].second]<<" ";
    }
}