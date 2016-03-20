#include <bits/stdc++.h>
#define forn(i, n) for (int i = 0; i < (int)n; i++)
#define fore(i, b, e) for (int i = (int)b; i <= (int)e; i++)
#define all(x) (x).begin(), (x).end()
#define se second
#define fi first
#define mp make_pair
#define pb push_back
#define op operator
#define itn int
#define LL long long
#define pb push_back
#define mp make_pair
#define x first
#define y second
#define all(x) (x).begin(), (x).end()


using namespace std;

typedef vector <int> vi;
typedef pair<int, int> pii;
typedef long long i64;



inline int nxt(){
    int x;
    scanf("%d", &x);
    return x;
}
 
const int es = 15;  // earth speed
const int gr = 3600;
 
// directed
pair<int, int> dist(const pair<int, int>& p, const pair<int, int>& q){
    int sec = q.second - p.second;
    sec %= (360 * gr);
    if (sec >= 180 * gr)
        sec -= 360 * gr;
    return {q.first - p.first, sec};
}
 
pair<int, int> operator +(const pair<int, int>& p, const pair<int, int>& q){
    int nl = p.second + q.second;
    nl %= (360 * gr);
    if (nl >= 180 * gr)
        nl -= 360 * gr;
    return make_pair(p.first + q.first, nl);
}
 
struct Satellite{
    int T;
    int v, w, d;
    int num;
    vector<pair<int, int>> pos;
    multiset<pair<int, pair<int, int>>> taken;
 
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
            } else if (phi + v < -90 * gr){
                phi = -180 * gr - phi - v;
                lambda = -180 * gr + lambda - es;
                v = -v;
            }
            lambda %= (360 * gr);
            if (lambda >= 180 * gr)
            lambda -= (360 * gr);
 
            pos[i + 1] = {phi, lambda};
        }
    }
 
    pair<int, int> get(int t) const {
        return pos[t];
    }
 
    pair<int, int> operator [](int t) const {
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
        pair<int, int> pp = make_pair(phi, lambda);
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
        pair<int, int> pp = make_pair(phi, lambda);
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
            res.push_back(t);
        }
        return res;
    }
};
struct Collection{
	int val;
	vector<pair<int, int>> t;
	vector<pair<int, int>> r;

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
};

struct Photo
{
    int phi, lambda, turn, id;
};


int score(vector <Collection> & cols, vector <Photo> & photos)
{
    int result = 0;
    map <pair <int, int>, vector <int> > M;
    for (int i = 0; i < (int)photos.size(); i++)
        M[make_pair(photos[i].phi, photos[i].lambda)].push_back(photos[i].turn);
    for (auto col : cols)
    {
        bool col_ok = true;
        for (int part = 0; part < (int)col.t.size(); part++)
        {
            pair <int, int> p = col.t[part];
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
                for (pair <int, int> seg : col.r)
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


vector <Photo> oneSat(int T, Satellite sat, vector <pii> list1)
{
    set <pii> list;
    for (auto p : list1)
        list.insert(p);
    printf("list size is %d\n", (int)list.size());
    vector <Photo> res;
    for (int cur = 0; cur < T; cur++)
    {
        for (auto  p : list)
        {
            if (sat.check_photo(cur, p.fi, p.se))
            {
                sat.add_photo(cur, p.fi, p.se);
                res.pb(Photo{p.fi, p.se, cur, 0});           
                list.erase(p);
                break;
            }
        }
    }
    return res;
}


int main(){

	int T = nxt();
	int S = nxt();
	vector<Satellite> sat(S);
	for (int i = 0; i < S; i++)
		sat[i].in(T, i);

	int C = nxt();
	vector<Collection> col(C);
	for (int i = 0; i < C; i++)
		col[i].in();
    vector <Collection> tmp1;
    tmp1.push_back(col[0]);
    vector <Photo> tmp2;
    tmp2.push_back(Photo{col[0].t[0].first, col[0].t[0].second, col[0].r[0].first, 0});
    printf("%d\n", score(tmp1, tmp2));
 /*   forn(i, C)
    {
        printf("size of col %d is %d range %d %d\n", i, (int)col[i].t.size(), col[i].r[0].fi, col[i].r[0].se);
        //cout << col[i].t.size() << " ";       
        assert(col[i].r.size() == 1);
    }*/
    /*for (int j = 0; j < C; j++)
    {
        printf("col %d\n", j);
        vector <pii> list;
        list.pb(col[j].t[0]);
        vector <Photo> answer = oneSat(T, sat[0], list);
        assert(answer.size() == 0);
//        printf("%d\n", (int)answer.size());
    }*/
    //for (auto photo : answer)
      //  printf("%d %d %d %d\n", photo.phi, photo.lambda, photo.turn, photo.id);
//    oneSat();   

	return 0;
}
