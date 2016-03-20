#include <bits/stdc++.h>

#define itn int
#define LL long long
#define pb push_back
#define mp make_pair
#define x first
#define y second
#define all(x) (x).begin(), (x).end()

using namespace std;

typedef pair<int, int> pii;

inline int nxt(){
	int x;
	scanf("%d", &x);
	return x;
}

const int es = 15;	// earth speed
const int gr = 3600;

// directed
pii dist(const pii& p, const pii& q){
	int sec = q.second - p.second;
	sec %= (360 * gr);
	if (sec < 0)
		sec += 360 * gr;
	if (sec >= 180 * gr)
		sec -= 360 * gr;
	return {q.first - p.first, sec};
}

pii operator +(const pii& p, const pii& q){
	int nl = p.second + q.second;
	nl %= (360 * gr);
	if (nl < 0)
		nl += 360 * gr;
	if (nl >= 180 * gr)
		nl -= 360 * gr;
	return make_pair(p.first + q.first, nl);
}

pii find_good_moments(const vector<pii>& a, int l, int r,
								 int _l, int _r){
	if (_l <= _r){
		auto q = lower_bound(a.begin() + l, a.begin() + r, mp(_l, 0));
		auto w = upper_bound(a.begin() + l, a.begin() + r, mp(_r, 0));
		return make_pair(q - a.begin(), w - a.begin());
	} else {
		auto q = lower_bound(a.begin() + l, a.begin() + r, mp(_l, 0),
							greater<pii>());
		auto w = upper_bound(a.begin() + l, a.begin() + r, mp(_r, 0),
							greater<pii>());
		return make_pair(q - a.begin(), w - a.begin());
	}
}

struct Photo{
	int phi, lambda, t, num;

	Photo(){}

	Photo(int phi, int lambda, int t, int num):phi(phi),lambda(lambda),
		t(t),num(num){};

	void out() const {
		cout << phi << " " << lambda << " " << t << " " << num << "\n";
	}
};

struct Satellite{
	int T;
	int v, w, d;
	int num;
	vector<pii> pos;
	vector<int> change_dir;
	multiset<pair<int, pii>> taken;

	Satellite(){}

	void in(int _T, int nm){
		T = _T;
		num = nm;
		int phi = nxt();
		int lambda = nxt();
		v = nxt();
		w = nxt();
		d = nxt();
		taken.insert(make_pair(0, make_pair(0, 0)));
		change_dir.push_back(0);
		pos.resize(T + 1);
		pos[0] = {phi, lambda};

		for (int i = 0; i < T; i++){
			if (abs(phi + v) <= 90 * gr){
				phi += v;
				lambda -= es;
			} else if (phi + v > 90 * gr){
				phi = 180 * gr - phi - v;
				lambda = -180 * gr + lambda - es;
				v = -v;
				change_dir.push_back(i + 1);
			} else if (phi + v < -90 * gr){
				phi = -180 * gr - phi - v;
				lambda = -180 * gr + lambda - es;
				v = -v;
				change_dir.push_back(i + 1);
			}
			lambda %= (360 * gr);
			if (lambda < 0)
				lambda += 360 * gr;
			if (lambda >= 180 * gr)
			lambda -= (360 * gr);

			pos[i + 1] = {phi, lambda};
		}
	}

	pii get(int t) const {
		return pos[t];
	}

	pii operator [](int t) const {
		return pos[t];
	}

	bool check_photo(int t, int phi, int lambda) const {
		auto dlt = dist(pos[t], make_pair(phi, lambda));
		phi = dlt.first;
		lambda = dlt.second;
		if (abs(phi) > d || abs(lambda) > d)
			return false;
		auto p = make_pair(t, make_pair(phi, lambda));
		auto it = taken.upper_bound(p);
		if (it != taken.end()){
			int tt = it->first - t;
			if (abs(phi - it->second.first) > 1ll * w * tt)
				return false;
			if (abs(lambda - it->second.second) > 1ll * w * tt)
				return false;
		}
		--it;
		int tt = t - it->first;
		if (abs(phi - it->second.first) > 1ll * w * tt)
			return false;
		if (abs(lambda - it->second.second) > 1ll * w * tt)
			return false;
		return true;
	}

