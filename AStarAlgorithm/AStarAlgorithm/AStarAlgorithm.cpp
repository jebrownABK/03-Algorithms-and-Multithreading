// Ch1AlgorithmsChallenge.cpp : This file contains the 'main' function. Program execution begins and ends there.
// built following c++ tutorial from https://www.redblobgames.com/pathfinding/a-star/implementation.html
#include <iostream>
#include <chrono>
#include "Edge.h"
#include "Node.h"
#include <list>
#include <map>
#include <set>
#include <unordered_map>
#include <queue>
#include <unordered_set>

constexpr int RUN_SIZE = 100;
constexpr int ARRAY_SIZE = 100;

using namespace std;

void FillArray(int ArrayToFill[], int SizeOfArray);
int ChooseASearchKey(int ArrayToPickFrom[], int SizeOfArray);

void BubbleSort(int ArrayToFill[], int SizeOfArray);
void BinarySearch(int ArrayToSearch[], int Low, int Hight, int SearchKey);

unordered_map<char, char> BFS(char start, char goal, map<char, list<char>> graph);
void AStar(char start, char goal, map<char, list<char>> graph);

uint32_t GetNanos();

template<typename T, typename priority_t>
struct PriorityQueue {
    typedef std::pair<priority_t, T> PQElement;
    std::priority_queue<PQElement, std::vector<PQElement>,
        std::greater<PQElement>> elements;

    bool empty() const {
        return elements.empty();
    }

    void put(T item, priority_t priority) {
        elements.emplace(priority, item);
    }

    T get() {
        T best_item = elements.top().second;
        elements.pop();
        return best_item;
    }
};

int main()
{
    //Challenge 1
    uint32_t startNanos = 0;
    uint32_t endNanos = 0;

    uint32_t totalNanos = 0;

    for (int i = 0; i < RUN_SIZE; i++)
    {
        int dataset[ARRAY_SIZE];

        srand(time(nullptr));

        FillArray(dataset, ARRAY_SIZE);

        //PrintArray(dataset, ARRAY_SIZE);

        startNanos = GetNanos();
        BubbleSort(dataset, ARRAY_SIZE);
        endNanos = GetNanos();

        //PrintArray(dataset, ARRAY_SIZE);

        totalNanos += (endNanos - startNanos);
    }

    std::cout << "Average time: " << totalNanos / RUN_SIZE << endl << endl;
    //BinarySearch(Dataset, 0, ARRAY_SIZE, SearchKey); --> never ending loop?

    //Challenge 2

    std::map<char, list<char>> graph = {{
        {'a', {'b', 'd'}},
        {'b', {'a', 'c'}},
        {'c', {'b', 'd'}},
        {'d', {'a', 'c'}}
    }}; //to get neighbors, do graph[char]

    unordered_map<char, char> result = BFS('a', 'd', graph);
    cout <<  result['a'] << endl;
    //AStar('a', 'd', graph, came_from, cost_so_far);

    AStar('a', 'd', graph);

}

void FillArray(int ArrayToFill[], int SizeOfArray)
{
    for (int i = 0; i < SizeOfArray; i++)
    {
        ArrayToFill[i] = rand() % SizeOfArray + 1;
    }
}

void BubbleSort(int ArrayToSort[], int SizeOfArray)
{
    for (int pass = 0; pass < SizeOfArray; pass++)
    {
        for (int i = 0; i < SizeOfArray - 1; i++)
        {
            if (ArrayToSort[i] > ArrayToSort[i + 1])
            {
                int temp = ArrayToSort[i];
                ArrayToSort[i] = ArrayToSort[i + 1];
                ArrayToSort[i + 1] = temp;
            }
        }
    }
}

int ChooseASearchKey(int ArrayToPickFrom[], int SizeOfArray)
{
    int RandomIndex = rand() % SizeOfArray + 1;
    return ArrayToPickFrom[RandomIndex];
}

void BinarySearch(int ArrayToSearch[], int Low, int High, int SearchKey)
{
    while (Low <= High)
    {
        int Middle = (Low + High) / 2;
        if (SearchKey == ArrayToSearch[Middle])
        {
            cout << "Found " << SearchKey << " at index " << Middle << endl;
        }
        else
        {
            if (SearchKey < Middle)
            {
                BinarySearch(ArrayToSearch, 0, Middle - 1, SearchKey);
            }
            else
            {
                BinarySearch(ArrayToSearch, Middle + 1, High, SearchKey);
            }
        }
    }
}

uint32_t GetNanos()
{
    using namespace std::chrono;
    return static_cast<uint32_t>(duration_cast<nanoseconds>(system_clock::now().time_since_epoch()).count());
}

/*void AStar(Node* start, Node* goal, list<Edge> graph)
{

    priority_queue<Node, double> frontier;
    frontier.push(start, 0);

    came_from[start] = start;
    cost_so_far[start] = 0;

    while (!frontier.empty()) {
        Location current = frontier.get();

        if (current == goal) {
            break;
        }

        for (Location next : graph.neighbors(current)) {
            double new_cost = cost_so_far[current] + graph.cost(current, next);
            if (cost_so_far.find(next) == cost_so_far.end()
                || new_cost < cost_so_far[next]) {
                cost_so_far[next] = new_cost;
                double priority = new_cost + 0; //normally, 0 would be the heuristic
                frontier.put(next, priority);
                came_from[next] = current;
            }
        }
    }
}*/

unordered_map<char, char> BFS(char start, char goal, map<char, list<char>> graph)
{
    queue<char> queue;
    queue.push(start);

    //unordered_set<char> reached;
    //reached.insert(start);

    unordered_map<char, char> cameFrom;
    cameFrom[start] = start;

    while (!queue.empty())
    {
        char current = queue.front();
        queue.pop();

        if (current == goal)
        {
            break;
        }

        for (char next : graph[current])
        {
            if (cameFrom.find(next) == cameFrom.end())
            {
                queue.push(next);
                cameFrom[next] = current;
            }
        }
    }
    return cameFrom;
}

void AStar(char start, char goal, map<char, list<char>> graph)
{
    PriorityQueue<char, double> queue;
    queue.put(start, 0);

    unordered_map<char, char> cameFrom;
    cameFrom[start] = start;

    unordered_map<char, double> totalCost;
    totalCost[start] = 0;

    while (!queue.empty())
    {
        char current = queue.get();

        if (current == goal)
        {
            break;
        }

        for (char next : graph[current])
        {
            double cost = totalCost[current] + 0; //0 would be the heuristic in A*
            if ( (totalCost.find(next) == totalCost.end()) || cost < totalCost[next] )
            {
                totalCost[next] = cost;
                cameFrom[next] = current;
                queue.put(next, cost);
            }
        }
    }
}