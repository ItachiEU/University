#include<bits/stdc++.h>
using namespace std;
priority_queue<int> q;

int main(){
	ios_base:sync_with_stdio(false);
	int n, x;
	cin>>n;
	for(int i=0; i<n; i++){
		cin>>x;
		q.push(x);
	}
	int sum1 = 0, sum2 =0, ind = 0;
	while(!q.empty()){
		int val = q.top();
		q.pop();
		if(ind%2==0)
			sum1+=val;
		else
			sum2+=val;
		ind++;
	}
	cout<<sum1<<" "<<sum2<<endl;
}