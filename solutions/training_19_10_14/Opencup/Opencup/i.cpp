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

const int INF = 32000;

int n, m;
vector<int> g[5010];
int A, B, C, D;
bool used[5010];
vector<int> order;
int pos[5010];
unsigned short int dp[5010][5010][2];
unsigned short int pred[5010][5010][2];

inline unsigned short int code(pair<pair<int, int>, int> a, pair<pair<int, int>, int> old) {
	unsigned short int res = 0;
	res = old.second;
	if (a.first.first != old.first.first) {
		res += 2;
		res ^= (a.first.first - old.first.first) * 4;
	} else {
		res ^= (a.first.second - old.first.second) * 4;
	}
	return res;
}

inline pair<pair<int, int>, int> decode(unsigned short int a) {
	int v1, v2, k = 0;
	if (a % 2)
		k = 1;
	int p = (a & 2);
	if (p != 0) {
		v1 = a / 4;
		v2 = 0;
	} else {
		v1 = 0;
		v2 = a / 4;
	}
	return mp(mp(v1, v2), k);
}

inline void update(int v1, int v2, int k, int to1, int to2, int t) {
	if (dp[to1][to2][t] > dp[v1][v2][k] + 1) {
		dp[to1][to2][t] = dp[v1][v2][k] + 1;
		pred[to1][to2][t] = code(mp(mp(to1, to2), t), mp(mp(v1, v2), k));
	}
}

void dfs(int v) {
	used[v] = true;
	for (int i = 0; i < (int)g[v].size(); i++) {
		int to = g[v][i];
		if (!used[to])
			dfs(to);
	}
	order.push_back(v);
}

void init() {
	dp[pos[A]][pos[C]][0] = 0;
	for (int i = pos[A]; i < pos[C]; i++) {
		int v = order[i];
		if (dp[i][pos[C]][0] == INF)
			continue;
		for (int j = 0; j < (int)g[v].size(); j++) {
			int to = g[v][j];
			
			if (pos[to] < pos[C]) {
				update(pos[v], pos[C], 0, pos[to], pos[C], 0);
			}
		}
	}
}

int main()
{
	freopen("two-paths.in", "r", stdin);
	freopen("two-paths.out", "w", stdout);
	
	pair<pair<int, int>, int> res = decode(4);

	bool swapped = false;
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		u--, v--;
		g[u].push_back(v);
	}

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			for (int k = 0; k <= 1; k++)
				dp[i][j][k] = INF;
	memset(pred, 255, sizeof(pred));

	cin >> A >> B >> C >> D;
	A--, B--, C--, D--;

	for (int i = 0; i < n; i++)
		if (!used[i])
			dfs(i);
	reverse(order.begin(), order.end());
	for (int i = 0; i < n; i++)
		pos[order[i]] = i;
	if (pos[A] > pos[C]) {
		swap(A, C), swap(B, D);
		swapped = true;
	}

	init();

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			for (int k = 0; k <= 1; k++) {
				int v1 = order[i];
				int v2 = order[j];
				if (dp[i][j][k] == INF)
					continue;
				if (i >= j) {
					// from i
					for (int l = 0; l < (int)g[v1].size(); l++) {
						int to1 = g[v1][l];
						int t;
						if (v1 == v2)
							t = 1;
						else
							t = 0;
						update(i, j, k, pos[to1], j, t);
					}

					// from j
					for (int l = 0; l < (int)g[v2].size(); l++) {
						int to2 = g[v2][l];
						if (pos[to2] < pos[v1] || (k == 1 && pos[to2] == pos[v1]))
							continue;
						int t;
						if (v1 == v2)
							t = 1;
						else
							t = 0;
						update(i, j, k, i, pos[to2], t);
					}
				} else {
					// from j
					for (int l = 0; l < (int)g[v2].size(); l++) {
						int to2 = g[v2][l];
						int t;
						if (v1 == v2)
							t = 1;
						else
							t = 0;
						update(i, j, k, i, pos[to2], t);
					}

					// from i
					for (int l = 0; l < (int)g[v1].size(); l++) {
						int to1 = g[v1][l];
						if (pos[to1] < pos[v2] || (k == 1 && pos[to1] == pos[v2]))
							continue;
						int t;
						if (v1 == v2)
							t = 1;
						else
							t = 0;
						update(i, j, k, pos[to1], j, t);
					}
				}
			}
		}

		if (min(dp[pos[B]][pos[D]][0], dp[pos[B]][pos[D]][1]) == INF) {
			cout << "NO" << endl;
			return 0;
		}
		cout << "YES" << endl;
		//cout << A << ' ' << B << ' ' << C << ' ' << D << endl;
		vector<int> r1, r2;
		if (dp[pos[B]][pos[D]][0] < dp[pos[B]][pos[D]][1]) {
			int v1 = pos[B], v2 = pos[D], t = 0;
			while (v1 != pos[A] || v2 != pos[C]) {
				r1.push_back(order[v1]);
				r2.push_back(order[v2]);
				pair<pair<int, int>, int> r = decode(pred[v1][v2][t]);
				v1 -= r.first.first;
				v2 -= r.first.second;
				t = r.second;
			}
			r1.push_back(order[v1]);
			r2.push_back(order[v2]);
		} else {
			int v1 = pos[B], v2 = pos[D], t = 1;
			while (v1 != pos[A] || v2 != pos[C]) {
				r1.push_back(order[v1]);
				r2.push_back(order[v2]);
				pair<pair<int, int>, int> r = decode(pred[v1][v2][t]);
				v1 -= r.first.first;
				v2 -= r.first.second;
				t = r.second;
			}
			r1.push_back(order[v1]);
			r2.push_back(order[v2]);
		}

			

		reverse(r1.begin(), r1.end());
		reverse(r2.begin(), r2.end());

		if (swapped)
			r1.swap(r2);

		int len1 = 1, len2 = 1;
		for (int i = 1; i < (int)r1.size(); i++)
			if (r1[i] != r1[i - 1])
				len1++;
		for (int i = 1; i < (int)r2.size(); i++)
			if (r2[i] != r2[i - 1])
				len2++;

		cout << len1 << endl;
		cout << r1[0] + 1 << ' ';
		for (int i = 1; i < (int)r1.size(); i++)
			if (r1[i] != r1[i - 1])
				cout << r1[i] + 1 << ' ';
		cout << endl;
		cout << len2 << endl;
		cout << r2[0] + 1 << ' ';
		for (int i = 1; i < (int)r2.size(); i++)
			if (r2[i] != r2[i - 1])
				cout << r2[i] + 1 << ' ';
		cout << endl;
	return 0;
}