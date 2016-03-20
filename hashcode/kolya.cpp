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

struct Photo
{
    int phi, lambda, turn, id;

    Photo(int phi = 0, int lambda = 0, int turn = 0, int id = 0) :
        phi(phi), lambda(lambda), turn(turn), id(id) { };
};

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

		for (int _ = 0; _ < (int)change_dir.size(); _++){
			int l = change_dir[_];
			int r = (_ + 1 < (int)change_dir.size() ? change_dir[_ + 1] : T);
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

int score(vector <Collection> & cols, vector <Photo> & photos)
{
 //   printf("photos size = %d\n", photos.size());
    int result = 0;
    map <pair <int, int>, vector <int> > M;
    for (int i = 0; i < (int)photos.size(); i++)
        M[make_pair(photos[i].phi, photos[i].lambda)].push_back(photos[i].turn);
    for (auto col : cols)
    {
        bool col_ok = true;
        for (int part = 0; part < (int)col.t.size(); part++)
        {
            pair <int, int> p = col.r[part];
            if (M.find(p) == M.end())
            {
                col_ok = false;
                break;
            }
            vector <int> & v = M[p];
            bool part_covered = false;
            for (int turn : v)
            {
                bool found_seg = false;
                for (pair <int, int> seg : col.t)
                {
                    if (turn >= seg.first && turn <= seg.second)
                    {
                        found_seg = true;
                        break;
                    }
                }
                if (found_seg)
                {
                    part_covered = true;
                    break;
                }
            }
            if (!part_covered)
            {
                col_ok = false;
                break;
            }
        }
        if (col_ok)
            result += col.val;
    }
    return result;
}

const int PACK_SIZE = 5;

int main(){

	int T = nxt();
	int S = nxt();
	vector<Satellite> sats(S);
	for (int i = 0; i < S; i++)
		sats[i].in(T, i);

	int C = nxt();
	vector<Collection> cols(C);
	for (int i = 0; i < C; i++)
		cols[i].in();

	// SOLUTION

	sort(all(cols), [](const Collection& x, const Collection& y){
		return (x.val > y.val);
	});

    vector <Photo> photos;
    for (int itt = 0; itt < (itn)cols.size(); itt += PACK_SIZE) {
        int msk_sz = min((int)cols.size() - itt, PACK_SIZE);
        int best = -1;
        vector<pair<pair<int, int>, pair<int, int> > > cli_best;
        for (int msk = 0; msk < (1 << msk_sz); msk++) {
            bool ok = true;
            int sum_score = 0;
            vector<pair<pair<int, int>, pair<int, int> > > cli;
            vector<pair<pair<int, int>, pair<const Collection&, int> > > r;
            for (int i = 0; i < msk_sz; i++) {
                if (msk & (1 << i)) {
                    const auto &col = cols[itt + i];
                    sum_score += col.val;
                    int j = 0;
                    for (auto p : col.r) {
                        r.push_back({ p, { col, j } });
                        j++;
                    }
                }
            }
            for (int ittq = 0; ittq < (int)r.size(); ittq++){
                auto pp = r[ittq];
                auto col = pp.second.first;
                auto p = pp.first;
                int i = 0;
                int t;
                while (i < S){
                    vector<int> v = sats[i].moments(p.first, p.second);
                    int j = 0;
                    while (j < (int)v.size() && !col.fit(v[j]))
                        j++;
                    if (j < (int)v.size()){
                        t = v[j];
                        break;
                    }
                    i++;
                }
                if (i < S){
                    sats[i].add_photo(t, p.first, p.second);
                    cli.push_back({{i, t}, { p.first, p.second }});
                } else {
                    //cerr << "t" << endl;
                    for (int j = 0; j < (int)cli.size(); j++){
                        pair<int, int> q = cli[j].first;
                        sats[q.first].del_photo(q.second, cli[j].second.first,
                                                cli[j].second.second);
                        ok = false;
                    }
                    //cerr << "T" << endl;
                    break;
                }
            }
            if (ok && sum_score > best) {
                    for (int j = 0; j < (int)cli_best.size(); j++){
                        pair<int, int> q = cli_best[j].first;
                        sats[q.first].del_photo(q.second, cli_best[j].second.first,
                                                cli_best[j].second.second);
                    }
                    cli_best.clear();
                    for (auto c : cli) {
                        cli_best.push_back(c);
                    }
                    best = sum_score;
            }
        }
	}

	for (auto sat : sats)
		sat.publish();
    printf("%d\n", (int)photos.size());
    for (Photo p : photos)
        printf("%d %d %d %d\n", p.phi, p.lambda, p.turn, p.id);
    //cerr << score(cols, photos);

	return 0;
}

