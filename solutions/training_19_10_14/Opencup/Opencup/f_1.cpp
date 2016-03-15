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

const double eps = 1.0e-7;

struct Point
{
	int x;
	int y;
	Point(){}
	Point(Point s, Point f)
	{
		x = f.x - s.x;
		y = f.y - s.y;
	}
	int operator % (Point an)
	{
		return x * an.y - y * an.x;
	}
	double getDist(Point an)
	{
		return sqrt((double)(x - an.x) * (x - an.x) + (y - an.y) * (y - an.y));
	}
};

inline bool intersect_1dim(int s1, int f1, int s2, int f2)
{
	if (s1 > f1)
		swap(s1, f1);
	if (s2 > f2)
		swap(s2, f2);
	return max(s1, s2) <= min(f1, f2);
}

inline int sgn(int x)
{
	if (x == 0)
		return 0;
	return (x > 0 ? 1 : -1);
}

struct Seg
{
	Point p1;
	Point p2;
	Seg() {}
	Seg(Point _p1, Point _p2) : p1(_p1), p2(_p2) {}
	inline bool intersect(Seg an)
	{
		Point p3 = an.p1;
		Point p4 = an.p2;
		if (!intersect_1dim(p1.x, p2.x, p3.x, p4.x))
			return false;
		if (!intersect_1dim(p1.y, p2.y, p3.y, p4.y))
			return false;
		Point p1p3(p1, p3);
		Point p1p4(p1, p4);
		Point p1p2(p1, p2);
		if (sgn(p1p2 % p1p3) * sgn(p1p2 % p1p4) > 0)
			return false;
		Point p3p1(p3, p1);
		Point p3p4(p3, p4);
		Point p3p2(p3, p2);
		return sgn(p3p4 % p3p1) * sgn(p3p4 % p3p2) <= 0;
	}
};

Seg sides_seg[10];
Point p[10];

inline int get_area(vi list)
{
	int ret = 0;
	forn(j, list.size())
	{
		ret += p[list[j]] % p[list[(j + 1) % list.size()]];
	}
	return abs(ret);
}

int total_area;

inline bool check(int chosen, int end)
{
	if (chosen > end)
		swap(chosen, end);
	double D = p[chosen].getDist(p[end]);
	forn(u, 5)
		if ((u != chosen) && (u != end))
		{
			if (abs(p[u].getDist(p[chosen]) + p[u].getDist(p[end]) - D) < eps)
				return false;
		}
	Seg s1(p[chosen], p[end]);
	forn(side, 5)
	{
		int to = (side + 1) % 5;
		if (side == chosen || side == end || to == chosen || to == end)
			continue;
		if (s1.intersect(sides_seg[side]))
			return false;
	}
	vi first_part;
	fore(j, chosen, end)
		first_part.pb(j);
	vi second_part;
	fore(j, end, 4)
		second_part.pb(j);
	fore(j, 0, chosen)
		second_part.pb(j);
	int area1 = get_area(first_part);
	int area2 = get_area(second_part);
	return (area1 + area2 == total_area);
}

int main()
{
	freopen("pentagon.in", "r", stdin);
	freopen("pentagon.out", "w", stdout);
	int tests;
	scanf("%d", &tests);
	forn(test, tests)
	{
		forn(j, 5)
			scanf("%d%d", &p[j].x, &p[j].y);
		p[5] = p[0];
		forn(j, 5)
			sides_seg[j] = Seg(p[j], p[j + 1]);
		vi tmp;
		forn(j, 5)
			tmp.pb(j);
		total_area = get_area(tmp);
		int answer = 0;
		forn(chosen, 5)
		{
			bool f1 = check(chosen, (chosen + 2) % 5);
			bool f2 = check(chosen, (chosen - 2 + 5) % 5);
			if (f1 && f2)
				answer++;
		}
		printf("%d\n", answer);
	}

	return 0;
}