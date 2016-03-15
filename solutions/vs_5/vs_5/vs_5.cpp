#include <iostream>
#include <cstdio>
#include <vector>
#include <map>
#include <cmath>
#include <algorithm>
#include <cassert>

using namespace std;

vector<int> a(100001);
map<pair<int, int>, pair<int, int> > d;

int dummy[100001];

const int N = 4;
const int M = 100;
const int MOD = 10;

int main() {
	freopen("input.txt", "r", stdin);
	int n, m, l, r, mx = 0, cnt = 0, ans, dlt;
	char z;
	//scanf("%d", &n);
	n = N;
	int k = (int)sqrt(n);

	for (int i = 0; i < n; ++i)
	{
		cnt++;
		//scanf("%d", &a[i]);
		a[i] = rand() % MOD;
		printf("a[%d] = %d\n", i, a[i]);
		dummy[i] = a[i];
		mx = max(a[i], mx);

		if (cnt == k || i == n - 1)
		{
			d[{i - cnt + 1, i}] = { mx, 0 };
			mx = 0;
			cnt = 0;
		}
	}
	//scanf("%d", &m);
	m = M;

	for (int i = 0; i < m; ++i)
	{
		//scanf("\n%c", &z);
		
		if (rand() % 2 == 0)
		{
			//scanf("%d %d", &l, &r);
			l = rand() % N;
			r = rand() % N;
			if (l > r)
				swap(l, r);
			printf("i = %d l = %d r = %d\n", i, l, r);
			//l--; r--;
			ans = 0;

			if (r - l + 1 < k)
			{
				for (int j = l; j <= r; ++j)
				{
					ans = max(ans, a[j] + d[{l / k * k, l / k * k + k - 1}].second);
				}
			}

			else if (l > l / k * k && r < l / k * k + 2 * k - 1)
			{
				for (int j = l; j <= l / k * k + k - 1; ++j)
				{
					ans = max(ans, a[j] + d[{l / k * k, l / k * k + k - 1}].second);
				}

				for (int j = l / k * k + k; j <= r; ++j)
				{
					ans = max(ans, a[j] + d[{l / k * k + k, l / k * k + 2 * k - 1}].second);
				}
			}
			else
			{
				for (int j = l; j <= l / k * k + k - 1; ++j)
				{
					ans = max(ans, a[j] + d[{l / k * k, l / k * k + k - 1}].second);
				}
				for (int j = (l % k == 0 ? l / k : l / k + 1); j < r / k; ++j)
				{
					ans = max(ans, d[{j * k, j * k + k - 1}].first + d[{j * k, j * k + k - 1}].second);
				}
				for (int j = r / k * k; j <= r; ++j)
				{
					ans = max(ans, a[j] + d[{r / k * k, r / k * k + k - 1}].second);
				}
			}
			//cout << ans << ' ';
			int right_ans = -1e9;
			for (int j = l; j <= r; j++)
				right_ans = max(right_ans, dummy[j]);
			cout << ans << " " << right_ans << endl;
			assert(ans == right_ans);
		}
		else
		{
			l = rand() % N;
			r = rand() % N;
			dlt = rand() % MOD;
			if (l > r)
				swap(l, r);
			printf("i = %d l = %d r = %d dlt = %d\n", i, l, r, dlt);
			//scanf("%d %d %d", &l, &r, &dlt);
			//l--; r--;
			for (int j = l; j <= r; j++)
				dummy[j] += dlt;

			if (r - l + 1 < k)
			{
				for (int j = l; j <= r; ++j)
				{
					a[j] += dlt;
					d[{l / k * k, l / k * k + k - 1}].first = a[j] > d[{l / k * k, l / k * k + k - 1}].first + d[{l / k * k, l / k * k + k - 1}].second ? a[j] : d[{l / k * k, l / k * k + k - 1}].first;
				}
			}

			else if (l > l / k * k && r < l / k * k + 2 * k - 1)
			{
				for (int j = l; j <= l / k * k + k - 1; ++j)
				{
					a[j] += dlt;
					d[{l / k * k, l / k * k + k - 1}].first = a[j] > d[{l / k * k, l / k * k + k - 1}].first + d[{l / k * k, l / k * k + k - 1}].second ? a[j] : d[{l / k * k, l / k * k + k - 1}].first;
				}

				for (int j = l / k * k + k; j <= r; ++j)
				{
					a[j] += dlt;
					d[{l / k * k + k, l / k * k + 2 * k - 1}].first = a[j] > d[{l / k * k + k, l / k * k + 2 * k - 1}].first + d[{l / k * k + k, l / k * k + 2 * k - 1}].second ? a[j] : d[{l / k * k + k, l / k * k + 2 * k - 1}].first;
				}
			}
			else
			{
				for (int j = l; j <= l / k * k + k - 1; ++j)
				{
					a[j] += dlt;
					d[{l / k * k, l / k * k + k - 1}].first = (a[j] > d[{l / k * k, l / k * k + k - 1}].first + d[{l / k * k, l / k * k + k - 1}].second) ? a[j] : d[{l / k * k, l / k * k + k - 1}].first;
				}
				for (int j = (l % k == 0 ? l / k : l / k + 1); j < r / k; ++j)
				{
					d[{j * k, j * k + k - 1}].second += dlt;
				}
				for (int j = r / k * k; j <= r; ++j)
				{
					a[j] += dlt;
					d[{r / k * k, r / k * k + k - 1}].first = (a[j] > d[{r / k * k, r / k * k + k - 1}].first + d[{r / k * k, r / k * k + k - 1}].second) ? a[j] : d[{r / k * k, r / k * k + k - 1}].first;
				}
			}
		}
	}

	return 0;
}