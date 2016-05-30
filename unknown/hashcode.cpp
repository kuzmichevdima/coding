#include <bits/stdc++.h>

#define NAME "test"

#define EPS (1e-9)
#define INF ((int)(1e+9))
#define LINF ((long long)(1e+18))

#define pb push_back
#define mp make_pair
#define fi first
#define se second

using namespace std;

typedef long long li;

void solve(int test_number);

//#define TEST "mother_of_all_warehouses"
//#define TEST "busy_day"
//#define TEST "redundancy"

int main() {
/*#ifdef LOCAL
    freopen(TEST ".in", "r", stdin);
    freopen(TEST ".out", "w", stdout);
#else
#endif*/
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout.setf(ios::fixed);
    cout.precision(9);
    cerr.setf(ios::fixed);
    cerr.precision(3);
    int n = 1;
    for (int i = 0; i < n; i++) {
        solve(i + 1);
    }
    return 0;
}

void load(int drone, int house, int type, int count){
    cout << drone << " L " << house << " " << type << " " << count << endl;
}
 
void unload(int drone, int house, int type, int count){
    cout << drone << " U " << house << " " << type << " " << count << endl;
}
 
void deliver(int drone, int order, int type, int count){
    cout << drone << " D " << order << " " << type << " " << count << endl;
}
 
void wait(int drone, int amount){
    cout << drone << " W " << amount << endl;
}

const int PROD = 2010;
const int STOCKS = 20;
const int ORDERS = 4000;
const int DRONES = 50;

struct Point {
    int x, y;

    Point(int x = 0, int y = 0) : x(x), y(y) { }

    void read() {
        cin >> x >> y;
    }
};

inline double sqr(double x) {
    return x * x;
}

inline int dist(Point a, Point b) {
    double d = sqrt(sqr(a.x - b.x) + sqr(a.y - b.y)); 
    if (fabs(d - floor(d)) < EPS) 
        return int(floor(d) + EPS);
    else
        return int(floor(d) + 1.0 + EPS);
}

struct Drone {
    Point pos;
    int cnt[PROD]; 
    int payload;
    int num;

    Drone(Point pos = { 0, 0 }, int payload = 0) : pos(pos), payload(payload) {
        memset(cnt, 0, sizeof(cnt));
    }
};

int cnt_products;

struct Stock {
    Point pos;
    int cnt[PROD];

    void read() {
        pos.read();
        for (int i = 0; i < cnt_products; i++) {
            cin >> cnt[i];
        }
    }
};

struct Order {
    Point pos;
    vector<int> need;
    bool done;
    int num;

    void read() {
        pos.read();
        int sz;
        cin >> sz;
        need.resize(sz);
        for (int i = 0; i < sz; i++) {
            cin >> need[i];
        }
        sort(need.begin(), need.end());
        done = false;
    }
};

int n, m;
int cnt_drones;
int turns;
int payload;
int weight[PROD];
int cnt_stocks;
Stock stocks[STOCKS];
int cnt_orders;
Order orders[ORDERS];
Drone drones[DRONES];

int get_time(Drone &drone, Order &order, bool print = false) {
    int tm = 0;
    Point start = drone.pos;
    vector<pair<int, int> > taken;
    for (auto pr : order.need) {
        if (drone.payload < weight[pr]) {
            for (int i = 0; i < cnt_products; i++) {
                if (drone.cnt[i] != 0) {
                    if (print) {
                        deliver(drone.num, order.num, i, drone.cnt[i]);
                    }
                    drone.payload += drone.cnt[i] * weight[i];
                    drone.cnt[i] = 0;
                    tm += dist(drone.pos, order.pos);
                    drone.pos = order.pos;
                }
            }
        }
        if (drone.payload >= weight[pr]) {
            drone.payload -= weight[pr];

            int bst = INF;
            int pos = 0;
            for (int i = 0; i < cnt_stocks; i++) {
                if (stocks[i].cnt[pr] > 0) {
                    int cur = dist(drone.pos, stocks[i].pos);
                    if (cur < bst) {
                        bst = cur;
                        pos = i;
                    }
                }
            }
            drone.cnt[pr]++;
            tm += dist(drone.pos, stocks[pos].pos);
            drone.pos = stocks[pos].pos;
            stocks[pos].cnt[pr]--;
            taken.push_back({ pos, pr });
            if (print) {
                load(drone.num, pos, pr, 1);
            }
        }
    }

    for (int i = 0; i < cnt_products; i++) {
        if (drone.cnt[i] != 0) {
            if (print) {
                deliver(drone.num, order.num, i, drone.cnt[i]);
            }
            drone.payload += drone.cnt[i] * weight[i];
            drone.cnt[i] = 0;
            tm += dist(drone.pos, order.pos);
            drone.pos = order.pos;
        }
    }
    if (!print) {
        drone.pos = start;
        for (auto cur : taken) {
            stocks[cur.first].cnt[cur.second]++;
        }
    }
    return tm;
}

