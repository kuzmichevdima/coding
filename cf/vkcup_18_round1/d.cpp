#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#define DEBUG(args...) { vector<string> _v = aux::split(#args, ','); aux::err(_v.begin(), args); }
#else
#define DEBUG(args...) { }
#endif

namespace aux{

template<std::size_t...> struct seq{};

template<std::size_t N, std::size_t... Is>
struct gen_seq : gen_seq<N-1, N-1, Is...>{};

template<std::size_t... Is>
struct gen_seq<0, Is...> : seq<Is...>{};

template<class Ch, class Tr, class Tuple, std::size_t... Is>
void print_tuple(std::basic_ostream<Ch,Tr>& os, Tuple const& t, seq<Is...>) {
  using swallow = int[];
  (void)swallow{0, (void(os << (Is == 0? "" : ", ") << std::get<Is>(t)), 0)...};
}


vector<string> split(const string& s, char c) {
	vector<string> v;
	stringstream ss(s);
	string x;
	while (getline(ss, x, c)) {
		v.emplace_back(x);
    }
    return v;
}

void err(vector<string>::iterator it) {}

template<typename T, typename... Args>
void err(vector<string>::iterator it, T a, Args... args) {
	cerr << it -> substr((*it)[0] == ' ', it -> length()) << " = " << a << '\n';
	err(++it, args...);
}
} // aux::

template<class Ch, class Tr, class... Args>
auto operator<<(std::basic_ostream<Ch, Tr>& os, std::tuple<Args...> const& t)
    -> std::basic_ostream<Ch, Tr>& {
    os << "(";
    aux::print_tuple(os, t, aux::gen_seq<sizeof...(Args)>());
    return os << ")";
}

template<class S, class T>
std::ostream & operator<<(std::ostream & o, const std::pair<S,T> & p) {
    return o << "(" << p.first << ", " << p.second << ")";
}

template<class T>
std::ostream & operator<<(std::ostream & os, const std::vector<T> & vec) {
    os<<"[";
    if(vec.size() != 0) {
        std::copy(vec.begin(), vec.end()-1, std::ostream_iterator<T>(os, ", "));
        os<<vec.back();
    }
    return os<<"]";
}

template<class T>
std::ostream & operator<<(std::ostream & os, const std::set<T> & s) {
    os<<"{";
    if(s.size() != 0) {
        std::copy(s.begin(), --s.end(), std::ostream_iterator<T>(os, ", "));
        os<<*(--s.end());
    }
    return os<<"}";
}

template <class It, char Delim = ' '>
void print_range(It a, It b) {
    for (auto it = a; it != b; it++) {
        cout << *it << Delim;
    }
    cout  << "\n";
}

template<class T> bool uin(T &a, T b) { return a > b ? (a = b, true) : false; }
template<class T> bool uax(T &a, T b) { return a < b ? (a = b, true) : false; }

struct Test {
    Test(int test_number) : test_number(test_number) {
    }

    int test_number;

    void solve();

    void run() {
        auto start = chrono::steady_clock::now();
        solve();
        auto end = chrono::steady_clock::now();
        auto diff = end - start;
        cerr << "Running time: " << chrono::duration_cast<chrono::milliseconds>(diff).count() << "ms\n";
    }
};


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cout.setf(ios::fixed);
    cout.precision(9);

    cerr.setf(ios::fixed);
    cerr.precision(3);

    int num_tests = 1;
    for (int i = 1; i <= num_tests; i++) {
        Test cur(i);
        cur.run();
    }
}


////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////


const int MAX_N = 100005; // TODO
const int INF = 0x3f3f3f3f;
const int MOD = 1000000007;

string s, t;
int q, suf_a[2][MAX_N], cnt_d[2][MAX_N];

int count_d(int q, int a, int b) {
    if (a == 0) {
        return cnt_d[q][b];
    }
    return cnt_d[q][b] - cnt_d[q][a - 1];
}

bool can_sol(int a, int b, int c, int d) {
    int sa = min(b - a + 1, suf_a[0][b]);
    int ta = min(d - c + 1, suf_a[1][d]);
    if (sa < ta || (sa - ta) % 3 != 0) {
        return false;
    }
    if (sa == b - a + 1) {
        return ta == d - c + 1;
    }
    int cd1 = count_d(1, c, d);
    int cd2 = count_d(0, a, b);
    return cd1 >= cd2 && (cd1 - cd2) % 2 == 0;
}

void Test::solve() {
    cin >> s >> t;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == 'A') {
            suf_a[0][i] = (i == 0)? 1: suf_a[0][i - 1] + 1;
            cnt_d[0][i] = (i == 0)? 0: cnt_d[0][i - 1];
        } else {
            suf_a[0][i] = 0;
            cnt_d[0][i] = (i == 0)? 1: cnt_d[0][i - 1] + 1;
        }
    }
    for (int i = 0; i < t.size(); i++) {
        if (t[i] == 'A') {
            suf_a[1][i] = (i == 0)? 1: suf_a[1][i - 1] + 1;
            cnt_d[1][i] = (i == 0)? 0: cnt_d[1][i - 1];
        } else {
            suf_a[1][i] = 0;
            cnt_d[1][i] = (i == 0)? 1: cnt_d[1][i - 1] + 1;
        }
    }
    cin >> q;
    for (int i = 0; i < q; i++) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        --a, --b;
        --c, --d;
        cout << can_sol(a, b, c, d);
    }
    cout << endl;
}
