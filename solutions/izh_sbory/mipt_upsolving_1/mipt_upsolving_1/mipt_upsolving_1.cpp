#include <iostream>
#include <vector>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <memory.h>
#include <map>
#include <set>
#include <cmath>
#include <algorithm>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <cassert>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)n; i++)
#define fore(i, b, e) for (int i = (int)b; i <= (int)e; i++)
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define i64 long long
#define li long long
#define lint long long
#define vi vector <int>
#define pii pair <int, int>
#define INF (int)1e9
#define LINF (li)1e18

#define DEBUG false

#define TASK "records-and-cycles"

void solve(int test_number, string & s, int n);

const int S_LEN = 10;
const int PRIME_LIMIT = 1000;
const int CON = 1600005;
const int N = 10;

int primes[PRIME_LIMIT];

int main() {
#ifdef LOCAL
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#else
	
#endif
	cout.precision(9);
	cout.setf(ios::fixed);
	/*int n = N;
	int PRIME_CNT = 0;
	fore(i, 2, PRIME_LIMIT)
	{
		bool fail = false;
		for (int j = 2; j * j <= i; j++)
			if (i % j == 0)
			{
				fail = true;
				break;
			}
		if (!fail)
		{
			primes[PRIME_CNT] = i;
			PRIME_CNT++;
		}
	}
	for (int i = 0; i < n; i++)
	{
		string s = "";
		//int slen = rand() % S_LEN + 1;
		int slen = S_LEN;
		forn(j, slen)
			s += ('1' + rand() % 9);
		solve(i + 1, s, primes[rand() % PRIME_CNT]);
	}*/
	string s = "";
	solve(1, s, 1);
}

string s, x;
int n;

li MOD1 = 1000000007;
li MOD2 = 1000000009;
li base1 = 17;
li base2 = 13;
li h1[CON + 5];
li h2[CON + 5];
li p1[CON + 5];
li p2[CON + 5];



void build_hash(string &s) {
	h1[0] = s[0] - '0';
    h2[0] = s[0] - '0';
	p1[0] = 1;
    p2[0] = 1;
//	printf("waqew");
//	fflush(stdout);
	for (int i = 1; i < s.length(); i++) {
		//h1[i] = (h1[i - 1] * base1 + (s[i] - '0')) % MOD1;
        //h2[i] = (h2[i - 1] * base2 + (s[i] - '0')) % MOD2;
		p1[i] = (p1[i - 1] * base1) % MOD1;
        p2[i] = (p2[i - 1] * base2) % MOD2;
		h1[i] = (h1[i - 1] + p1[i] * (i64)(s[i] - '0')) % MOD1;
		h2[i] = (h2[i - 1] + p2[i] * (i64)(s[i] - '0')) % MOD2;
	}
	
}

inline pair<li, li> get_hash(int l, int r) {
	if (l == 0)
		return mp(h1[r] * p1[CON - r] % MOD1, h2[r] * p2[CON - r] % MOD2);
	else
		return mp(
                (h1[r] - h1[l - 1] + MOD1) * p1[CON - r] % MOD1,
                (h2[r] - h2[l - 1] + MOD2) * p2[CON - r] % MOD2);
}

inline bool is_eq(int l1, int l2, int len) {
	if (l1 > l2)
		swap(l1, l2);
	int r1 = l1 + len - 1, r2 = l2 + len - 1;
	pair<li, li> h1 = get_hash(l1, r1), h2 = get_hash(l2, r2);
	if (h1 == h2)
		return true;
	else
		return false;
}

inline bool cmp(string &s, int l1, int len1, int l2, int len2) {
	if (len1 < len2)
		return true;
	if (len2 < len1)
		return false;

	int len = len1;
	int l = 0, r = len + 1;
	while (l + 1 != r) {
		int d = (l + r) / 2;
		if (is_eq(l1, l2, d))
			l = d;
		else
			r = d;
	}
	if (l == len)
		return false;
	else
		return s[l1 + l] < s[l2 + l];
}

int pred[CON + 5];
li p10[CON + 5];



void solve(int test_number, string & s, int n)
{
	//cout << "s: " << s << " n = " << n << endl;
	cin >> s >> n;
	
	if (n == 2 || n == 5) {
		int inf = 1e9;
		int minn = inf;
		for (int i = 0; i < s.length(); i++) {
			int c = s[i] - '0';
			if (c % n == 0) {
				minn = min(minn, c);
				//return;
			}
		}
		if (minn == inf)
			cout << -1 << endl;
		else printf("%d\n", minn);
		return;
	} else {
		p10[0] = 1;
		x = "";
		while (x.length() + s.length() < CON)
			x += s;
		s = x;
		for (int i = 1; i < s.length(); i++)
			p10[i] = (p10[i - 1] * 10) % n;
		
		build_hash(s);
//		printf("here!");
//		fflush(stdout);
		li cur = 0;
		li from = 0, len = INF;
		//memset(pred, 255, sizeof(pred));
		forn(j, n)
			pred[j] = -1;
		pred[0] = s.length();
		p10[0] = 1;
		for (int i = s.length() - 1; i >= 0; i--) {
			cur = (p10[s.length() - 1 - i] * (s[i] - '0') + cur) % n;
			if (pred[cur] != -1) {
				if (cmp(s, i, pred[cur] - i, from, len)) {
					from = i;
					len = pred[cur] - i;
				}
			}
			pred[cur] = i;
		}
		string answer = s.substr(from, len);
		len = 1;
		string alt = "";
		if (DEBUG)
		{
			
			while(true)
			{
				bool found = false;
				forn(start, s.length() - len)
				{
					int cur = 0;
					fore(pos, start, start + len - 1)
					{
						cur = (cur * 10 + s[pos] - '0') % n;
					}
					if (cur == 0)
					{
						string tmp = s.substr(start, len);
						if (alt == "" || tmp < alt)
							alt = tmp;
						found = true;
					}
				}
				if (found)
					break;
				len++;
			}
		}
		//cout << "alternative: " << alt << endl;
		//answer = alt;
		cout << answer << endl;
		//assert(answer == alt);
		if (DEBUG)
		{
			if (answer != alt)
			{
				assert(false);
				printf("FAIL!!!!!\n");
				exit(-1);
			}
		}
	}
}
