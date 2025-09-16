#include <bits/stdc++.h>
using namespace std;

int main() {
    int n,m;
    cin>>n>>m;
    vector<vector<pair<int,int>>> adj(n);
    for(int i=0;i<m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        adj[u].push_back({v,w});
    }

    int src;
    cin>>src;
    vector<int> dist(n,1e9);
    dist[src]=0;

    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    pq.push({0,src});

    while(!pq.empty()){
        int d=pq.top().first;
        int u=pq.top().second;
        pq.pop();
        if(d>dist[u]) continue;
        for(auto edge: adj[u]){
            int v=edge.first;
            int w=edge.second;
            if(dist[u]+w<dist[v]){
                dist[v]=dist[u]+w;
                pq.push({dist[v],v});
            }
        }
    }

    for(int i=0;i<n;i++){
        if(dist[i]==1e9) cout<<-1<<" ";
        else cout<<dist[i]<<" ";
    }
    cout<<endl;

    return 0;
}
