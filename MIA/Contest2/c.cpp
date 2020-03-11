#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+5;
set<long long int> result, temp, temp2;
long long int t[maxn];

int main(){
	ios_base::sync_with_stdio(false);
	long long int n;
	cin>>n;
	for(int i=0; i<n; i++)
		cin>>t[i];
	temp.insert(t[0]);
	result.insert(temp.begin(), temp.end());
	for(int i=1; i<n; i++){
		if(i%2==1){
			for(auto s: temp){
				temp2.insert(__gcd(t[i],s));
			}
			temp2.insert(t[i]);
			result.insert(temp2.begin(), temp2.end());
			temp.clear();
		}
		else{
			for(auto s: temp2){
				temp.insert(__gcd(t[i], s));
			}
			temp.insert(t[i]);
			result.insert(temp.begin(), temp.end());
			temp2.clear();
		}
	}
	cout<<result.size()<<endl;
}