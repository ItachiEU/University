#include <bits/stdc++.h>

using namespace std;

void convertToOnp(string inp, queue<char> &out)
{
   stack<char> stos;
   unordered_set<char> operators = {'+', '-', '*', '/', '^'};
   unordered_map<char, int> priority = {{'+', 1},
                                        {'-', 1},
                                        {'*', 2},
                                        {'/', 2},
                                        {'^', 3}};
   int pointer = 0;
   while (pointer < (int)inp.size())
   {
      char currChar = inp[pointer];
      if (isdigit(currChar))
      {
         int tmpPointer = pointer + 1;
         string number = "";
         number += currChar;

         while (tmpPointer < (int)inp.size() && isdigit(inp[tmpPointer]))
            number += inp[tmpPointer++];

         for (auto c : number)
         {
            out.push(c);
         }
         out.push(' ');
         pointer = tmpPointer - 1;
      }
      else if (currChar == '(')
      {
         stos.push(currChar);
      }
      else if (operators.count(currChar))
      {
         while (!stos.empty() && priority[stos.top()] >= priority[currChar])
         {
            char tmp = stos.top();
            stos.pop();
            out.push(tmp);
            out.push(' ');
         }
         stos.push(currChar);
      }
      else if (currChar == ')')
      {
         while (!stos.empty() && stos.top() != '(')
         {
            char temp = stos.top();
            out.push(temp);
            out.push(' ');
            stos.pop();
         }

         if (stos.empty())
            return;
         else
            stos.pop();
      }
      pointer++;
   }
   while (!stos.empty())
   {
      out.push(stos.top());
      out.push(' ');
      stos.pop();
   }
}

int main()
{
   string test = "30+42*12/(14-512)^22";
   string test2 = "5*(-40)+5";
   queue<char> q;
   convertToOnp(test2, q);
   while (!q.empty())
   {
      cout << q.front();
      q.pop();
   }
}