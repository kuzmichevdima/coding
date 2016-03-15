#include <iostream>
#include <vector>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <memory.h>
#include <map>
#include <set>
#include <cmath>
#include <algorithm>
#include <queue>
#include <cassert>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)n; i++)
#define fore(i, b, e) for (int i = (int)b; i <= (int)e; i++)
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define i64 long long
#define li long long
#define uli unsigned long long
#define lint long long
#define vi vector <int>
#define pii pair <int, int>
#define INF (int)1e9
#define LINF (li)1e18

#define TASK "records-and-cycles"

void solve(int test_number);

int main() {
#ifdef LOCAL
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#else

#endif
	cout.precision(9);
	cout.setf(ios::fixed);
	int n = 1;
	for (int i = 0; i < n; i++)
		solve(i + 1);
}

#define MOD 1000000009LL

int k, m, n;
int a[40100][70];
int b[40100][70];

vector<li> resA[40100];
li rr[40100][7];
vector<li> resB[40100];
li A[40100];
int res[100100];
li p[40100];
bool badA[40100];
bool badB[40100];

inline li binpow(li a, li n) {
	if (n == 0)
		return 1;
	if (n % 2 == 1)
		return (binpow(a, n - 1) * a) % MOD;
	else {
		li buf = binpow(a, n / 2);
		return buf * buf % MOD;
	}
}

inline li rev(li a) {
	return binpow(a, MOD - 2LL);
}

inline li divmod(li a, li b) {
	return (a * b) % MOD;
}

inline bool sqr(vector<li> &a, vector<li> &b) {
	vector<li> r(a.size());
	for (int i = 0; i < a.size(); i++)
		if (b[i] != (a[i] * a[i]) % MOD)
			return false;
	return true;
}

const li base = 29;

li hsh(vector<li> &a) {
	li pow = 1;
	li res = 0;
	for (int i = 0; i < a.size(); i++) {
		res += pow * a[i];
		pow *= base;
	}
	return res;
}

void solve(int test_number)
{
	int cntBad = 0;
	srand(47);
	ios_base::sync_with_stdio(false);
	//cin >> k >> m >> n;
	int maxk = 40000 / 100;
	int maxm = 150 / 10;
	int maxn = 20 / 4;
	int mymod = 10;
	k = maxk;
	m = maxm;
	n = maxn;
	for (int i = 0; i < 7; i++)
		p[i] = rand();
	int cnt = 0;
	for (int i = 0; i < k; i++) {
		bool flag = false;
		for (int j = 0; j <= n; j++) {
			//cin >> a[i][j];
			a[i][j] = rand() % mymod;
			if (a[i][j] < 0)
				a[i][j] += MOD;
			if (a[i][j] != 0)
				flag = true;
		}
		if (!flag) {
			badA[i] = true;
			cntBad++;
			continue;
		}

		for (int val = 0; val < 7; val++) {
			li r = 0;
			li pow = 1;
			for (int j = 0; j <= n; j++) {
				r = (r + pow * a[i][j]) % MOD;
				pow = (pow * p[val]) % MOD;
			}
			resA[i].push_back(r);
		}
		A[cnt] = hsh(resA[i]);
		cnt++;
	}
	sort(A, A + cnt);


	for (int i = 0; i < m; i++) {
		bool flag = false;
		for (int j = 0; j < 2 * n + 1; j++) {
			//cin >> b[i][j];
			b[i][j] = rand() % mymod;
			if (b[i][j] < 0)
				b[i][j] += MOD;
			if (b[i][j] != 0)
				flag = true;
		}
		if (!flag) {
			badB[i] = true;
			//continue;
		}

		for (int val = 0; val < 7; val++) {
			li r = 0;
			li pow = 1;
			for (int j = 0; j < 2 * n + 1; j++) {
				r = (r + pow * b[i][j]) % MOD;
				pow = (pow * p[val]) % MOD;
			}
			resB[i].push_back(r);
		}
	}

	for (int i = 0; i < cnt; i++)
		for (int it = 0; it < 7; it++) {
			rr[i][it] = rev(resA[i][it]);
		}
	for (int i = 0; i < k; i++) {
		for (int j = 0; j < m; j++) {
			if (badA[i] || badB[j])
				continue;
			vector<li> cur(7);
			for (int it = 0; it < 7; it++) {
				cur[it] = divmod(resB[j][it], rr[i][it]);
			}
			li curcur = hsh(cur);
			i64 * it = lower_bound(A, A + cnt, curcur);
			if (it != A + cnt && *it == curcur)
				res[j]++;
		}
	}

	for (int i = 0; i < k; i++) {
		for (int j = 0; j < m; j++) {
			if (sqr(resA[i], resB[j]))
				res[j]++;
		}
	}

	for (int i = 0; i < m; i++)
		if (!badB[i]) 
			cout << res[i] / 2 << '\n';
		else {
			cout << cntBad * (k - cntBad) + cntBad * (cntBad - 1) / 2 + cntBad << '\n';
		}
}