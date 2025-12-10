
#include <bits/stdc++.h>
using namespace std;

static const long long m1 = 1000000007LL;
static const long long m2 = 1000000009LL;
static const long long p = 31LL;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    if (!(cin >> s)) return 0;
    int n = (int)s.size();

    vector<long long> pwr1(n + 1), pwr2(n + 1);
    pwr1[0] = pwr2[0] = 1;
    for (int i = 1; i <= n; ++i) {
        pwr1[i] = (pwr1[i - 1] * p) % m1;
        pwr2[i] = (pwr2[i - 1] * p) % m2;
    }

    vector<long long> h1(n + 1, 0), h2(n + 1, 0);
    string rev_s = s;
    reverse(rev_s.begin(), rev_s.end());
    vector<long long> rh1(n + 1, 0), rh2(n + 1, 0);

    for (int i = 0; i < n; ++i) {
        int v = s[i] - 'a' + 1;
        h1[i + 1] = (h1[i] * p + v) % m1;
        h2[i + 1] = (h2[i] * p + v) % m2;
        
        v = rev_s[i] - 'a' + 1;
        rh1[i + 1] = (rh1[i] * p + v) % m1;
        rh2[i + 1] = (rh2[i] * p + v) % m2;
    }

    auto get_h = [&](int l, int r, const vector<long long>& h_v, const vector<long long>& p_v, const long long mod) {
        int len = r - l + 1;
        long long hash_val = (h_v[r + 1] - (h_v[l] * p_v[len]) % mod + mod) % mod;
        return hash_val;
    };
    
    auto mix_h = [&](long long x1, long long x2) {
        return ((uint64_t)x1 << 32) ^ (uint64_t)x2;
    };

    vector<vector<int>> dp(n, vector<int>(n, 0));
    vector<long long> diff(n + 2, 0);

    for (int len = 1; len <= n; ++len) {
        for (int l = 0; l + len - 1 < n; ++l) {
            int r = l + len - 1;

            int rl = n - 1 - r;
            int rr = n - 1 - l;
            
            uint64_t hf = mix_h(get_h(l, r, h1, pwr1, m1), get_h(l, r, h2, pwr2, m2));
            uint64_t hr = mix_h(get_h(rl, rr, rh1, pwr1, m1), get_h(rl, rr, rh2, pwr2, m2));
            
            if (hf != hr) {
                continue;
            }

            dp[l][r] = 1;

            if (len > 1) {
                int half = len / 2;
                int lr = l + half - 1;
                int rl_half = r - half + 1;

                uint64_t lh = mix_h(get_h(l, lr, h1, pwr1, m1), get_h(l, lr, h2, pwr2, m2));
                uint64_t rh = mix_h(get_h(rl_half, r, h1, pwr1, m1), get_h(rl_half, r, h2, pwr2, m2));

                if (lh == rh) {
                    dp[l][r] = dp[l][lr] + 1;
                }
            }

            int k_val = dp[l][r];
            diff[1] += 1;
            diff[k_val + 1] -= 1;
        }
    }

    vector<long long> ans(n + 1, 0);
    long long cur = 0;
    for (int k = 1; k <= n; ++k) {
        cur += diff[k];
        ans[k] = cur;
    }

    for (int k = 1; k <= n; ++k) {
        if (k > 1) cout << ' ';
        cout << ans[k];
    }
    cout << '\n';
    return 0;
}