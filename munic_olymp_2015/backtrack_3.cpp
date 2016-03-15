#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <iostream>
#include <cassert>
#include <cmath>
#include <string>
#include <queue>
#include <set>
#include <map>
#include <cstdlib>

using namespace std;

#define INF 1e+9
#define mp make_pair
#define pb push_back
#define fi first
#define fs first
#define se second
#define i64 long long
#define li long long
#define lint long long
#define pii pair<int, int>
#define vi vector<int>

#define forn(i, n) for (int i = 0; i < (int)n; i++)
#define fore(i, b, e) for (int i = (int)b; i <= (int)e; i++)

#define MaxN 200000

using namespace std;

int music[MaxN];
int res[MaxN][2];
int n;

const int dx[5] = {-1, 0, 1, 0, 0};
const int dy[5] = {0, 1, 0, 0, -1};
const int counter_limit = 3e7;

int counter;
int perm[5];

bool check(int x, int a, int b) {
	return (x == a || x == b);
}

bool play(int tab1, int tab2, int note) {
//    printf("play note = %d\n", note);
	if (note == n - 1) {
		res[note][0] = tab1;
		res[note][1] = tab2;
		return true;
	}
	
	counter++;
	if (counter > counter_limit) {
//        printf("counter = %d\n", counter);
//		cout << "NO" << endl;
        return false;
		//exit(0);
	}
	
    forn(move, 5)
    {
        int newx = tab1 + dx[perm[move]];
        int newy = tab2 + dy[perm[move]];
        if (newx >= 1 && newx <= 7 && newy >= 1 && newy <= 7 &&
            check(music[note + 1], newx, newy) && play(newx, newy, note + 1))
            {
                res[note][0] = tab1;
                res[note][1] = tab2;
                return true;
            }
    }
	
	return false;
}

int main() {
	
    cin >> n;
	for (int j = 0; j < n; j++)
		scanf("%d", &music[j]);
	
    forn(j, 5)
        perm[j] = j;
    srand(n);
    random_shuffle(perm, perm + 5);
    counter = 0;		
    bool ans = false;
    for (int s = 1; s <= 7; s++)
        if ( s != music[0] && (ans = play(music[0], s, 0)) ) break;
		
	if (ans) {
		cout << "YES" << endl;
		for (int i = 0; i < n; i++) 
		    printf("%d %d\n", res[i][0], res[i][1]);
	} else {
		cout << "NO" << endl;
	}
    
}
