#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

struct treap {
    treap *right, *left;
    long long sum, size, val, prior;
    treap() {}
    treap(long long val): val(val), size(1), sum(val), prior(rand()), left(NULL), right(NULL) {}
    
    void recalc() {
        size = (right == NULL ? 0: right -> size) + (left == NULL ? 0: left -> size) + 1;
        sum = (right == NULL ? 0: right -> val) + (left == NULL ? 0: left -> val) + val;
    }
    ~treap() {
        delete left;
        delete right;
    }
};

void merge(treap *L, treap *R, treap *&T) {
    if (L == NULL && R == NULL)
    {
        T = NULL;
        return;
    }
    if (L == NULL)
    {
        T = R;
        return;
    }
    if (R == NULL)
    {
        T = L;
        return;
    }
    if (L -> prior <= R -> prior)
    {
        T = L;
        merge(T -> right, R, T -> right);
    }
    else
    {
        T = R;
        merge(L, R -> left, R -> left);
    }
    T -> recalc();
}	

void split(treap *T, treap *&L, treap *&R, long long x, long long passed) {
    if (T == NULL)
    {
        L = NULL;
        R = NULL;
        return;
    }
    long long ind = (T -> left == NULL ? 0: T -> left -> size) + passed + 1;
    if (ind > x)
    {
        R = T;
        split(R -> left, L, R -> left, x, passed);
        
    }
    else
    {
        L = T;
        split(L -> right, L -> right, R, x, ind);
        
    }
	if (L != NULL)
		L -> recalc();
	if (R != NULL)
		R -> recalc();
}

void add(treap *&T, long long ind, long long x) {
    treap *T1, *T2, *T3;
    split(T, T1, T2, ind, 0);
    merge(T1, new treap(x), T3);
    merge(T3, T2, T);
}

long long get_sum(treap *&T, long long l, long long r) {
    long long ans;
    treap *T1, *T2, *T3, *T4;
    split(T, T1, T2, l - 1, 0);
    split(T2, T3, T4, r - l + 1, 0);
    ans = (T3 == NULL ? 0: T3 -> sum);
    merge(T3, T4, T2);
    merge(T1, T2, T);
    return ans;
}

void replace(treap *&n, treap *&m, long long l, long long r, long long i, long long j)
{
    treap *T1, *T2, *T3, *T4;
    split(n, T1, T2, l - 1, 0);
    split(T2, T3, T4, r - l + 1, 0);
    
    treap *T5, *T6, *T7, *T8;
    split(m, T5, T6, i - 1, 0);
    split(T6, T7, T8, r - l + 1, 0);
    
    swap(T3, T7);
    merge(T7, T8, T6);
    merge(T5, T6, m);
    
    merge(T3, T4, T2);
    merge(T1, T2, n);
}

void print(treap *T)
{
    if (T == NULL)
        return;
    else
    {
        print(T -> left);
        cout << T -> sum << " ";
        print(T -> right);
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    
    treap *root_f, *root_s;
    
    long long n, m, a, t = 0;
    long long z, l, r;
    
    while (cin >> n >> m)
    {
        root_f = NULL;
        root_s = NULL;
        if (n == 0 && m == 0)
            break;
        
        for (long long i = 1; i <= n; ++i)
        {
            cin >> a;
            if (i % 2 == 0)
                add(root_f, (i - 1) / 2, a);
            else
                add(root_s, (i - 1) / 2, a);
        }
        //print(root_f);
        //print(root_s);
        cout << "Swapper " << (++t) << ':' << endl;
        for (long long i = 0; i < m; ++i)
        {
            cin >> z >> l >> r;
            if (z == 1)
                replace(root_f, root_s, (l + 1) / 2, r / 2, l / 2 + 1, (r + 1) / 2);
            else {
                cout << get_sum(root_f, (l + 1) / 2, r / 2) + get_sum(root_s, l / 2 + 1, (r + 1) / 2) << endl;
            }
            
        }
    }
    return 0;
}