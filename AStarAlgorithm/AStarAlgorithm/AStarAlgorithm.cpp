// Ch1AlgorithmsChallenge.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <iostream>
#include <chrono>
#include "Edge.h"
#include "Node.h"
#include <list>

constexpr int RUN_SIZE = 100;
constexpr int ARRAY_SIZE = 100;

using namespace std;

void FillArray(int ArrayToFill[], int SizeOfArray);
int ChooseASearchKey(int ArrayToPickFrom[], int SizeOfArray);

void BubbleSort(int ArrayToFill[], int SizeOfArray);
void BinarySearch(int ArrayToSearch[], int Low, int Hight, int SearchKey);

void AStar(Node* start, Node* end);

uint32_t GetNanos();

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
    list<Edge> graph;
    Node nodeA('a');
    Node nodeB('b');
    Node nodeC('c');
    Node nodeD('c');

    Edge edgeAB(nodeA, nodeB, 5);
    Edge edgeBC(nodeB, nodeC, 1);
    Edge edgeAD(nodeA, nodeD, 7);
    Edge edgeCD(nodeC, nodeD, 1);

    graph.push_back(edgeAB);
    graph.push_back(edgeBC);
    graph.push_back(edgeAD);
    graph.push_back(edgeCD);



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

void AStar(Node* start, Node* end)
{

    list<int> queue;
    queue.push_back(source);

    std::map<int, int> came_from;
    came_from[source] = NULL;

    while (!queue.empty())
    {
        int current = queue.front();
        std::cout << current << " ";
        queue.pop_front();

        if (current == goal)
        {
            break;
        }

        //get all adjacent vertices of queued
        //if adjacent has not been visited, mark visited and enqueue
        for (int adj : m_adjacentNodes[current])
        {
            if (came_from[adj] == NULL)
            {
                queue.push_back(adj);
                came_from[adj] = current;
            }
        }
    }
}