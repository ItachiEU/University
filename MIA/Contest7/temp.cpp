#include <bits/stdc++.h>
const int SZ=1e5+5;
typedef long long ll;
using namespace std;
 
ll a,b,c,d;
 
ll getLen(ll x)
{
    ll res=0;
    while(res*(res-1)/2LL<=x) res++;
    res--;
    
    if(res*(res-1)/2LL==x)
        return res;
    return -1;
}
 
int main()
{
    cin>>a>>b>>c>>d;
    ll x=getLen(a);
    ll y=getLen(d);
    
    if(a+b+c+d==0)
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
        int n=getLen(a+b+c+d);
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