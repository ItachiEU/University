#include <bits/stdc++.h>
using namespace std;

class Simple
{
public:
   uint64_t counter = 1;
   virtual ~Simple()
   {
      cerr << "destructor: " << counter << endl;
   }
};

void recursive(int m, unique_ptr<vector<Simple>> p)
{
   if (m == 0)
      return;
   auto index = rand() % p->size();
   (*p)[index].counter += m;
   recursive(m - 1, move(p));
}

int main()
{

   srand(time(NULL));
   int n = 10, m = 5;
   vector<Simple> tab(n);
   auto p = make_unique<vector<Simple>>(tab);
   recursive(m, move(p));
}