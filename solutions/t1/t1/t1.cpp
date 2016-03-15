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

const int maxn = 1e6 + 5;

char s[maxn];
int p[maxn];

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	scanf("%s", &s);
	int len = strlen(s);
	int k = 0;
	fore(i, 1, len - 1)
	{
		while(k > 0 && s[i] != s[k])
			k = p[k - 1];
		if (s[i] == s[k])
			k++;
		p[i] = k;
	}
	forn(j, len)
		printf("%d ", p[j]);
	return 0;
}