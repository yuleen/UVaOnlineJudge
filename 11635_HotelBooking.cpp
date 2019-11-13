
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <cstring>
#include <vector>
#include <list>
#include <queue>
#include <algorithm>

static const int MAX_CITIES = 10001;
static const int MAX_HOTELS = 103;
static const int DISTANCE_PER_DAY = 600;
static const int MAX_INTEGER = 1e9;

struct CityNode
{
    int destination;        // 目的 city 號碼
    int distance;           // 與目的 city 的距離
    CityNode(int dest, int dist) { destination = dest; distance = dist; }

    bool operator> (const CityNode &node) const
    {
        return (distance > node.distance);
    }

    bool operator< (const CityNode &node) const
    {
        return (distance < node.distance);
    }
};

std::vector<CityNode> city_list[MAX_CITIES];
int hotel_to_city_map[MAX_HOTELS];
int hotel_booking_count[MAX_HOTELS][MAX_HOTELS];

int city_count;
int hotel_count;


int distance_from_source[MAX_CITIES];
void dumpShortestPathResult(int source)
{
    printf("Distance from city %3d: \n", source);
    for(int c = 1; c <= city_count; c++) {
        printf("  To city %3d: distance = %d\n", c, distance_from_source[c]);
    }
}

// 使用 shortest path faster algorithm (SPFA) 找出從 source 到任何一點的最短路徑
bool in_calc_queue[MAX_CITIES];
void shortestPath(int source)
{
    memset(in_calc_queue, 0, sizeof(in_calc_queue));
    std::fill(distance_from_source, distance_from_source + city_count + 1, 1e9);

    std::queue<int> calc_queue;
    calc_queue.push(source);
    in_calc_queue[source] = true;
    distance_from_source[source] = 0;

    while(!calc_queue.empty()) {
        int current_city = calc_queue.front();
        calc_queue.pop();
        in_calc_queue[current_city] = false;

        for(int n = 0, max_n = city_list[current_city].size(); n < max_n; n++) {
            CityNode next_city = city_list[current_city][n];

            int new_distance = distance_from_source[current_city] + next_city.distance;
            if(new_distance < distance_from_source[next_city.destination]) {
                distance_from_source[next_city.destination] = new_distance;
                if(!in_calc_queue[next_city.destination]) {
                    calc_queue.push(next_city.destination);
                    in_calc_queue[next_city.destination] = true;
                }
            }
        }
    }

    //dumpShortestPathResult(source);
}

// 使用 Dijkstra 演算法找出從 source 到任何一點的最短路徑
bool visited[MAX_CITIES];
void dijkstra(int source)
{
    memset(visited, 0, sizeof(visited));
    std::fill(distance_from_source, distance_from_source + city_count + 1, 1e9);

    // 注意: 這裡使用的是 priority queue
    std::priority_queue<CityNode, std::vector<CityNode>, std::greater<CityNode> > calc_queue;
    calc_queue.emplace(source, 0);
    distance_from_source[source] = 0;

    for(int n = 0; n < city_count; n++) {
        // 注意: 由於 STL 的 priority queue 無法更新元素的內容
        //       所以這裡的作法是將更新過後的內容重新 push 入 priority queue
        //       在這裡要判斷 queue 頂端的 node 有沒有拜訪過了, 如果有的話就將這個 node 忽略
        while(!calc_queue.empty() && visited[calc_queue.top().destination])
            calc_queue.pop();

        if(calc_queue.empty())
            break;

        int current_city = calc_queue.top().destination;
        calc_queue.pop();
        visited[current_city] = true;

        for(int i = 0, _max_i = city_list[current_city].size(); i < _max_i; i++) {
            CityNode next_city = city_list[current_city][i];

            if(!visited[next_city.destination]) {
                int new_distance = distance_from_source[current_city] + next_city.distance;
                if(new_distance < distance_from_source[next_city.destination]) {
                    distance_from_source[next_city.destination] = new_distance;
                    calc_queue.emplace(next_city.destination, new_distance);
                }
            }
        }
    }
}

