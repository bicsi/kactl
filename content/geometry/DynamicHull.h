/**
 * Author: Lucian Bicsi
 * Date: 2019-04-17
 * License: CC0
 * Source: https://codeforces.com/blog/entry/75929
 * Description: Persistent dynamic convex hull tree. Useful
 * for onion peeling. Hull is trigonometric ordered and
 * non-strict. To make it strict, play with the inequalities.
 * To allow insertions as well, wrap it in a segment tree of
 * integers and combine with the given function. Works in around
 * 2 seconds for N = 200000. Does products up to $O(X^3)$.
 * Time: O(\log^2 N) per operation
 * Status: tested on library-checker
 */

namespace DynamicLowerHull {
  struct Node { int bl, br, l, r, lc, rc; };
  vector<Point> pts;
  vector<Node> T = {{-1, -1, -1, -1, 0, 0}};

  bool leaf(int x) { 
    return T[x].l == T[x].r; 
  }
  int combine(int lc, int rc) {
    if (!lc || !rc) return lc + rc;
    auto split_x = pts[T[rc].l].real();
    int ret = T.size();
    T.push_back({-1, -1, T[lc].l, T[rc].r, lc, rc});

    while (!leaf(lc) || !leaf(rc)) {
      int a = T[lc].bl, b = T[lc].br, 
          c = T[rc].bl, d = T[rc].br;
      if (a != b && det(pts[a], pts[b], pts[c]) > 0) {
        lc = T[lc].lc;
      } else if (c != d && det(pts[b], pts[c], pts[d]) > 0) {
        rc = T[rc].rc;
      } else if (a == b) {
        rc = T[rc].lc;
      } else if (c == d) {
        lc = T[lc].rc;
      } else {
        auto s1 = det(pts[a], pts[b], pts[c]);
        auto s2 = det(pts[b], pts[a], pts[d]);
        assert(s1 + s2 >= 0);
        if (s1 + s2 == 0 || s1 * pts[d].real() 
            + s2 * pts[c].real() < split_x * (s1 + s2)) {
          lc = T[lc].rc;
        } else {
          rc = T[rc].lc;
        }
      }
    }
    T[ret].bl = T[lc].l; T[ret].br = T[rc].l;
    return ret;
  }
  void hull(int x, int l, int r, vector<int>& ret) {
    if (!x || l > r) return;
    if (leaf(x)) { ret.push_back(l); return; }
    hull(T[x].lc, max(l, T[x].l), min(r, T[x].bl), ret);
    hull(T[x].rc, max(l, T[x].br), min(r, T[x].r), ret);
  }
  // Get actual hull.
  vector<int> Hull(int x) {
    vector<int> ret; hull(x, T[x].l, T[x].r, ret); return ret;
  }
  // Erase pts[i] from hull (if it exists)
  int Erase(int x, int i) {
    if (!x || T[x].l > i || T[x].r < i) return x;
    if (leaf(x)) return 0;
    return combine(Erase(T[x].lc, i), Erase(T[x].rc, i));
  }
  // Build the hull from points pts[l..r]
  int Build(int l, int r) {
    // assert(is_sorted(pts.begin() + l, pts.begin() + r + 1));
    if (l == r) {
      T.push_back({l, l, l, l, 0, 0});
      return T.size() - 1;
    }
    int m = (l + r) / 2;
    return combine(Build(l, m), Build(m + 1, r));
  }
}