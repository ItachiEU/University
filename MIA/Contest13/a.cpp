#include<bits/stdc++.h>
using namespace std;

vector<int> input;

int ile(int a){
	int res = 0;

	while(a>=1){
		if(a%2==1)
			res++;
		a/=2;
	}
	return res;
}

int main(){
	int n, m, k;
	cin>>n>>m>>k;
	for(int i=0; i<=m; i++){
		int a;
		cin>>a;
		input.push_back(a);
	}
	int End = input.size()-1;
	int result = 0;
	for(int i=0; i<m; i++){
		int temp = input[i]^input[End];
		if(ile(temp)<=k)
			result++;
	}
	cout<<result;
}