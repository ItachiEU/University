#include<bits/stdc++.h>
using namespace std;
const double PI = 3.1415926;
int main(){
	ios_base::sync_with_stdio(false);
	double m, n, x1, x2,y1,y2;
	double r;
	cin>>m>>n>>r;
	cin>>x1>>y1>>x2>>y2;
	double dist = abs(x2-x1), h = min(y1, y2);
	//cout<<dist<<endl;
	double result = (double)(dist/m)*PI*(h/n)*r, result2;
	result += (abs(y1-y2)/n)*r;
	result2 = (y1/n)*r + (y2/n)*r;
	//cout<< (abs(y1-y2)/n)*r<<endl;
	cout<<fixed;
	cout<<setprecision(7)<<min(result, result2)<<endl;
}