#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct R {
    unsigned n;
    bool *tbl;
};

typedef struct R RelBin;



unsigned size(RelBin R)
{
    return R.n * R.n;
}


/*
 * Tworzy dynamiczną kopię relacji R
 */

RelBin* copy_rel(const RelBin R)
{
    RelBin *result = malloc(sizeof(RelBin));
    result->n = R.n;
    result->tbl = malloc( size(R) * sizeof(bool));
    //memcpy(result->tbl, R.tbl, (result->n)*(result->n) * sizeof(bool));
   for(unsigned i = 0; i < size(R); i++)
        *((result->tbl) + i)  = *(R.tbl + i);   //result->tbl[i] = R.tbl[i];

      return result;
  }



  void set_true(RelBin R, unsigned i, unsigned j)
  {
    R.tbl[i*R.n + j] = true;
  }

  bool get(RelBin R, unsigned i, unsigned j)
  {
    return R.tbl[i*R.n + j];
      }

  /**
   *
   * Uzwratnia relację.
   */
  void make_reflexive(RelBin R)
  {
    for(unsigned i = 0; i < R.n; i++)
        set_true(R, i, i);
  }

  void make_transitive(RelBin R)
  {
   bool non_saturated = true;

   while (non_saturated)
   {
       non_saturated = false;

       for(unsigned i = 0; i < R.n; i++)
           for(unsigned j = 0; j < R.n; j++)
               if (get(R, i, j)) {
                 for(unsigned k = 0; k < R.n; k++)
                   {
                            if (get(R, j, k)) {
                                set_true(R, i, k);
                                non_saturated = true;
                                break;
                            }
                   }


               }
   }


  }

  bool check_as(RelBin R)
  {

      for(unsigned i = 0; i < R.n; i++)
          for(unsigned j = i+1; j < R.n; j++)
              if (get(R, i, j) && get(R, j, i))
                  return false;



   return true;
  }

  /*
   * Algorytm: najpier kopiuję R, późnej obliczam
   * */
  RelBin *min_order_rel(RelBin R)
  {

    RelBin  *result = copy_rel(R);

    make_reflexive(*result);
    make_transitive(*result);

   return check_as(*result) ? result : NULL;
    }


  int main() {
      printf("Hello, World!\n");
      return 0;
  }
