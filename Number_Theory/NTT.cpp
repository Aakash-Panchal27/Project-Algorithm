// source : https://codeforces.com/blog/entry/86827
void ntt(vector<Mint> &a, bool inv) {
  int n = sz(a);
  int ln = __builtin_ctz(n);
  forn(i, n) {
    int ni = rv[ln][i];
    if (i < ni) swap(a[i], a[ni]);
  }
  forn(st, ln) {
    int len = 1 << st;
    for (int k = 0; k < n; k += (len << 1)) {
      fore(pos, k, k + len){
        Mint l = a[pos];
        Mint r = a[pos + len] * w[st][pos - k];
        a[pos] = l + r;
        a[pos + len] = l - r;
      }
    }
  }
  if (inv) {
    Mint rn = Mint(n).inv();
    forn(i, n) a[i] *= rn;
    reverse(a.begin() + 1, a.end());
  }
}

vector<Mint> mul(vector<Mint> a, vector<Mint> b) {
  int cnt = 1 << (32 - __builtin_clz(sz(a) + sz(b) - 1));
  a.resize(cnt);
  b.resize(cnt);
  ntt(a, false);
  ntt(b, false);
  vector<Mint> c(cnt);
  forn(i, cnt) c[i] = a[i] * b[i];
  ntt(c, true);
  return c;
}
