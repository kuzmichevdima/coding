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

int z[maxn];
char s[maxn];
int L_arr[maxn];
int R_arr[maxn];

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	scanf("%s", &s);
	int len = strlen(s);
	int L = 0;
	int R = 0;
	z[0] = len;
	fore(i, 1, len - 1)
	{
		int cur = (i <= R ? min(z[i - L], R - i + 1) : 0);
		while(i + cur < len && s[i + cur] == s[cur])
			cur++;
		z[i] = cur;
		if (cur > 0 && i + z[i] - 1 > R)
		{
			L = i;
			R = i + z[i] - 1;
		}
		L_arr[i] = L;
		R_arr[i] = R;
	}
	forn(j, len)
		printf("%d ", z[j]);
	printf("\n");
	forn(j, len)
		printf("%d ", L_arr[j]);
	printf("\n");
	forn(j, len)
		printf("%d ", R_arr[j]);
	return 0;
}