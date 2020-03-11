#include<bits/stdc++.h>
using namespace std;
const int maxn=1e3+7;
const long long int INF = 1e18+4;

long long int x, suma;

long long int ludzie[maxn], ludzie_rek[maxn], visited[maxn], ojciec[maxn];

vector<pair<long long int, long long int> > G[maxn];
priority_queue<long long int> q;

void dfs(int a){
	visited[a] = x;
	for(int i=0; i<G[a].size(); i++){
		if(visited[G[a][i].first]!=x){
			ojciec[G[a][i].first] = a;
			dfs(G[a][i].first);
		}
	}
	ludzie_rek[a] = ludzie[a];
	for(int i=0; i<G[a].size(); i++){
		if(G[a][i].first  != ojciec[a])
			ludzie_rek[a] += ludzie_rek[G[a][i].first];
	}
	for(int i=0; i<G[a].size(); i++){
		if(G[a][i].first  == ojciec[a]){
			suma += ludzie_rek[a]*G[a][i].second;
			q.push(ludzie_rek[a]*G[a][i].second);
		}
	}
}

int main(){
	ios_base::sync_with_stdio(false);
	int n, k;
	cin>>n>>k;
	for(int i=1; i<=n; i++)
		cin>>ludzie[i];
	for(int i=0; i<n-1; i++){
		long long int a, b, c;
		cin>>a>>b>>c;
		G[a].push_back(make_pair(b,c));
		G[b].push_back(make_pair(a,c));
	}
	long long int res = INF, temp;
	for(int i=1; i<=n; i++){
		x++;
		suma = 0;
		temp = k;
		ojciec[i] = i;
		dfs(i);
		while(temp--){
			suma-=q.top();
			q.pop();
		}
		while(!q.empty())
				q.pop();
		if(suma<res)
				res = suma;
		for(int j=1; j<=n; j++){
			ludzie_rek[j] = 0;
			ojciec[j] = 0;
		}
	}
	cout<<res<<endl;
}