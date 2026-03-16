#include <bits/stdc++.h>
using namespace std;

void djprime(int n) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
    
    cout << 2 << " ";
    q.push({4, 2});

    for (int i = 3; i <= n; i++) {
        if (i < q.top().first) {
            cout << i << " ";
            q.push({i * i, i});
        } else {
            while (i == q.top().first) {
                pair<int, int> tmp = q.top();
                q.pop();
                q.push({tmp.first + tmp.second, tmp.second});
            }
        }
    }
    cout << endl;
}

int main() {
    int val;
    cin >> val;
    djprime(val);
    return 0;
}