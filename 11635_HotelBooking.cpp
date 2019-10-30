
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <vector>
#include <algorithm>

static const int MAX_CITIES = 10001;

struct CityNode
{
    int destination;        // 目的 city 號碼
    int distance;           // 與目的 city 的距離
    CityNode(int dest, int dist) { destination = dest; dist = dist; }
};

std::vector<CityNode> city_list[MAX_CITIES];


// 使用 shortest path faster algorithm (SPFA) 找出從 source 到任何一點的最短路徑
void shortestPath(int source)
{

}

int main(int argc, char *argv[])
{
    while(1){
        int city_count;
        scanf("%d\n", &city_count);
        if(city_count <= 0)
            break;

        printf("city count = %d\n", city_count);

        int hotel_count;
        scanf("%d", &hotel_count);

        printf("hotel_count = %d\n", hotel_count);

        printf("cities with hotel: ");
        for(int h = 0; h < hotel_count; h++) {
            int city;
            scanf("%d", &city);
            printf("%d ", city);
        }
        scanf("\n");
        printf("\n");

        int route_count;
        scanf("%d\n", &route_count);

        printf("route_count = %d\n", route_count);

        for(int r = 0; r < route_count; r++) {
            int start, end, distance;
            scanf("%d %d %d\n", &start, &end, &distance);
            printf("route[%2d]: start=%d, end=%d, distance=%d\n", r, start, end, distance);
        }
    }

    return 0;
}