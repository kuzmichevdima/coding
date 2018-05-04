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

#define UNDEF -1

const int maxn = 2e5+5;

vi list[maxn];
vector <pii> occur[maxn];
int value[maxn];
bool cycleFound;
vector <pii> edges[maxn];
vector <pii> st;
bool vertex_mark[maxn];
bool mark[maxn][2];
int st_place[maxn];
bool edges_processed[maxn];

inline void apply(int var)
{
//    printf("apply %d\n", var);
    if (var > 0)
        value[var] = 1;
    else value[-var] = 0;
}

inline int determ(int var)
{
    if (!mark[var][0] || !mark[var][1])
    {
        if (!mark[var][0])
            return 1;
        else return 0;
    }
    else return UNDEF;
}

void dfs_determ(int v)
{
    vertex_mark[v] = true;
    for (pii e : edges[v]) if (value[abs(e.se)] == UNDEF)
    {
        apply(e.se);
    }
    edges_processed[v] = true;
    for (pii e : edges[v])
    {
        if (!edges_processed[e.fi])
            dfs_determ(e.fi);
    }

}


void dfs(int v, int prevEdge)
{

    vertex_mark[v] = true;
//    printf("dfs v = %d prevEdge = %d\n", v, prevEdge);
    if (cycleFound)
    {
        st_place[v] = -1;
        st.pop_back();
        return;
    }
//    st_place[v] = st.size();
  //  st.pb(v);
    for (pii e : edges[v])
    {
        int u = e.fi;    
        if (!vertex_mark[u])
        {
            st_place[u] = st.size();
            st.pb(mp(u, e.se));
            dfs(u, abs(e.se));   
        }
        else if (abs(e.se) != prevEdge && st_place[u] != -1 && !cycleFound)
        {
         //   printf("cycle  found\n");
            cycleFound = true;       
            for (int j = st_place[u] + 1; j < (int)st.size(); j++)
            {
                apply(st[j].se);
            }
            apply(e.se);
            for (int j = st_place[u]; j < (int)st.size(); j++) if (!edges_processed[st[j].fi])
            {
            //    printf("vertex %d in cycle\n", st[j].fi);
                dfs_determ(st[j].fi);
            }
            return;     
        }
    }
    st_place[v] = -1;
    st.pop_back();
}

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    int n, m;
    scanf("%d%d", &n, &m);
    forn(i, n)
    {
        int k;
        scanf("%d", &k);
        list[i].resize(k);
        forn(j, k)
        {
            int var;
            scanf("%d", &var);
            list[i][j] = var;
            occur[abs(var)].pb(mp(i, var));
            mark[abs(var)][var > 0] = true;
        }
    }
    fore(j, 1, m)
        value[j] = UNDEF;
    queue <int> Q;
    fore(j, 1, m)
        if (determ(j) != UNDEF)
        {
            Q.push(j);
            value[j] = determ(j);
     //       printf("set %d value = %d\n", j, value[j]);
        }

    while(!Q.empty())
    {
        int var = Q.front();
    //    printf("process var = %d\n", var);
        Q.pop();
        for(pii diz0 : occur[var])
        {
            int diz = diz0.fi;
//            printf("for var = %d diz = %d\n", var, diz);
            for (int an : list[diz])
            {
  //              printf("an = %d\n", an);
                mark[abs(an)][an > 0] = false;
                if (value[abs(an)] == UNDEF && determ(abs(an)) != UNDEF)
                {
                    value[abs(an)] = determ(abs(an));
                    Q.push(abs(an));
                }
            }
        }
    }

    vi undef_list;
    fore(j, 1, m) if (value[j] == UNDEF)
        undef_list.pb(j);
    vi destr(n, false);
    forn(diz, n)
    {
        for (int var : list[diz])
            if (value[abs(var)] != UNDEF)
            {
//                printf("var %d\n", var);
                destr[diz] = true;
            }
//        printf("destr[%d] = %d\n", diz, destr[diz]);
    }
 //   for (int x : undef_list)
   //     printf("%d ", x);
    for (int var : undef_list)
    {
        assert(occur[var].size() == 2);
        pii occ0 = occur[var][0];
        pii occ1 = occur[var][1];
        edges[occ0.fi].pb(occ1);
     //   printf("add_edge %d (%d %d)\n", occ0.fi, occ1.fi, occ1.se);
        edges[occ1.fi].pb(occ0);
       // printf("add edge %d (%d %d)\n", occ1.fi, occ0.fi, occ0.se);
    }
//    exit(0);

    forn(diz, n) if (!vertex_mark[diz] && !destr[diz])
    {
        cycleFound = false;
        st.clear();
        st_place[diz] = 0;
        st.pb(mp(diz, 0));
        dfs(diz, -1); 
        if (!cycleFound)
        {
            printf("NO");
            exit(0);
        }
    }
    printf("YES\n");
    fore(j, 1, m)
    {
        assert(value[j] != UNDEF);
        printf("%d", value[j]);
    }
}
