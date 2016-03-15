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

void fft(vector <base> & a, bool flag)
{
	int n = a.size();
	if (n == 1)
		return;
	vector <base> a0(n / 2), a1(n / 2);
	forn(j, n / 2)
	{
		a0[j] = a[j * 2];
		a1[j] = a[j * 2 + 1];
	}
	fft(a0, flag);
	fft(a1, flag);
	base w(1);
	double angle = 2.0 * M_PI / (double)n;
	if (flag)
		angle = -angle;
	base wn(cos(angle), sin(angle));
	forn(k, n / 2)
	{
		a[k] = a0[k] + w * a1[k];
		a[k + n / 2] = a0[k] - w * a1[k];
		if (flag)
		{
			a[k] /= 2;
			a[k + n / 2] /= 2;
		}
		w *= wn;
	}
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