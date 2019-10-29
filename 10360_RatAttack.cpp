
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <vector>

static const int MAP_SIZE = 1025;
static const int MAX_ELEMENTS = MAP_SIZE * MAP_SIZE;

int map[MAP_SIZE][MAP_SIZE];

int main(int argc, char *argv[])
{
    //clock_t t = clock();

    int test_cases = 0;

    scanf("%d", &test_cases);
    for(int i = 0; i < test_cases; i++) {
        memset(map, 0, sizeof(map));

        int location_x = 0;
        int location_y = 0;
        int max_rats = 0;
        int strength = 0;
        scanf("%d\n", &strength);

        int data_count = 0;
        scanf("%d\n", &data_count);
        for(int n = 0; n < data_count; n++) {
            int x = 0, y = 0, rats = 0;
            scanf("%d %d %d\n", &x, &y, &rats);

            int start_x = std::max<int>(x - strength, 0);
            int start_y = std::max<int>(y - strength, 0);
            int end_x = std::min<int>(x + strength, MAP_SIZE - 1);
            int end_y = std::min<int>(y + strength, MAP_SIZE - 1);

            for(int xn = start_x; xn <= end_x; xn++) {
                for(int yn = start_y; yn <= end_y; yn++) {
                    map[xn][yn] += rats;
                    if(max_rats < map[xn][yn]) {
                        location_x = xn;
                        location_y = yn;
                        max_rats = map[xn][yn];
                    }
                }
            }
        }

        printf("%d %d %d\n", location_x, location_y, max_rats);
    }

    //clock_t elapsed = clock() - t;
    //printf("Elapsed: %.3f", elapsed*1.0 / CLOCKS_PER_SEC);

    return 0;
}