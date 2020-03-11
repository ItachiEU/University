#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
int d[maxn], visited[maxn], deep, init[maxn], goal[maxn];
vector<int>G[maxn], result;
void depth(int a){
	d[a]=deep;
	visited[a] = 1;
	deep++;
	for(int i=0; i<G[a].size(); i++){
		if(visited[G[a][i]]==0)
			depth(G[a][i]);
	}
	deep--;
}
void dfs(int a, int parzyste, int nieparzyste){
		//cout<<a<<" "<<parzyste<<" "<<nieparzyste<<" d: "<<d[a]<<endl;
		visited[a]=2;
		if(d[a]%2==0){
			if(init[a]==goal[a] && parzyste%2==1){
				parzyste++;
				result.push_back(a);
			}else
			if(init[a]!=goal[a] && parzyste%2==0){
				parzyste++;
				result.push_back(a);
			}
		}else{
			if(init[a]==goal[a] && nieparzyste%2==1){
				nieparzyste++;
				result.push_back(a);
			}else
			if(init[a]!=goal[a] && nieparzyste%2==0){
				nieparzyste++;
				result.push_back(a);
			}
		}
		for(int i=0; i<G[a].size(); i++){
			if(visited[G[a][i]]!=2)
				dfs(G[a][i],parzyste, nieparzyste);
		}
}
int main(){
	ios_base::sync_with_stdio(false);
	int n;
	cin>>n;
	for(int i=0; i<n-1; i++){
		int a, b;
		cin>>a>>b;
		G[a].push_back(b);
		G[b].push_back(a);
	}
	for(int i=1; i<=n; i++)
			cin>>init[i];
	for(int i=1; i<=n; i++)
			cin>>goal[i];
	d[1]=0;
	deep = 0;
	depth(1);
	dfs(1, 0, 0);
	cout<<result.size()<<endl;
	for(int i=0; i<result.size(); i++)
			cout<<result[i]<<endl;
}