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

const int inf = 1e9;

struct elem
{
	int fr;
	int to;
	int number;
	elem(int _fr, int _to, int _number) : fr(_fr), to(_to), number(_number){}
};

bool operator < (elem first, elem second)
{
	if (first.fr != second.fr)
		return first.fr < second.fr;
	return first.to < second.to;
}

/*bool operator == (elem first, elem second)
{
	return first.fr == second.fr && first.to == second.to;
}*/

multiset <elem> order;

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int n;
	scanf("%d", &n);
	forn(j, n)
	{
		int in, out;
		scanf("%d%d", &in, &out);
		out--;
		order.insert(elem(out, in, j + 1));
	}
	int cur = -inf;
	vi answer;
	forn(j, n)
	{
		multiset <elem> :: iterator iter = order.lower_bound(elem(cur, -inf, -1));
		if (iter == order.end())
		{
			printf("No");
			exit(0);
		}
		cur = iter->to;
		answer.pb(iter->number);
		order.erase(iter);
		
	}
	printf("Yes\n");
	for (int j = answer.size() - 1; j >= 0; j--)
		printf("%d ", answer[j]);
	return 0;
}