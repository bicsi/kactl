/**
 * Author: Lucian Bicsi
 * Date: 2019-04-17
 * License: CC0
 * Source: https://codeforces.com/blog/entry/75929
 * Description: Dynamic convex hull tree. Useful
 * for onion peeling. Can be made persistent by replacing the
 * condition at (*) with true. Hull is trigonometric ordered and
 * non-strict. To make it strict, play with the inequalities.
 * To allow insertions as well, wrap it in a segment tree of
 * integers and combine with the given function. Works in around
 * 1.5 seconds for N = 200000. Does products up to $O(X^3)$.
 * Time: O(\log^2 N) per operation
 * Status: tested on library-checker
 * Warning: $P$ has to be sorted (either increasing or decreasing)
 */

#pragma once

struct DynHull {
  struct Node { int bl, br, l, r, lc, rc; };
  vector<Node> T = {{-1, -1, -1, -1, 0, 0}};
  vector<Point> P;

  DynHull(vector<Point> P) : P(P) {}

  bool leaf(int x) { return T[x].l == T[x].r; }
  int combine(int lc, int rc, int ret = -1) {
    if (!lc || !rc) return lc + rc; 
    if (ret == -1 || ret == lc || ret == rc) // (*) 
      ret = T.size(), T.push_back({});

    T[ret] = {-1, -1, T[lc].l, T[rc].r, lc, rc};
    while (!leaf(lc) || !leaf(rc)) {
      int a = T[lc].bl, b = T[lc].br, 
          c = T[rc].bl, d = T[rc].br;
      if (a != b && det(P[a], P[b], P[c]) > 0) {
        lc = T[lc].lc;
      } else if (c != d && det(P[b], P[c], P[d]) > 0) {
        rc = T[rc].rc;
      } else if (a == b) {
        rc = T[rc].lc;
      } else if (c == d) {
        lc = T[lc].rc;
      } else {
        auto s1 = det(P[a], P[b], P[c]), 
             s2 = det(P[a], P[b], P[d]);
        assert(s1 >= s2);
        auto xc = P[c].real(), xd = P[d].real(), 
             xm = P[T[rc].l].real(), xa = P[a].real();
        if ((s1 * xd - s2 * xc < (s1 - s2) * xm) ^ (xa < xm)) {
          rc = T[rc].lc;
        } else { 
          lc = T[lc].rc;
        }
      }
    }
    T[ret].bl = T[lc].l; T[ret].br = T[rc].l;
    return ret;
  }
  // Build the hull from points P[l..r]
  int Build(int l, int r) {
    if (l == r) {
      T.push_back({l, l, l, l, 0, 0});
      return T.size() - 1;
    }
    int m = (l + r) / 2;
    return combine(Build(l, m), Build(m + 1, r));
  }
  // Maximize dot product with p [set p = {x, 1} for CHT]
  // UNTESTED: USE WITH CAUTION
  int Maximize(int x, Point p) {
    assert(x);
    if (leaf(x)) return T[x].l; // can also return dot here
    return (dot(P[T[x].br], p) > dot(P[T[x].bl], p) 
      ? Maximize(T[x].rc, p)
      : Maximize(T[x].lc, p));
  }
  // Erase P[i] from hull (if it exists)
  int Erase(int x, int i) { 
    if (!x || T[x].r < i || T[x].l > i) return x;
    return leaf(x) ? 0 : combine(
      Erase(T[x].lc, i), Erase(T[x].rc, i), x);
  }
  // Calls callback on all points of the hull.
  template<typename Callback>
  void Hull(int x, Callback&& cb, int l = 0, int r = 1e9) { 
    if (!x || l > r) return;
    if (leaf(x)) { cb(T[x].l); return; }
    Hull(T[x].lc, cb, max(l, T[x].l), min(r, T[x].bl));
    Hull(T[x].rc, cb, max(l, T[x].br), min(r, T[x].r));
  }
};