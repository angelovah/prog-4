#include <bits/stdc++.h>


using namespace std;

class gstr {
private:
    char* txt;
    int32_t len;
    char* pre; 

    void init_prefix(const char* str, int size) {
        if (size <= 12) {
            pre = new char[5];
            int prefix_len = min(4, size);
            memcpy(pre, str, prefix_len);
            pre[prefix_len] = '\0';
        } else {
            pre = nullptr;
        }
    }

    void cleanup() {
        delete[] txt;
        delete[] pre;
        txt = nullptr;
        pre = nullptr;
        len = 0;
    }

public:
    gstr() {
        len = 0;
        txt = nullptr;
        pre = nullptr;
    } 

    gstr(const char* str) {
        if (str) {
            len = strlen(str);
            txt = new char[len + 1];
            memcpy(txt, str, len + 1); 
            init_prefix(str, len);
        } else {
            len = 0;
            txt = nullptr;
            pre = nullptr;
        }
    }

    gstr(const gstr& other) {
        len = other.len;
        if (len > 0) {
            txt = new char[len + 1];
            memcpy(txt, other.txt, len + 1);

            if (len <= 12) {
                pre = new char[5];
                memcpy(pre, other.pre, min(4, len) + 1);
            } else {
                pre = nullptr;
            }
        } else {
            txt = nullptr;
            pre = nullptr;
        }
    }

    gstr& operator=(const gstr& other) {
        if (this == &other) return *this;

        cleanup(); 

        len = other.len;
        if (len > 0) {
            txt = new char[len + 1];
            memcpy(txt, other.txt, len + 1);

            if (len <= 12) {
                pre = new char[5];
                memcpy(pre, other.pre, min(4, len) + 1);
            } else {
                pre = nullptr;
            }
        }
        return *this;
    }

    ~gstr() {
        cleanup();
    }

    int size_of() const {
        return len;
    }

    void print() const {
        if (txt) {
            cout << txt << '\n';
        } else {
            cout << "" << '\n';
        }
    }

    void clear() {
        cleanup();
    }

    const char& operator[](int idx) const {
        return txt[idx];
    }

    int find(char c) const {
        if (!txt) return -1;
        for (int i = 0; i < len; ++i) {
            if (txt[i] == c) return i;
        }
        return -1;
    }

    char& operator[](int idx) {
        return txt[idx]; 
    }
};

gstr operator+(const gstr& one, const gstr& other) {
    int len_one = one.size_of();
    int len_other = other.size_of();
    int new_len = len_one + len_other;
    
    char* new_txt = new char[new_len + 1];
    
    for (int i = 0; i < len_one; i++) {
        new_txt[i] = one[i];
    }
    
    for (int i = 0; i < len_other; i++) {
        new_txt[len_one + i] = other[i];
    }
    
    new_txt[new_len] = '\0';

    gstr res(new_txt);

    delete [] new_txt;
    
    return res;
}

int main()
{
    string s_input, k_input;
    
    cin >> s_input >> k_input;

    gstr s(s_input.c_str());
    gstr k(k_input.c_str());

    cout << s.size_of();
    cout << endl;

    s.print();

    cout << s[2];
    cout << endl;

    s[2] = 'p';

    cout << s[2];
    cout << endl;
    
    char f = 'a';
    cout << s.find(f);
    cout << endl;

    gstr c = s + k;

    c.print();

    return 0;
}