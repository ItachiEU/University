#include <bits/stdc++.h>

using namespace std;
 
 
long long int getLen(long long int x)
{
    long long int res=0;
    while(res*(res-1)/2<=x) 
    	res++;
    res--;
    
    if(res*(res-1)/2==x)
        return res;
    return -1;
}
 
int main()
{
	int a, b, c, d;
	ios_base::sync_with_stdio(false);
    cin>>a>>b>>c>>d;
    int x=getLen(a);
    int y=getLen(d);
    
    if(a==0 && b==0 && c==0 && d==0)
        cout<<0;
    else
    if(x==-1 || y==-1)
        cout<<"Impossible"; 
    else
    if(!a && !b && !c)
        for(int i=0;i<y;i++) cout<<'1';
    else
    if(!b && !c && !d)
        for(int i=0;i<x;i++) cout<<'0';
    else
    if(x*y!=b+c)
        cout<<"Impossible";
    else
    {
        int n=getLen(a*1LL+b*1LL+c*1LL+d*1LL);
        for(int i=0;i<n;i++)
        {
            if(x>0 && b>=y)
            {
                cout<<0;
                x--, b-=y;
            }
            else
            if(y>0 && c>=x)
            {
                cout<<1;
                y--, c-=x;
            }
        }
    }
}