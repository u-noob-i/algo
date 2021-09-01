#include<iostream>
#include<vector>

using namespace std;

class Graph{
    private:

    int vertices;
    vector<vector<int>> adjlist;
    vector<bool> visited;

    public:

    Graph(int v)
    {
        vertices=v;
        adjlist.resize(vertices);
        visited.resize(vertices);

        return;
    }

    void addEdge(int u, int v)
    {
        adjlist[u].push_back(v);

        return;
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

    void dfs(int v)
    {
        visited[v]=1;

        cout<<v<<" ";

        for(auto itr:adjlist[v])
        {
            if(!visited[itr])
            {
                dfs(itr);
            }
        }

        return;
    }

    void dfsUtil(int v)
    {
        for(int i=0;i<vertices;i++)
        {
            visited[i]=0;
        }

        dfs(v);

        return;
    }

};

int main()
{
    Graph *g=new Graph(10);

    g->addEdge(0, 1);
    g->addEdge(1, 5);
    g->addEdge(5, 2);
    g->addEdge(2, 3);
    g->addEdge(3, 9);
    g->addEdge(7, 6);
    g->addEdge(6, 8);

    g->dfsUtil(0);
}