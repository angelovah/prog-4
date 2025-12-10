#include <bits/stdc++.h>


using namespace std;

string has_dup(string const& s, int len) {
    int n = s.size();
    if (len == 0) return "";

    const int base = 31;
    const int mod = 1e9 + 9;
    
    long long p_pow_len = 1;
    for(int i = 0; i < len; ++i) {
        p_pow_len = (p_pow_len * base) % mod;
    }

    long long curr_h = 0;
    
    for (int i = 0; i < len; ++i) {
        curr_h = (curr_h * base + (s[i] - 'a' + 1)) % mod;
    }
    
    unordered_set<long long> seen;
    seen.insert(curr_h);

    for (int i = len; i < n; ++i) {
        long long v_old = (s[i - len] - 'a' + 1);
        curr_h = (curr_h - (v_old * p_pow_len) % mod + mod) % mod;

        curr_h = (curr_h * base + (s[i] - 'a' + 1)) % mod;

        if (seen.count(curr_h)) {
            return s.substr(i - len + 1, len);
        }
        seen.insert(curr_h);
    }

    return "";
}

string find_longest(string s) {
    int n = s.size();
    int low = 1, high = n - 1;

    string ans = "";

    while (low <= high) {
        int mid = low + (high - low) / 2;

        string tmp = has_dup(s, mid);

        if (!tmp.empty()) {
            ans = tmp;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return ans;
}

int main() {
    string s = "";
    cin >> s;

    cout << find_longest(s) << "\n";
}