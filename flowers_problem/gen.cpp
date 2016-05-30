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
    
    for (int i = 1; i <= n; i++) {
        int x = rnd.next(-X, X), t;
        if (abs(x) + 1 <= T && rnd.next(0, K) != 0) {
            t = rnd.next(abs(x) + 1, T);
        }
        else t = rnd.next(0, T);
        printf("%d %d\n", x, t);
    }
	return 0;
}
