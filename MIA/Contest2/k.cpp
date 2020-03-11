#include<bits/stdc++.h>
using namespace std;
const int maxn=1e3+5;

void dfs(int a, vector<string> &input, vector<int> &sequence, vector<int> &visited){
	visited[a]=1;
	cout<<a<<endl;
	for(int i=0; i< input.size(); i++)
		if(input[a][i] == '1' && visited[i] == 0)
				dfs(i, input, sequence, visited);
	sequence.push_back(a);
}

int main(){
	ios_base::sync_with_stdio(false);
	int n;
	cin>>n;
	vector<string> input(n);
	for(string &s : input) cin>>s;
	vector<int> sequence, visited(n,0);
	dfs(0, input, sequence, visited);

	if(sequence.size() < input.size())
			cout<<"impossible\n";
	else
		for(int i=0; i<n; i++)
				cout<<sequence[i]<<" ";
	}