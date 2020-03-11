#include<bits/stdc++.h>
using namespace std;
struct card{
	char color;
	int val;
};
int x;
vector<card>input;
vector<int> permutacje;

int visited[12];

int check(vector<int>& a){
	x++;
	int ile = 0;
	for(int i=0; i<a.size(); i++){
		switch(a[i]){
			case 1:
				for(int j=0; j<input.size(); j++){
					if(input[j].val == 1){
						if(visited[j]!=x){
							visited[j]= x;
							ile++;
						}
					}
				}
				if(ile == input.size()-1){
					return i+1;
				}
				break;
			case 2:
				for(int j=0; j<input.size(); j++){
					if(input[j].val == 2){
						if(visited[j]!=x){
							visited[j]= x;
							ile++;
						}
					}
				}
				if(ile == input.size()-1){
					return i+1;
				}
				break;
			case 3:
				for(int j=0; j<input.size(); j++){
					if(input[j].val == 3){
						if(visited[j]!=x){
							visited[j]= x;
							ile++;
						}
					}
				}
				if(ile == input.size()-1){
					return i+1;
				}
				break;
			case 4: // R, G, B, Y, W`
				for(int j=0; j<input.size(); j++){
					if(input[j].val == 4){
						if(visited[j]!=x){
							visited[j]= x;
							ile++;
						}
					}
				}
				if(ile == input.size()-1){
					return i+1;
				}
				break;
			case 5:
				for(int j=0; j<input.size(); j++){
					if(input[j].val == 5){
						if(visited[j]!=x){
							visited[j]= x;
							ile++;
						}
					}
				}
				if(ile == input.size()-1){
					return i+1;
				}
				break;
			case 6:
				for(int j=0; j<input.size(); j++){
					if(input[j].color == 'R'){
						if(visited[j]!=x){
							visited[j]= x;
							ile++;
						}
					}
				}
				if(ile == input.size()-1){
					return i+1;
				}
				break;
			case 7:
				for(int j=0; j<input.size(); j++){
					if(input[j].color == 'G'){
						if(visited[j]!=x){
							visited[j]= x;
							ile++;
						}
					}
				}
				if(ile == input.size()-1){
					return i+1;
				}

				break;
			case 8:
				for(int j=0; j<input.size(); j++){
					if(input[j].color == 'B'){
						if(visited[j]!=x){
							visited[j]= x;
							ile++;
						}
					}
				}
				if(ile == input.size()-1){
					return i+1;
				}
				break;
			case 9:
				for(int j=0; j<input.size(); j++){
					if(input[j].color == 'Y'){
						if(visited[j]!=x){
							visited[j]= x;
							ile++;
						}
					}
				}
				if(ile == input.size()-1){
					return i+1;
				}
				break;
			case 10:
				for(int j=0; j<input.size(); j++){
					if(input[j].color == 'W'){
						if(visited[j]!=x){
							visited[j]= x;
							ile++;
						}
					}
				}
				if(ile == input.size()-1){
					return i+1;
				}
				break;
		}
	}
}

int main(){
	ios_base::sync_with_stdio(false);
	int n;
	cin>>n;
	string line;
	getline(cin, line);
	permutacje = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	for(int i=0; i<line.size(); i++){
		card a;
		if(i%3==0)
			a.color = line[i];
		if(i%3==1){
			a.val = line[i]-'0';
			input.push_back(a);
		}
	}
	int mini = 123;
	do{
		int x = check(permutacje);
		if(x < mini)
			mini = x;
	}while(next_permutation(permutacje.begin(), permutacje.end()));
	cout<<mini<<endl;
}