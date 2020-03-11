#include<bits/stdc++.h>
using namespace std;
const int pot=(1<<19);

struct baum
{
	vector<int> tree;
	baum(void):tree(2*pot){};
	int podmiana(int a, int val){
		int poz=a+pot, licznik=0;
		tree[poz]=val;
		poz/=2;
		while(poz>=1) //co drugi or co drugi xor
		{
			if(licznik%2==0)
				tree[poz]=(tree[poz*2] | tree[poz*2+1]);
			else
				tree[poz]=(tree[poz*2]^tree[poz*2+1]);
			poz/=2;
			licznik++;
		}
		return tree[1];
	}
};
int main(){
	ios_base::sync_with_stdio(false);
	int n, m;
	cin>>n>>m;
	baum drzewko;
	for(int i=0; i<(1<<n); i++){
		int a;
		cin>>a;
		drzewko.podmiana(i,a);
	}
	while(m--){
		int a, b;
		cin>>a>>b;
		a--;
		cout<<drzewko.podmiana(a, b)<<endl;
	}
}	