void naive_sol() {
    set<pair<int, int> > fr;
    for (int i = 0; i < cnt_drones; i++) {
        fr.insert({ 0, i });
    }
    while (!fr.empty()) {
        auto at = *fr.begin();
        fr.erase(fr.begin());
        int num = at.second;
        int tm = at.first;
        int bst = INF;
        int num_order = -1;
        //cerr << num << ' ' << tm << endl;
        for (int i = 0; i < cnt_orders; i++) {
            if (!orders[i].done) {
                int cur = get_time(drones[num], orders[i]);
                if (bst > cur) {
                    bst = cur;
                    num_order = i;
                }
            }
        }
        if (num_order != -1) {
            tm += bst;
            if (tm < turns) {
                fr.insert({ tm, num });
                get_time(drones[num], orders[num_order], true);
                orders[num_order].done = true;
            }
        }
    }
}

void solve(int) {
    cin >> n >> m >> cnt_drones >> turns >> payload;
    cin >> cnt_products;
    for (int i = 0; i < cnt_products; i++) {
        cin >> weight[i];
    }
    cin >> cnt_stocks;
    for (int i = 0; i < cnt_stocks; i++) {
        stocks[i].read();
    }
    cin >> cnt_orders;
    for (int i = 0; i < cnt_orders; i++) {
        orders[i].read();
        orders[i].num = i;
    }
    sort(orders, orders + cnt_orders, [](const Order &a, const Order &b) {
        return a.need.size() < b.need.size();
    });
//    random_shuffle(orders, orders + cnt_orders);
    for (int i = 0; i < cnt_orders; i++)
    {
        vector <int> need = orders[i].need;
        vector <int> new_need;
        vector <pair <int, int >> list;
        int start = 0;
        for (int j = 1; j < (int)need.size(); j++)
        {
            if (need[j] != need[start])
            {
                list.push_back(make_pair(need[start], j - start));       
                start = j;
            }   
        }
        list.push_back(make_pair(need[start], (int)need.size() - start));
        vector <bool> used(list.size(), false);
        int cur = 0;
        int CC = 0;
        for (int i = 0; i < (int)list.size(); i++)
        {
            for (int j = 0; j < list[cur].second; j++)
                new_need.push_back(list[cur].first);       
            used[cur] = true;
            long long best_sum = -1;
            int best = -1;
            for (int j = 0; j < (int)list.size(); j++)
                if (used[j] == false)
                {
                    long long sum = 0;
                    for (int st = 0; st < cnt_stocks; st++)
                        sum += (long long)(stocks[st].cnt[list[j].first] + CC) * (stocks[st].cnt[list[cur].first] + CC) * (stocks[st].cnt[list[j].first] + CC) * (stocks[st].cnt[list[cur].first] + CC);;
                    if (best == -1 || sum > best_sum)
                    {
                        best = j;
                        best_sum = sum;
                    }
                }
            cur = best;
        }
        assert(new_need.size() == orders[i].need.size());
        orders[i].need = new_need;
    }
//    random_shuffle(orders, orders + cnt_orders);
    vector<Order> new_order;
    int CON = 25;
    for (int i = 0; i < cnt_orders; i++) {
        //cerr << i << endl;
        const Order &o = orders[i];
        for (int j = 0; j < (int) o.need.size(); j += CON) {
            int to = min(j + CON, (int) o.need.size());
            Order no;
            no.num = o.num;
            no.done = false;
            no.pos = o.pos;
            no.need.insert(no.need.end(), o.need.begin() + j, o.need.begin() + to);
            new_order.push_back(no);
        }
    }
    cnt_orders = new_order.size();
    //cerr << "HUI " << cnt_orders << endl;
    for (size_t i = 0; i < new_order.size(); ++i) {
      orders[i] = new_order[i];
    }

    for (int i = 0; i < cnt_drones; i++) {
        drones[i] = Drone(stocks[0].pos, payload);
        drones[i].num = i;
    }

    naive_sol();
}
