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
const i64 BIG = 2e10;

const int AVG_CONST = 1;

struct Task {
    vector <i64> sums;
    vi counters;
    vi averages;
    int tl, testsCnt;
    Task() {}
    Task(int _tl, int _testsCnt) {
        tl = _tl;
        testsCnt = _testsCnt;
        averages.resize(testsCnt + 1, 0);
        counters.resize(testsCnt + 1, 0);
        sums.resize(testsCnt + 1, 0);
        averages[testsCnt] = (tl / AVG_CONST) * testsCnt;
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
        average = task[taskNum].averages.back();
        if (DEBUG) cerr << "new solution with average = " << average << endl;
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

void upd_task(int taskNum, int complete, int x) {
    task[taskNum].sums[complete] += x;
    task[taskNum].counters[complete]++;
    task[taskNum].averages[complete] = task[taskNum].sums[complete] / task[taskNum].counters[complete];
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


        list[sol].testsComplete++;
        int complete = list[sol].testsComplete;
        list[sol].sum += timer - list[sol].testStart[test];

        int taskNum = list[sol].taskNum;

        upd_task(taskNum, complete, list[sol].sum);

        //if (task[taskNum].counters.back() == 0 || task[taskNum].averages.back() <= list[sol].sum)
        if (task[taskNum].counters.back() == 0)
            list[sol].average = (list[sol].sum / list[sol].testsComplete) * (task[taskNum].testsCnt - list[sol].curTest);
        //else list[sol].average = task[taskNum].average * (task[taskNum].testsCnt - list[sol].curTest) / task[taskNum].testsCnt;
        else {
            int total = (i64)list[sol].sum * task[taskNum].averages.back() / task[taskNum].averages[complete];   
            list[sol].average = total - list[sol].sum;
        }
        list[sol].average = max(1, list[sol].average);
        if (DEBUG)
            fprintf(stderr, "complete = %d average = %d averages.back() = %d averages[%d] = %d\n", complete, list[sol].average, task[taskNum].averages.back(), complete,
                    task[taskNum].averages[complete]);


        if (list[sol].curTest != task[list[sol].taskNum].testsCnt) {

            order.insert(mp(list[sol].average, sol));
            pull.insert(mp(list[sol].average, sol));
        } else if (!list[sol].counted) {
            upd_task(taskNum, task[taskNum].testsCnt, list[sol].sum);
            list[sol].counted = true;
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

bool add_query(int sol) {
    list[sol].testStart[list[sol].curTest] = timer;
    if (DEBUG) cerr << "request " << sol << " " << list[sol].curTest << endl;
    printf("%d %d\n", sol, list[sol].curTest);
    list[sol].curTest++;
    t--;
    if (list[sol].curTest == task[list[sol].taskNum].testsCnt) {
        pull.erase(mp(list[sol].average, sol));
        return true;
    } else return false;
}


vector <pair <i64, int> > partials;

void build() {
    if (DEBUG) cerr << "build" << endl;
    partials.clear();
    for (pii p : pull) {
        if (DEBUG) cerr << p.first << " " << p.second << endl;
        partials.pb(mp((partials.empty() ? 0 : partials.back().first) + BIG / p.first, p.second));
    }
}

void pull_part() {
    if (t == 0 || pull.empty())
        return;
    build();
    while(t > 0 && !pull.empty()) {
        i64 r = (i64)rand() * rand() % partials.back().first;
        int num = lower_bound(partials.begin(), partials.end(), mp(r, 0)) - partials.begin();
        if (DEBUG) cerr << "num = " << num << " size = " << partials.size() << endl;
        assert(num >= 0 && num < (int)partials.size());
        int sol = partials[num].second;
        bool need_erase = add_query(sol);
        if (need_erase) {
            build();
        }
    }
}

void order_part() {
    while(t > 0 && !order.empty()) {
        int sol = order.begin()->second;
        if (DEBUG) cerr << "sol = " << sol << endl;
        order.erase(order.begin());
        add_query(sol);
    }

}

void queries() {
    //order_part();
    pull_part();
    printf("-1 -1\n");
    fflush(stdout);
}


int main() {
    if (DEBUG)
        freopen("stderr.txt", "w", stderr);
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
