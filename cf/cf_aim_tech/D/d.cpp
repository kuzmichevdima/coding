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
const int maxk = 100;

double p[maxn];
int cnt[maxn];
int x[maxn];

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
    forn(j, n)
    {
        scanf("%d", &x[j]);
    }
    sort(x, x + n);
    reverse(x, x + n);
    forn(j, n)
        p[j] = 0.01 * x[j];
    int g = 100 - x[0];
    fore(j, 1, n - 1)
        g = __gcd(g, 100 - x[j]);
    int g1 = (100 - x[0]) / g;
    fore(j, 1, n - 1)
        g1 = __gcd(g1, (100 - x[j]) / g);
    //cout << g << endl;
    vi order;
    for (int i = n - 1; i >= 0; i--)
    {
        forn(iter, x[i] * g1)
            order.pb(i);
    }
   for (int x : order)
        printf("%d ", x);
    double answer = 0.0;
    double sum_prob = 0.0;
    forn(k, maxk)
        forn(j, order.size())
        {
            int i = order[j];
            double prob = pow(1 - p[i], cnt[i]) * p[i];
          //  printf("prob now = %.5lf\n", prob);
            forn(another, n) if (i != another)
                prob *= (1 - pow(1 - p[another], cnt[another]));
            sum_prob += prob;
            //printf("k = %d j = %d i = %d prob = %.5lf\n", k, j, i, prob);
            answer += prob * (order.size() * k + j + 1);

            cnt[i]++;
        }
    // printf("answer = %.10lf sum_prob = %.10lf\n", answer, sum_prob);
    printf("%.10lf\n", answer);
/*    double p = 0.5;
    double q = 0.5;
    double sum = 0;
    fore(k, 0, 100)
    {
        if (k != 0)
        {
            sum += (2 * k) * (1 - pow(1 - p, k)) * pow(1 - q, k - 1) * q;
        }
        sum += (2 * k + 1) * pow(1 - p, k) * p * (1 - pow(1 - q, k));
    }
    printf("sum = %.5lf\n", sum);*/
}
