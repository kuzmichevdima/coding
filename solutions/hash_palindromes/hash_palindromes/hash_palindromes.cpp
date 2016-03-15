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

const int maxlen = 1e5 + 5;

const i64 P0 = 239;
const i64 P1 = 241;
const i64 M0 = 1e9 + 7;
const i64 M1 = 1e9 + 9;

typedef pair <i64, i64> mypair;

char s[maxlen];
int len;
i64 h[4][maxlen];
i64 p[2][maxlen];
i64 M[2];
i64 P[2];
char srev[maxlen];

inline void precalc()
{
	P[0] = P0;
	P[1] = P1;
	M[0] = M0;
	M[1] = M1;
	forn(m, 2)
	{
		p[m][0] = 1;
		fore(j, 1, len)
		{
			p[m][j] = p[m][j - 1] * P[m] % M[m];
		}
	}
	forn(m, 2)
	{
		h[m][0] = s[0];
		fore(j, 1, len - 1)
			h[m][j] = (h[m][j - 1] + p[m][j] * s[j]) % M[m];
	}
	forn(m, 2)
	{
		h[m + 2][0] = srev[0];
		fore(j, 1, len - 1)
			h[m + 2][j] = (h[m + 2][j - 1] + p[m][j] * srev[j]) % M[m];
	}
}

inline mypair get(int s, int f)
{
	//printf("get s = %d f = %d\n", s, f);
	i64 tmp0 = (s == 0 ? 0 : h[0][s - 1]);
	i64 tmp1 = (s == 0 ? 0 : h[1][s - 1]);
	return mp((h[0][f] - tmp0 + M[0]) % M[0] * p[0][len - s] % M[0], (h[1][f] - tmp1 + M[1]) % M[1] * p[1][len - s] % M[1]);
}

inline mypair get_rev(int s, int f)
{
	//printf("get s = %d f = %d\n", s, f);
	int s1 = len - f - 1;
	int f1 = len - s - 1;
	s = s1;
	f = f1;
	i64 tmp0 = (s == 0 ? 0 : h[2][s - 1]);
	i64 tmp1 = (s == 0 ? 0 : h[3][s - 1]);
	return mp((h[2][f] - tmp0 + M[0]) % M[0] * p[0][len - s] % M[0], (h[3][f] - tmp1 + M[1]) % M[1] * p[1][len - s] % M[1]);
}

int main()
{
	freopen("palindr.in", "r", stdin);
	freopen("palindr.out", "w", stdout);
	scanf("%s", &s);
	len = strlen(s);
	forn(j, len)
		srev[j] = s[len - j - 1];
	precalc();
	i64 ans = 0;
	forn(p, len)
	{
		//printf("p = %d part1\n", p);
		int s = 1;
		int f = min(p + 1, len - p);
		while(s < f)
		{
			int m = (s + f) / 2 + 1;
			if (get(p - m + 1, p) == get_rev(p, p + m - 1))
				s = m;
			else f = m - 1;
		}
		ans += s - 1;
		s = 0;
		f = min(p + 1, len - p - 1);
		while(s < f)
		{
			int m = (s + f) / 2 + 1;
			mypair g1 = get(p - m + 1, p);
			mypair g2 = get_rev(p + 1, p + m);
			if (g1 == g2)
				s = m;
			else f = m - 1;
		}
		ans += s;
	}
	cout << ans << endl;
	return 0;
}