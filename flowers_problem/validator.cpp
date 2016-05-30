#include <bits/stdc++.h>
#include "testlib.h"

using namespace std;

const int X = 1e9;
const int T = 1e9;
const int MAXN = 2e5;

int main(){

	registerValidation();
	int n = inf.readInt(1, MAXN, "Flowers number");
	inf.readEoln();
	for (int i = 0; i < n; i++){
		int x = inf.readInt(-X, X, "t");
        inf.readSpace();
        int t = inf.readInt(-T, T, "x");
        if (i != n) 
            inf.readEoln();
	}
	inf.readEof();

	return 0;
}
