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

#define START 0
#define FINISH 1
#define LEFT 2
#define RIGHT 3

struct Event {
    int x, start_or_finish, id, left_or_right;
    Event(int x, int start_or_finish, int id, int left_or_right) : x(x), start_or_finish(start_or_finish), id(id), left_or_right(left_or_right) {}
};

bool operator < (Event first, Event second) {
    if (first.x != second.x)
        return first.x < second.x;
    return first.left_or_right < second.left_or_right;
}

const int maxn = 1e6 + 5;

vector <Event> events;
int a[maxn];
int next_bad[maxn];

inline void check(int start_id, int finish_id, int x) {
//    printf("check start_id = %d finish_id = %d x = %d\n", start_id, finish_id, x);
    if (start_id != -1 && finish_id != -1 && next_bad[start_id] >= finish_id) {
        printf("%d", x);
        exit(0);
    }
}

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int n, m, h_min, h_max;
    scanf("%d", &n);
    forn(i, n)
        scanf("%d", &a[i]);
    scanf("%d%d%d", &m, &h_min, &h_max);
    if (m >= h_min && m <= h_max) {
        printf("%d", a[0] - m);
        exit(0);
    }
    next_bad[n] = n;
    for (int i = n - 1; i >= 0; i--) {
        next_bad[i] = next_bad[i + 1];
        if (i != n - 1 && (a[i + 1] - a[i] < h_min || a[i + 1] - a[i] > h_max))
            next_bad[i] = i + 1;
    }
    fore(i, 0, n) {
       if (i != n) {
           int start_L = a[i] - h_max;
           if (i != 0)
               start_L = max(start_L, a[i - 1]);
           int start_R = a[i] - h_min;
           if (start_L <= start_R) {
               events.pb(Event(start_L, START, i, LEFT));
               events.pb(Event(start_R, START, i, RIGHT));
           }
       }
       if (i != 0) {
           int finish_L = a[i - 1] + h_min;
           int finish_R = a[i - 1] + h_max;
           if (i != n)
               finish_R = min(finish_R, a[i]);
           if (finish_L <= finish_R) {
               events.pb(Event(finish_L - m, FINISH, i, LEFT));
               events.pb(Event(finish_R - m, FINISH, i, RIGHT));
           }
       }
    }
    sort(events.begin(), events.end());
/*    for (Event e : events)
        printf("event x = %d id = %d left? = %d start? = %d\n", e.x, e.id, e.left_or_right == LEFT, e.start_or_finish == START);*/
    int start_id = -1;
    int finish_id = -1;
    for (Event e : events) {
        if (e.start_or_finish == START) {
            if (e.left_or_right == LEFT) {
                start_id = e.id;
                check(start_id, finish_id, e.x);
            } else {
                if (start_id == e.id)
                    start_id = -1;
            }
        } else {
            if (e.left_or_right == LEFT) { 
                finish_id = e.id;
                check(start_id, finish_id, e.x);
            } else {
                if (finish_id == e.id)
                    finish_id = -1;
            }
        }
    }
    assert(false);
}
