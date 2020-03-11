#include<bits/stdc++.h>
using namespace std;

vector<string> dictionary;

int main(){
	ios_base::sync_with_stdio(false);
	srand(time(NULL));
	int n = rand()%10+1;
	for(int i=0; i<n; i++){
		int k = rand()%8;
		switch(k){
			case 0:{
				cout<<"cd ..\n";
			}
			case 1:{
				if(dictionary.size()>0){
					int j = rand()%(dictionary.size());
					cout<<"cd "<<dictionary[j]<<"\n";
				}
				else
				cout<<"cd kupa\n";	
			}
			case 2:{
				int len = rand()%20+1;
				string a = "";
				for(int i=0; i<len; i++)
					a.push_back((char)(97+rand()%26));
				dictionary.push_back(a);
				cout<<"mkdir "<<a<<"\n";
			}
			case 3:{
				cout<<"pwd\n";
			}
			case 4:{
				if(dictionary.size()>0){
					int j = rand()%(dictionary.size());
					cout<<"cd "<<dictionary[j]<<"\n";
				}
				else
				cout<<"cd kupa\n";	
			}
			case 5:{
				int len = rand()%20+1;
				string a = "";
				for(int i=0; i<len; i++)
					a.push_back((char)(97+rand()%26));
				dictionary.push_back(a);
				cout<<"mkdir "<<a<<"\n";
			}
			case 6:{
				if(dictionary.size()>0){
					int j = rand()%(dictionary.size());
					cout<<"cd "<<dictionary[j]<<"\n";
				}
				else
				cout<<"cd kupa\n";
			}
			case 7:{
				cout<<"pwd\n";
			}
		}
	}
}