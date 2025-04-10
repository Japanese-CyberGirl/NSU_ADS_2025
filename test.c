#include <stdio.h>
#include <math.h>

int main()
{

    for (int i = 2 ; i < 10000 ; i ++ ) {
        if ((i * i) > (int)(2 * i * log2(i))) {
            printf("%d\n", i);
            break;
            
        }
    }

    return 0;
}