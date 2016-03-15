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
typedef unsigned long long i64;

const i64 MOD = (1LL << 32);
const int maxk = 17;

i64 sumf[maxk];
i64 sumg[maxk];
i64 cur, a_gen, b_gen;

inline i64 getNext()
{
	cur = (cur * a_gen + b_gen) % MOD;
	return cur / (1 << 16);
}

inline void add(i64 & x, i64 y)
{
	x = (x + y) % MOD;
}

i64 f[1 << maxk];
i64 g[1 << maxk];

int main()
{
	freopen("convolution.in", "r", stdin);
	freopen("convolution.out", "w", stdout);
	int tests, n;
	cin >> n >> tests >> a_gen >> b_gen;
	cur = 0;
	forn(test, tests)
	{
		i64 Sf = 0;
		forn(j, 1 << n)
		{
			f[j] = getNext();
			//cout << f[j] << " ";
			add(Sf, f[j]);
		}
		//cout << endl;
		i64 Sg = 0;
		forn(j, 1 << n)
		{
			g[j] = getNext();
			//cout << g[j] << " ";
			add(Sg, g[j]);
		}
		//cout << endl;
		i64 S = Sf * Sg % MOD;
		memset(sumf, 0, sizeof(sumf));
		memset(sumg, 0, sizeof(sumg));
		forn(i, (1 << n))
		{
			forn(bit, n) if ((i & (1 << bit)) == 0)
			{
				add(sumf[bit], f[i]);
				add(sumg[bit], g[i]);
			}
		}
		i64 answer = 0;
		forn(k, n)
		{
			i64 bad = (sumf[k] * sumg[k]) % MOD;
			i64 to_add = ((S + MOD - bad) % MOD) * (1LL << k) % MOD;
			add(answer, to_add);
		}
		add(answer, S);
		cout << answer << endl;
	}
	return 0;
}