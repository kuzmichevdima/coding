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

int n, m;
vector<int> g[100100];
bool marked[100100];
bool used[100100];
vector<int> res;

int dfs(int v) {
	used[v] = true;
	bool flag = false;
	bool removed = false;
	for (int i = 0; i < (int)g[v].size(); i++) {
		int to = g[v][i];
		if (used[to])
			continue;
		int cnt = dfs(to);
		if (cnt != 0) {
			if (flag == true) {
				removed = true;
			} else {
				flag = true;
			}
		}
	}
	if (removed || (flag && marked[v])) {
		res.push_back(v);
		return 0;
	} else {
		if (flag || marked[v])
			return 1;
		else
			return 0;
	}
}

int main()
{
	freopen("removing.in", "r", stdin);
	freopen("removing.out", "w", stdout);

	scanf("%d%d", &n, &m);
	n++;
	for (int i = 0; i < m; i++) {
		int u, v;
		scanf("%d%d", &u, &v);
		if (u > v)
			swap(u, v);
		if (u != 0) {
			g[u].push_back(v);
			g[v].push_back(u);
		} else {
			marked[v] = true;
		}
	}
	for (int i = 1; i <= n; i++) {
		if (!used[i])
			dfs(i);
	}

	cout << res.size() << endl;
	for (int i = 0; i < (int)res.size(); i++)
		cout << res[i] << ' ';
	cout << endl;

	return 0;
}