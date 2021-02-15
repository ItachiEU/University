#include <bits/stdc++.h>
#include <filesystem>
#include <chrono>

using namespace std;

//https://stackoverflow.com/questions/61030383/how-to-convert-stdfilesystemfile-time-type-to-time-t
template <typename T>
auto convert_time(const T &time) -> std::time_t
{
   return chrono::system_clock::to_time_t(
       chrono::time_point_cast<chrono::system_clock::duration>(
           time - T::clock::now() + chrono::system_clock::now()));
}

int main(int argc, char *argv[])
{
   for (int i = 1; i < argc; i++)
   {
      if (filesystem::exists(filesystem::path(argv[i])))
      {
         auto path = filesystem::path(argv[i]);

         cout << filesystem::canonical(path) << endl;

         auto time = filesystem::last_write_time(path);
         std::time_t ctime = convert_time(time);
         std::cout << std::asctime(std::localtime(&ctime));

         cout << filesystem::file_size(argv[i]) << endl;
      }
   }
}