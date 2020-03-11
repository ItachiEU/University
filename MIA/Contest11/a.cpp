#include<bits/stdc++.h>
using namespace std;
set<string>secik;
void obroty(string a)
{
	if(secik.find(a)!=secik.end())return;
	secik.insert(a);
	string s1 ={a[1],a[2],a[3],a[0],a[4],a[5]};
	obroty(s1);
	string s2 ={a[0],a[4],a[2],a[5],a[3],a[1]};
	obroty(s2);
}
int main()
{
	ios_base::sync_with_stdio(false);
	int res=0;
	string s;
	cin>>s;
	sort(s.begin(),s.end());
	do{
		if(secik.find(s)!=secik.end()) 
			continue;
		res++;
		obroty(s);
	}while(next_permutation(s.begin(),s.end()));
	cout<<res<<endl;
}