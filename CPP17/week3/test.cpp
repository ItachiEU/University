#include <iostream>
#include <utility>
#include <string>

template <
    typename From,
    typename To,
    typename std::enable_if_t<
        std::is_pointer<From>::value> * = nullptr,
    typename std::enable_if_t<
        std::is_convertible<
            typename std::remove_pointer<From>::type,
            To>::value> * = nullptr>

void move_from_to(From from, To &to)
{
   to = std::move(*from);
   std::cout << "Pointer version" << std::endl;
   return;
}

template <
    typename From,
    typename To,
    typename std::enable_if_t<
        std::is_convertible<From, To>::value> * = nullptr>
void move_from_to(From &from, To &to)
{
   to = std::move(from);
   std::cout << "Value version" << std::endl;
   return;
}

auto main() -> int
{
   std::string s0 = "abc123";
   std::string s1 = "qwe890";
   std::string s2;
   std::string *s3 = new std::string("123abc");

   move_from_to(s1, s2);
   std::cout << s2 << std::endl;

   move_from_to(s3, s0);
   std::cout << s0 << std::endl;

   std::cout << *s3 << std::endl;
   std::cout << s1 << std::endl;

   delete s3;

   struct A
   {
   };
   struct B
   {
      A a;
      operator A() { return a; }
   };

   A a;
   B b;

   move_from_to(b, a);
}
