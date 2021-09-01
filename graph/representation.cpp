#include<iostream>
#include<vector>

using namespace std;

class Graph{
    private:

    int vertices;
    vector<vector<int>> adjlist;

    public:

    Graph(int v)
    {
        vertices=v;
        adjlist.resize(vertices);
    }

    void addEdge(int u, int v)
    {
        //undirected graph

        adjlist[u].push_back(v);
        adjlist[v].push_back(u);
    }

    void print()
    {
        cout<<"Adjacency list:\n";

        for(int i=0;i<vertices;i++)
        {
            cout<<i<<": ";
            for(int j=0;j<adjlist[i].size();j++)
            {
                cout<<adjlist[i][j]<<" ";
            }
            cout<<"\n";
        }

        return;
    }

};

int main()
{
    Graph *g=new Graph(5);

    g->addEdge(0, 1);
    g->addEdge(0, 4);
    g->addEdge(1, 2);
    g->addEdge(1, 3);
    g->addEdge(1, 4);
    g->addEdge(2, 3);
    g->addEdge(3, 4);

    g->print();
}