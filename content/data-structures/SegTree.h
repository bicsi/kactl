/**
 * Author: Lucian Bicsi
 * Description: Very fast and quick segment tree.
 * Only useful for easy invariants. 0-indexed.
 * Range queries are half-open.
 */
#pragma once

struct SegTree {
  vector<ll> T; int n;
  SegTree(int n) : T(2 * n, -INF), n(n) {}
  
  void Update(int pos, ll val) {
    for (T[pos += n] = val; pos /= 2)
      T[pos] = f(T[pos * 2], T[pos * 2 + 1]);
  }
  ll Query(int b, int e) {
    ll r1 = -INF, r2 = -INF;
    for (b += n, e += n; b < e; b /= 2, e /= 2) {
      if (b % 2) r1 = max(r1, T[b++]);
      if (e % 2) r2 = max(T[--e], r2);
    }
    return max(r1, r2);
  }
};