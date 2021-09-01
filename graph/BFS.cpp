#include<iostream>
#include<vector>
#include<queue>

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

    void bfs(int v)
    {
        for(int i=0;i<vertices;i++)
        {
            visited[i]=0;
        }

        queue<int> q;
        q.push(v);
        visited[v]=1;

        while(!q.empty())
        {
            int x=q.front();
            q.pop();
            
            cout<<x<<" ";

            for(auto itr: adjlist[x])
            {
                if(!visited[itr])
                {
                    visited[itr]=1;
                    q.push(itr);
                }
            }
        }        

        return;
    }

};

int main()
{
    Graph *g=new Graph(9);

    g->addEdge(0, 1);
    g->addEdge(0, 2);
    g->addEdge(1, 0);
    g->addEdge(1, 2);
    g->addEdge(1, 3);
    g->addEdge(2, 0);
    g->addEdge(2, 1);
    g->addEdge(2, 3);
    g->addEdge(3, 1);
    g->addEdge(3, 2);
    g->addEdge(3, 4);
    g->addEdge(4, 3);
    g->addEdge(4, 5);
    g->addEdge(4, 6);
    g->addEdge(5, 4);
    g->addEdge(5, 6);
    g->addEdge(5, 7);
    g->addEdge(6, 4);
    g->addEdge(6, 5);
    g->addEdge(6, 7);
    g->addEdge(7, 5);
    g->addEdge(7, 6);
    g->addEdge(8, 7);

    g->bfs(8);
}