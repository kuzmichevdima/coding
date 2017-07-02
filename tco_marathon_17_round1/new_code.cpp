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

#define PLACED 1

class GraphDrawing {
    public:
        static const int sz = 701;
        static const int C = 5;

        vector <pii> coord;
        vector <vector<bool> > used;
        vi status;
        vector <vi> edges, need, placed_nei;
        double min_ratio, max_ratio;

        GraphDrawing() {
            min_ratio = 1.;
            max_ratio = 1.;
        }

        double sqr(double x) const {
            return x * x;
        }

        double get_ratio(int chosen, pii pos, int num) const {
            return sqrt(sqr(pos.fi - coord[num].fi) + sqr(pos.se - coord[num].se)) / need[chosen][num];
        }

        double get_ratio_placed(int x, int y) const {
            return sqrt(sqr(coord[x].fi - coord[y].fi) + sqr(coord[x].se - coord[y].se)) / need[x][y];
        }

        void put(int num, pii pos) {
            //fprintf(stderr, "put number %d\n", num);
            assert(!used[pos.fi][pos.se]);
            used[pos.fi][pos.se] = true;
            coord[num] = pos;
            status[num] = PLACED;
            for (int u : edges[num]) {
                if (status[u] == PLACED) {
                    double nnew = get_ratio_placed(u, num);
                    //fprintf(stderr, "added nei %d to %d nnew = %.5lf\n", num, u, nnew);
                    min_ratio = min(min_ratio, nnew);
                    max_ratio = max(max_ratio, nnew);
                } else placed_nei[u].pb(num);
            }
        }

        double eval_place(int num, pii pos) {
            double minn = min_ratio;
            double maxx = max_ratio;
            for (int nei : placed_nei[num]) {
                double nnew = get_ratio(num, pos, nei);
                minn = min(minn, nnew);
                maxx = max(maxx, nnew);
            }
            return minn / maxx;
        }

        pair<double, int> get_best_y(int chosen, int x) {
            int lowery = 0;
            int uppery = sz - 1;
            while(uppery - lowery >= 3) {
                int m1y = lowery + (uppery - lowery) / 3;
                int m2y = uppery - (uppery - lowery) / 3;
                if (eval_place(chosen, mp(x, m1y)) < eval_place(chosen, mp(x, m2y)))
                    lowery = m1y;
                else uppery = m2y;
            }
            pair<double, int> result;
            double best = -1;
            fore(y, lowery, uppery) {
                double nnew = eval_place(chosen, mp(x, y));
                if (nnew > best) {
                    best = nnew;
                    result = mp(nnew, y);
                }
            }
            return result;
        }

        pii get_best_pos(int chosen) {
            int lowerx = 0;
            int upperx = sz - 1;
            while(upperx - lowerx >= 3) {
                int m1x = lowerx + (upperx - lowerx) / 3;
                int m2x = upperx - (upperx - lowerx) / 3;
                if (get_best_y(chosen, m1x).fi < get_best_y(chosen, m2x).fi) {
                    lowerx = m1x;
                } else {
                    upperx = m2x;
                }
            }
            pii result;
            double best = -1;
            fore(x, lowerx, upperx) {
                auto nnew = get_best_y(chosen, x);
                if (nnew.fi > best) {
                    best = nnew.fi;
                    result = mp(x, nnew.se);
                }
            }
            //fprintf(stderr, "best %.5lf\n", best);
            return result;
        }

        vi plot(int n, vi edges1) {
            edges.resize(n);
            need.resize(n);
            placed_nei.resize(n);
            forn(j, n)
                need[j].resize(n);
            forn(j, edges1.size() / 3) {
                int u = edges1[j * 3];
                int v = edges1[j * 3 + 1];
                int w = edges1[j * 3 + 2];
                edges[u].pb(v);
                edges[v].pb(u);
                need[u][v] = need[v][u] = w;
            }
            used.resize(sz);
            status.resize(n, 0);
            forn(j, sz)
                used[j].resize(sz, false);
            coord.resize(n);

            forn(iter, n) {
                //fprintf(stderr, "\n=================\niter %d\n", iter);
                //fprintf(stderr, "min_ratio = %.5lf; max_ratio = %.5lf\n", min_ratio, max_ratio);
                int chosen = -1;
                forn(j, n) if (status[j] == 0) {
                    if (chosen == -1 || (placed_nei[j].size() > placed_nei[chosen].size()) ||
                            (placed_nei[j].size() == placed_nei[chosen].size() && edges[j].size() > edges[chosen].size()))
                    //if (chosen == -1 || deg[j] * edges[j].size() > deg[chosen] * edges[chosen].size())
                        chosen = j;
                }
                //fprintf(stderr, "chosen = %d\n", chosen);
                if (placed_nei[chosen].empty()) {
                    put(chosen, mp(sz / 2, sz / 2));
                    continue;
                }

                pii best_pos = get_best_pos(chosen);
                int delta = 0;
                while(true) {
                    bool found = false;
                    fore(x, max(0, best_pos.fi - delta), min(sz - 1, best_pos.fi + delta)) {
                        fore(y, max(0, best_pos.se - delta), min(sz - 1, best_pos.se + delta))
                            if (!used[x][y]) {
                                put(chosen, mp(x, y));
                                found = true;
                                break;
                            }
                        if (found)
                            break;
                    }
                    if (found)
                        break;
                    delta++;
                }
                //fprintf(stderr, "chosen = %d A = %d B = %d\n", chosen, A, B);
            }
            forn(j, n)
                assert(status[j] == PLACED);
            vi answer;
            forn(j, n) {
                answer.pb(coord[j].fi);
                answer.pb(coord[j].se);
            }
            return answer;
        }
};
