/**
 * Author: Lucian Bicsi
 * License: CC0
 * Description: Add and remove intervals from a set of disjoint intervals.
 * Will merge the added interval with any overlapping intervals in the set when adding.
 * Intervals are [inclusive, exclusive).
 * Status: Somehow tested (Infoarena hotel)
 * Time: O(\log N)
 */
#pragma once
struct IntervalContainer {
  map<int, int> s;
  using Iter = map<int, int>::iterator;
  
  Iter AddInterval(int l, int r) {
    if (l == r) return s.end();
    Iter it = s.lower_bound(l);
    while (it != s.end() && it->first <= r) {
      r = max(r, it->second);
      it = s.erase(it);
    }
    while (it != s.begin() && (--it)->second >= l) {
      l = min(l, it->first);
      r = max(r, it->second);
      it = s.erase(it);
    }
    return s.insert({l, r}).first;
  }
  
  Iter FindInterval(int x) {
    auto it = s.upper_bound(x);
    if (it == s.begin() or (--it)->second <= x)
      return s.end();
    return it;
  }
  
  void RemoveInterval(int l, int r) {
    if (l == r) return;
    auto it = AddInterval(l, r);
    int l2 = it->first, r2 = it->second;
    s.erase(it);
    if (l != l2) s.insert({l2, l});
    if (r != r2) s.insert({r, r2});
  }
};
