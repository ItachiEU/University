#include<bits/stdc++.h>
using namespace std;
vector<pair<int, int> > input;
int main(){
	ios_base::sync_with_stdio(false);
	int n, m;
	cin>>n>>m;
	for(int i=0; i<m; i++){
		int a, b;
		cin>>a>>b;
		input.push_back(make_pair(a, b));
	}
	if(n == 1){
		cout<<"1\n";
		return 0;
	}
	int ans = -1;
	for(int i=1; i<=100; i++){
		for(int j=0; j<input.size(); j++){
			if(((input[j].first+i-1)/i)!=input[j].second)
				break;
			if(j==input.size()-1){
				if(ans == -1)
					ans = (n+i-1)/i;
				else
				if(ans != -1 && (n+i-1)/i != ans){
					cout<<"-1\n";
					return 0;
				}
			}
		}
	}
	cout<<ans<<endl;
}