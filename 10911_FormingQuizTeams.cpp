
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <limits>
#include <algorithm>

static const int MAX_STUDENTS = 16;
static const double MAX_DOUBLE = 1000000;

struct Point {
    int x;
    int y;

    double distanceTo(const Point &p) {
        return sqrt((x - p.x)*(x - p.x) + (y - p.y)*(y - p.y));
    }
};

int teams;
int students;

Point positions[MAX_STUDENTS];
double distance_map[MAX_STUDENTS][MAX_STUDENTS];
double distance_calc[1 << MAX_STUDENTS];
double distance_count;

int countSetBits(int n)
{
    int bits = 0;
    while(n) {
        n &= (n-1);
        bits++;
    }
    return bits;
}

double findSolution()
{
    distance_calc[0] = 0;
    int mask_pool[MAX_STUDENTS];
    for(int s = 1, max_s = 1 << students; s < max_s; s++) {
        distance_calc[s] = MAX_DOUBLE;

        int set_bits = countSetBits(s);
        if(set_bits % 2)
            continue;

        int candidate_index;
        int candidate_mask;
        for(candidate_index = students - 1; candidate_index >= 0; candidate_index--) {
            candidate_mask = (1 << candidate_index);
            if(s & candidate_mask)
                break;
        }

        int base_distance_mask = s ^ candidate_mask;
        for(int pair_index = 0; pair_index < candidate_index; pair_index++) {
            int pair_mask = (1 << pair_index);
            if(s & pair_mask) {
                int base_distance_index = base_distance_mask ^ pair_mask;
                double &base = distance_calc[base_distance_index];

                double new_distance = distance_map[candidate_index][pair_index] + base;
                double &ptr = distance_calc[s];
                if(new_distance < ptr) {
                    ptr = new_distance;
                }
            }
        }
    }

    return distance_calc[(1 << students) - 1];
}

int main(int argc, char *argv[])
{
    int test_case = 1;
    while(1) {
        scanf("%d\n", &teams);
        if(teams <= 0)
            break;

        students = teams << 1;
        for(int n = 0; n < students; n++)
            scanf("%*s %d %d\n", &positions[n].x, &positions[n].y);

        for(int n1 = 0; n1 < students; n1++) {
            for(int n2 = n1+1; n2 < students; n2++) {
                distance_map[n2][n1] = positions[n1].distanceTo(positions[n2]);
            }
        }

        double solution = findSolution();
        printf("Case %d: %.2f\n", test_case++, solution);
    }

    return 0;
}