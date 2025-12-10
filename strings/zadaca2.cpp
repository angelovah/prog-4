#include <bits/stdc++.h>
using namespace std;
static const long long m1 = 1000000007LL;
static const long long m2 = 1000000009LL;
static const long long p1 = 31LL;
static const long long p2 = 37LL;

struct hash_val {
    long long h1;
    long long h2;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    if (!(cin >> s)) return 0;
    
    string g;
    cin >> g;
    
    int k;
    cin >> k;

    int n = s.size();

    vector<bool> ok(26);
    for (int i = 0; i < 26; ++i) {
        ok[i] = (g[i] == '1');
    }

    unordered_set<uint64_t> seen;
    seen.reserve(1 << 20);

    for (int l = 0; l < n; ++l) {
        int bad = 0;
        hash_val h = {0, 0};
        
        for (int r = l; r < n; ++r) {
            
            if (!ok[s[r] - 'a']) {
                bad++;
            }

            if (bad > k) {
                break;
            }

            int v = s[r] - 'a' + 1; 
            
            h.h1 = (h.h1 * p1 + v) % m1;
            h.h2 = (h.h2 * p2 + v) % m2;

            uint64_t key = ((uint64_t)h.h1 << 32) | (uint64_t)h.h2;

            seen.insert(key);
        }
    }

    cout << seen.size() << '\n';
    
    return 0;
}