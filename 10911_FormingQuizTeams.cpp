
#include <stdio.h>
#include <stdlib.h>

float distance;

int main(int argc, char *argv[])
{
    int teams = 0;
    int test_case = 1;
    while(1) {
        scanf("%d\n", &teams);
        if(teams <= 0)
            break;

        for(int n = 0, _n = teams*2; n < _n; n++) {
            char name[21];
            int x, y;
            scanf("%s %d %d\n", name, &x, &y);
            printf("%d %d\n", x, y);
        }

        printf("Case %d: %.2f\n", test_case++, distance);
    }

    return 0;
}