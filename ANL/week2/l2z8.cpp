#include <bits/stdc++.h>

using namespace std;

double fx_weak(double x)
{
   return 4040.0 * ((sqrt(pow(x, 11.0) + 1.0) - 1.0) / pow(x, 11.0));
}
double fx_better(double x)
{
   return 4040.0 / (sqrt(pow(x, 11) + 1.0) + 1.0);
}

int main()
{
   cout << fx_weak(0.001) << "\n"
        << fx_better(0.001) << endl;
}