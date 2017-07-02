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

#include <message.h>

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

const int mod = 1e9+7;

int bin_pow(int x, int p) {
    if (p == 0)
        return 1;
    int y = bin_pow(x, p / 2);
    y = (i64)y * y % mod;
    if (p & 1)
        y = (i64)y * x % mod;
    return y;
}

int GetNumberLength() {
    return 1e9;
}

const int tt = 1e8 + 1;

int GetDigit(int pos) {
    return ((int)1e9 - pos) / tt;
}

int main() {
    int work_nodes = NumberOfNodes() - 1;
    int seq_len = GetNumberLength();
    int id = MyNodeId();
    if (id == work_nodes) {
        int bound = 0;
        int ans = 0;
        int len = 0;
        for (int digit = 9; digit > 0; digit--) {
            for (int worker = 0; worker < work_nodes; worker++) {
                PutInt(worker, bound);
                Send(worker);
            }
            int new_bound = bound;
            for (int worker = 0; worker < work_nodes; ++worker) {
                Receive(worker);
                int cnt = GetInt(worker);
                int last = GetInt(worker);
                int addit = GetInt(worker);
                //fprintf(stderr, "digit = %d worker = %d cnt = %d last = %d\n", digit, worker, cnt, last);
                if (last != -1)
                    new_bound = max(new_bound, last + 1);
                len += cnt;
                ans = ((i64)ans * bin_pow(10, cnt) + addit) % mod;
            }
            bound = new_bound;
        }
        ans = (i64)ans * bin_pow(10, seq_len - len) % mod;
        printf("%d", ans);
    } else {
        for (int digit = 9; digit > 0; digit--) {
            Receive(work_nodes);
            int bound = GetInt(work_nodes);
            int cnt = 0;
            int last = -1;
            int addit = 0;
            for (int pos = bound + id; pos < seq_len; pos += work_nodes)
                if (GetDigit(pos) == digit) {
                    cnt++;
                    last = pos;
                    addit = ((i64)addit * 10 + digit) % mod;
                }
            PutInt(work_nodes, cnt);
            PutInt(work_nodes, last);
            PutInt(work_nodes, addit);
            Send(work_nodes);
        }
    }

}

