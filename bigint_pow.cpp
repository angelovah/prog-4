#include <bits/stdc++.h>
using namespace std;

class bigint {
public:
    string s;

    bigint(string n = "0") {
        s = n;
    }

    bool low(bigint b) {
        if (s.length() != b.s.length()) {
            return s.length() < b.s.length();
        }
        return s < b.s;
    }

    bool eq(bigint b) {
        return s == b.s;
    }

    bigint operator+(bigint b) {
        string r = "";
        int i = s.length() - 1;
        int j = b.s.length() - 1;
        int c = 0;
        while (i >= 0 || j >= 0 || c) {
            int v1 = 0;
            if (i >= 0) {
                v1 = s[i] - '0';
                i--;
            }
            int v2 = 0;
            if (j >= 0) {
                v2 = b.s[j] - '0';
                j--;
            }
            int sum = v1 + v2 + c;
            r += (char)((sum % 10) + '0');
            c = sum / 10;
        }
        reverse(r.begin(), r.end());
        return bigint(r);
    }

    bigint operator-(bigint b) {
        string r = "";
        int i = s.length() - 1;
        int j = b.s.length() - 1;
        int t = 0;
        while (i >= 0) {
            int v1 = s[i] - '0';
            i--;
            int v2 = 0;
            if (j >= 0) {
                v2 = b.s[j] - '0';
                j--;
            }
            int sub = v1 - v2 - t;
            if (sub < 0) {
                sub += 10;
                t = 1;
            } else {
                t = 0;
            }
            r += (char)(sub + '0');
        }
        while (r.length() > 1 && r.back() == '0') {
            r.pop_back();
        }
        reverse(r.begin(), r.end());
        return bigint(r);
    }

    bigint operator*(bigint b) {
        int n = s.length();
        int m = b.s.length();
        vector<int> v(n + m, 0);
        for (int i = n - 1; i >= 0; i--) {
            for (int j = m - 1; j >= 0; j--) {
                int p = (s[i] - '0') * (b.s[j] - '0') + v[i + j + 1];
                v[i + j + 1] = p % 10;
                v[i + j] += p / 10;
            }
        }
        string res = "";
        for (int x : v) {
            if (res.empty() && x == 0) continue;
            res += (char)(x + '0');
        }
        if (res.empty()) return bigint("0");
        return bigint(res);
    }

    pair<bigint, bigint> dm(bigint b) {
        if (b.s == "0") return {bigint("0"), bigint("0")};
        string q = "";
        string tmp = "";
        for (char c : s) {
            tmp += c;
            while (tmp.size() > 1 && tmp[0] == '0') {
                tmp.erase(0, 1);
            }
            bigint cur(tmp);
            int cnt = 0;
            while (!cur.low(b)) {
                cur = cur - b;
                if (cur.s == "0") tmp = "";
                else tmp = cur.s;
                cnt++;
            }
            q += (char)(cnt + '0');
        }
        size_t p = q.find_first_not_of('0');
        string fq;
        if (p == string::npos) fq = "0";
        else fq = q.substr(p);
        string fr;
        if (tmp == "") fr = "0";
        else fr = tmp;
        return {bigint(fq), bigint(fr)};
    }

    bigint operator/(bigint b) { return dm(b).first; }
    bigint operator%(bigint b) { return dm(b).second; }
};

bigint bpow(bigint a, bigint e, bigint m) {
    bigint res("1");
    a = a % m;
    while (!e.eq(bigint("0"))) {
        bigint rem = e % bigint("2");
        if (!rem.eq(bigint("0"))) {
            res = (res * a) % m;
        }
        a = (a * a) % m;
        e = e / bigint("2");
    }
    return res;
}

int main() {
    string s1, s2, s3;
    cin >> s1 >> s2 >> s3;
    bigint b(s1), e(s2), m(s3);
    bigint res = bpow(b, e, m);
    cout << res.s << endl;
    return 0;
}