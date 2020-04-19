
inline int64_t gilbertOrder(int x, int y, int pow, int rotate) {
	if (pow == 0) {
		return 0;
	}
	int hpow = 1 << (pow-1);
	int seg = (x < hpow) ? (
		(y < hpow) ? 0 : 3
	) : (
		(y < hpow) ? 1 : 2
	);
	seg = (seg + rotate) & 3;
	const int rotateDelta[4] = {3, 0, 0, 1};
	int nx = x & (x ^ hpow), ny = y & (y ^ hpow);
	int nrot = (rotate + rotateDelta[seg]) & 3;
	int64_t subSquareSize = int64_t(1) << (2*pow - 2);
	int64_t ans = seg * subSquareSize;
	int64_t add = gilbertOrder(nx, ny, pow-1, nrot);
	ans += (seg == 1 || seg == 2) ? add : (subSquareSize - add - 1);
	return ans;
}
 
struct query {
	int l, r, id;
	int64_t ord;
	query(int a,int b,int dd){
		l=a,r=b,id=dd;
	}
	inline void calcOrder() {
		ord = gilbertOrder(l, r, 21, 0);
	}
};
 
inline bool operator<(const query &a, const query &b) {
	return a.ord < b.ord;
}


int cur_l = 0;
    int cur_r = -1;
	for(auto q:Queries){
		while (cur_l > q.l) {
            cur_l--;
            add(v[cur_l]);
        }
        while (cur_r < q.r) {
            cur_r++;
            add(v[cur_r]);
        }
        while (cur_l < q.l) {
            remove(v[cur_l]);
            cur_l++;
        }
        while (cur_r > q.r) {
            remove(v[cur_r]);
            cur_r--;
        }
		if(akp==size)ans[q.id]=1;
	}
