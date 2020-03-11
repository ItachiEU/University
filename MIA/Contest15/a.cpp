#include <bits/stdc++.h>
using namespace std;
int counter;
bool check(int a){
	counter++;
	cout<<a<<endl;
	fflush(stdout);
	string b;
	cin>>b;
	return b == "yes";
}

int main(){
	ios_base::sync_with_stdio(false);

	vector<int> primes = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97};
	int temp = 0;
	for(int i=0; i<20; i++){
		if(counter>=19)
			break;
		if(check(primes[i])){
			temp++;
			if(counter>=19)
				break;
			if(primes[i]*primes[i]<=100)
			 if(check(primes[i]*primes[i])){
				temp++;
				if(counter>=19)
					break;
			}
		}
		if(temp >=2)
			break;
	}
	string result;
	temp >= 2 ? result = "composite" : result = "prime";
	cout<<result;
}