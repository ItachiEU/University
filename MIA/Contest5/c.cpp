#include<bits/stdc++.h>
using namespace std;
vector<set<int> > literki(26);

int main(){
	ios_base::sync_with_stdio(false);
	string s;
	int n;
	cin>>s;
	for(int i=0; i<s.size(); i++)
		literki[s[i]-'a'].insert(i);
	cin>>n;
	while(n--){
		int typ;
		cin>>typ;
		if(typ==1){
			int pos;
			char c;
			cin>>pos>>c;
			pos--;
			literki[s[pos]-'a'].erase(pos);
			s[pos]=c;
			literki[s[pos]-'a'].insert(pos);
		}	
		else
		if(typ==2){
			int a, b, result=0;
			cin>>a>>b;
			a--; b--;
			for(int i=0; i<26; i++){
				auto it = literki[i].lower_bound(a);
				if(it!=literki[i].end() && *it<=b)
					result++;
			}
			cout<<result<<endl;
		}
	}
}