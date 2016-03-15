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

int main()
{
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	int n;
	scanf("%d", &n);
	string a, b;
	cin >> a >> b;
	int pref, suff;
	forn(j, a.length())
		if (a[j] != b[j])
		{
			pref = j;
			break;
		}
	for (int j = a.length() - 1; j >= 0; j--)
		if (a[j] != b[j])
		{
			suff = j;
			break;
		}
	if (pref == suff)
	{
		printf("2");
		exit(0);
	}
	bool f1 = (a.substr(pref + 1, suff - pref) == b.substr(pref, suff - pref));
	bool f2 = (a.substr(pref, suff - pref) == b.substr(pref + 1, suff - pref));
	if (f1 || f2)
		printf("1");
	else printf("0");
	return 0;
}