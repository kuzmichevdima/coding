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

map <int, int> x_trans;
map <int, set <int> > s_trans;
set <int> banned;

int main()
{
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	string denied = "DENIED";
	string granted = "GRANTED";
	string ignored = "IGNORED";
	char typ;
	int trans, item;
	while(scanf("%c%d%d\n", &typ, &trans, &item) == 3)
	{
		if (banned.find(trans) != banned.end())
		{
			cout << ignored << endl;
			continue;
		}
		bool fail = false;
		if (typ == 'S')
		{
			if (x_trans.find(item) != x_trans.end())
			{
				if (x_trans[item] == trans)
				{
					//x_trans.erase(item);
					s_trans[item].insert(trans);
				}
				else fail = true;
			}
			else s_trans[item].insert(trans);
		}
		else
		{
			bool bad_s = (!s_trans[item].empty()) && ((*s_trans[item].begin()) != trans);
			bool bad_x = (x_trans.find(item) != x_trans.end()) && (x_trans[item] != trans);
			if (s_trans[item].size() > 1 || bad_s || bad_x)
			{
				fail = true;
			}
			else
			{
				//s_trans[item].erase(trans);
				x_trans[item] = trans;
			}
		}
		if (fail)
		{
			banned.insert(trans);
			cout << denied << endl;
		}
		else cout << granted << endl;
	}
	return 0;
}