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

inline bool check(string & t)
{
    if (t == "")
        return false;
    for (char c : t)
        if (c < '0' || c > '9')
            return false;
    if (t[0] == '0' && t.length() > 1)
        return false;
    return true;
}

void print(vector <string> & a)
{
    if (a.empty())
        printf("-");
    else
    {
        cout << "\"";
        forn(j, a.size())
        {
            cout << a[j];
            if (j + 1 != (int)a.size())
                cout << ",";
        }
        cout << "\"";
    }

}

int main() {
#ifdef LOCAL
    freopen("inp", "r", stdin);
    //freopen("outp", "w", stdout);
#else
    // freopen(TASKNAME ".in", "r", stdin);
    // freopen(TASKNAME ".out", "w", stdout);
#endif
    string s;
    char c;
    while((c = getchar()) != '\n' && c != -1)
    {
        s += c;
    }
    int start = -1;
    vector <string> a, b;
    forn(j, s.length())
    {
        if (s[j] == ',' || s[j] == ';')
        {
            if (start == -1)
            {
                b.pb("");
            }
            else
            {
                string t = s.substr(start, j - start);
                if (check(t))
                    a.pb(t);
                else b.pb(t);
            }
            start = -1;
        }
        else if (start == -1)
            start = j;
    }
    if (start != -1)
    {
        string t = s.substr(start, s.length() - start);
        if (check(t))
            a.pb(t);
        else b.pb(t);
    }
    else b.pb("");
    print(a);
    printf("\n");
    print(b);
}
