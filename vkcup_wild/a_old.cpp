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

const int AVG_CONST = 2;

struct Task {
    i64 sum;
    int cnt, average, tl, testsCnt;
    Task() {}
    Task(int _tl, int _testsCnt) {
        sum = 0;
        tl = _tl;
        testsCnt = _testsCnt;
        average = (tl / AVG_CONST) * testsCnt;
        cnt = 0;
    }
};


Task task[maxp];

struct Solution {
    int curTest, sum, average, taskNum, testsComplete;
    vi testStart;
    bool counted;
    Solution(int _taskNum) {
        taskNum = _taskNum;
        curTest = sum = testsComplete = 0;
        testStart.resize(task[taskNum].testsCnt);
        average = task[taskNum].average;
        counted = false;
    }
};


int p, t, timer;
vector <Solution> list;
set <pii> order;
set <pii> pull;

void readSolutions() {
    while(true) {
        int x;
        if (scanf("%d", &x) != 1)
            exit(0);
        if (x == -1)
            break;
        if (DEBUG) cerr << "timer = " << timer << " t = " << t << endl;
        if (DEBUG) cerr << "new sol for task " << x << " with number of tests = " << task[x].testsCnt << endl;
        list.pb(Solution(x));
        order.insert(mp(list.back().average, (int)list.size() - 1));
        pull.insert(mp(list.back().average, (int)list.size() - 1));
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
        pull.erase(mp(list[sol].average, sol));
        order.erase(mp(list[sol].average, sol));
        if (verdict != "OK")
            list[sol].curTest = task[list[sol].taskNum].testsCnt;
        if (DEBUG) cerr << "new result " << sol << " " << test << " " << verdict << endl;
        if (list[sol].curTest != task[list[sol].taskNum].testsCnt) {

            //task[list[sol].taskNum].sum -= list[sol].average;

            list[sol].testsComplete++;
            list[sol].sum += timer - list[sol].testStart[test];
            list[sol].average = (list[sol].sum / list[sol].testsComplete) * (task[list[sol].taskNum].testsCnt - list[sol].curTest);

            //task[list[sol].taskNum].sum += list[sol].average;
            //task[list[sol].taskNum].average = task[list[sol].taskNum].sum / task[list[sol].taskNum].cnt;

            order.insert(mp(list[sol].average, sol));
            pull.insert(mp(list[sol].average, sol));
        } else if (!list[sol].counted) {
            int taskNum = list[sol].taskNum;
            list[sol].counted = true;
            task[taskNum].sum += list[sol].sum;
            task[taskNum].cnt++;
            task[taskNum].average = task[taskNum].sum / task[taskNum].cnt;
        }
    }
}

bool active(int sol) {
    return list[sol].curTest < task[list[sol].taskNum].testsCnt;
}

void myassert(bool f) {
    if (f) return;
    while(true) {}
}

vi to_erase;

void add_query(int sol) {
    list[sol].testStart[list[sol].curTest] = timer;
    if (DEBUG) cerr << "request " << sol << " " << list[sol].curTest << endl;
    printf("%d %d\n", sol, list[sol].curTest);
    list[sol].curTest++;
    if (list[sol].curTest == task[list[sol].taskNum].testsCnt)
        to_erase.pb(sol);
    t--;
}

void extra() {
    while(t > 0 && !pull.empty()) {
        to_erase.clear();
        for (pii p : pull) {
            if (t == 0)
                break;
            //myassert(active(p.second));
            add_query(p.second);
        }
        for (int sol : to_erase)
            pull.erase(mp(list[sol].average, sol));
    }
}

void queries() {
//    cerr << "queries t = " << t << endl;
    to_erase.clear();
    while(t > 0 && !order.empty()) {
        int sol = order.begin()->second;
        /*if (order.begin()->first != list[sol].average) {
            assert(false);
            order.erase(order.begin());
            continue;
        }*/
        if (DEBUG) cerr << "sol = " << sol << endl;
        order.erase(order.begin());
        //if (active(sol))
        //myassert(active(sol));
        add_query(sol);
    }
    for (int sol : to_erase)
        pull.erase(mp(list[sol].average, sol));
    if (t > 0)
        extra();
    printf("-1 -1\n");
    fflush(stdout);
}


int main() {
    if (DEBUG) freopen("stderr.txt", "w", stderr);
    scanf("%d%d", &t, &p);
    if (DEBUG) cerr << "t = " << t << " p = " << p << endl;
    forn(j, p) {
        int x, y;
        scanf("%d%d", &x, &y);
        task[j] = Task(x, y);
    }
    while(true) {
        readSolutions();
        readResults();
        queries();
        timer += 10;
    }
}
