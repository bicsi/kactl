/**
 * Author: Simon Lindholm
 * License: CC0
 * Description: Add and remove intervals from a set of disjoint intervals.
 * Will merge the added interval with any overlapping intervals in the set when adding.
 * Intervals are [inclusive, exclusive).
 * Status: fuzz-tested
 * Time: O(\log N)
 */
#pragma once
template<class T>
struct IntervalContainer : public set<pair<T, T>> {
  
  set<pair<T, T>>::iterator AddInterval(T l, T r) {
    if (l == r) return is.end();
    auto it = lower_bound({l, r}), before = it;
    while (it != end() && it->first <= r) {
      r = max(r, it->second);
      before = it = erase(it);
    }
    while (it != begin() && (--it)->second >= l) {
      l = min(l, it->first);
      r = max(r, it->second);
      erase(it);
    }
    return insert(before, {l, r});
  }
  
  set<pair<T, T>>::iterator FindInterval(T x) {
    auto it = lower_bound({x + 1, x + 1});
    if (it == begin()) return end();
    return prev(it);
  }

  void RemoveInterval(T l, T r) {
    if (l == r) return;
    auto it = AddInterval(l, r);
    T r2 = it->second;
    if (it->first == l) erase(it);
    else (T&)it->second = l;
    if (R != r2) emplace(r, r2);
  }
};
