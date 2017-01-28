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

const int maxn = 1e6+5;

int marked[maxn];
int len[maxn];
vi tree[maxn * 4];
int answer;
int sum[maxn * 4];

void add_seg(int i, int L, int R, int A, int B, int num) {
    //printf("add_seg L = %d R = %d A = %d B = %d num = %d\n", L, R, A, B, num);
    if (L == A && R == B) {
        if (sum[i] == R - L)
            marked[num] += R - L;
        else tree[i].pb(num);
        return;
    }
    if (L >= B || A >= R)
        return;
    int M = (L + R) / 2;
    add_seg(i * 2, L, M, A, min(M, B), num);
    add_seg(i * 2 + 1, M, R, max(A, M), B, num);
}

void upd(int i, int L, int R, int pos) {
    sum[i]++;
    if (sum[i] == R - L) {
        for (int num : tree[i]) {
            marked[num] += R - L;
            if (marked[num] == len[num])
                answer++;
        }
    }
    if (L + 1 == R)
        return;
    int M = (L + R) / 2;
    if (pos < M)
        upd(i * 2, L, M, pos);
    else upd(i * 2 + 1, M, R, pos);
}

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#endif
    int n, Q;
    scanf("%d%d", &n, &Q);
    //if (n > 1e4 || Q > 1e4)
    //    exit(0);
    int cnt = 0;
    forn(query, Q) {
        int typ;
        scanf("%d", &typ);
        if (typ == 0) {
            int L, R;
            scanf("%d%d", &L, &R);
            len[cnt] = R - L + 1;
            add_seg(1, 1, n + 1, L, R + 1, cnt++);
            fflush(stdout);
        } else {
            int pos;
            scanf("%d", &pos);
            answer = 0;
            upd(1, 1, n + 1, pos);
            printf("%d\n", answer);
            fflush(stdout);
        }  
    }
}
