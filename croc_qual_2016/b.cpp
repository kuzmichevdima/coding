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

const int maxn = 2e5+5;

struct Event
{
    i64 number, time;   
};

bool operator < (Event first, Event second)
{
    if (first.time != second.time)
        return first.time < second.time;
    return first.number < second.number;
}

set <Event> order;

i64 ans[maxn];
int d[maxn];
queue <int> Q;

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int n, b;
    scanf("%d%d", &n, &b);
    forn(i, n)
    {
        int t;
        scanf("%d%d", &t, &d[i]);
        order.insert(Event{i, t});
    }
    while(!order.empty())
    {
        Event e = *order.begin();
        //printf("Event %d %d\n", e.time, e.number);
        order.erase(order.begin());
        if (e.number >= 0)
        {
            if (Q.empty())
            {
                order.insert(Event{-1, e.time + d[e.number]});
            }
            if ((int)Q.size() <= b)
                Q.push(e.number);
            else ans[e.number] = -1;
        }
        else
        {
            ans[Q.front()] = e.time;
            Q.pop();
            if (!Q.empty())
                order.insert(Event{-1, e.time + d[Q.front()]});
        }
    }
    forn(u, n)
        cout << ans[u] << " ";
}

