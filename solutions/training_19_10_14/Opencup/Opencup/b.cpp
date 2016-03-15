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

string s;
int a[100100];
int na, nb;
int b[100100];

void Less() {
	cout << "<" << endl;
	exit(0);
}

void Greater() {
	cout << ">" << endl;
	exit(0);
}

int main()
{
	freopen("ccf.in", "r", stdin);
	freopen("ccf.out", "w", stdout);
	
	cin >> na;
	for (int i = 0; i <= na; i++)
		cin >> a[i];
	cin >> nb;
	for (int i = 0; i <= nb; i++)
		cin >> b[i];

	/*for (int i = 0; i <= na; i++)
		cout << a[i] << ' ';
	cout << endl;
	for (int i = 0; i < nb; i++)
		cout << b[i] << ' ';
	cout << endl;*/
	na++, nb++;
	for (int i = 0; i < max(na, nb); i++) {
		if (i >= na)
			a[i] = 2000000000;
		if (i >= nb)
			b[i] = 2000000000;
	}

	for (int i = 0; i < max(na, nb); i++) {
		if (i % 2 == 0) {
			if (a[i] > b[i])
				Greater();
			if (a[i] < b[i])
				Less();
		} else {
			if (a[i] < b[i])
				Greater();
			if (a[i] > b[i])
				Less();
		}
	}

	cout << "=" << endl;
	return 0;
}