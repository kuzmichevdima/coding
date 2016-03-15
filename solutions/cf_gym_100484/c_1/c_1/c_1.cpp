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

char s[maxn][maxn * 55];

int main()
{
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	int n;
	scanf("%d", &n);
	sprintf(s[0], "((A0|B0)|(A0|B0))");
	fore(i, 1, n - 1)
	{
		sprintf(s[i], "((A%d|B%d)|(%s|((A%d|A%d)|(B%d|B%d))))", i, i, s[i - 1], i, i, i, i);
	}
	printf("%s", s[n - 1]);
	return 0;
}