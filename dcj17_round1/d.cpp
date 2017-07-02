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
#include "query_of_death.h"

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

int main() {
    int work_nodes = NumberOfNodes() - 1;
    int id = MyNodeId();
    int len = GetLength();
    if (id == work_nodes) {
        if (len == 1) {
            printf("%d", GetValue(0));
            exit(0);
        }
        int last = -1;
        for (int w = 0; w < work_nodes; w++) {
            Receive(w);
            int bad = GetInt(w);
            fprintf(stderr, "w = %d bad = %d\n", w, bad);
            if (bad != -1) {
                assert(last == -1);
                last = bad;
            }
        }
        assert(last != -1);
        int ans = 0;
        forn(i, len)
            if (i != last)
                ans += GetValue(i);
        ans += GetValue(last);
        printf("%d", ans);
    } else {
        vi list;
        bool found = false;
        for (int i = id; i < len; i += work_nodes) {
            int iter = 100;
            int prev = GetValue(i);
            forn(j, iter) {
                int x = GetValue(i);
                if (x != prev) {
                    PutInt(work_nodes, i);
                    Send(work_nodes);
                    found = true;
                    break;
                }
                prev = x;
            }
            if (found)
                break;
        }
        if (!found) {
            PutInt(work_nodes, -1);
            Send(work_nodes);
        }
        vi values;
    }

}

