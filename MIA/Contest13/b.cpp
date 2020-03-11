#include<bits/stdc++.h>

using namespace std;

set<int>res;

int main(){
	ios_base::sync_with_stdio(false);
	int n;
	cin>>n;
	for(int m=1; m<=10; m++)
		for(int l=0; l<1024; l++)
			for(int i=0; i<=9; i++)
				for(int j=0; j<=9; j++){
					int temp=0;
					int pow = 1;
					for(int s=1; s<m; s++){
						if(l&(1<<s))
							temp+=i*pow;
						else
							temp+=j*pow;
						pow*=10;
					}
					if(temp <= n){
						res.insert(temp);
						//cout<<temp<<endl;
					}
				}
	int result = res.size()-1;
	if(n==1000000000)
		result++;
	cout<<result;
}