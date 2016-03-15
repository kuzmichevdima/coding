#include <iostream>
#include <cstdio>
#include <cmath>

#define y1 y123767623

using namespace std;

long double eps = 1e-9;

//#define PI 3.14159265

struct Vector {
    long double x, y;
    Vector() {}
    Vector(long double x, long double y): x(x), y(y) {}
    
    Vector operator-(Vector p) {return Vector(x - p.x, y - p.y);}
    long double Length() {return sqrt(x * x + y * y);}
};

long double r;

int A, B, C, D, E;
    long double d, x1, y1, x2, y2, x3, y3, a, b;



inline long double sqr(long double x)
{
	return x * x;
}

void check(long double x, long double y)
{
	printf("%.5Lf\n", sqrt(sqr(x - E / 2) + sqr(y - D / 2)));
}

int main() {
	freopen("input.txt", "r", stdin);
    
    scanf("%d %d %d %d %d", &A, &B, &C, &D, &E);
    
    if (A > B)
    {
        swap(A, B);
        if (A > C)
        {
            swap(A, C);
        }
        if (B > C)
        {
            swap(B, C);
        }
    }
    else
    {
        if (A > C)
        {
            swap(A, C);
        }
        if (B > C)
        {
            swap(B, C);
        }
    }
    if (D > E)
    {
        swap(D, E);
    }
    
    if (A <= D && B <= E)
    {
        printf("YES\n");
    }
    else
    {
        d = A * A + B * B; r = sqrt(d) / 2.0;
		printf("r=%.5Lf\n", r);
        x1 = E / 2.0 - sqrt(r * r - ((D / 2.0) * (D / 2.0)));
        y1 = D;
		check(x1, y1);
        x2 = 0.0;
        y2 = D / 2 + sqrt(r * r - ((E / 2.0) * (E / 2.0)));
		check(x2, y2);
        x3 = E / 2 + sqrt(r * r - (D / 2.0) * (D / 2.0));
        y3 = 0.0;
		check(x3, y3);
        
        //cout << ((Vector(x1, y1) - Vector(x3, y3)).Length() / 2.0) << endl;
        a = (Vector(x1, y1) - Vector(x2, y2)).Length();
        b = (Vector(x2, y2) - Vector(x3, y3)).Length();

        if (a - A >= eps && b - B >= eps)
        {
            printf("YES\n");
        }
        else
        {
            printf("NO\n");
        }
        
    }
    
    return 0;
}