	void add_photo(int t, int phi, int lambda){
		auto dlt = dist(pos[t], make_pair(phi, lambda));
		phi = dlt.first;
		lambda = dlt.second;
		auto p = make_pair(t, make_pair(phi, lambda));
		taken.insert(p);
	}

	void del_photo(int t, int phi, int lambda){
		auto dlt = dist(pos[t], make_pair(phi, lambda));
		phi = dlt.first;
		lambda = dlt.second;
		auto p = make_pair(t, make_pair(phi, lambda));
		taken.erase(taken.find(p));
	}

	void publish() const {
		for (auto p : taken){
			int t = p.first;
			auto q = p.second + pos[t];
			cout << q.first << " " << q.second << " " << t << " " << num << "\n";
		}
	}

	int earliest(int phi, int lambda){
		auto it = taken.begin();
		auto nit = it;
		++nit;
		pii pp = make_pair(phi, lambda);
		for (itn t = 0; t < T; t++){
			while (nit != taken.end() && nit->first <= t)
				++it, ++nit;
			auto p = dist(pos[t], pp);
			int old = it->first;
			if (abs(p.first) > d || abs(p.second) > d)
				continue;
			auto q = it->second;
			if (abs(q.first - p.first) > 1ll * w * (t - old))
				continue;
			if (abs(q.second - p.second) > 1ll * w * (t - old))
				continue;
			if (nit != taken.end()){
				old = nit->first;
				q = nit->second;
				if (abs(q.first - p.first) > -1ll * w * (t - old))
					continue;
				if (abs(q.second - p.second) > -1ll * w * (t - old))
					continue;
			}
			return t;
		}
		return -1;
	}

	vector<int> moments(int phi, int lambda){
		vector<int> res;
		auto it = taken.begin();
		auto nit = it;
		++nit;
		pii pp = make_pair(phi, lambda);

		for (int _ = 0; _ < change_dir.size(); _++){
			int l = change_dir[_];
			int r = (_ + 1 < change_dir.size() ? change_dir[_ + 1] : T);
			int _l = (pos[r].first < pos[l].first) ? d : -d;
			int _r = -_l;
			_l += phi, _r += phi;
			auto xui = find_good_moments(pos, l, r, _l, _r);

			for (int t = xui.first; t < xui.second; t++){
				while (nit != taken.end() && nit->first <= t)
					++it, ++nit;
				auto p = dist(pos[t], pp);
				int old = it->first;
				if (abs(p.first) > d || abs(p.second) > d)
					continue;
				auto q = it->second;
				if (abs(q.first - p.first) > 1ll * w * (t - old))
					continue;
				if (abs(q.second - p.second) > 1ll * w * (t - old))
					continue;
				if (nit != taken.end()){
					old = nit->first;
					q = nit->second;
					if (abs(q.first - p.first) > -1ll * w * (t - old))
						continue;
					if (abs(q.second - p.second) > -1ll * w * (t - old))
						continue;
				}
				res.push_back(t);
			}
		}

		return res;
	}
};

struct Collection{
	int val;
	vector<pii> t;
	vector<pii> r;

	Collection(){}

	void in(){
		val = nxt();
		int L = nxt();
		int R = nxt();
		r.resize(L);
		for (int i = 0; i < L; i++){
			r[i].first = nxt();
			r[i].second = nxt();
		}
		t.resize(R);
		for (int i = 0; i < R; i++){
			t[i].first = nxt();
			t[i].second = nxt();
		}
		sort(all(t));
	}

	void out(int num, int sat, int t) const {
		cout << r[num].first << " " << r[num].second << " " << t << " " << sat << "\n";
	}

	bool fit(int tt) const {
		pii p = make_pair(tt, tt);
		auto it = upper_bound(all(t), p);
		if (it == t.begin())
			return false;
		--it;
		return (tt >= it->first && tt <= it->second);
	}
};

long long max_dist(const Collection & col)
{
    long long maxx = 1;
    for (int i = 0; i < (int)col.r.size(); i++)
        for (int j = i + 1; j < (int)col.r.size(); j++)
        {
            long long delta_x = abs(col.r[j].first - col.r[i].first);
            long long delta_y = abs(col.r[j].second - col.r[i].second);
            maxx = max(maxx, delta_x * delta_x + delta_y * delta_y);
        }
    return maxx;
}


