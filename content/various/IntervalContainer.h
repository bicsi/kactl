/**
 * Author: Lucian Bicsi
 * License: CC0
 * Description: Add and remove intervals from a set of disjoint intervals.
 * Will merge the added interval with any overlapping intervals in the set when adding.
 * Intervals are [inclusive, exclusive).
 * Status: Somewhat tested (Infoarena hotel)
 * Time: O(\log N)
 */
#pragma once

struct IntervalContainer : map<int, int> {
  iterator AddInterval(int l, int r) {
    if (l == r) return end();
    auto it = lower_bound(l);
    while (it != end() && it->first <= r) {
      r = max(r, it->second);
      it = erase(it);
    }
    while (it != begin() && (--it)->second >= l) {
      l = min(l, it->first), r = max(r, it->second);
      it = erase(it);
    }
    return emplace(l, r).first;
  }
  iterator FindInterval(int x) {
    auto it = upper_bound(x);
    if (it == begin() || (--it)->second <= x)
      return end();
    return it;
  }
  void RemoveInterval(int l, int r) {
    if (l == r) return;
    auto it = AddInterval(l, r);
    auto [l2, r2] = *it; erase(it);
    if (l != l2) emplace(l2, l);
    if (r != r2) emplace(r, r2);
  }
};