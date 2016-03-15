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

i64 sqr(i64 x)
{
    return x * x;
}

struct Point
{
    int x, y;
    i64 sqrdist(Point an)
    {
        return sqr(x - an.x) + sqr(y - an.y);
    }
};

struct Vector
{
    i64 x, y;
	//Vector(i64 x, i64 y) : x(x), y(y) {}
    Vector(Point p1, Point p2)
    {
        x = p2.x - p1.x;
        y = p2.y - p1.y;
    }
    i64 sqrlen()
    {
        return x * x + y * y;
    }
    void print()
    {
        cout << x << " " << y << endl;
    }
};

Vector v;

i64 operator % (Vector v1, Vector v2)
{
    return v1.x * v2.y - v1.y * v2.x;
}

i64 operator * (Vector v1, Vector v2)
{
    return v1.x * v2.x + v1.y * v2.y;
}

const int maxn = 2e5 + 5;

Point p[maxn];
int st[maxn];

bool operator < (Vector v1, Vector v2)
{
    i64 cp = v1 % v2;
    /*printf("v1:\n");
    v1.print();
    printf("v2:\n");
    v2.print();
    printf("cp = %lld\n", cp);*/
    return (cp < 0 || (cp == 0 && v1.sqrlen() < v2.sqrlen()));
}

bool operator < (Point p1, Point p2)
{
    Vector v1(p[0], p1);
    Vector v2(p[0], p2);
    return v1 < v2;
}

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int n;
    scanf("%d", &n);
    if (n == 1)
    {
        printf("0.0");
        exit(0);
    }
    forn(j, n)
        scanf("%d%d", &p[j].x, &p[j].y);
    int border = 0;
    forn(j, n)
        if (p[j].y < p[border].y || (p[j].y == p[border].y && p[j].x < p[border].x))
            border = j;
//    printf("border = %d\n", border);
    swap(p[0], p[border]);
    sort(p + 1, p + n);
    /*printf("after sort\n");
    forn(j, n)
        printf("%d %d\n", p[j].x, p[j].y);*/
    st[0] = 0;
    st[1] = 1;
    int sz = 2;
	
    fore(i, 2, n - 1)
    {
      //  printf("i = %d\n", i);
        while(sz >= 2)
        {
           // printf("current: %d %d\n", st[sz - 2], st[sz - 1]);
            Point p1 = p[st[sz - 2]];
            Point p2 = p[st[sz - 1]];
            Point p3 = p[i];
            Vector prevv(p1, p2);
            Vector v(p2, p3);
            i64 cp = prevv % v;
            if (cp < 0 || (cp == 0 && p1.sqrdist(p2) > p1.sqrdist(p3)))
                break;
            sz--;
        }
        st[sz] = i;
        sz++;
    }
/*    printf("sz = %d\n", sz);
    forn(j, sz)
        printf("%d %d\n", p[st[j]].x, p[st[j]].y);*/
    if (sz <= 2)
    {
        printf("0.0");
        exit(0);
    }
    double ans = 100500;
    forn(j, sz)
    {
        int prevj = (j == 0 ? sz - 1 : j - 1);
        int nextj = (j == sz - 1 ? 0 : j + 1);
        Vector v1(p[st[j]], p[st[prevj]]);
        Vector v2(p[st[j]], p[st[nextj]]);
        /*printf("j = %d\n", j);
        v1.print();
        v2.print();*/
        double ang = abs(atan2((double)(v1 % v2), (double)(v1 * v2)));
        ans = min(ans, ang);

//        printf("j = %d ans = %.10lf\n", j, ans);
    }
    //printf("%.10lf\n", ans / M_PI * 180.0);
}
