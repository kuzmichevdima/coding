#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cassert>
#include <string>
#include <vector>
#include <cstdio>
#include <set>
#include <map>
#include <queue>
#include <memory.h>
#include <cmath>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)n; i++)
#define fore(i, b, e) for (int i = (int)b; i <= (int)e; i++)
#define all(x) (x).begin(), (x).end()
#define se second
#define fi first
#define mp make_pair
#define pb push_back
#define op operator
typedef vector <int> vi;
typedef pair<int, int> pii;
typedef long long i64;

const int maxn = 105;
const int inf = 1e9;

//bool bad[maxn];
string option[maxn];
int dp[maxn];
string s;

inline void upd(int & x, int y)
{
	x = min(x, y);
}

int main()
{
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	int k;
	scanf("%d", &k);
	forn(j, k)
	{
		cin >> option[j];
		//bad[j] = (s.substr(0, option[j].length() != option[j]));
	}
	cin >> s;
	int len = s.length();
	fore(j, 0, len)
		dp[j] = inf;
	dp[0] = 0;
	fore(j, 0, len - 1)
	{
		upd(dp[j + 1], dp[j] + 1);
		vector <string> v;
		forn(choice, k) if (option[choice].length() >= j)
			if (s.substr(0, j) == option[choice].substr(0, j))
			{
				v.pb(option[choice]);
			}
		sort(all(v));
		forn(pos, v.size()) if (v[pos].length() <= len && s.substr(0, v[pos].length()) == v[pos])
		{
			upd(dp[v[pos].length()], dp[j] + pos + 1);
		}
	}
	printf("%d", dp[len] + 1);
	return 0;
}