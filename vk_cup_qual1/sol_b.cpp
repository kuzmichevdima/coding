#include <cstdio>
#include <vector>
#include <string.h>
#include <cstdlib>
#include <iostream>
#include <algorithm>

using namespace std;

int p[1000], a[1000];
int cur = 1;
int n;

bool cmp(int x, int y) {
    return a[x] > a[y];
}

int main (){
    
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        p[i] = i;
    }
    sort(p+1, p + n, cmp);
    vector<pair<int, int> > ans;
    for(int i = 0; i < cur && cur < n; i++) {
        for(int j = 0; j < a[p[i]] && cur < n; j++) {
            ans.push_back({p[i] + 1, p[cur++]+1});
        }
        
    }
    if (cur == n) {
        cout << ans.size() << endl;
        for(auto x : ans)
            cout << x.first << " " << x.second << endl;
    } else {
        cout << -1 << endl;
    }
    
}
