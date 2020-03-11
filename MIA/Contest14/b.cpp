#include<bits/stdc++.h>
using namespace std;

int main(){
	ios_base::sync_with_stdio(false);
	long long int a, b, result = 0;
	cin>>a>>b;
	for(int i=0; i <= 60; i++){
		long long int temp = (1LL<<i) - 1;
		for(int j=0; j<i-1; j++){
			long long int temp2 = temp - (1LL<<j);
			if( temp2 >= a && temp2 <= b)
				result++;
		}
	}
	cout<<result<<endl;
}