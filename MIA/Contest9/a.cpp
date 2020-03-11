#include<bits/stdc++.h>
using namespace std;
int ile[26];
int main(){
	ios_base::sync_with_stdio(false);	
	string a;
	cin>>a;
	for(int i=0; i<a.size(); i++)
		ile[a[i]-'a']++;
	int np =0;
	for(int i=0; i<26; i++)
		if(ile[i]%2==1)
			np++;
	if(np<=1){
		cout<<"First\n";
		return 0;
	}
	if(np%2==1)
		cout<<"First\n";
	else
		cout<<"Second\n";
}