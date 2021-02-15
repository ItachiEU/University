#include <bits/stdc++.h>

using namespace std;

bool zad1(string a)
{
   regex godzina("^([0-1][0-9]|2[0-3]):([0-5][0-9])(:[0-5][0-9])?$");
   return regex_match(a, godzina);
}

bool zad2(string a)
{
   regex data(
       "^("
       "(30-(01|03|04|05|06|07|08|09|10|11|12))"
       "|"
       "(31-(01|03|05|07|08|10|12))"
       "|"
       "((0[1-9])|([1-2][0-9]))-((0[1-9])|(1[0-2])))"
       "-(?!0000)[0-9]{4}$");
   return regex_match(a, data);
}

bool zad3(string a)
{
   regex miasto(
       "^("
       "([[:upper:]]|Ą|Ć|Ę|Ł|Ń|Ó|Ś|Ź|Ż)([[:lower:]]|ą|ć|ę|ł|ń|ó|ś|ź|ż){1,}"     //pierwsze slowo
       "(-([[:upper:]]|Ą|Ć|Ę|Ł|Ń|Ó|Ś|Ź|Ż)([[:lower:]]|ą|ć|ę|ł|ń|ó|ś|ź|ż){1,})?" //opcjonalne drugie po myślniku
       "(\\s+|$)"
       ")+$");
   return regex_match(a, miasto);
}

bool zad4(string a)
{
   regex zespo(
       "\\s*\\(\\s*"
       "[0-9]+(\\.[0-9]+)?"
       "\\s*\\+\\s*"
       "[0-9]+(\\.[0-9]+)?[iI]"
       "\\s*\\)\\s*");
   return regex_match(a, zespo);
}

void zad5(string a)
{
   regex href(
       "<a\\s+(?:[^>]*?\\s+)?href=\"([^\"]*)\"");
   smatch match;
   while (regex_search(a, match, href))
   {
      cout << match.str(1) << endl;
      a = match.suffix().str();
   }
}

int main()
{
   string godzina, data, miasto, zespo, href;
   // cin >> godzina;
   // cout << zad1(godzina) << endl;
   // cin >> data;
   // cout << zad2(data);
   // cin >> miasto;
   // cout << zad3(miasto);
   // cin >> zespo;
   // cout << zad4(zespo);
   ifstream in;
   in.open("test.txt", ifstream::in);
   string line;
   while (getline(in, line))
   {
      href += line;
   }
   zad5(href);
}