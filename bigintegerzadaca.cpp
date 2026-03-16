#include <bits/stdc++.h>
using namespace std;

class BigInt {
public:
    string s;

    BigInt(string n = "0") : s(n) { fix(); }

    void fix() {
        size_t p = s.find_first_not_of('0');
        s = (p == string::npos) ? "0" : s.substr(p);
    }

    bool operator<(const BigInt& b) const {
        if (s.size() != b.s.size()) return s.size() < b.s.size();
        return s < b.s;
    }

    BigInt operator+(const BigInt& b) {
        string r = "";
        int i = s.size()-1, j = b.s.size()-1, c = 0;
        while (i >= 0 || j >= 0 || c) {
            int v = (i >= 0 ? s[i--]-'0' : 0) + (j >= 0 ? b.s[j--]-'0' : 0) + c;
            r += (char)(v % 10 + '0');
            c = v / 10;
        }
        reverse(r.begin(), r.end());
        return BigInt(r);
    }

    BigInt operator-(const BigInt& b) {
        string r = "";
        int i = s.size()-1, j = b.s.size()-1, t = 0;
        while (i >= 0) {
            int v = (s[i--]-'0') - (j >= 0 ? b.s[j--]-'0' : 0) - t;
            if (v < 0) { v += 10; t = 1; } else t = 0;
            r += (char)(v + '0');
        }
        reverse(r.begin(), r.end());
        return BigInt(r);
    }

    BigInt operator*(const BigInt& b) {
        int n = s.size(), m = b.s.size();
        vector<int> v(n + m, 0);
        for (int i = n - 1; i >= 0; i--) {
            for (int j = m - 1; j >= 0; j--) {
                int p = (s[i]-'0') * (b.s[j]-'0') + v[i+j+1];
                v[i+j+1] = p % 10;
                v[i+j] += p / 10;
            }
        }
        string r = "";
        for (int x : v) if (!(r.empty() && x == 0)) r += (char)(x + '0');
        return r.empty() ? BigInt("0") : BigInt(r);
    }

    BigInt operator/(const BigInt& b) {
        if (b.s == "0") return BigInt("0");
        string r = "", cur = "";
        for (char c : s) {
            cur += c;
            BigInt tmp(cur);
            int k = 0;
            while (!(tmp < b)) {
                tmp = tmp - b;
                cur = tmp.s;
                k++;
            }
            r += (char)(k + '0');
        }
        return BigInt(r);
    }
};

int main() {
    string in1, in2;
    if (!(cin >> in1 >> in2)) return 0;

    BigInt a(in1), b(in2);

    cout << (a + b).s << "\n";
    cout << (a - b).s << "\n";
    cout << (a * b).s << "\n";
    cout << (a / b).s << "\n";

    return 0;
}