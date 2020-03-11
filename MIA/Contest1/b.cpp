#include<bits/stdc++.h>
using namespace std;

int main(){
	ios_base::sync_with_stdio(false);
	long long int k,n,m,x1,y1,x2,y2;
	cin>>k;
	while(k--){
		cin>>n>>m>>x1>>y1>>x2>>y2;
		long long int dol, gora, prawo, lewo;
		dol = min(m-y1, m-y2);
		gora = min(y1-1, y2-1);
		prawo = min(n-x1,n-x2);
		lewo = min(x1-1, x2-1);
		long long int x,y,sumka,sumka2, extrax, extray;
		x = lewo + prawo +1;
		y = gora + dol +1;
		sumka = x*y*2;
		extrax = 2*x-n;
		extray = 2*y-m;
		if(extrax < 0 || extray < 0)
			sumka2 = 0;
		else
			sumka2 = extrax*extray;
		long long int result = n*m - sumka + sumka2;
		cout<<result<<endl;

	}	
}