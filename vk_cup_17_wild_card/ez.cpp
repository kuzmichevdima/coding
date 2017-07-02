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


const int n_days = 6;
const int n_lectures = 7;
const int inf = 1e9;
const int maxn = 65;
int FLAG_USE_MULT = false;
int FLAG_NEED_MEASURE = false;
int candidates_cnt;
int FLAG_GROUP_CMP = false;
int FLAG_TEACHER_CMP = false;

inline void min_eq(int & x, int y) {
    x = min(x, y);
}

inline void max_eq(int & x, int y) {
    x = max(x, y);
}


inline int sqr(int x) {
    return x * x;
}

int G, T, A;


struct It {
    //private:
    //    vi need;
    private:
        int measure;
    public:
    vi min_lecture, max_lecture;
    vector <vi> schedule;
    It() {
        measure = 0;
        //need.resize(maxn, 0);
        min_lecture.resize(n_days + 1, inf);
        max_lecture.resize(n_days + 1, -inf);
        schedule.resize(n_days + 1);
        fore(j, 1, n_days)
            schedule[j].resize(n_lectures + 1, 0);
    }
    int cost_of_day(int day) const {
        if (min_lecture[day] == inf)
            return 0;
        return sqr(max_lecture[day] - min_lecture[day] + 3);
    }
    void add_lecture(int day, int lecture, int teacher) {
        //printf("add lecture day = %d lecture = %d teacher = %d\n", day, lecture, teacher);
        //printf("before min = %d max = %d\n", min_lecture[day], max_lecture[day]);
        schedule[day][lecture] = teacher;
        min_eq(min_lecture[day], lecture);
        max_eq(max_lecture[day], lecture);
        //printf("after min = %d max = %d\n", min_lecture[day], max_lecture[day]);
    }
    bool busy(int day, int lecture) {
        return schedule[day][lecture] != 0;
    }
    int get_measure() {
        return measure;
    }
    int get_total_cost() {
        int result = 0;
        fore(day, 1, n_days)
            result += cost_of_day(day);
        return result;
    }
    void set_need(int x, int val) {
        //need[x] = val;
        measure += val;
    }
};

It groups[maxn];
It teachers[maxn];
int free_audit[n_days + 1][n_lectures + 1];

struct Placement {
    int cost, day, lecture;
    Placement(int cost, int day, int lecture) : cost(cost), day(day), lecture(lecture) {}
};



struct GTPair {
    int group, teacher, need;
    GTPair(int group, int teacher, int need) : group(group), teacher(teacher), need(need) {}
    void print() {
        printf("group = %d teacher = %d need = %d\n", group, teacher, need);
    }
    bool get_measure() {
        if (FLAG_USE_MULT)
            return groups[group].get_measure() * teachers[teacher].get_measure();
        else
            return groups[group].get_measure() + teachers[teacher].get_measure();
    }

    inline int add_cost(int day, int lecture) const {
        if (free_audit[day][lecture] == 0)
            return inf;
        if (groups[group].busy(day, lecture) || teachers[teacher].busy(day, lecture))
            return inf;
        int group_cost = sqr(max(lecture, groups[group].max_lecture[day])
                - min(lecture, groups[group].min_lecture[day]) + 3) - groups[group].cost_of_day(day);
        int teacher_cost = sqr(max(lecture, teachers[teacher].max_lecture[day])
                - min(lecture, teachers[teacher].min_lecture[day]) + 3) - teachers[teacher].cost_of_day(day);
        return (group_cost + teacher_cost);
        //return max(group_cost, teacher_cost);
    }

    
    inline Placement find_best_place() const {
        int min_cost = inf;
        int best_day;
        int best_lecture;
        fore(day, 1, n_days)
            fore(lecture, 1, n_lectures) {
                int cost = add_cost(day, lecture);
                if (cost == inf)
                    continue;
                if (cost < min_cost || (cost == min_cost && free_audit[day][lecture] > free_audit[best_day][best_lecture])) {
                //if (cost < min_cost) {
                    min_cost = cost;
                    best_day = day;
                    best_lecture = lecture;
                }
            }
        //printf("min_cost = %d day = %d lecture = %d\n", min_cost, best_day, best_lecture);
        //printf("placing group = %d teacher = %d to day %d lecture %d\n", p.group, p.teacher, best_day, best_lecture);
        return Placement(min_cost, best_day, best_lecture);
    }

