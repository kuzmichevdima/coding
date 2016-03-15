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


const int maxn = 50005;
//const int inf = 2e9;

int w[maxn];
int s[maxn];
int n;
bool used[maxn];

bool cmp(int first, int second)
{
	return w[first] + s[first] < w[second] + s[second];
}

int order[maxn];

int main()
{
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	scanf("%d", &n);
	int sum_w = 0;
	forn(j, n)
	{
		scanf("%d%d", &w[j], &s[j]);
		sum_w += w[j];
		order[j] = j;
	}
	sort(order, order + n, cmp);
	int start = -1e9;
	int finish = 1e9;
	while(start < finish)
	{
		int middle = start + (finish - start) / 2;
		//if (middle == finish)
		//	middle = finish - 1;
		int w_left = sum_w;
		bool fail = false;
		for (int j = n - 1; j >= 0; j--)
		{
			int id = order[j];
			if (s[id] + w[id] >= w_left - middle)
			{
				w_left -= w[id];
			}
			else
			{
				fail = true;
				break;
			}
		}
		if (!fail)
			finish = middle;
		else start = middle + 1;
	}
	printf("%d", start);
	return 0;
}