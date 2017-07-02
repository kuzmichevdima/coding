#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <iostream>
#include <cassert>
#include <cmath>
#include <string>
#include <queue>
#include <set>
#include <map>
#include <cstdlib>

using namespace std;

#define INF 1e+9
#define mp make_pair
#define pb push_back
#define fi first
#define fs first
#define se second
#define i64 long long
#define li long long
#define lint long long
#define pii pair<int, int>
#define vi vector<int>

#define forn(i, n) for (int i = 0; i < (int)n; i++)
#define fore(i, b, e) for (int i = (int)b; i <= (int)e; i++)

const double eps = 1.e-9;


double sqr(double x) {
    return x * x;
}

struct Point {
    double x, y;
    Point() {}
    Point(double x, double y) : x(x), y(y) {}
    Point(Point a, Point b) {
        x = b.x - a.x;
        y = b.y - a.y;
    }
    double dist(Point an) {
        return sqrt(sqr(x - an.x) + sqr(y - an.y));
    }
    void print() {
        printf("%.5lf %.5lf\n", x, y);
    }
    double dot(Point an) {
        return x * an.x + y * an.y;
    }
};

Point p[4];

struct Line {
    double a, b, c;
    Line(Point p1, Point p2) {
        a = p2.y - p1.y;
        b = p1.x - p2.x;
        c = -p1.x * a - p1.y * b;
    }
    Point intersect(Line second, bool & flag) {
        double tmp = b * second.a - a * second.b;
        if (abs(tmp) <= eps) {
            flag = false;
            return Point(-1, -1);
        }
        flag = true;
        double y = -(c * second.a - a * second.c) / tmp;
        double x = (c * second.b - b * second.c) / tmp;
        return Point(x, y);
    }
    bool lies(Point p) {
        return abs(a * p.x + b * p.y + c) < eps;
    }
};

bool on_seg(Point A, Point B, Point C) {
    Line l(A, B);
    if (!l.lies(C))
        return false;
    Point AB(A, B);
    Point AC(A, C);
    if (AB.dot(AC) < 0)
        return false;
    Point BA(B, A);
    Point BC(B, C);
    if (BA.dot(BC) < 0)
        return false;
    return true;
}

bool check(vector<Point> tri) {
    if (!(tri[0].dist(tri[1]) > eps && tri[0].dist(tri[2]) > eps))
        return false;
    /*printf("check\n");
    for (auto p : tri)
        printf("%.1lf %.1lf\n", p.x, p.y);*/
    forn(i, 4) {
        bool found = false;
        forn(first, 3)
            fore(second, first + 1, 2)
                if (on_seg(tri[first], tri[second], p[i])) {
                    found = true;
                }
        if (!found)
            return false;
    }
    return true;
}

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int tests;
    scanf("%d", &tests);
    forn(test, tests) {
        forn(i, 4)
            scanf("%lf%lf", &p[i].x, &p[i].y);
        vi perm(4);
        forn(i, 4)
            perm[i] = i;
        bool flag = false;
        vector <Point> ans;
        do {
            Point A = p[perm[0]];
            Point B = p[perm[1]];
            Point C = p[perm[2]];
            Point D = p[perm[3]];
            Line l1(A, B);
            Line l2(C, D);
            Point E = l1.intersect(l2, flag);
            if (flag) {
                vector <Point> tri(3);
                tri[0] = E;
                flag = false;
                forn(first, 4) {
                    tri[1] = p[first];
                    fore(second, first + 1, 3) {
                        tri[2] = p[second];
                        if (check(tri)) {
                            ans = tri;
                            flag = true;
                            break;
                        }
                    }
                }
                if (flag)
                    break;
            }
        } while (next_permutation(perm.begin(), perm.end()));
        if (!flag) {
            Line l(p[0], p[1]);
            if (l.lies(p[2]) && l.lies(p[3])) {
                double dx = p[1].x - p[0].x;
                double dy = p[1].y - p[0].y;
                flag = true;
                vector <Point> triag;
                triag.pb(Point(p[0].x + dx * 1000, p[0].y + dy * 1000));
                triag.pb(Point(p[0].x - dx * 1000, p[0].y - dy * 1000));
                int maxx = 1e5;
                triag.pb(Point(rand() % maxx, rand() % maxx));
                if (check(triag)) {
                    flag = true;
                    ans = triag;
                }
            }
        }
        if (flag) {
            printf("YES ");
            forn(j, 3)
                printf("%.10lf %.10lf ", ans[j].x, ans[j].y);
        } else {
            printf("NO");
        }
        printf("\n");
        
    }
}

