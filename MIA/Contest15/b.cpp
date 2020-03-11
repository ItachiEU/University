#include <bits/stdc++.h>
using namespace std;

int a1, a2, a3;
vector<int> result;

void init(){
	int c1, c2, c3;
	cout<<"? 1 2\n";
	fflush(stdout);
	cin>>c1;
	cout<<"? 1 3\n";
	fflush(stdout);
	cin>>c2;
	cout<<"? 2 3\n";
	fflush(stdout);
	cin>>c3;
	a3 = (c3 - c1 + c2)/2;
	a1 = c2 - a3;
	a2 = c1 - a1;
	result.push_back(a1);
	result.push_back(a2);
	result.push_back(a3);
}

int main(){
	ios_base::sync_with_stdio(false);
	int n;
	cin>>n;
	init();
	int i = 4;
	while(i<=n){
		cout<<"? 1 "<<i<<endl;
		fflush(stdout);
		i++;
		int temp;
		cin>>temp;
		result.push_back(temp-a1);
	}
	cout<<"!";
	for(int i=0; i<result.size(); i++)
		cout<<" "<<result[i];
	fflush(stdout);
}