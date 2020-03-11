#include <stdio.h>

/* Wartości jakiej funkcji oblicza poniższy program? 
 *      Autor: Marek Piotrów, Data: 1.10.2019
 */

int main(void)
{
    int n = 0;
    float x = 0.0, dx = 0.0, eps = 0.0;
    float y1, y2;

    while (n <= 0 || x <= 0.0) { 
        printf(u8"Podaj dwie liczby dodatnie: naturalną i rzeczywistą:\n");
        scanf("%d %f", &n, &x);
    }
    while(dx <=0.0 || eps<=0.0 ){
        printf("Podaj wartosc dx oraz wartosc eps: ");
        scanf("%f %f", &dx, &eps);
    }
    for (int i = 0; i < n; i++) {
        y1 = x;
        y2 = y1 / 2;
        while (y1 - y2 > eps || y2 - y1 > eps) {
            y1 = y2;
            y2 = (y1 + x / y1) / 2;
        }
        printf("x = %.8f, f(x) = %.8f\n", x, y2);
        x += dx;
    }
    return 0;
}
  
    