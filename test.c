#include <stdio.h>

int main()
{
    printf("start amount\n");
    int summa = 0;
    scanf("%d", &summa);
    printf("duration\n");
    int M = 0;
    scanf("%d", &M);

    for (int i = 0 ; i <= M ; i ++ ) {
        printf("total: %d + %d = %d\n", summa, (int)(double)(summa/10), summa + summa/10);
        summa += summa * 0.1;
    }
    return 0;
}