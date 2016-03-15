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

#define OPEN 1
#define BRIDGE 2
#define CLOSE 3

struct Event
{

    i64 x;
    int typ, number;
    Event(i64 _x, int _typ, int _number) : x(_x), typ(_typ), number(_number) {}
};

bool operator < (Event first, Event second)
{
    if (first.x != second.x)
        return first.x < second.x;
    return first.typ < second.typ;
}

const int maxn = 2e5+5;

vector <Event> events;
i64 L[maxn];
i64 R[maxn];
int ans[maxn];
i64 left_bound[maxn];
i64 right_bound[maxn];

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int n, m;
    scanf("%d%d", &n, &m);
    forn(j, n)
    {
        cin >> L[j] >> R[j];
    }
    forn(j, n - 1)
    {
        right_bound[j] = -L[j] + R[j + 1];
        left_bound[j] = L[j + 1] - R[j];
    //    cout << j << " " << left_bound[j] << " " << right_bound[j] << endl;
        events.pb(Event(left_bound[j], OPEN, j));
        events.pb(Event(right_bound[j], CLOSE, j));  
    }
    forn(j, m)
    {
        i64 a;
        cin >> a;
        events.pb(Event(a, BRIDGE, j));
    }
    sort(events.begin(), events.end());
    set <pair <i64, int > > s;
    for (Event e : events)
    {
 //       cout << "event " << e.x << " " << e.typ << " " << e.number << endl;
        if (e.typ == OPEN)
            s.insert(mp(right_bound[e.number], e.number));
        else if (e.typ == CLOSE)
        {
            if (s.find(mp(e.x, e.number)) != s.end())
            {
                printf("No");
                exit(0);
            }
        }
        else if (!s.empty())
        {
            auto seg = *s.begin();
//            printf("extracting R = %d number = %d\n", seg.fi, seg.se);
            ans[seg.se] = e.number;
            s.erase(s.begin());
        }
    }
    printf("Yes\n");
    forn(j, n - 1)
        printf("%d ", ans[j] + 1);
}
