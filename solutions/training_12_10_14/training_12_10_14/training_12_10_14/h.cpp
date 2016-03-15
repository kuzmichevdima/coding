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

char s[1000100];
int k;

int cnt[12];
const int msk2 = (1 << 2) + (1 << 4) + (1 << 6) + (1 << 8);
const int msk3 = (1 << 3) + (1 << 6) + (1 << 9);
const int msk5 = (1 << 5);
const int msk7 = (1 << 7);

inline bool good(int msk) {
	if (msk & (1 << 0))
		msk ^= (1 << 0);
	if (msk & (1 << 1))
		return true;

	if (msk == (msk & msk2) ||
		msk == (msk & msk3) ||
		msk == (msk & msk5) ||
		msk == (msk & msk7))
		return false;
	return true;
}

inline bool solve(char *s, int k) {
	int n = strlen(s);
	memset(cnt, 0, sizeof(cnt));
	int msk = 0;
	for (int i = 0; i < k; i++)
		cnt[s[i] - '0']++;
	for (int i = 0; i < 10; i++)
		if (cnt[i] != 0) 
			msk ^= (1 << i);
	if (!good(msk))
		return false;

	for (int i = k; i < n; i++) {
		int c = s[i] - '0';
		cnt[c]++;
		if (cnt[c] == 1) 
			msk ^= (1 << c);

		c = s[i - k] - '0';
		cnt[c]--;
		if (cnt[c] == 0)
			msk ^= (1 << c);

		if (!good(msk) || (msk == 1))
			return false;
	}
	return true;
}

int main()
{
	freopen("numbers.in", "r", stdin);
	freopen("numbers.out", "w", stdout);
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	
	int cnt = 0;
	while (true) {
		cnt++;
		scanf("%s %d\n", s, &k);
		if (k == 0)
			return 0;
		printf("Number %d is ", cnt);
		if (solve(s, k))
			printf("crooked.\n");
		else
			printf("not crooked.\n");
	}

	return 0;
}