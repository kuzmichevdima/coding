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

#define DEBUG false

const int maxp = 10005;

int taskTL[maxp];
int taskTestCnt[maxp];

struct Solution {
    int curTest, sum, average, taskNum, testStart;
    Solution(int _taskNum) {
        taskNum = _taskNum;
        curTest = 0;
        sum = 0;
        testStart = 0;
        average = taskTL[taskNum];
    }
};

int p, t, timer;
vector <Solution> list;
set <pii> order;

void readSolutions() {
    while(true) {
        int x;
        if (scanf("%d", &x) != 1)
            exit(0);
        if (x == -1)
            break;
        if (DEBUG) cerr << "new sol for task " << x << endl;
        list.pb(Solution(x));
        order.insert(mp(list.back().average, (int)list.size() - 1));
    }
}

void readResults() {
    while(true) {
        int sol, test;
        scanf("%d%d", &sol, &test);
        if (sol == -1 && test == -1)
            break;
        string verdict;
        cin >> verdict;
        t++;
        if (DEBUG) cerr << "new result " << sol << " " << test << " " << verdict << endl;
        
        if ((verdict == "OK" && list[sol].curTest == taskTestCnt[list[sol].taskNum] - 1) || verdict != "OK") {
                    
        } else {
            list[sol].curTest++;
            list[sol].sum += timer - list[sol].testStart;
            list[sol].average = list[sol].sum / list[sol].curTest;
            order.insert(mp(list[sol].average, sol));
        }
    }
}

void queries() {
//    cerr << "queries t = " << t << endl;
    while(t > 0 && !order.empty()) {
        int sol = order.begin()->second;
        /*if (order.begin()->first != list[sol].average) {
            assert(false);
            order.erase(order.begin());
            continue;
        }*/
        t--;
        if (DEBUG) cerr << "sol = " << sol << endl;
        order.erase(order.begin());
        list[sol].testStart = timer;
        if (DEBUG) cerr << "request " << sol << " " << list[sol].curTest << endl;
        printf("%d %d\n", sol, list[sol].curTest);
    }
    printf("-1 -1\n");
    fflush(stdout);
}

int main() {
    if (DEBUG) freopen("stderr.txt", "w", stderr);
    scanf("%d%d", &t, &p);
    if (DEBUG) cerr << "t = " << t << " p = " << p << endl;
    forn(j, p) {
        scanf("%d%d", &taskTL[j], &taskTestCnt[j]);
        if (DEBUG) cerr << taskTL[j] << " " << taskTestCnt[j] << endl;
    }
    while(true) {
        readSolutions();
        readResults();
        queries();
        timer += 10;
    }
}

