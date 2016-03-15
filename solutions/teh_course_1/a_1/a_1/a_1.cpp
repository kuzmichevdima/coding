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

const int maxn = 16;
const int maxm = 8;

i64 dp[maxn + 2][maxm][1 << (maxm + 1)][1 << (maxm - 1)];

inline void upd(i64 & x, i64 y)
{
	x += y;
}

inline void print(int fr1, int fr2, int fr3, int fr4, int to1, int to2, int to3, int to4, int value)
{
	printf("(%d %d %d %d) -> (%d %d %d %d), %d\n", fr1, fr2, fr3, fr4, to1, to2, to3, to4, value);
}

int main()
{
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	int n, m;
	scanf("%d%d", &n, &m);
	if (n < m)
		swap(n, m);
	int max_prof = 1 << (m + 1);
	int max_closed = 1 << (m - 1);
	dp[1][0][0][0] = 1;
	i64 answer = 0;
	fore(col, 1, n) 
		forn(i, m)
			forn(prof, max_prof)
				forn(closed, max_closed) if (dp[col][i][prof][closed] != 0)
				{
					i64 value = dp[col][i][prof][closed];
					if (i == m - 1)
					{
						bool prelast = prof & (1 << (m - 1));
						bool last = prof & (1 << m);

						if (last)
						{
							int shift_1 = 2 * (prof ^ (1 << m));
							if (shift_1 != 0)
							{
								//print(col, i, prof, closed, col + 1, 0, shift_1, closed, value);
								upd(dp[col + 1][0][shift_1][closed], value);
							}
							else if (col == n && closed == max_closed - 1)
								answer += value;
							
						}

						if ((!last) && (!prelast))
						{
							int shift_2 = 2 * (prof | (1 << (m - 1)));
							if (shift_2 != 0)
							{
								//print(col, i ,prof, closed, col + 1, 0, shift_2, closed, value);
								upd(dp[col + 1][0][shift_2][closed], value);
							}
							else if (col == n && closed == max_closed - 1)
								answer += value;
						}
						continue;
					}
					bool bit0 = prof & (1 << i);
					bool bit1 = prof & (1 << (i + 1));
					bool bit2 = prof & (1 << (i + 2));
					
					if (bit1)
					{
						int new_prof = prof ^ (1 << (i + 1));
						//print(col, i, prof, closed, col, i + 1, new_prof, closed, value);
						upd(dp[col][i + 1][new_prof][closed], value);
					}
					else
					{
						if (!bit0)
						{	
							int new_prof = prof | (1 << i);
							//print(col, i, prof, closed, col, i + 1, new_prof, closed, value);
							upd(dp[col][i + 1][new_prof][closed], value);
						}
						if (i < m - 1 && (!bit2))
						{
							//print(col, i, prof, closed, col, i + 1, prof | (1 << (i + 2)), closed | (1 << i), value);
							upd(dp[col][i + 1][prof | (1 << (i + 2))][closed | (1 << i)], value);
						}
					}
				}
	//i64 answer = 0;
	//forn(prof, max_prof)
	//	answer += dp[n][0][prof][max_closed - 1];
	//i64 answer = dp[n][0][max_prof - 2][max_closed - 1];
	cout << answer;
	return 0;
}