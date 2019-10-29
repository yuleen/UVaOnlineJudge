
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <vector>
#include <algorithm>

static const int MAX_BUDGET    = 200;
static const int MAX_GARMENTS  = 20;
static const int MAX_MODELS    = 20;

int price_list[MAX_GARMENTS][MAX_MODELS];
int model_count[MAX_GARMENTS];

int budget;
int garments;
int total_count;

inline void readGarments()
{
    budget = 0;
    garments = 0;

    scanf("%d %d\n", &budget, &garments);
    for(int g = 0; g < garments; g++) {
        int models = 0;
        scanf("%d", &models);
        for(int m = 0; m < models; m++) {
            int price = 0;
            scanf("%d", &price);
            price_list[g][m] = price;
        }
        scanf("\n");
        model_count[g] = models;
    }

    for(int g = 0; g < garments; g++) {
        std::sort(price_list[g], price_list[g] + model_count[g]);

        //for(int m = 0; m < model_count[g]; m++) {
        //    printf("%d ", price_list[g][m]);
        //}
        //printf("\n");
    }
}

bool checkMinimumCount()
{
    int minimum = 0;
    for(int g = 0; g < garments; g++)
        minimum += price_list[g][0];
    if(minimum > budget) {
        printf("no solution\n");
        return false;
    }

    return true;
}

inline void reduceModel()
{
    int candidate = -1;
    int min_delta = -1;
    for(int g = 0; g < garments; g++) {
        int model_index = model_count[g] - 1;
        if(model_index < 1)
            continue;

        int new_count = total_count - price_list[g][model_index] + price_list[g][model_index - 1];
        int delta = abs(budget - new_count);
        //printf("g = %d, delta = %d\n", g, delta);
        if(delta < min_delta || min_delta < 0) {
            min_delta = delta;
            candidate = g;
        }
    }

    if(candidate >= 0) {
        model_count[candidate] -= 1;

        //printf("reduced model\n");
        //for(int g = 0; g < garments; g++) {
        //    for(int m = 0; m < model_count[g]; m++)
        //        printf("%d ", price_list[g][m]);
        //    printf("\n");
        //}
    }
}

inline void findSolution()
{
    if(!checkMinimumCount())
        return;

    do {
        total_count = 0;
        for(int g = 0; g < garments; g++) {
            total_count += price_list[g][model_count[g]-1];
        }

        if(total_count > budget) {
            //printf("total count = %d > budget %d\n", total_count, budget);
            reduceModel();
        }
    } while(total_count > budget);

    printf("%d\n", total_count);
}

int result[201][21];
void findSolution2()
{
    memset(result, -1, sizeof(result));
    //for(int i = 0; i <= budget; i++)
    //    for(int j = 0; j <= garments; j++)
    //        result[i][j] = -2;

    for(int m = 0; m <= budget; m++) {
        result[m][0] = 0;
        for(int g = 1; g <= garments; g++) {
            for(int i = 0; i < model_count[g-1]; i++) {
                int price = price_list[g-1][i];
                if(m >= price && result[m-price][g-1] != -1)
                    result[m][g] = std::max(result[m-price][g-1] + price, result[m][g]);
            }
        }
    }

    if(result[budget][garments] == -1)
        printf("no solution\n");
    else
        printf("%d\n", result[budget][garments]);
}

int main(int argc, char *argv[])
{
    //int timestamp = clock();

    int test_case = 0;
    scanf("%d\n", &test_case);
    while(test_case--) {
        memset(price_list, 0, sizeof(price_list));
        memset(model_count, 0, sizeof(model_count));

        //printf("======================\n");
        readGarments();
        //findSolution();
        findSolution2();
        //printf("======================\n");
    }

    //int elapsed = clock() - timestamp;
    //printf("Elapsed time: %.3f seconds\n", elapsed*1.0/CLOCKS_PER_SEC);

    return 0;
}