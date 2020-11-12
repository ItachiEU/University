#include <bits/stdc++.h>
using namespace std;

void zad1()
{
   cout << "Zadanie 1: \n";
   cout << numeric_limits<long long int>::max() << endl;
   cout << numeric_limits<long long int>::min() << endl;
   cout << numeric_limits<long long int>::digits << endl;
   cout << numeric_limits<long long int>::digits10 << endl;
   cout << endl;
}
void zad2()
{
   cout << "Zadanie 2: \n";
   cout << "Min double: " << numeric_limits<double>::min() << "\n";
   cout << "Min float: " << numeric_limits<float>::min() << "\n";

   cout << "Max double: " << numeric_limits<double>::max() << "\n";
   cout << "Max float: " << numeric_limits<float>::max() << "\n";

   cout << "1 - close to 1 double: " << (double)1 - numeric_limits<double>::denorm_min() << "\n";
   cout << "1 - close to 1 float: " << (float)1 - numeric_limits<float>::denorm_min() << "\n\n";
}
//zad3:
// source:
//https: //monoinfinito.wordpress.com/series/introduction-to-c-template-metaprogramming/
template <int N>
struct harmoniczny : ratio_add<ratio<1, N>, harmoniczny<N - 1>>
{
};

template <>
struct harmoniczny<1> : ratio<1, 1>
{
};

template <int N>
auto harmonic()
{
   if constexpr (N == 1)
   {
      return ratio<1, 1>();
   }
   else
   {
      return ratio_add<decltype(harmonic<N - 1>()), ratio<1, N>>();
   }
}
//Zadanie 4
template <
    typename From,
    typename To,
    typename std::enable_if_t<
        std::is_pointer<From>::value> * = nullptr,
    typename std::enable_if_t<
        std::is_convertible<
            typename std::remove_pointer<From>::type,
            To>::value> * = nullptr>

void moveFromTo(From from, To &to)
{
   to = std::move(*from);
   cout << "Pointer version" << endl;
   return;
}

template <
    typename From,
    typename To,
    typename std::enable_if_t<
        std::is_convertible<From, To>::value> * = nullptr>
void moveFromTo(From &from, To &to)
{
   to = std::move(from);
   cout << "Value version" << endl;
   return;
}

//zadanie 5
void print_matrix(vector<vector<double>> &M)
{
   int n = M.size();
   for (int i = 0; i < n; i++)
   {
      for (int j = 0; j < n; j++)
      {
         cout << M[i][j] << " ";
      }
      cout << endl;
   }
}
random_device rd;
mt19937 mt(rd());
const int n1 = 10, n2 = 100, n3 = 1000;
// array<array<double, n1>, n1> M1;
// array<array<double, n2>, n2> M2;
// array<array<double, n3>, n3> M3;

template <int N>
struct Matrix
{
   double t[N * N];
   double *operator[](const int i) { return t + i * N; };
};

Matrix<n1> M1;
Matrix<n2> M2;
Matrix<n3> M3;

void matrix_fill()
{
   uniform_real_distribution<double> dist(0.5, 2.0);
   for (int i = 0; i < n1; i++)
      for (int j = 0; j < n1; j++)
         M1[i][j] = dist(mt);
   for (int i = 0; i < n2; i++)
      for (int j = 0; j < n2; j++)
         M2[i][j] = dist(mt);
   for (int i = 0; i < n3; i++)
      for (int j = 0; j < n3; j++)
         M3[i][j] = dist(mt);
}
void squareM1()
{
   Matrix<n1> temp;
   // array<array<double, n1>, n1> temp = {};
   for (int i = 0; i < n1; i++)
   {
      for (int j = 0; j < n1; j++)
      {
         for (int k = 0; k < n1; k++)
            temp[i][j] += M1[i][k] * M1[k][j];
      }
   }
   M1 = temp;
}
void squareM2()
{
   Matrix<n2> temp;
   // array<array<double, n2>, n2> temp = {};
   for (int i = 0; i < n2; i++)
   {
      for (int j = 0; j < n2; j++)
      {
         for (int k = 0; k < n2; k++)
            temp[i][j] += M2[i][k] * M2[k][j];
      }
   }
   M2 = temp;
}

void squareM3()
{
   Matrix<n3> temp;
   // array<array<double, n3>, n3> temp = {};
   for (int i = 0; i < n3; i++)
   {
      for (int j = 0; j < n3; j++)
      {
         for (int k = 0; k < n3; k++)
            temp[i][j] += M3[i][k] * M3[k][j];
      }
   }
   M3 = temp;
}

void zad5()
{
   // vector<vector<double>> M1(n1, vector<double>(n1));
   // vector<vector<double>> M2(n2, vector<double>(n2));
   // vector<vector<double>> M3(n3, vector<double>(n3));
   matrix_fill();

   chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
   for (int i = 0; i < 100; i++)
      squareM1();
   chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
   chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double>>(t2 - t1);
   cout << "100x100 Time " << time_span.count() / 100 << " seconds.\n\n";

   t1 = chrono::high_resolution_clock::now();
   for (int i = 0; i < 100; i++)
      squareM2();
   t2 = chrono::high_resolution_clock::now();
   time_span = chrono::duration_cast<chrono::duration<double>>(t2 - t1);
   cout << "1000x1000 Time " << time_span.count() / 100 << " seconds.\n\n";

   t1 = chrono::high_resolution_clock::now();
   squareM3();
   t2 = chrono::high_resolution_clock::now();

   time_span = chrono::duration_cast<chrono::duration<double>>(t2 - t1);
   cout << "10000x10000 Time " << time_span.count() << " seconds.\n\n";
}

int main()
{
   zad1();
   zad2();

   //dla 47 i wiecej juz jest błąd
   using h = harmoniczny<46>;
   cout << "zadanie3: " << endl;
   cout << h::num << "/" << h::den << endl;
   cout << endl;

   //Zadanie 4
   string s0 = "s0";
   string s1 = "s1";
   string s2;
   int a;
   long long int b = 1;
   string *s3 = new string("s3");

   moveFromTo(s1, s2);
   cout << s2 << endl;

   moveFromTo(b, a);

   moveFromTo(s3, s0);
   cout << s0 << endl;

   cout << *s3 << endl;
   cout << s1 << endl;

   cout << "zadanie 5: " << endl;

   zad5();
}