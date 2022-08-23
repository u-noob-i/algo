#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
#include <limits.h>

using namespace std;

struct Edge
{
    int source, dest, weight;
};

bool sortedge(Edge e1, Edge e2)
{
    return (e1.weight < e2.weight);
}

class DisjointUnion
{
private:
    struct data
    {
        int root;
        int rank;
    };

    data *arr = nullptr;
    int size;

public:
    DisjointUnion(int n)
    {
        arr = (data *)malloc(sizeof(data) * n);
        size = n;
        for (int i = 0; i < n; i++)
        {
            arr[i].root = -1;
            arr[i].rank = 0;
        }
    }

    int find(int i)
    {
        if (arr[i].root < 0)
        {
            return i;
        }

        arr[i].root = find(arr[i].root);
        return arr[i].root;
    }

    void Union(int i, int j)
    {
        int x = find(i);
        int y = find(j);
        if (arr[x].rank < arr[y].rank)
        {
            arr[x].root = y;
        }
        else if (arr[x].rank > arr[y].rank)
        {
            arr[y].root = x;
        }
        else
        {
            arr[y].root = x;
            arr[x].rank++;
        }

        return;
    }
};

class Graph
{
private:
    int vertices;
    vector<vector<pair<int, int>>> adjlist;
    vector<Edge> edge;

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

        edge.push_back({u, v, d});

        return;
    }

    void Kruskal()
    {
        sort(edge.begin(), edge.end(), sortedge);
        vector<Edge> ans(vertices - 1);

        DisjointUnion *s = new DisjointUnion(vertices);
        for (int i = 0, j = 0; i < edge.size() && j < vertices - 1; i++)
        {
            int source = edge[i].source;
            int destination = edge[i].dest;
            if (s->find(source) != s->find(destination))
            {
                ans[j++] = edge[i];
                s->Union(source, destination);
            }
        }

        int cost = 0;
        cout << "Edges in MST:\n";
        for (int i = 0; i < vertices - 1; i++)
        {
            cout << ans[i].source << " -- " << ans[i].dest << "; cost: " << ans[i].weight << "\n";
            cost += ans[i].weight;
        }
        cout << "cost of MST: " << cost << "\n";

        return;
    }
};

int main()
{
    Graph *g = new Graph(9);
    g->addEdge(0, 1, 10);
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

    g->Kruskal();
}