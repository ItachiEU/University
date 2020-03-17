#include <stdio.h>
#include<math.h>

struct punkt
{
    int x;
    int y;
};


struct prosta
{
    int a;
    int b;
    int c;    
};

struct odcinek
{
    struct punkt poczatek;
    struct punkt koniec;
};

typedef struct punkt punkt_p;
typedef struct prosta prosta_p;
typedef struct odcinek odcinek_p;

prosta_p prosta_f(punkt_p A, punkt_p B)
{
    int A_l = B.y - A.y;
    int B_l = A.x - B.x;
    int C_l = A_l*A.x + B_l*B.y;
    prosta_p rezultat = {A_l,B_l,C_l};
    return rezultat;
}

prosta_p prostopadla(prosta_p p, punkt_p o)
{
    int A_l = -1/p.a;
    int C_L = o.y - o.x*A_l;
    prosta_p rezultat = {A_l,1,C_L};
    return rezultat;
}

punkt_p przeciecie(prosta_p pierw, prosta_p druga)
{
    if (pierw.a == druga.a)
        return NULL;

    int determinant = pierw.a*druga.b - druga.a*pierw.b;
    double x = (pierw.c*druga.b - druga.c*pierw.b)/determinant;
    double y = (pierw.a*druga.c - druga.a*pierw.c)/determinant;
    punkt_p rezultat = {x,y};
    return rezultat; 
}

double odleglosc(prosta_p p, punkt_p o)
{
    double distance = fabs((p.a*o.x + p.b*o.y + p.c))/sqrt((p.a*p.a + p.b*p.b));
    return distance;
}

int main()
{
    int n;
    scanf("%d",&n);

    for (int i = 0; i < n; i++)
    {
        punkt_p A,B,C;
        scanf("%d %d %d %d %d %d",&A.x, &A.y, &B.x, &B.y, &C.x, &C.y);
        printf("%f",odleglosc(prosta_f(A,B), C));
    }
    
    return 0;
}
