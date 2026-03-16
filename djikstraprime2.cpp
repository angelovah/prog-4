#include <bits/stdc++.h>
using namespace std;

class bigint {
public:
    string val;

    bigint(string s = "0") {
        val = s;
    }

    bool low(bigint b) {
        if (val.size() != b.val.size())
            return val.size() < b.val.size();
        return val < b.val;
    }

    bigint operator+(bigint b) {
        string res = "";
        int i = val.size() - 1, j = b.val.size() - 1, car = 0;
        while (i >= 0 || j >= 0 || car) {
            int v1 = (i >= 0) ? val[i--] - '0' : 0;
            int v2 = (j >= 0) ? b.val[j--] - '0' : 0;
            int sum = car + v1 + v2;
            res += (char)((sum % 10) + '0');
            car = sum / 10;
        }
        reverse(res.begin(), res.end());
        return bigint(res);
    }

    bigint operator-(bigint b) {
        string res = "";
        int i = val.size() - 1, j = b.val.size() - 1, bor = 0;
        while (i >= 0) {
            int v1 = val[i--] - '0';
            int v2 = (j >= 0) ? b.val[j--] - '0' : 0;
            int sub = v1 - v2 - bor;
            if (sub < 0) {
                sub += 10;
                bor = 1;
            } else {
                bor = 0;
            }
            res += (char)(sub + '0');
        }
        while (res.size() > 1 && res.back() == '0') res.pop_back();
        reverse(res.begin(), res.end());
        return bigint(res);
    }

    bigint operator*(bigint b) {
        int n = val.size(), m = b.val.size();
        vector<int> v(n + m, 0);
        for (int i = n - 1; i >= 0; i--) {
            for (int j = m - 1; j >= 0; j--) {
                int mul = (val[i] - '0') * (b.val[j] - '0');
                int sum = mul + v[i + j + 1];
                v[i + j + 1] = sum % 10;
                v[i + j] += sum / 10;
            }
        }
        string r = "";
        for (int x : v) if (!(r.empty() && x == 0)) r += (char)(x + '0');
        return r.empty() ? bigint("0") : bigint(r);
    }

    bigint operator/(bigint b) {
        if (b.val == "0") return bigint("err");
        string res = "", curS = "";
        for (char c : val) {
            curS += c;
            while(curS.size() > 1 && curS[0] == '0') curS.erase(0, 1);
            bigint cur(curS);
            int cnt = 0;
            while (!(cur.low(b))) {
                cur = cur - b;
                curS = (cur.val == "0") ? "" : cur.val;
                cnt++;
            }
            res += (char)(cnt + '0');
        }
        size_t p = res.find_first_not_of('0');
        return (p == string::npos) ? bigint("0") : bigint(res.substr(p));
    }
};

struct comp {
    bool operator()(pair<bigint, bigint> p1, pair<bigint, bigint> p2) {
        return p2.first.low(p1.first);
    }
};

void djbig(int n) {
    priority_queue<pair<bigint, bigint>, vector<pair<bigint, bigint>>, comp> q;
    cout << "2 ";
    q.push({bigint("4"), bigint("2")});
    for (int i = 3; i <= n; i++) {
        bigint cur(to_string(i));
        if (cur.low(q.top().first)) {
            cout << i << " ";
            q.push({cur * cur, cur});
        } else {
            while (cur.val == q.top().first.val) {
                pair<bigint, bigint> top = q.top();
                q.pop();
                q.push({top.first + top.second, top.second});
            }
        }
    }
    cout << endl;
}

int main() {
    int num;
    cin >> num;
    djbig(num);
    return 0;
}