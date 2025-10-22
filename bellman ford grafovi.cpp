#include <iostream>
#include <vector>
#include <fstream>
using namespace std;


vector<int> bf(int start, int n, vector<vector<int>> edges)
{
    vector<int> dist(n,INT_MAX);

    dist[start] = 0;

    for(int i=0; i<n; i++)
    {
        for(auto edge : edges)
        {
            int from = edge[0];
            int to = edge[1];
            int w = edge[2];

            if(dist[from]!=INT_MAX && dist[from]+w < dist[to])
            {
                if(i==n-1)
                {
                    return {-1};
                }

                dist[to] = dist[from] + w;
            }
        }
    }

    return dist;
}


vector<vector<int>> make_graph(int n)
{
    vector<vector<int>> edges;

    for(int i=0; i<n-1; i++)
    {
        int w = (rand() % 33) - 14;
        if(w==0)
        w = 1;

        edges.push_back({i,i+1,w});
    }

    for(int i=0; i<7; i++)
    {
        int from = rand() % n;
        int to = rand() % n;

        if(from==to)
        continue;

        int w = (rand() % 33) - 14;
        if(w==0)
        w = -11;

        edges.push_back({from,to,w});
    }

    return edges;

}


int main()
{
    int n = 50;
    srand(time(0));
    
    ofstream file("output.txt");

    for(int i=0; i<10; i++)
    {
        
        vector<vector<int>> graph = make_graph(n);

        vector<int> dist = bf(0,n,graph);
        

        if(file.is_open())
        {
            for(auto v:graph)
            {
                file << v[0] << ' ' << v[1] << ' ' << v[2] << '\n';
            }

            file << '\n';

            if(dist.size() == 1)
            {
                file << -1;
            }
            else
            {
                for(int i=0;i<n;i++)
                {
                    file << dist[i] << ' ';
                }
            }
           

            file << endl;

            
        }

    }

    file.close();

    return 0;
}