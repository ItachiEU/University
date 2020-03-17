#include<stdio.h>

struct przedmiot
{
    int waga;
    int wartosc;
};

typedef struct przedmiot przedmiot;

int max(int a, int b)
{
    if (a>b)
        return a;
    return b;
}


int main()
{
    int N, W;
    scanf("%d %d",&N,&W);
    przedmiot lista[N];
    int dynamik[W+1][N+1];

    for (int i = 0; i < W+1; i++)
        dynamik[i][0] = 0;
    for (int i = 0; i < N+1; i++)
        dynamik[0][i] = 0;
    
    for (int i = 0; i < N; i++)
    {
        przedmiot nowy;
        scanf("%d %d", &nowy.waga, &nowy.wartosc);
        lista[i] = nowy;
    }

    for (int i = 1; i < W+1; i++)
        for (int j = 1; j < N+1; j++)
            {
                if (lista[j].waga > i)
                    dynamik[i][j] = dynamik[i][j-1];
                else
                    dynamik[i][j] = max(dynamik[i][j-1], dynamik[i-lista[j].waga][j-1] + lista[j].wartosc);
            }

    printf("%d", dynamik[W][N]);

    return 0;
}
