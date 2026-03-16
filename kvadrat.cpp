#include <bits/stdc++.h>
using namespace std;

class dot {
public:
    double x, y, z;
    dot(double a = 0, double b = 0, double c = 0) {
        x = a; y = b; z = c;
    }
};

class sq {
public:
    dot a, b, c, d;
    sq(dot p1, dot p2, dot p3, dot p4) {
        a = p1; b = p2; c = p3; d = p4;
    }
};

void move(sq &k) {
    k.a.x += 2.0;
    k.b.x += 2.0;
    k.c.x += 2.0;
    k.d.x += 2.0;
}

void rot45(sq &k) {
    double rad = 45.0 * M_PI / 180.0;
    double s = sin(rad);
    double c = cos(rad);

    double mx = (k.a.x + k.b.x + k.c.x + k.d.x) / 4.0;
    double my = (k.a.y + k.b.y + k.c.y + k.d.y) / 4.0;

    double x1 = k.a.x - mx; double y1 = k.a.y - my;
    k.a.x = x1 * c - y1 * s + mx;
    k.a.y = x1 * s + y1 * c + my;

    double x2 = k.b.x - mx; double y2 = k.b.y - my;
    k.b.x = x2 * c - y2 * s + mx;
    k.b.y = x2 * s + y2 * c + my;

    double x3 = k.c.x - mx; double y3 = k.c.y - my;
    k.c.x = x3 * c - y3 * s + mx;
    k.c.y = x3 * s + y3 * c + my;

    double x4 = k.d.x - mx; double y4 = k.d.y - my;
    k.d.x = x4 * c - y4 * s + mx;
    k.d.y = x4 * s + y4 * c + my;
}

void zoom(sq &k) {
    double f = 2.0;
    double mx = (k.a.x + k.b.x + k.c.x + k.d.x) / 4.0;
    double my = (k.a.y + k.b.y + k.c.y + k.d.y) / 4.0;
    double mz = (k.a.z + k.b.z + k.c.z + k.d.z) / 4.0;

    k.a.x = mx + (k.a.x - mx) * f; k.a.y = my + (k.a.y - my) * f; k.a.z = mz + (k.a.z - mz) * f;
    k.b.x = mx + (k.b.x - mx) * f; k.b.y = my + (k.b.y - my) * f; k.b.z = mz + (k.b.z - mz) * f;
    k.c.x = mx + (k.c.x - mx) * f; k.c.y = my + (k.c.y - my) * f; k.c.z = mz + (k.c.z - mz) * f;
    k.d.x = mx + (k.d.x - mx) * f; k.d.y = my + (k.d.y - my) * f; k.d.z = mz + (k.d.z - mz) * f;
}

int main() {
    ifstream f1("file.txt");
    string ln;
    vector<dot> v;

    if (f1.is_open()) {
        while (getline(f1, ln)) {
            stringstream ss(ln);
            string pre;
            ss >> pre;
            if (pre == "v") {
                double x, y, z;
                ss >> x >> y >> z;
                v.push_back(dot(x, y, z));
            }
        }
        f1.close();
    }

    if (v.size() >= 4) {
        sq k(v[0], v[1], v[2], v[3]);

        cout << k.a.x << " " << k.a.y << endl;
        move(k);
        cout << k.a.x << endl;
        rot45(k);
        cout << k.a.x << " " << k.a.y << endl;
        zoom(k);
        cout << k.a.x << " " << k.a.y << endl;
    } else {
        cout << "err" << endl;
    }

    return 0;
}