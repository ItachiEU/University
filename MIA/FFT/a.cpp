#include<bits/stdc++.h>
using namespace std;

typedef complex<double> comp;
const double PI = acos(-1);

void fft(vector<comp> & a, bool invert) {
    int n = a.size();
    if (n == 1)
        return;

    vector<comp> a_even(n / 2), a_odd(n / 2);
    for (int i = 0; 2 * i < n; i++) {
        a_even[i] = a[2*i];
        a_odd[i] = a[2*i+1];
    }
    fft(a_even, invert);
    fft(a_odd, invert);

    double ang = 2 * PI / n * (invert ? -1 : 1);

    comp w(1), wn(cos(ang), sin(ang));

    for (int i = 0; 2 * i < n; i++) {
        a[i] = a_even[i] + w * a_odd[i];
        a[i + n/2] = a_even[i] - w * a_odd[i];
        if (invert) {
            a[i] /= 2;
            a[i + n/2] /= 2;
        }
        w *= wn;
    }
}
vector<long long int> multiply(vector<long long int> const& a, vector<long long int> const& b) {
    vector<comp> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < a.size() + b.size()) 
        n <<= 1;
    fa.resize(n);
    fb.resize(n);

    fft(fa, false);
    fft(fb, false);
    for (int i = 0; i < n; i++)
        fa[i] *= fb[i];
    fft(fa, true);

    vector<long long int> result(n);
    for (int i = 0; i < n; i++)
        result[i] = round(fa[i].real());
    return result;
}
int main(){
	ios_base::sync_with_stdio(false);
	int t, n, a;
	cin>>t;
	while(t--){
		cin>>n;
		vector<long long int> t1(n+1, 0), t2(n+1, 0);
		for(int i=0; i<=n; i++)
			cin>>t1[i];
		for(int i=0; i<=n; i++)
			cin>>t2[i];
		vector<long long int> res = multiply(t1, t2);
		for(int i=0; i<2*n+1; i++)
			cout<<res[i]<<" ";
		cout<<endl;
	}
}