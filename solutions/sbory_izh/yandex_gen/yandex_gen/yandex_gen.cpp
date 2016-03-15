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

const int maxn = 20;
const int maxm = 150;
const int maxk = 40000;

const int n = maxn / 4;
const int m = maxm / 4;
const int k = maxk / 4;
const int mod = 10;

int a[k][n + 1];
int b[m][2 * n + 1];

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	printf("%d %d %d\n", k, m, n);
	forn(i, k)
	{
		//while(true)
		//{
			forn(j, n + 1)
			{
				a[i][j] = rand() % mod;
			}
		//}
			forn(j, n + 1)
				printf("%d ", a[i][j]);
		printf("\n");
	}
	forn(i, m)
	{
		forn(j, 2 * n + 1)
			printf("%d ", rand() % mod);
		printf("\n");
	}
	return 0;
}