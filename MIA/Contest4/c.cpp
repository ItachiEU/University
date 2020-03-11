#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+7;
int visited[maxn], ile, kolorek, start;
vector<int> G[maxn];
vector<int> kolorki[maxn];

void dfs(int a){
	//cout<<a<<" "<<kolorek<<" "<<kolorki[kolorek].size()<<endl;
	if(kolorki[kolorek].size()==2)
			kolorek++;
	visited[a] = 1;
	if(kolorki[kolorek].size()==0)
		kolorki[kolorek].push_back(start);
	for(int i=0; i<G[a].size(); i++){
		if(visited[G[a][i]]!=1)
			dfs(G[a][i]);
	}
	//cout<<"wychodze z: "<<a<<endl;
	if(kolorki[kolorek].size()==1)
	kolorki[kolorek].push_back(a);
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
	start=-1;
	for(int i=1; i<=n; i++)
			if(G[i].size()>=3){
				ile++;
				start=i;
			}
	if(ile>1){
		cout<<"No\n";
		return 0;
	}
	//cout<<"start: "<<start<<endl;
	if(start==-1){
		start = 1;
		dfs(1);
	}
	else
		dfs(start);

	cout<<"Yes\n";
	cout<<kolorek+1<<endl;
	for(int i=0; i<kolorek+1; i++){
		cout<<kolorki[i][0]<<" "<<kolorki[i][1]<<endl;
	}
}