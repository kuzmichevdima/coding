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

set <string> ans;
string a, b;

bool f(string s, string a)
{
	int pref = a.length();
	int suff = 0;
	forn(j, a.length())
		if (a[j] != s[j])
		{
			pref = j;
			break;
		}
	for (int j = a.length() - 1; j >= 0; j--)
		if (a[j] != s[s.length() - (a.length() - j)])
		{
			suff = j;
			break;
		}
	forn(j, s.length())
		if (pref >= j && suff <= j)
			return true;
	return false;
}

void check(string s, bool flag)
{
	cout << "check " << s << endl;
	bool f1 = f(s, a);
	bool f2 = f(s, b);
	if (f1 && f2)
	{
		if (flag)
			ans.insert(s);
		else
		{
			forn(j, s.length() / 2)
				swap(s[j], s[s.length() - j - 1]);
			cout << "s = " << s << endl;
			ans.insert(s);
		}

	}
}

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int n;
	scanf("%d", &n);
	cin >> a;
	cin >> b;
	
	forn(j, n)
		if (a[j] != b[j])
		{
			
			check(a.substr(0, j) + a[j] + b[j] + a.substr(j + 1, a.length()), true);
			check(a.substr(0, j) + b[j] + a[j] + a.substr(j + 1, a.length()), true);
			break;
		}
	forn(j, a.length() / 2)
		swap(a[j], a[a.length() - j - 1]);
	forn(j, b.length() / 2)
		swap(b[j], b[b.length() - j - 1]);
	forn(j, n)
		if (a[j] != b[j])
		{
			
			check(a.substr(0, j) + a[j] + b[j] + a.substr(j + 1, a.length()), false);
			check(a.substr(0, j) + b[j] + a[j] + a.substr(j + 1, a.length()), false);
			break;
		}
	printf("%d", ans.size());
	return 0;
}