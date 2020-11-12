#include <bits/stdc++.h>
using namespace std;

template <typename F, typename G, typename H>
class compose2_t
{
   typedef typename F::result_type typ_wynik;
   typedef typename G::argument_type typ_x;

   F _f;
   G _g;
   H _h;

public:
   compose2_t(F f, G g, H h) : _f(f), _g(g), _h(h){};

   typ_wynik operator()(typ_x x)
   {
      return _f(_g(x), _h(x));
   }
};

template <typename F, typename G, typename H>
compose2_t<F, G, H>
compose2(F f, G g, H h) { return compose2_t<F, G, H>(f, g, h); };

template <typename F, typename G>
class po_kolei_t
{
public:
   typedef F First;
   typedef typename F::result_type result_type;
   typedef typename G::argument_type argument_type;
   F _f;
   G _g;

public:
   po_kolei_t(F f, G g) : _f(f), _g(g){};

   result_type operator()(argument_type x)
   {
      cout << _g(_f(x)) << endl;
      return _g(_f(x));
   }
};
template <typename F, typename G>
po_kolei_t<F, G>
po_kolei(F f, G g)
{
   return po_kolei_t<F, G>(f, g);
};

struct f : public binary_function<int, int, int>
{
   int operator()(int x, int y) { return x + y; }
};
struct g : public unary_function<int, int>
{
   int operator()(int x) { return x * 2; }
};
struct h : public unary_function<int, int>
{
   int operator()(int x) { return x - 1; }
};

int main()
{
   f f1;
   g g1;
   h h1;
   cout << compose2(f1, g1, h1)(10) << endl;
   cout << po_kolei(g1, h1)(10) << endl;

   cout << po_kolei(po_kolei(g1, h1), g1)(10) << endl;
}