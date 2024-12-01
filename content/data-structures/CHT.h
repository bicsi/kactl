/**
 * Author: Lucian Bicsi
 * Description: Simple convex hull trick. Requires lines to 
 * be inserted in increasing slopes order. Queries have to 
 * be increasing in $x$, but it can be relaxed to any values,
 * by doing binary search on the stack.
 * Time: O(1) amortized per operation
 * Status: tested
 */
#pragma once

struct CHT {
  deque<tuple<ll, ll, ll>> stk;
  ll ceil(ll a, ll b) { return a / b + (a % b > 0); }
  
  void InsertLine(ll a, ll b) {
    ll p = -INF;
    while (stk.size()) {
      auto [pp, ap, bp] = stk.back();
      if (ap == a) p = bp > b ? INF : -INF;
      else p = ceil(bp - b, a - ap);
      if (p > pp) break;
      stk.pop_back();
    }
    if (p != INF) stk.emplace_back(p, a, b);
  }
  ll EvalMax(ll x) {
    // prev(upper_bound(all(stk), {x, INF, INF}))
    while ((int)stk.size() > 1 && get<0>(stk[1]) <= x)
      stk.pop_front(); 
    auto [_, a, b] = stk.front();
    return a * x + b;
  }
};