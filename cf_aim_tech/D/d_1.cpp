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

const int maxn = 105;
const int it_count = 3e5;

double p[maxn];
double fail_prob[maxn];

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
    forn(i, n) {
        int x;
        scanf("%d", &x);
        p[i] = 1.0 * x / 100;
    }
    double cur = 1;
    forn(i, n) {
        fail_prob[i] = 1 - p[i];
        cur *= (1 - fail_prob[i]);
    }
    double sum = cur * n;
    fore(it, 1, it_count) {
        double optimal = 0.0;
        int best = -1;
        forn(chosen, n) {
            double nnew = cur / (1 - fail_prob[chosen]) * (1 - fail_prob[chosen] * (1 - p[chosen]));
            //printf("chosen = %d nnew = %.5lf\n", chosen, nnew);
            if (nnew > optimal) {
                optimal = nnew;
                best = chosen;
            }
        }
        sum += (it + n) * (optimal - cur);
        cur = optimal;
        fail_prob[best] *= (1 - p[best]);
    }
    printf("%.10lf\n", sum);
    //double answer = it_count * cur - sum;
    //printf("%.10lf", answer);
}

