#include <cstdio>
#include <vector>
#include <string.h>
#include <cstdlib>
#include <iostream>
using namespace std;

const int MAXSIZE = 100;
const int base = (1 << 14);

int d[base];
int masks[base];
int size = 0;
int main (){
    int n, k;
    scanf("%d%d", &n, &k);
    
    for(int i = 0; i < base; i++) {
        if (__builtin_popcount(i) == k) {
            masks[size++] = i;
        }
    }
    long long ans = 0;
    for(int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        for(int j = 0; j < size; j++)
            ans += d[x ^ masks[j]];
        d[x]++;
    }
    cout << ans << endl;
}
