#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+7;
long long int input[maxn];

int main(){
	ios_base::sync_with_stdio(false);
	int n;
	cin>>n;
	for(int i=0; i<n; i++)
		cin>>input[i];
	long long int result = 0, last = input[n-1];
	result += last;
	for(int i=n-2; i>=0; i--){
		result+= max(min(last-1,input[i]), (long long int)0);
		last = max(min(last-1, input[i]), (long long int)0);
	}
	cout<<result;
}