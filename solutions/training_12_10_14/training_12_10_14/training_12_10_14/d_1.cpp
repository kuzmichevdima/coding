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

void solve(int test_number, int n);

int main()
{
	freopen("indent.in", "r", stdin);
	freopen("indent.out", "w", stdout);
	int tests = 1;
	while(true)
	{
		int n;
		scanf("%d", &n);
		if (n == 0)
			break;
		solve(tests, n);
		tests++;
	}
	return 0;
}

const int maxn = 10005;

bool ended[maxn];
int cnt_tab[maxn];
int cnt_space[maxn];
int total[maxn];
int st[maxn];

inline void get(string & s, int j)
{
	cnt_tab[j] = cnt_space[j] = 0;
	forn(pos, s.length())
	{
		if (s[pos] == '*')
			cnt_tab[j]++;
		else if (s[pos] == '.')
			cnt_space[j]++;
		else break;
	}
	ended[j] = (s[s.length() - 1] == ':');
}

void solve(int test_number, int n)
{
	forn(j, n)
	{
		string s;
		cin >> s;
		get(s, j);
		//cout << s << endl;
		//printf("cnt_tab[%d] = %d cnt_space[%d] = %d ended[%d] = %d\n", j, cnt_tab[j], j, cnt_space[j], j, ended[j]);
	}
	vi answer;
	if (!ended[n - 1])
	{
		fore(L, 1, 64)
		{
			int sz = 1;
			st[0] = 0;
			bool fail = false;
			forn(j, n)
			{
				total[j] = cnt_tab[j] * L + cnt_space[j];
				if (j == 0 || (!ended[j - 1]))
				{
					while(sz > 0 && (st[sz - 1] != total[j]))
						sz--;
					if (sz == 0)
					{
						fail = true;
						break;
					}
				}
				else
				{
					if (total[j] > total[j - 1])
					{
						st[sz] = total[j];
						sz++;
					}
					else
					{
						fail = true;
						break;
					}
				}
			}
			if (!fail)
				answer.pb(L);
		}
	}
	printf("Testcase #%d:\n", test_number);
	if (answer.empty())
		printf("none\n");
	else if (answer.size() == 1)
		printf("unique\n");
	else printf("multiple\n");
	forn(j, answer.size())
		printf("%d ", answer[j]);
	printf("\n\n");
}