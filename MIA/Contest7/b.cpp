#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+7;
char input[maxn];
int licz[2];

int licz_1(int n){
	int res = 0;
	for(int i=0; i<n; i++){
		if(input[i]!='r' && i%2==0)
			licz[0]++;
		if(input[i]!='b' && i%2==1)
			licz[1]++;
	}
	int temp = min(licz[0], licz[1]);
	res +=temp;
	licz[0]-=temp;
	licz[1]-=temp;
	res+=max(licz[1], licz[0]);
	return res;
}
int licz_2(int n){
	int res = 0;
	for(int i=0; i<n; i++){
		if(input[i]!='b' && i%2==0)
			licz[0]++;
		if(input[i]!='r' && i%2==1)
			licz[1]++;
	}
	int temp = min(licz[0], licz[1]);
	res +=temp;
	licz[0]-=temp;
	licz[1]-=temp;
	res+=max(licz[1], licz[0]);
	return res;
}

int main(){
	ios_base::sync_with_stdio(false);
	int n;
	cin>>n;
	for(int i=0; i<n; i++)
		cin>>input[i];
	int result1=0, result2=0;
	result1=licz_1(n);
	licz[0]=0; licz[1]=0;
	result2=licz_2(n);
	cout<<min(result1, result2);

}