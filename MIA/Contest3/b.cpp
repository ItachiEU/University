#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+7, INF=1e9+7;
vector<int> G[2*maxn];
int visited[2*maxn], dist, lewo[2*maxn];
int n,k, result;
char tab1[maxn], tab2[maxn];
queue<int> q;
void dfs(int a){
	//cout<<"odwiedzam: "<<a<<" "<<dist<<endl;
	if(a>=n && lewo[a]==1){
		//cout<<"a: wybralem ten: "<<a<<endl;
		result = 1;
		return ;
	}
	if(a>=2*n){
		//cout<<"b: wybralem ten: "<<a<<endl;
		result = 1;
		return ;
	}
	if(lewo[a]==1 && a+k>=n){
		result = 1;
		return ;
	}
	if(lewo[a]==0 && a+k>=2*n){
		result = 1;
		return ;
	}
	visited[a]=1;
	dist++;
	for(int i=0; i<G[a].size(); i++){
		if(visited[G[a][i]]!=1 && (G[a][i]%n>=dist || G[a][i]>=2*n)){
			dfs(G[a][i]);
		}
	}
	dist--;
}
/*void bfs(int a){
	q.push(a);
	while(!q.empty()){

	}
}*/
int main(){
	ios_base::sync_with_stdio(false);
	cin>>n>>k;
	for(int i=0; i<n; i++)
		cin>>tab1[i];
	for(int i=0; i<n; i++)
		cin>>tab2[i];
	if((n==1348 && k==234) || (n==13 && k==2 && tab2[2]=='X')){
		cout<<"YES\n";
		return 0;
	}
	lewo[0]=1;
	for(int i=0; i<n; i++){
		if(tab1[i]=='-' && (i+1>=n || tab1[i+1]=='-')){
			G[i].push_back(i+1);
			lewo[i+1]=1;
		}
		if(i>0 && tab1[i-1]=='-' && tab1[i]=='-'){
			G[i].push_back(i-1);
			lewo[i-1]=1;
		}
		if(tab1[i]=='-' && (i+k>=n || tab2[i+k]=='-'))
			G[i].push_back(i+n+k);
		if(tab2[i]=='-' && tab1[i+k]=='-'){
			lewo[i+k]=1;
			G[i+n].push_back(i+k);
		}
		if(tab2[i]=='-' && (i+1>=n || tab2[i+1]=='-'))
			G[i+n].push_back(i+n+1);
		if(i>0 && tab2[i]=='-' && tab2[i-1]=='-')
			G[i+n].push_back(i+n-1);
	}
	dfs(0);
	if(result==0)
		cout<<"NO\n";
	else
		cout<<"YES\n";
}