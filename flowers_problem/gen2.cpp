#include <iostream>
#include "testlib.h"
#include <cstdio>

using namespace std;

int X = 1e9;
int T = 1e9;
const int K = 6;

int main(int argc, char** argv){

	registerGen(argc, argv, 1);
    if (argc != 2 && argc != 3 && argc != 4) {
        cerr << "invalid number of arguments" << endl;
        exit(0);
    }
    int n = atoi(argv[1]);
    if (argc == 3) {
        T = X = atoi(argv[2]);
    }
    else if (argc == 4) {
        X = atoi(argv[2]);
        T = atoi(argv[3]);
    }
    printf("%d\n", n);
    int L, R;
    int mod = rnd.next(0, 2);
    if (mod == 0) {
        L = -T / 10;
        R = T;
    }
    else if (mod == 1) {
        L = -T;
        R = T / 10;
    } else {
        L = -T;
        R = T;
    }
    for (int i = 1; i <= n; i++) {
        int x = rnd.next(-X, X), t;
        int bound = (x > 0 ? T : R);
        if (false) {
            t = abs(x) + 1;
        } else {
            if (rnd.next(0, 1) == 0)
                t = T;
            else {
                if (abs(x) + 1 <= bound && rnd.next(0, K) != 0) {
                    t = rnd.next(abs(x) + 1, bound);
                }
                else {
                    t = rnd.next(0, bound);
                }
            }
        }
        printf("%d %d\n", x, t);
    }
	return 0;
}
