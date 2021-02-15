#include <bits/stdc++.h>
using namespace std;

// zad 1

template <long long int n>
struct Lucas
{
   static constexpr long long value = Lucas<n - 1>::value + Lucas<n - 2>::value;
};

template <>
struct Lucas<1>
{
   static constexpr long long value = 1;
};

template <>
struct Lucas<0>
{
   static constexpr long long value = 2;
};
//zad 2

template <long long int n, long long int k>
struct Binom
{
   static constexpr long long int value = n * Binom<n - 1, k - 1>::value / k;
};

template <long long int n>
struct Binom<n, 0>
{
   static constexpr long long int value = 1;
};

template <long long int n>
struct Binom<n, n>
{
   static constexpr long long int value = 1;
};

//zad 3

template <int a, int b>
struct gcdd
{
   static constexpr int value = gcdd<b, a % b>::value;
};

template <int a>
struct gcdd<a, 0>
{
   static constexpr int value = a;
};

// zad 4

template <size_t N, typename T>
struct dotProduct
{
   static constexpr T result(T *a, T *b)
   {
      return *a * *b + dotProduct<N - 1, T>::result(a + 1, b + 1);
   }
};

template <typename T>
struct dotProduct<0, T>
{
   static constexpr T result(T *, T *)
   {
      return T{};
   }
};

// zad 5

constexpr int on_stack_max = sizeof(string);

template <typename T>
struct On_heap
{
   On_heap() : p(new T) {}
   ~On_heap() { delete p; }
   T &operator*() { return *p; }
   T *operator->() { return p; }
   On_heap(const On_heap &) = delete;
   On_heap &operator=(const On_heap &) = delete;

private:
   T *p;
};

template <typename T>
struct Scoped
{
   Scoped() {}
   T &operator*() { return x; }
   T *operator->() { return &x; }
   Scoped(const Scoped &) = delete;
   Scoped &operator=(const Scoped &) = delete;

private:
   T x;
};

template <typename T>
struct Obj_holder
{
   using type = typename conditional<
       (sizeof(T) <= on_stack_max),
       Scoped<T>,
       On_heap<T>>::type;
};

//zad 5 part 2

constexpr int on_stack_max_arr = sizeof(string);

template <typename T>
struct On_heap_array
{
   using elemtype = typename remove_extent<T>::type;
   On_heap_array() : p(new elemtype[sizeof(T) / sizeof(elemtype)]) {} // new t[size]
   ~On_heap_array() { delete[] p; }                                   // delete[] p
   elemtype &operator*() { return *p; }
   elemtype *operator->() { return p; }
   On_heap_array(const On_heap_array &) = delete;
   On_heap_array &operator=(const On_heap_array &) = delete;
   const elemtype &operator[](const int i) const { return p[i]; };
   elemtype &operator[](const int i) { return p[i]; };

private:
   elemtype *p;
};

template <typename T>
struct Scoped_array
{
   Scoped_array() {}
   T &operator*() { return x; }
   T *operator->() { return &x; }
   Scoped_array(const Scoped_array &) = delete;
   Scoped_array &operator=(const Scoped_array &) = delete;

private:
   T x;
};

template <typename T>
struct Arr_holder
{
   using type = typename conditional<
       (sizeof(T) <= on_stack_max_arr),
       Scoped_array<T>,
       On_heap_array<T>>::type;
};

int main()
{
   Lucas<10> luc;
   cout << "Lucas: " << luc.value << endl;

   Binom<6, 3> bin;
   cout << "6 po 3: " << bin.value << endl;

   gcdd<32, 48> nwd;

   cout << "nwd(32,48): " << nwd.value << endl;

   int t1[4] = {1, 2, 3, 4};
   int t2[4] = {4, 3, 2, 1}; // dotProduct = 20

   cout << "dotProduct: " << dotProduct<4, int>::result(t1, t2) << endl;

   typename Obj_holder<double>::type v1;
   typename Arr_holder<int[50]>::type v2;

   *v1 = 7.0;
   cout << *v1 << endl;
   v2[40] = 3;
   cout << v2[40] << " " << v2[41] << endl;
}