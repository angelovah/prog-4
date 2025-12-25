#include <bits/stdc++.h>
using namespace std;

string clean(string s) {
    string res = "";
    for (char c : s) {
        if (isalpha(c)) res += tolower(c);
    }
    return res;
}

struct Node {
    string val;
    bool fin;
    vector<Node*> kids;

    Node(string v = "") : val(v), fin(false) {
        kids.assign(26, nullptr);
    }

    ~Node() {
        for (Node* k : kids) delete k;
    }
};

class PatTrie {
private:
    Node* root;

    int get_idx(char c) const { return c - 'a'; }

    int match(string s1, string s2) const {
        int i = 0;
        while (i < s1.size() && i < s2.size() && s1[i] == s2[i]) i++;
        return i;
    }

public:
    PatTrie() { root = new Node(); }
    ~PatTrie() { delete root; }

    void add(string w) {
        string s = clean(w);
        if (s.empty()) return;

        Node* cur = root;
        while (!s.empty()) {
            int idx = get_idx(s[0]);
            Node* nxt = cur->kids[idx];

            if (!nxt) {
                cur->kids[idx] = new Node(s);
                cur->kids[idx]->fin = true;
                return;
            }

            int len = match(s, nxt->val);

            if (len == nxt->val.size()) {
                s = s.substr(len);
                cur = nxt;
            } else {
                string com = nxt->val.substr(0, len);
                Node* mid = new Node(com);
                
                nxt->val = nxt->val.substr(len);
                mid->kids[get_idx(nxt->val[0])] = nxt;
                
                string rem = s.substr(len);
                if (rem.empty()) {
                    mid->fin = true;
                } else {
                    Node* leaf = new Node(rem);
                    leaf->fin = true;
                    mid->kids[get_idx(rem[0])] = leaf;
                }
                cur->kids[idx] = mid;
                return;
            }
        }
        cur->fin = true;
    }

    bool has(string w) const {
        string s = clean(w);
        if (s.empty()) return false;

        Node* cur = root;
        while (!s.empty()) {
            int idx = get_idx(s[0]);
            Node* nxt = cur->kids[idx];

            if (!nxt) return false;

            int len = match(s, nxt->val);
            if (len < nxt->val.size()) {
                return (len == s.size() && nxt->fin); 
            }
            s = s.substr(len);
            cur = nxt;
        }
        return cur->fin;
    }
};

int main() {
    PatTrie pt;
    string w;

    ifstream in("zborovi.txt");
    if (in.is_open()) {
        while (in >> w) {
            pt.add(w);
        }
        in.close();
    }

    return 0;
}