#include <bits/stdc++.h>

using namespace std;

vector<int> bellmanFord(int v, vector<vector<int>>& edges, int src) {
    vector<int> dist(v, 1e8);
    dist[src] = 0;
    for (int i = 0; i < v; i++) {
        for (vector<int> edge : edges) {
            int u = edge[0];
            int w = edge[1];
            int wt = edge[2];
            if (dist[u] != 1e8 && dist[u] + wt < dist[w]) {
                if (i == v - 1)
                    return {-1};
                dist[w] = dist[u] + wt;
            }
        }
    }
    return dist;
}

int main() {
    int v, e;
    cin >> v >> e;
    vector<vector<int>> edges(e, vector<int>(3));
    for (int i = 0; i < e; i++) {
        cin >> edges[i][0] >> edges[i][1] >> edges[i][2];
    }
    int src;
    cin >> src;
    vector<int> dist = bellmanFord(v, edges, src);
    if (dist.size() == 1 && dist[0] == -1) {
        cout << -1 << endl;
    } else {
        for (int i = 0; i < v; i++) {
            if (dist[i] == 1e8)
                cout << -1 << " ";
            else
                cout << dist[i] << " ";
        }
        cout << endl;
    }
    return 0;
}
