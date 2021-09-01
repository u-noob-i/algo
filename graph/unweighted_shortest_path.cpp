#include<iostream>
#include<vector>
#include<queue>
#include<stack>

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

    void shortest(int v)
    {
        vector<int> a(vertices),path(vertices);
        for(int i=0;i<vertices;i++)
        {
            a[i]=-1;
        }

        a[v]=0;
        path[v]=-1;
        queue<int> q;
        q.push(v);

        while(!q.empty())
        {
            int x=q.front();
            q.pop();
            
            for(auto itr:adjlist[x])
            {
                if(a[itr]==-1)
                {
                    path[itr]=x;
                    a[itr]=a[x]+1;
                    q.push(itr);
                }
            }
        }
        
        for(int i=1;i<vertices;i++)
        {
            cout<<"Shortest path from "<<v<<" to "<<i<<" is: \n";
            stack<int> p;
            p.push(i);

            int ind=i;

            while(ind!=v)
            {
                p.push(path[ind]);
                ind=path[ind];
            }

            while(!p.empty())
            {
                cout<<p.top()<<" ";
                p.pop();
            }
            cout<<"\n";
        }

        return;
    }

};

int main()
{
    Graph *g=new Graph(8);

    g->addEdge(1, 2);
    g->addEdge(1, 4);
    g->addEdge(2, 4);
    g->addEdge(2, 5);
    g->addEdge(3, 1);
    g->addEdge(3, 6);
    g->addEdge(4, 3);
    g->addEdge(4, 5);
    g->addEdge(4, 6);
    g->addEdge(4, 7);
    g->addEdge(5, 7);
    g->addEdge(7, 6);
    
    g->shortest(3);
}