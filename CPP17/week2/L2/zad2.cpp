#include <bits/stdc++.h>
using namespace std;

class Line_writer
{
private:
   ofstream *of;

public:
   Line_writer()
   {
      of = new ofstream("plik.txt", ios::app);
   }
   ~Line_writer()
   {
      cout << "closing" << endl;
      of->close();
      free(of);
   }
   void write(vector<string> text)
   {
      for (auto line : text)
         (*of) << line << endl;
   }
};

int main()
{
   Line_writer lw;
   vector<string> sample = {"Judyta dała wczoraj Stefanowi czekoladki",
                            "Babuleńka miała dwa rogate koziołki",
                            "Jestem dzisiaj jakoś straszliwie głodny"};
   lw.write(sample);
   auto writer1 = make_shared<Line_writer>();
   auto writer2 = writer1;
   auto writer3 = writer1;
   auto writer4 = writer1;
   vector<string> w = {"writer1"};
   writer1->write(w);
   w = {"writer2"};
   writer2->write(w);
   w = {"writer3"};
   writer3->write(w);
   w = {"writer4"};
   writer4->write(w);
}