    void place(const Placement & p) {
        groups[group].add_lecture(p.day, p.lecture, teacher);
        teachers[teacher].add_lecture(p.day, p.lecture, teacher);
        free_audit[p.day][p.lecture]--;
    }

};


bool operator < (GTPair first, GTPair second) {
    if (FLAG_NEED_MEASURE) {
        if (first.need * first.get_measure() != second.need * second.get_measure())
            return first.need * first.get_measure() > second.need * second.get_measure();
    } else {
        if (first.need != second.need)
            return first.need > second.need;
    }
    if (first.group != second.group)
        return (first.group < second.group) == FLAG_GROUP_CMP;
    return (first.teacher > second.teacher) == FLAG_TEACHER_CMP;
}

int inp[maxn][maxn];

struct Answer {
    int answer;
    vector <vector<vi> > schedule;
    Answer(bool initial) {
        if (initial) {
            answer = inf;
            return;
        }
        answer = 0;
        fore(g, 1, G)
            answer += groups[g].get_total_cost();
        //cerr << "groups part of answer: " << answer << endl;
        fore(t, 1, T)
            answer += teachers[t].get_total_cost();

        schedule.resize(G + 1);
        fore(g, 1, G) {
            schedule[g].resize(n_lectures + 1);
            fore(lecture, 1, n_lectures) {
                schedule[g][lecture].resize(n_days + 1);
                fore(day, 1, n_days) {
                    schedule[g][lecture][day] = groups[g].schedule[day][lecture];
                }
            }
        }
    }
    void write() {
        printf("%d\n\n", answer);
        fore(g, 1, G) {
            fore(lecture, 1, n_lectures) {
                fore(day, 1, n_days) {
                    printf("%d ", schedule[g][lecture][day]);
                }
                printf("\n");
            }
            printf("\n");
        }
    }
};

Answer final_answer(true);

void solve() {
   set <GTPair> order;
   fore(g, 1, G)
       groups[g] = It();
   fore(t, 1, T)
       teachers[t] = It();
   fore(g, 1, G)
       fore(t, 1, T) {
           if (inp[g][t] > 0) {
                order.insert(GTPair(g, t, inp[g][t]));
                groups[g].set_need(t, inp[g][t]);
                teachers[t].set_need(g, inp[g][t]);
           }
       }
    fore(day, 1, n_days)
        fore(lecture, 1, n_lectures)
            free_audit[day][lecture] = A;
    while(!order.empty()) {
        vector <GTPair> candidates;
        while(!order.empty() && (int)candidates.size() < candidates_cnt) {
            candidates.pb(*order.begin());
            order.erase(order.begin());
        }
        vector <Placement> placements;
        for(const GTPair & candidate : candidates) {
            placements.pb(candidate.find_best_place());
        }
        int best_ind = 0;
        forn(ind, candidates.size())
            if (placements[ind].cost < placements[best_ind].cost)
                best_ind = ind;
        candidates[best_ind].place(placements[best_ind]);
        candidates[best_ind].need--;
        for (const GTPair & candidate : candidates)
            if (candidate.need > 0)
                order.insert(candidate);
    }
    Answer nnew(false);
    //cerr << "new " << nnew.answer << endl;
    if (nnew.answer < final_answer.answer)
        final_answer = nnew;

}

int main() {
    scanf("%d%d%d", &G, &T, &A);
    fore(g, 1, G)
        fore(t, 1, T) {
            scanf("%d", &inp[g][t]);
        }
    for (candidates_cnt = 1; candidates_cnt <= 10; candidates_cnt++) {
        for (FLAG_USE_MULT = 0; FLAG_USE_MULT <= 1; FLAG_USE_MULT++)
            for (FLAG_NEED_MEASURE = 0; FLAG_NEED_MEASURE <= 1; FLAG_NEED_MEASURE++)
                for (FLAG_GROUP_CMP = 0; FLAG_GROUP_CMP <= 1; FLAG_GROUP_CMP++)
                    for (FLAG_TEACHER_CMP = 0; FLAG_TEACHER_CMP <= 1; FLAG_TEACHER_CMP++) {
                        solve();
                    }
    }
    final_answer.write();
    //cerr << "ans2 = " << ans2.answer << endl;
    //cerr << "answer = " << answer << endl;
}
