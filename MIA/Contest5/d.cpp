#include<bits/stdc++.h>
using namespace std;
#define mp make_pair
const int INF=1e9+7, maxn = 1e6+5;
const int pot = (1<<18);
vector<int> temp;
int input[maxn];
struct baum
{
	vector<pair<int, int> > tree;

	baum(void):tree(2*pot, mp(-INF, 0)){};

	void update(int pos, int val){
		int poz = pos+pot;
		tree[poz].first = val;
		tree[poz].second = pos;
		poz/=2;
		while(poz>=1){
			tree[poz]=max(tree[poz*2], tree[poz*2+1]);
			poz/=2;
		}
	}
	int maksik(int l, int p){
		int a = l+pot, b = p+pot;
		int result = -INF, resi = 0;
		while(a<=b){
			if(a%2==1){
				if(tree[a].first>result)
					{
						result=tree[a].first;
						resi=tree[a].second;
					}
				else
				if(tree[a].first==result)
					resi=max(tree[a].second, resi); 
			}
			if(b%2==0){
				if(tree[b].first>result)
					{
						result=tree[b].first;
						resi=tree[b].second;
					}
				else
				if(tree[b].first==result)
					resi=max(tree[b].second, resi); 					
			}
			a=(a+1)/2;
			b=(b-1)/2;
		}
		if(result!=-INF)
			return resi;
		else
			return -1;
	}
	void wypisz(int n)
	{
		for(int i=0; i<n; i++)
		{
			cout<<tree[i+pot].first<<"<->"<<tree[i+pot].second<<" "; 
		}
		cout<<endl;
	}
};

int main(){
	ios_base::sync_with_stdio(false);
	int n;
	cin>>n;
	baum drzewko;
	for(int i=0; i<n; i++){
		int a;
		 cin>>a;
		 input[i]=a;
		 drzewko.update(i, a);
	}
	int licznik=0;
	while(licznik<n){
		int pocz = 0, kon = n-1;
		while(kon>=0){
			int index = drzewko.maksik(pocz, kon);
			if(index==-1)
				break;
			drzewko.update(index, -INF);
			temp.push_back(input[index]);
			kon = index - 1;
			licznik++;
		}
		for(int i=temp.size()-1; i>=0; i--)
			cout<<temp[i]<<" ";
		cout<<endl;
		temp.resize(0);
	}
}