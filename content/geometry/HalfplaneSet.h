/**
 * Author: Lucian Bicsi
 * Date: 2021-01-26
 * License: CC0
 * Source: Basic geometry
 * Description: Data structure that dynamically keeps track
 * of the intersection of halfplanes. Use is straigntforward.
 * Area should be able to be kept dynamically with some
 * modifications. Does products up to $O(X^4)$.
 *
 * Time: O(\log N) amortized per operation
 * Status: tested on infoarena camera and codechef ALLPOLY
 * Usage:
 *  HalfplaneSet hs;
 *  hs.Cut({0, 1, 2});
 *  double best = hs.Maximize({1, 2});
 */
#pragma once

#include "Line.h"
#include "LineIntersection.h"

struct HalfplaneSet : multiset<Line> {
  HalfplaneSet() {
    insert({+1, 0, INF}); insert({0, +1, INF});
    insert({-1, 0, INF}); insert({0, -1, INF});
  };
 
  auto adv(auto it, int z) { // z = {-1, +1}
    return (z == -1
      ? --(it == begin() ? end() : it) 
      : (++it == end() ? begin() : it));
  }
  bool chk(auto it) {
    Line l = *it, pl = *adv(it, -1), nl = *adv(it, +1);
    auto [x, y, d] = LineIntersection(pl, nl);
    T4 sat = l.a * x + l.b * y - (T4)l.c * d;
    if (d < 0 && sat < 0) return clear(), 0; // unsat
    if ((d > 0 && sat <= 0) || (d == 0 && sat < 0))
      return erase(it), 1;
    return 0;
  }
  void Cut(Line l) { // add ax + by <= c
    if (empty()) return;
    auto it = insert(l);
    if (chk(it)) return;
    for (int z : {-1, +1}) 
      while (size() && chk(adv(it, z)));
  }
  double Maximize(T a, T b) { // max ax + by
    if (empty()) return -1/0.;
    auto it = lower_bound({a, b});
    if (it == end()) it = begin();
    auto [x, y, d] = LineIntersection(*adv(it, -1), *it);
    return (1.0 * a * x + 1.0 * b * y) / d;
  }
  double Area() {
    double total = 0.;
    for (auto it = begin(); it != end(); ++it) {
      auto [x1, y1, d1] = LineIntersection(*adv(it, -1), *it);
      auto [x2, y2, d2] = LineIntersection(*it, *adv(it, +1));
      total += (1.0 * x1 * y2 - 1.0 * x2 * y1) / d1 / d2;
    }
    return total * 0.5;
  }
};