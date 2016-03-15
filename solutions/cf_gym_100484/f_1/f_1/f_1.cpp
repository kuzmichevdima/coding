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

const int maxn = 1e5 + 5;

string st[maxn];

int main()
{
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	int sz = 0;
	string s;
	while(cin >> s)
	{
		while(sz > 0)
		{
			if (s.length() >= sz && s.substr(0, sz) == st[sz - 1].substr(0, sz))
				break;
			sz--;
		}
		forn(j, sz)
			printf(" ");
		cout << s << endl;
		st[sz] = s;
		sz++;
	}
	return 0;
}