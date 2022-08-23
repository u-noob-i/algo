#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <limits.h>

using namespace std;

class BinaryHeap
{

public:
    friend class Graph;

private:
    vector<pair<int, int>> array;
    vector<int> position;
    unsigned int cursize;

    bool isEmpty() const
    {
        return !cursize;
    }

    void percolateDown(int hole)
    {
        int child;
        int temp = array[hole].first;
        int ind = array[hole].second;

        for (; hole * 2 <= cursize; hole = child)
        {
            child = hole * 2;
            if (child != cursize && array[child + 1].first < array[child].first)
            {
                ++child;
            }
            if (array[child].first < temp)
            {
                array[hole].first = array[child].first;
                array[hole].second = array[child].second;
                position[array[hole].second] = hole;
            }
            else
            {
                break;
            }
        }
        array[hole].first = temp;
        array[hole].second = ind;
        position[array[hole].second] = hole;

        return;
    }

    void percolateUp(int hole)
    {
        int copy;
        array[0].first = copy = array[hole].first;
        int ind = array[hole].second;
        for (; copy < array[hole / 2].first; hole /= 2)
        {
            array[hole].first = array[hole / 2].first;
            array[hole].second = array[hole / 2].second;
            position[array[hole].second] = hole;
        }
        array[hole].first = copy;
        array[hole].second = ind;
        position[array[hole].second] = hole;
    }

    pair<int, int> deleteMin()
    {

        pair<int, int> x = array[1];
        position[array[1].second] = INT_MAX;

        array[1].first = array[cursize].first;
        array[1].second = array[cursize--].second;
        percolateDown(1);

        return x;
    }

    void decreaseKey(int i, int d)
    {
        if (i > cursize)
        {
            return;
        }

        array[i].first = d;
        percolateUp(i);

        return;
    }

    BinaryHeap(int size)
    {
        cursize = size;
        array.resize(size + 10);
        position.resize(size + 10);
        for (int i = 1; i <= cursize; i++)
        {
            array[i].first = INT_MAX;
            array[i].second = i;
            position[i] = i;
        }
    }
};

class Graph
{
private:
    int vertices;
    vector<vector<pair<int, int>>> adjlist;

public:
    Graph(int v)
    {
        vertices = v;
        adjlist.resize(vertices);

        return;
    }

    void addEdge(int u, int v, int d)
    {
        adjlist[u].push_back({v, d});
        adjlist[v].push_back({u, d});

        return;
    }

    void dijkstra(int v)
    {
        vector<int> MST(vertices);

        for (int i = 10; i < vertices; i++)
        {
            MST[i] = -1;
        }

        BinaryHeap *pq = new BinaryHeap(vertices);
        pq->decreaseKey(1, 0);
        while (!pq->isEmpty())
        {
            pair<int, int> a = pq->deleteMin();
            int x = a.second - 1;
            for (auto itr : adjlist[x])
            {
                if (pq->position[itr.first + 1] != INT_MAX)
                {
                    if (pq->array[pq->position[itr.first + 1]].first > itr.second)
                    {
                        pq->decreaseKey(pq->position[itr.first + 1], itr.second);
                        MST[itr.first] = x;
                    }
                }
            }
        }

        cout << "Edges of MST are:\n";
        for (int i = 1; i < vertices; i++)
        {
            cout << MST[i] << " -- " << i << "\n";
        }

        return;
    }
};

int main()
{
    Graph *g = new Graph(9);
    g->addEdge(0, 1, 4);
    g->addEdge(0, 7, 8);
    g->addEdge(1, 2, 8);
    g->addEdge(1, 7, 11);
    g->addEdge(2, 3, 7);
    g->addEdge(2, 8, 2);
    g->addEdge(2, 5, 4);
    g->addEdge(3, 4, 9);
    g->addEdge(3, 5, 14);
    g->addEdge(4, 5, 10);
    g->addEdge(5, 6, 2);
    g->addEdge(6, 7, 1);
    g->addEdge(6, 8, 6);
    g->addEdge(7, 8, 7);

    g->dijkstra(0);
}