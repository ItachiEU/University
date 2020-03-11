#include<bits/stdc++.h>
const int maxn = 105;
const long long int INF = 1e18+7;
using namespace std;
vector<int> G[maxn];
long long int d[maxn], dp[maxn];
queue<int> q;

void bfs(int a, int n){
	for(int i=1; i<=n; i++){
		d[i] = INF;
		dp[i] = 0;
	}
	d[a] = 0;
	dp[a] = 1;
	q.push(a);
	while(!q.empty()){
		int v = q.front();
		q.pop();
		for(int i=0; i<G[v].size(); i++){
			if(d[G[v][i]] > d[v] + 1){
				d[G[v][i]] = d[v] + 1;
				dp[G[v][i]] = dp[v];
				q.push(G[v][i]);
			}
			else
			if(d[G[v][i]] == d[v] + 1)
				dp[G[v][i]] += dp[v];
		}
	}
}

int main(){
	ios_base::sync_with_stdio(false);
	double result = 1.0;
	int n, m;
	cin>>n>>m;
	for(int i=0; i<m; i++){
		int a, b;
		cin>>a>>b;
		G[a].push_back(b);
		G[b].push_back(a);
	}
	bfs(1, n);
	long long int distance = d[n], count = dp[n]; 
	for(int i=2; i<n; i++){
		bfs(i, n);
		if(d[1]+d[n] == distance)
			result = max(result, (2.0*dp[1]*dp[n])/(1.0*count));
	}
	cout.precision(12);
	cout<<fixed;
	cout<<result<<endl;
}