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

const int maxn = 1005;
const int con = 1e4;

int A[maxn];
int B[maxn];
int mark[2 * con + 5];
int order[maxn];

bool cmp(int first, int second)
{
	return B[first] < B[second];
}

int main()
{
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	int k, n;
	scanf("%d%d", &k, &n);
	forn(j, n)
	{
		scanf("%d%d", &A[j], &B[j]);
		if (A[j] > B[j])
			swap(A[j], B[j]);
		A[j] += con;
		B[j] += con;
		order[j] = j;
	}
	sort(order, order + n, cmp);
	forn(tmp, n)
	{
		int j = order[tmp];
		int cnt = 0;
		fore(pos, A[j], B[j])
			if (mark[pos])
				cnt++;
		int L = k - cnt;
		for (int pos = B[j]; pos >= A[j] && L > 0; pos--) if (!mark[pos])
		{
			mark[pos] = true;
			L--;
		}
	}
	vi answer;
	fore(pos, 0, 2 * con)
		if (mark[pos])
			answer.pb(pos);
	printf("%d\n", answer.size());
	forn(j, answer.size())
		printf("%d\n", answer[j] - con);
	return 0;
}