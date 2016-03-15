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

#define li unsigned long long

#define vi vector <int>
#define pii pair <int, int>
#define INF (int)1e9
#define LINF (li)1e18

#define TASK "board-blitz"

typedef unsigned int uint;

void solve(int test_number);

int main() {
#ifdef LOCAL
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#else
	freopen(TASK".in", "r", stdin);
	freopen(TASK".out", "w", stdout);
#endif
	cout.precision(9);
	cout.setf(ios::fixed);
	int n = 1;
	for (int i = 0; i < n; i++)
		solve(i + 1);
}

int n;
long long A, C, S;

inline long long gen() {
	return S = S * A + C;
}

void bin(li a, li cnt) {
	string r = "";
	for (int i = 0; i < cnt; i++) {
		int rm = a % 2;
		a /= 2;
		r = char(rm + '0') + r;
	}
	cout << r << ' ' ;
}

inline li liabs(li a) {
	if (a >= 0)
		return a;
	else
		return -a;
}

void print(li s, li p, li dir, li msk) {
	cout << s << ' ' << p << ' ';
	bin(dir, 2);
	bin(msk, 8);
	cout << endl;
}

int bit[8][8];

void print_field(li a, li b)
{
	forn(i, 8)
	{
		forn(j, 8)
		{
			int bit_num = bit[i][j];
			if (a & (1ULL << bit_num))
				printf("W");
			else if (b & (1ULL << bit_num))
				printf("B");
			else printf(".");
		}
		printf("\n");
	}
}

inline li clockwise(li a) {
	return (a << 16) ^ (a >> 48);
}

inline li counterclockwise(li a) {
	return (a >> 16) ^ (a << 48);
}

inline li move_right(li a, li msk) {
	li x = a & ((1ULL << 16) - 1ULL);
	li y = x & ((1 << 3) + (1 << 7) + (1 << 11) + (1 << 15));
	//cout << x << " " << y << " " << ((x ^ y) << 1)  << endl;
	x = ((x ^ y) << 1 )+ 
			(((msk & (1 << 0)) >> 0) << 0) +
			(((msk & (1 << 1)) >> 1) << 4) +
			(((msk & (1 << 2)) >> 2) << 8) +
			(((msk & (1 << 3)) >> 3) << 12);
	//cout << x << endl;

	li z = (a >> 16) & ((1ULL << 16) - 1ULL);
	z = z >> 4;
	z += (1 << 12) * ((y & (1 << 3)) >> 3) + (1 << 13) * ((y & (1 << 7)) >> 7) +
		(1 << 14) * ((y & (1 << 11)) >> 11) + (1 << 15) * ((y & (1 << 15)) >> 15);

	li v = (a >> 48) & ((1ULL << 16) - 1ULL);
	li q = v & ((1 << 15) ^ (1 << 14) ^ (1 << 13) ^ (1 << 12));
	v = ((v ^ q) << 4) + 
			(((msk & (1 << 7)) >> 7) << 0) +
			(((msk & (1 << 6)) >> 6) << 1) +
			(((msk & (1 << 5)) >> 5) << 2) +
			(((msk & (1 << 4)) >> 4) << 3);

	
	li w = (a >> 32) & ((1ULL << 16) - 1ULL);
	w = (w ^((1 << 0) + (1 << 4) + (1 << 8) + (1 << 12))) & w;
	w >>= 1;
	w += (q & (1 << 15)) + ((q & (1ULL << 14)) >> 14) * (1 << 11) +
		((q & (1ULL << 13)) >> 13) * (1 << 7) + ((q & (1ULL << 12)) >> 12) * (1 << 3);

	return x + (z << 16) + (w << 32) + (v << 48);
}

 li a, b;

li rev[10000];


inline li move_left(li a, li msk) {
	return clockwise(clockwise((move_right(counterclockwise(counterclockwise(a)), rev[msk]))));
}

inline li move_up(li a, li msk) {
	return counterclockwise(move_right(clockwise(a), msk));
}

inline li move_down(li a, li msk) {
	return clockwise(move_right(counterclockwise(a), rev[msk]));
}

inline li rever(li a) {
	li r = 0;
	for (int i = 0; i < 8; i++) {
		if (a & (1ULL << i))
			r ^= (1ULL << (7 - i));
	}
	return r;
}

void print_prepare()
{
	int cur = 0;
	forn(i, 4)
		forn(j, 4)
		{
			bit[i][j] = cur;
			cur++;
		}
	for (int j = 7; j >= 4; j--)
		forn(i, 4)
		{
			bit[i][j] = cur;
			cur++;
		}
	for (int i = 7; i >= 4; i--)
		for (int j = 7;j >= 4; j--)
		{
			bit[i][j] = cur;
			cur++;
		}
	forn(j, 4)
		for (int i = 7; i >= 4; i--)
		{
			bit[i][j] = cur;
			cur++;
		}
}

void read_table()
{
	a = 0;
	b = 0;
	forn(i, 8)
	{
		forn(j, 8)
		{
			//scanf("%c", &tmp[i][j]);
			char c;
			scanf("%c", &c);
			if (c == 'W')
				a += (1ULL << bit[i][j]);
			else if (c == 'B')
				b += (1ULL << bit[i][j]);
		}
	}
	a = move_right(a, 0);
	print_field(a, b);
}

void solve(int test_number)
{
	print_prepare();
	
	for (int i = 0; i < (1 << 8); i++) {
		rev[i] = rever(i);
	}
	//read_table();
	//exit(0);
	long long cnst = 0;
	for (int i = 53;  i <= 63; i++)
		cnst ^= (1LL << i);
	cin >> n >> A >> C >> S;
	a = b = 0;
	for (int i = 0; i < n; i++) {
		long long s = gen();
		long long p = (s & cnst) >> 53;
		long long dir = (p & ((1LL << 9) ^ (1LL << 8))) >> 8;
		long long msk = (p & ((1LL << 8) - 1LL));
		//print(s, p, dir, msk);

		if (i % 2 == 0) {
			if (p < 0) {
				a = clockwise(a);
			} else {
				if (dir == 0)
					a = move_up(a, msk);
				else if (dir == 1)
					a = move_left(a, msk);
				else if (dir == 2)
					a = move_down(a, msk);
				else
					a = move_right(a, msk);
			}
			b = b & (b ^ a);
		} else {
			if (p < 0) {
				b = counterclockwise(b);
			} else {
				if (dir == 0)
					b = move_up(b, msk);
				else if (dir == 1)
					b = move_left(b, msk);
				else if (dir == 2)
					b = move_down(b, msk);
				else
					b = move_right(b, msk);
			}
			a = a & (a ^ b);
		}
		//print_field(a, b);
		//printf("===============\n");
	}
	print_field(a, b);
}