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
#include "pancakes.h"

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
    int n = GetStackSize();
    int nodes = NumberOfNodes();
    int cnt = 0;
    for (int i = MyNodeId(); i < n; i += nodes)
        if (i != 0 && GetStackItem(i) < GetStackItem(i - 1))
            cnt++;
    if (MyNodeId() == 0) {
        cnt++;
        for (int node = 1; node < nodes; node++) {
            Receive(node);
            cnt += GetInt(node);
        }
        printf("%d", cnt);
    } else {
        PutInt(0, cnt);
        Send(0);
    }
}