struct System{
	int T;
	int S, C;
	vector<Satellite> sats;
	vector<Collection> cols;
	vector<vector<pii>> got;
	int score;
	string filename;

	System(string filename):filename(filename){
		freopen((filename + ".in").c_str(), "r", stdin);
		T = nxt();
		S = nxt();
		sats.resize(S);
		for (int i = 0; i < S; i++)
			sats[i].in(T, i);

		C = nxt();
		cols.resize(C);
		for (int i = 0; i < C; i++)
			cols[i].in();

		fclose(stdin);

sort(all(cols), [](const Collection& x, const Collection& y){
		//return (log(max_dist(x)) * x.val > log(max_dist(y)) * y.val);
        //return  x.val > y.val;
//        return pow(max_dist(x), 0.5) * x.val / x.r.size() > pow(max_dist(y), 0.5) * y.val / y.r.size();
        //0.4 is best
        return (double)x.val / (x.r.size() + 4) > (double)y.val / (y.r.size()) + 4);
        //return (double)x.val * pow(max_dist(x), 0.5) / (x.r.size() + 7) > (double)y.val * pow(max_dist(x), 0.5) / (y.r.size() + 7);

	});

		got.resize(C);
		for (int i = 0; i < C; i++){
			got[i].resize(cols[i].r.size(), {-1, -1});
		}
	}

	void solve(){
		score = 0;
		for (const Collection& col : cols){
			vector<pii> cli;
			bool ok = true;
			for (auto p : col.r){
				int i = 0;
				int t;
				int curr = -1;
				while (i < S){
					vector<int> v = sats[i].moments(p.first, p.second);
					int j = 0;
					while (j < v.size() && !col.fit(v[j]))
						j++;
					if (j < v.size()){
						if (curr == -1 || sats[i].taken.size() <
							sats[curr].taken.size()){
							t = v[j];
							curr = i;
						}
					}
					i++;
				}
				if (curr > -1){
					i = curr;
					sats[i].add_photo(t, p.first, p.second);
					cli.push_back({i, t});
				} else {
					for (int j = 0; j < cli.size(); j++){
						pii q = cli[j];
						sats[q.first].del_photo(q.second, col.r[j].first,
												col.r[j].second);
					}
					ok = false;
					break;
				}
			}
			if (ok)
				score += col.val;
		}
	}

	void publish() const {
		for (auto sat : sats)
			sat.publish();
	}

	pair<int, vector<Photo>> get_current() const {
		vector<Photo> res;
		for (const auto& sat : sats){
			for (auto p : sat.taken){
				res.emplace_back(p.second.first, p.second.second, p.first, sat.num);
			}
		}
		return mp(score, res);
	}

	void reset(){
		for (int i = 0; i < S; i++){
			sats[i].taken.clear();
			sats[i].taken.insert(mp(0, mp(0, 0)));
		}
		got.clear();
		got.resize(C);
		for (int i = 0; i < C; i++){
			got[i].resize(cols[i].r.size(), {-1, -1});
		}
	}

	void random_first(){
		vector<int> v;
		for (int i = 0; i < C; i++){
			if (got[i][0].first == -1){
				v.push_back(i);
			}
		}
		random_shuffle(all(v));
		v.resize(min((int)v.size(), 3));
		sort(all(v));
		for (int j : v){
			auto col = cols[j];
			cols.erase(cols.begin() + j);
			cols.insert(cols.begin(), col);
		}
		sort(cols.begin() + v.size(), cols.end(), [](const Collection& x,
			const Collection& y){
			return (x.val > y.val);
		});

	}

	void out() const {
		freopen((filename + ".out").c_str(), "w", stdout);
		publish();
		fclose(stdout);
	}
};

int main(int argc, char** argv){

	assert(argc >= 2);

	System sys((string)(argv[1]));
	sys.solve();

	cerr << "Score: " << sys.score << "\n";
	auto cur = sys.get_current();
	sys.out();

	for (int i = 0; i < 1000; i++){
		sys.random_first();
		sys.reset();
		sys.solve();
		auto tmp = sys.get_current();
		if (tmp.first > cur.first){
			cerr << "New score: " << tmp.first << "\n";
			sys.out();
			cur = tmp;
		}
	}

	return 0;
}
