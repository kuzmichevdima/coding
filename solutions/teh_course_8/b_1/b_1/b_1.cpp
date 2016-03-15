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

const int maxn = 30;

int edges[maxn];
int n;
int answer = 0;

void go(int cur, int mask)
{
	if (cur == n)
	{
		answer++;
		return;
	}
	if ((edges[cur] & mask) == mask)
		go(cur + 1, mask | (1 << cur));
	go(cur + 1, mask);
}

int main()
{
#ifdef LOCAL
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%d\n", &n);
	forn(j, n)
	{
		forn(i, n)
		{
			char c;
			scanf("%c", &c);
			if (c == '1' || i == j)
				edges[j] |= (1 << i);

		}
		scanf("\n");
	}
	go(0, 0);
	printf("%d", answer);
	return 0;
}