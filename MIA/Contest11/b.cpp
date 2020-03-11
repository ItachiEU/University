#include<bits/stdc++.h>
using namespace std;
vector<long long int> cluster1, cluster2;
long long int sumka1, sumka2, result1, result2;
int main(){
	ios_base::sync_with_stdio(false);
	int n, m;
	cin>>n>>m;
	for(int i=0; i<n; i++){
		int a;
		cin>>a;
		cluster1.push_back(a);
		sumka1+=a;
	}
	for(int i=0; i<m; i++){
		int a;
		cin>>a;
		cluster2.push_back(a);
		sumka2+=a;
	}
	sort(cluster1.begin(), cluster1.end());
	sort(cluster2.begin(), cluster2.end());
	for(int i=0; i<n-1; i++)
		result1 += min(sumka2, cluster1[i]);
	for(int i=0; i<m-1; i++)
		result2 += min(sumka1, cluster2[i]);
	cout<<min(result2+sumka1, result1 + sumka2)<<endl;
}