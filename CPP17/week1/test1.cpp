#include <bits/stdc++.h>
using namespace std;
using strings = set<string>;
void zad2()
{
   string test1 = R"(Instytut Informatyki Uniwersytetu Wrocławskiego
ul. Joliot-Curie 15
50-383 Wrocław)",
          test2 = R"(C:\Program Files)", test3 = R"###()(()"")))(((""""("")""))###";

   cout << test1 << endl;
   cout << test2 << endl;
   cout << test3 << endl;
   cout << "=================================" << endl;
}
void zad3()
{
   strings s{"abcd", "efgh", "ijkl", "mnop", "qrstu", "vwxyz"};
   for (auto str : s)
      cout << str << endl;
}
void zad4()
{
   enum class name : uint16_t
   {
      Piotr,
      Kasia,
      Basia,
      Szymon,
      Kacper,
      Klaudia
   };
   auto enum_to_string = [](name imie) {
      switch (imie)
      {
      case name::Piotr:
         return "Piotr";
      case name::Kasia:
         return "Kasia";
      case name::Basia:
         return "Basia";
      case name::Szymon:
         return "Szymon";
      case name::Kacper:
         return "Kacper";
      case name::Klaudia:
         return "Klaudia";
      default:
         return "";
      }
   };
   auto printit = [enum_to_string](string msg, name imie) {
      cout << enum_to_string(imie) << ", " << msg << endl;
   };
   printit("no zarycz no", name::Piotr);
}

auto lucas_number(uint32_t n)
{
   if (n == 0)
      return 2;
   if (n == 1)
      return 1;
   return lucas_number(n - 1) + lucas_number(n - 2);
}

void solve_rownanko(double a, double b, double c)
{
   auto is_zero = [](double x) {
      double epsilon = 0.0001;
      return x < epsilon && x > -epsilon;
   };
   if (double delta = b * b - 4.0 * a * c; is_zero(delta))
   {
      cout << "x: " << -b / (2.0 * a) << endl;
      return;
   }
   else if (delta > 0)
   {
      double deltasq = sqrt(delta);
      double x1 = (-b + deltasq) / (2.0 * a);
      double x2 = (-b - deltasq) / (2.0 * a);
      cout << "x1: " << x1 << " x2: " << x2 << endl;
   }
   else
   {
      complex<double> imaginare = sqrt(-delta) * 1i / (2.0 * a);
      double real = -b / (2.0 * a);
      complex<double> x1 = real + imaginare, x2 = real - imaginare;
      cout << "x1: " << x1 << " x2: " << x2 << endl;
   }
}
void zad6()
{
   //To kilka przykładów równań
   solve_rownanko(1.0, 4.0, 1.0);
   solve_rownanko(1.0, 2.0, 1.0);
   solve_rownanko(1.0, 1.0, 1.0);
}
void zad7()
{
   //Provide date in format DD.MM.YYYY
   auto print_date = [](string date) {
      switch (int month = stoi(date.substr(3, 2)); month)
      {
      case 1:
         cout << stoi(date.substr(0, 2)) << " stycznia " << stoi(date.substr(6)) << endl;
         return;
      case 2:
         cout << stoi(date.substr(0, 2)) << " lutego " << stoi(date.substr(6)) << endl;
         return;
      case 3:
         cout << stoi(date.substr(0, 2)) << " marca " << stoi(date.substr(6)) << endl;
         return;
      case 4:
         cout << stoi(date.substr(0, 2)) << " kwietnia " << stoi(date.substr(6)) << endl;
         return;
      case 5:
         cout << stoi(date.substr(0, 2)) << " maja " << stoi(date.substr(6)) << endl;
         return;
      case 6:
         cout << stoi(date.substr(0, 2)) << " czerwca " << stoi(date.substr(6)) << endl;
         return;
      case 7:
         cout << stoi(date.substr(0, 2)) << " lipca " << stoi(date.substr(6)) << endl;
         return;
      case 8:
         cout << stoi(date.substr(0, 2)) << " sierpnia " << stoi(date.substr(6)) << endl;
         return;
      case 9:
         cout << stoi(date.substr(0, 2)) << " wrzesnia " << stoi(date.substr(6)) << endl;
         return;
      case 10:
         cout << stoi(date.substr(0, 2)) << " pazdziernika " << stoi(date.substr(6)) << endl;
         return;
      case 11:
         cout << stoi(date.substr(0, 2)) << " listopada " << stoi(date.substr(6)) << endl;
         return;
      case 12:
         cout << stoi(date.substr(0, 2)) << " grudnia " << stoi(date.substr(6)) << endl;
         return;
      }
   };
   print_date("01.01.2008");
   print_date("02.02.2009");
   print_date("03.03.2010");
   print_date("04.04.2011");
   print_date("05.05.2012");
   print_date("01.12.2020");
}
int main()
{
   zad2();
   zad3();
   zad4();
   cout << lucas_number(5) << " " << lucas_number(10) << " " << lucas_number(20) << endl;
   zad6();
   zad7();
}

//Zad1
//Trójznaki nie działają, aby je aktywować musimy dodac flagę kompilacji -trigraphs