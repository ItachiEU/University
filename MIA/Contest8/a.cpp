#include<bits/stdc++.h>
using namespace std;
int ct[2];
int main(){
    ios_base::sync_with_stdio(false);
    int n;
    cin>>n;
    for(int i=0; i<n; i++){
        char a;
        cin>>a;
        ct[a-'0']++;
    }
    int result = n - (2*min(ct[0], ct[1]));
    cout<<result;
}