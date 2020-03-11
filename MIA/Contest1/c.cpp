#include<bits/stdc++.h>
using namespace std;

unsigned long long int mult(unsigned long long int a, unsigned long long int b, unsigned long long int C){
	unsigned long long int wynik = 0;
	while (b > 0) {
   	if (b % 2 == 1)
     	wynik += a;
    wynik %=C;
    a *= 2;
    a %=C;
    b /= 2;
  }
  return wynik;
}

long long int exponentMod(long long int A, long long int B, long long int C) 
{ 
    if (A == 0) 
        return 0; 
    if (B == 0) 
        return 1; 
  
    long long int y; 
    if (B % 2 == 0) { 
        y = exponentMod(A, B / 2, C); 
        y = mult(y, y, C) %C;
        //y = (y * y) % C; 
    } 
  
    else { 
        y = A % C; 
        y = mult(y, exponentMod(A, B - 1, C), C) %C;
       // y = (y * exponentMod(A, B - 1, C) % C) % C; 
    } 
  
    return (long long int)((y + C) % C); 
} 
int main(){
	ios_base::sync_with_stdio(false);
	int t;
	cin>>t;
	unsigned long long int n, k, m;
	for(int i=0; i<t; i++){
		cin>>n>>k>>m;
		cout<<exponentMod(k,n,m)<<endl;
	}
}