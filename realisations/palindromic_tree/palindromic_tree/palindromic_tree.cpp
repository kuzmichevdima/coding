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

struct node
{
	int link, len;
	int next[26];
	int counter;
};



const int maxn = 1e5 + 5;

//i64 to_add[maxn];
int t, cnt;
string s;
node tree[maxn];

void init_tree()
{
	cnt = 2;
	tree[0].len = -1;
	tree[0].link = tree[1].link = 0;
	tree[1].len = 0;
	forn(j, 26)
		tree[0].next[j] = tree[1].next[j] = -1;
}

void addLetter(int pos)
{
	char letter = s[pos];
	int cur = t;
	while(true)
	{
		int curlen = tree[cur].len;
		if (pos - 1 - curlen >= 0 && s[pos - 1 - curlen] == letter)
			break;
		cur = tree[cur].link;
	}
	if (tree[cur].next[letter - 'a'] != -1)
	{	
		t = tree[cur].next[letter - 'a'];
		//to_add[t]++;
		return;
	}
	cnt++;
	forn(j, 26)
		tree[cnt - 1].next[j] = -1;
	tree[cnt - 1].len = tree[cur].len + 2;
	t = cnt - 1;
	tree[cur].next[letter - 'a'] = cnt - 1;
	
	//to_add[cnt - 1]++;
	if (tree[cnt - 1].len == 1)
	{
		tree[cnt - 1].link = 1;
		tree[cnt - 1].counter = 1;
		return;
	}
	while(true)
	{
		cur = tree[cur].link;
		int curlen = tree[cur].len;
		if (pos - curlen - 1 >= 0 && s[pos - curlen - 1] == letter)
		{
			tree[cnt - 1].link = tree[cur].next[letter - 'a'];
			tree[cnt - 1].counter = tree[tree[cnt - 1].link].counter + 1;
			break;
		}
	}
}

int main()
{
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	init_tree();
	cin >> s;
	t = 1;
	i64 answer = 0;
	forn(j, s.length())
	{
		addLetter(j);
		answer += tree[t].counter;
	}
	cout << answer;
	return 0;
}