void dumpHotelCities()
{
    printf("City with hotel: ");
    for(int i = 0; i < hotel_count; i++) {
        printf("%d ", hotel_to_city_map[i]);
    }
    printf("\n");
}

void dumpCityList()
{
    printf("City Count: %d\n", city_count);
    for(int i = 1; i <= city_count; i++) {
        printf("City[%3d]: \n", i);
        for(int j = 0; j < city_list[i].size(); j++) {
            printf("  To city %3d: distance = %d\n", 
                city_list[i][j].destination,
                city_list[i][j].distance);
        }
    }
}

void dumpHotelBookingCount()
{
    printf("Hotel booking count: \n");
    for(int i = 0; i < hotel_count; i++) {
        for(int j = 0; j < hotel_count; j++) {
            if(hotel_booking_count[i][j] < MAX_INTEGER)
                printf("%3d ", hotel_booking_count[i][j]);
            else
                printf("%3c ", '-');
        }
        printf("\n");
    }
}

int main(int argc, char *argv[])
{
    while(1){
        scanf("%d\n", &city_count);
        if(city_count <= 0)
            break;

        scanf("%d", &hotel_count);

        // 起點和終點也當成是有 hotel 的 city
        hotel_count += 2;
        hotel_to_city_map[0] = 1;
        hotel_to_city_map[1] = city_count;
        for(int h = 2; h < hotel_count; h++) {
            int city;
            scanf("%d", &city);
            hotel_to_city_map[h] = city;
        }
        scanf("\n");

        int route_count;
        scanf("%d\n", &route_count);
        for(int r = 0; r < route_count; r++) {
            int start, end, distance;
            scanf("%d %d %d\n", &start, &end, &distance);

            city_list[start].push_back(CityNode(end, distance));
            city_list[end].push_back(CityNode(start, distance));
        }

        //dumpHotelCities();
        //dumpCityList();

        for(int i = 0; i < hotel_count; i++)
            std::fill(hotel_booking_count[i], hotel_booking_count[i] + hotel_count, MAX_INTEGER);

        for(int src_h = 0; src_h < hotel_count; src_h++) {
            hotel_booking_count[src_h][src_h] = 0;
            //shortestPath(hotel_to_city_map[src_h]);
            dijkstra(hotel_to_city_map[src_h]);
            //dijkstra_2(hotel_to_city_map[src_h]);

            for(int dest_h = 0; dest_h < hotel_count; dest_h++) {
            //for(int dest_h = src_h + 1; dest_h < hotel_count; dest_h++) {
                if(dest_h != src_h && distance_from_source[hotel_to_city_map[dest_h]] <= DISTANCE_PER_DAY) {
                //if(distance_from_source[hotel_to_city_map[dest_h]] <= DISTANCE_PER_DAY) {
                    hotel_booking_count[src_h][dest_h] = 1;
                    //hotel_booking_count[dest_h][src_h] = 1;
                }
            }
        }

        //dumpHotelBookingCount();

        // Floyd-Warshall algorithm
        for(int middle = 0; middle < hotel_count; middle++) {
            for(int start = 0; start < hotel_count; start++) {
                for(int end = 0; end < hotel_count; end++) {
                    if(hotel_booking_count[start][middle] + hotel_booking_count[middle][end] < hotel_booking_count[start][end])
                        hotel_booking_count[start][end] = hotel_booking_count[start][middle] + hotel_booking_count[middle][end];
                }
            }

            //printf("Via mid city %3d, ", hotel_to_city_map[middle]);
            //dumpHotelBookingCount();
        }

        printf("%d\n", hotel_booking_count[0][1] < MAX_INTEGER ? (hotel_booking_count[0][1] - 1) : -1);

        memset(hotel_booking_count, 0, sizeof(hotel_booking_count));
        for(int i = 0; i < city_count; i++)
            city_list[i].clear();
    }

    return 0;
}