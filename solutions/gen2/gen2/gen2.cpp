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

const int n = 1e5;
const int m = 30000;
const int X = 1e5;
const int k = 1000;
const int n1 = 1000;


int main()
{
	//freopen("output.txt", "w", stdout);
	printf("%d\n", n);
	forn(j, n)
		printf("%d ", rand() % X);
	printf("%d\n", m);
	forn(j, m - k)
	{ 
		int s = rand() % n1 + 1;
		int f = n - rand() % n1;
		if (s > f)
			swap(s, f);
		printf("a %d %d %d\n", s, f, X);
	}
	forn(j, k)
	{
		int s = rand() % n + 1;
		int f = rand() % n + 1;
		if (s > f)
			swap(s, f);
		printf("m %d %d\n", s, f);
	}

	return 0;
}