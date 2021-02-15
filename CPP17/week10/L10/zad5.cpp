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

      int sum = 0;

      for (auto component : filesystem::recursive_directory_iterator(directory))
      {
         if (filesystem::is_regular_file(component))
            sum += filesystem::file_size(component.path());
      }
      cout << "Sum of regular file sizes: " << sum << endl;
   }
}