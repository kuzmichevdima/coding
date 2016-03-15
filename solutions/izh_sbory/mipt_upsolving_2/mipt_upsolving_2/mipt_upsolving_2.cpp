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

const i64 MOD = 1e9 + 7;

//set <i64> myset;

int main()
{
#ifdef LOCAL
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	int tests;
	scanf("%d", &tests);
	forn(test, tests)
	{
		int n;
		i64 L, R;
		cin >> n >> L >> R;
		/*myset.clear();
		fore(first, L, R)
			fore(second, first, R)
			{
				myset.insert(first | second);
			}
		printf("right_ans = %d\n", myset.size());*/
		if (n == 1)
		{
			cout << (R - L + 1) % MOD << endl;
			continue;
		}
		if (L == R)
		{
			cout << 1 << endl;
			continue;
		}
		i64 ans = 0;
		for (int k = 61; k >= 0; k--)// if (R & (1LL << k))
		{
			bool Lbit = ((L & (1LL << k)) >> k);
			bool Rbit = ((R & (1LL << k)) >> k);
			if (Lbit && Rbit)
			{
				//ans += (1LL << k);
				L -= (1LL << k);
				R -= (1LL << k);
			}
			else if (Lbit == 0 && Rbit == 1)
			{
				i64 A = (1LL << k) - L;
				ans += A;

				i64 Br = (1LL << k);
				for (int j = k - 1; j >= 0; j--)
					if (R & (1LL << j))
					{
						Br = (1LL << k) + (1LL << (j + 1)) - 1LL;
						break;
					}
				
				i64 Cl = ((1LL << k) + L);
				if (Cl <= Br)
					ans += (1LL << k);
				else
				{
					ans += (Br - (1LL << k) + 1);
					ans += ((1LL << (k + 1)) - Cl);
				}
				break;
			}
		}
		cout << ans % MOD << endl;
		//assert(ans == myset.size());
	}
	return 0;
}