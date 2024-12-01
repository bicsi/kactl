/**
 * Author: Simon Lindholm
 * Date: 2017-04-20
 * License: CC0
 * Source: own work
 * Description: Container where you can add lines of the form kx+m, and query maximum values at points x.
 *  Useful for dynamic programming (``convex hull trick'').
 * Time: O(\log N) amortized per operation
 * Status: stress-tested
 */
#pragma once

bool QUERY;
struct Line {
  mutable ll a, b, p;
  ll Eval(ll x) const { return a * x + b; }
  bool operator<(const Line& o) const {
    return QUERY ? p < o.p : a < o.a;
  }
};
struct LineContainer : multiset<Line> {
  ll div(ll a, ll b) { return a / b - (a % b < 0); }
  void InsertLine(ll a, ll b) {
    auto isect = [&](auto x, auto y) {
      if (y == end()) return x->p = INF, false; 
      if (x->a == y->a) x->p = x->b > y->b ? INF : -INF;
      else x->p = div(x->b - y->b, y->a - x->a);
      return x->p >= y->p;
    };
    auto nx = insert({a, b, 0}), it = nx++, pv = it;
    while (isect(it, nx)) nx = erase(nx);
    if (pv != begin() && isect(--pv, it)) 
      isect(pv, it = erase(it));
    while ((it = pv) != begin() && (--pv)->p >= it->p)
      isect(pv, erase(it));
  }
  ll EvalMax(ll x) {
    assert(!empty());
    QUERY = 1; auto it = lower_bound({0, 0, x}); QUERY = 0;
    return it->Eval(x);
  }
};

