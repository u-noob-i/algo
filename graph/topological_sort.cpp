#include<iostream>
#include<vector>
#include<queue>

using namespace std;

class Graph{
    private:

    int vertices;
    vector<vector<int>> adjlist;
    vector<int> indegree;

    public:

    Graph(int v)
    {
        vertices=v;
        adjlist.resize(vertices);
        indegree.resize(vertices);
        for(int i=0;i<vertices;i++)
        {
            indegree[i]=0;
        }

        return;
    }

    void addEdge(int u, int v)
    {
        adjlist[u].push_back(v);
        indegree[v]++;

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

    void topo()
    {
        vector<int> a=indegree;
        queue<int> q;

        for(int i=0;i<vertices;i++)
        {
            if(a[i]==0)
            {
                q.push(i);
            }
        }   

        if(q.empty())
        {
            cout<<"F\n";
            return;
        }

        while(!q.empty())
        {
            int x=q.front();
            q.pop();
            cout<<x<<" ";

            for(auto itr:adjlist[x])
            {
                a[itr]--;
                if(a[itr]==0)
                {
                    q.push(itr);
                }
            }
        }

        return;
    }

};

int main()
{
    Graph *g=new Graph(6);

    g->addEdge(5, 2);
    g->addEdge(5, 0);
    g->addEdge(4, 0);
    g->addEdge(4, 1);
    g->addEdge(2, 3);
    g->addEdge(3, 1);

    g->topo();
}