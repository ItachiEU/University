#include<bits/stdc++.h>
using namespace std;
vector<int> alfa[26];
int main(){
	ios_base::sync_with_stdio(false);
	string a;
	cin>>a;
	int maksik = 0;
	for(int i=0; i<a.size(); i++){
		if(a[i]-'a'>maksik)
			maksik=a[i]-'a';
		alfa[a[i]-'a'].push_back(i);
	}
	int start = alfa[maksik][0], poz;
	poz = start;
	string result ="";
	result+=(char)((int)('a')+maksik);
	for(int i=start+1; i<a.size(); i++){
		for(int j = maksik; j>=0; j--){
			vector<int>::iterator it = upper_bound(alfa[j].begin(), alfa[j].end(), poz);
			if(it!=alfa[j].end()){
				result+=(char)((int)('a')+j);
				poz = alfa[j][it-alfa[j].begin()];
				break;
			}
		}
		i = poz;
	}
	cout<<result<<endl;
}