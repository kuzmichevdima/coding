#include <iostream>
#include <cstdio>

using namespace std;

struct treap {
    int p, val;
    treap *right, *left;
    treap(){}
    treap(int val): p(rand()), val(val), left(NULL), right(NULL) {}
};

void split(treap *n, treap *&L, treap *&R, int x) {
    if (n == NULL)
    {
        L = NULL;
        R = NULL;
        return;
    }
    if (n -> val > x)
    {
        R = n;
        split(R -> left, L, R -> left, x);
    }
    else
    {
        L = n;
        split(L -> right, L -> right, R, x);
    }
}

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
    if (L -> p <= R -> p)
    {
        T = L;
        merge(T -> right, R, T -> right);
    }
    else
    {
        T = R;
        merge(L, T -> left, T -> left);
    }
}

void add(treap *&T, int x) {
    treap *T1, *T2, *T3, *T4, *T5, *T6, *T7;
    split(T, T1, T2, x - 1);
    split(T2, T3, T4, x + 1);
    
    if (T3 != NULL)
        return;
    
    
    merge(T1, new treap(x), T5);
    merge(T5, T4, T7);
    T = T7;
}

int next(treap *T, int x) {
    treap *T1, *T2, *T3;
    int ans;
    split(T, T1, T2, x - 1);
    
    if (T2 == NULL)
    {
        cout << -1 << endl;
        ans = -1;
    }
    else
    {
        T3 = T2;
        while (T3 -> left != NULL)
            T3 = T3 -> left;
        cout << T3 -> val << endl;
        ans = T3 -> val;
    }
    return ans;
}

int main() {
	freopen("input.txt", "r", stdin);
    int n, a, y = 0;
    char cm;
    scanf("%d", &n);
    treap *root = NULL;
    
    for (int i = 0; i < n; ++i)
    {
        cin >> cm >> a;
        if (cm == '+')
        {
            add(root, a + y);
            y = 0;
        }
        else
        {
            y = next(root, a);
        }
    }
    
    return 0;
}







