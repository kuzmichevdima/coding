#include <iostream>
#include <cstdio>
#include <vector>
#include <map>
#include <cmath>
#include <cassert>
#include <algorithm>

using namespace std;

const int N = 4;
const int M = 5;
const int MOD = 10;

pair<vector<int>, pair<int, int> > a[1001];
int ez[100500];

int main() {
	//freopen("output.txt", "w", stdout);
	int n, m, l, r, mx = 0, cnt = 0, tail = -1, ans, dlt;
	char z;
	//scanf("%d", &n);
	n = N;
	int k = (int)sqrt(n);

	for (int i = 0; i < n; ++i)
	{
		if (cnt == k || tail == -1)
		{
			if (tail == k - 1)
			{
				a[++tail].first.resize(n - k * k);
			}
			else
			{
				a[++tail].first.resize(k);
			}
			mx = 0;
			cnt = 0;
		}
		ez[i] = rand() % MOD;
		printf("ez[%d] = %d\n", i, ez[i]);
		a[tail].first[cnt] = ez[i];
		//scanf("%d", &a[tail].first[cnt]);
		mx = max(a[tail].first[cnt], mx);
		a[tail].second.first = mx;
		cnt++;
	}

	//scanf("%d", &m);
	m = M;

	for (int i = 0; i < m; ++i)
	{
		//scanf("\n%c", &z);
		if (rand() % 2 == 0)
		{
			ans = 0;
			//scanf("%d %d", &l, &r);
			//l--; r--;
			l = rand() % N;
			r = rand() % N;
			if (l > r)
				swap(l, r);
			printf("get %d %d\n", l, r);

			for (int j = l - l / k * k; j <= (l % k == 0 ? -1 : l / k * k + k - l); ++j)
			{
				ans = max(ans, a[l / k].first[j]);
			}
			for (int i = (l % k == 0 ? l / k : l / k + 1); i < (r % k == 0 ? r / k : r / k + 1); ++i)
			{
				ans = max(ans, a[i].second.first);
			}
			for (int j = 0; j <= ((r + 1) % k == 0 ? -1 : r - r / k * k); ++j)
			{
				ans = max(ans, a[(r % k == 0 ? r / k : r / k + 1)].first[j]);
			}
			int right_ans = -1e9;
			for (int j = l; j <= r; j++)
				right_ans = max(right_ans, ez[j]);
			printf("%d %d\n", ans, right_ans);
			assert(ans == right_ans);
		}
		else
		{
			l = rand() % N;
			r = rand() % N;
			if (l > r)
				swap(l, r);
			dlt = rand() % MOD;
			printf("upd %d %d %d\n", l, r, dlt);

			for (int j = l - l / k * k; j <= (l % k == 0 ? -1 : l / k * k + k - l); ++j)
			{
				a[l / k].first[j] += dlt; a[l / k].second.first = max(a[l / k].first[j], a[l / k].second.first + a[l / k].second.second);
			}
			for (int i = (l % k == 0 ? l / k : l / k + 1); i < (r % k == 0 ? r / k : r / k + 1); ++i)
			{
				a[i].second.second += dlt;
			}
			for (int j = 0; j <= ((r + 1) % k == 0 ? -1 : r - r / k * k); ++j)
			{
				a[(r % k == 0 ? r / k : r / k + 1)].first[j] += dlt; a[(r % k == 0 ? r / k : r / k + 1)].second.first = max(a[(r % k == 0 ? r / k : r / k + 1)].second.first + a[(r % k == 0 ? r / k : r / k + 1)].second.second, a[(r % k == 0 ? r / k : r / k + 1)].first[j]);
			}
			for (int j = l; j <= r; j++)
				ez[j] += dlt;
		}
	}

	return 0;
}