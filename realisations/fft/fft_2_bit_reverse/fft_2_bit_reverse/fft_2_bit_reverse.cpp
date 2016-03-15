#define _USE_MATH_DEFINES
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
#include <complex>

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

typedef complex <double> base;

int get_rev(int x, int lg)
{
	int ret = 0;
	forn(i, lg)
	{
		if (x & (1 << i))
			ret |= (1 << (lg - i - 1));
	}
	return ret;
}

void fft(vector <base> & a, bool flag)
{
	int n = a.size();
	int lg = 0;
	while((1 << lg) < n)
		lg++;
	forn(i, n)
	{
		int r = get_rev(i, lg);
		if (i > r)
			swap(a[i], a[r]);
	}
	for (int len = 2; len <= n; len *= 2)
	{
		double angle = 2 * M_PI / len;
		if (flag)
			angle *= (-1);
		base wlen(cos(angle), sin(angle));
		for(int i = 0; i < n; i += len)
		{
			base w(1);
			for (int j = 0; j < len / 2; j++)
			{
				base first = a[i + j];
				base second = a[i + j + len / 2] * w;
				a[i + j] = first + second;
				a[i + j + len / 2] = first - second;
				w *= wlen;
			}
		}
	}
	if (flag)
		forn(i, n)
			a[i] /= n;
}

void read(vector <base> & a, bool & flag)
{
	string s;
	cin >> s;
	int start;
	if (s[0] == '-')
	{
		start = 1;
		flag = true;
	}
	else
	{
		start = 0;
		flag = false;
	}
	for(int j = s.length() - 1; j >= start; j--)
	{
		complex <double> tmp(s[j] - '0', 0);
		a.pb(tmp);
	}
}

int main()
{
	freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	vector <base> a, b;
	bool flaga, flagb;
	read(a, flaga);
	read(b, flagb);

	int n = 1;
	while(n < a.size() || n < b.size())
		n *= 2;
	n *= 2;
	a.resize(n);
	b.resize(n);

	fft(a, false);
	fft(b, false);

	forn(j, n)
		a[j] = a[j] * b[j];
	fft(a, true);

	int carry = 0;
	vi answer;
	bool was_not_zero = false;
	forn(j, n)
	{
		int c1 = int(a[j].real() + 0.5);
		int c = (c1 + carry) % 10;
		//if (was || c != 0)
		//{
			answer.pb(c);
			if (c != 0)
				was_not_zero = true;
			
		//}
		carry = (c1 + carry) / 10;
	}
	while(carry != 0)
	{
		answer.pb(carry % 10);
		carry /= 10;
	}
	if (!was_not_zero)
	{
		printf("0");
		exit(0);
	}
	bool was = false;
	if (flaga ^ flagb)
		printf("-");
	for (int j = answer.size() - 1; j >= 0; j--)
	{
		if (answer[j] != 0 || was)
		{
			printf("%d", answer[j]);
			was = true;
		}
	}
	
	return 0;
}