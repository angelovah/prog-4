#include <bits/stdc++.h>

using namespace std;

int main() {
    int n,m;
    cin>>n>>m;
    
    vector<vector<pair<int,int>>> adj(n);
    vector<vector<int>> mat(n, vector<int>(n,0));
    
    for(int i=0;i<m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        adj[u].push_back(make_pair(v,w));
        mat[u][v]=w;
    }
    
    for(int i=0;i<n;i++){
        for(size_t j=0;j<adj[i].size();j++){
            cout<<adj[i][j].first<<adj[i][j].second;
        }
        cout<<endl;
    }
    
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout<<mat[i][j];
        }
        cout<<endl;
    }
    
    return 0;
}
