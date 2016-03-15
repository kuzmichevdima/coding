#include <iostream>
#include <string>
#include <set>

using namespace std;

void solve(int test);

set<string> q;
set<string> w;
set<string> color;
set<string> item;
set<string> c, it;

int main() {

	freopen("barabashka.in", "r", stdin);
	freopen("barabashka.out", "w", stdout);

	q.insert("white Barabashka");
	q.insert("blue book");
	q.insert("red chair");
	q.insert("gray mouse");
	q.insert("green bottle");

	color.insert("white");
	color.insert("blue");
	color.insert("red");
	color.insert("gray");
	color.insert("green");

	item.insert("Barabashka");
	item.insert("book");
	item.insert("chair");
	item.insert("mouse");
	item.insert("bottle");

	int n = 1;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 5; j++)
			solve(i + 1);
	}
}

void solve(int v) {
	string s;
	getline(cin, s);
	w.clear();
	it.clear();
	c.clear();
	string x = "";
	string last = "";
	string separ = "";
	s += " ";
	for (int i = 0; i < s.length(); i++) {
		if (isalpha(s[i])) 
			x += s[i];
		else {
			string pr = last + separ + x;
			separ = "";
			separ += s[i];
			//cout << pr << endl;
			if (q.find(pr) != q.end()) {
				cout << pr << endl;
				return;
			}
			if (color.find(last) != color.end())
				c.insert(last), it.insert(x);
			last = x;
			x = "";
		}
	}
	for (set<string>::iterator iter = q.begin(); iter != q.end(); iter++) {
		s = *iter;
		string s1, s2;
		s1 = s2 = "";
		int p = -1;
		for (int i = 0; i < s.length(); i++)
			if (s[i] == ' ') {
				p = i + 1;
				break;
			} else {
				s1 += s[i];
			}
		for (int i = p; i < s.length(); i++)
			s2 += s[i];
		if (c.find(s1) == c.end() && it.find(s2) == it.end()) {
			cout << s << endl;
			return;
		}
			
	}
}