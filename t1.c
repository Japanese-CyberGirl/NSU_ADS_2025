#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool containsSubstring(const char *str, const char *substr) {
    return strstr(str, substr) != NULL;
  }

int main()
{
    FILE *input = fopen("input.txt", "r");
    int Q = 0;
    fscanf(input,"%d\n", &Q);
    double prev_p = 0.0 ; double prev_s = 0.0 ; double prev_l = 0.0;
    
    char string[1000];

    for (int i = 0 ; i < Q * 2 ; i ++ ) {

        double p = 0.0 ; double s = 0.0 ; double l = 0.0 ;

        fgets(string, sizeof(string), input);

        char *cash = strtok(string, " ");
        while(cash != NULL) {

            if (containsSubstring(cash, "^N")) {
                char *endptr;
                cash[strlen(cash)-1] = ' '; cash[strlen(cash)-2] = ' ';
                p = strtod(cash, &endptr);
            }

            if (containsSubstring(cash, "N^") && containsSubstring(cash, "log") == 0) {
                char *endptr;
                cash[0] = ' '; cash[1] = ' ';
                s = strtod(cash, &endptr);
            }

            else if(containsSubstring(cash, "N") && containsSubstring(cash, "log") == 0) {
                char *endptr;
                s = 1.0;
            }

            if (containsSubstring(cash, "logN^")) {
                char *endptr;
                cash[0] = ' '; cash[1] = ' '; cash[2] = ' '; cash[3] = ' '; cash[4] = ' ';
                l = strtod(cash, &endptr);
            }
            else if(containsSubstring(cash, "logN")) {
                l = 1.0;
            }
            

            cash = strtok(NULL, " ");
        }

        p = (p == 1.0) ? 0.0 : p;

        if (i%2!=0 && i > 0) {

            if (p > prev_p) {
                printf("%d\n", -1);  // Первая асимптотика меньше
            } else if (p < prev_p) {
                printf("%d\n", 1); // Первая асимптотика больше
            } else {
                if (s > prev_s) {
                    printf("%d\n", -1);  // Первая асимптотика меньше
                } else if (s < prev_s) {
                    printf("%d\n", 1); // Первая асимптотика больше
                } else {
                    if (l > prev_l) {
                        printf("%d\n", -1);  // Первая асимптотика меньше
                    } else if (l < prev_l) {
                        printf("%d\n", 1); // Первая асимптотика больше
                    } else {
                        printf("%d\n", 0);  // Асимптотики равны
                    }
                }
            }
        }

        prev_p = p; 
        prev_s = s;
        prev_l = l;
    }

    fclose(input);
    return 0;
}