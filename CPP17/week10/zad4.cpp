#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[])
{
   for (int i = 1; i < argc; i++)
   {
      auto directory = filesystem::path(argv[i]);
      if (!filesystem::exists(directory))
      {
         cout << "There is no such directory." << endl;
         continue;
      }
      else if (!filesystem::is_directory(directory))
      {
         cout << "That is not a directory" << endl;
         continue;
      }

      for (auto component : filesystem::directory_iterator(directory))
      {
         cout << component.path().filename() << endl;
      }
   }
}