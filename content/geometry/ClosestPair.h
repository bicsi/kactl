/**
 * Author: Simon Lindholm
 * Date: 2019-04-17
 * License: CC0
 * Source: https://codeforces.com/blog/entry/58747
 * Description: Finds the closest pair of points. Returns 
 * the minimum \textbf{squared distance}, along with the 
 * points. Need to include proper operator< in namespace std
 * (see Point.h).
 * Time: O(N \log N)
 * Usage: auto [d, p, q] = ClosestPair(pts);
 * Status: stress-tested
 */
#pragma once
#include "Point.h"

tuple<long long, Point, Point> ClosestPair(vector<Point> v) {
  assert((int)v.size() > 1);
  sort(v.begin(), v.end(), [&](Point a, Point b) {
    return a.imag() < b.imag();
  });
  set<Point> s; int j = 0;
  tuple<long long, Point, Point> ret{4e18, {}, {}};
  for (auto p : v) {
    long long d = 1 + sqrt(get<0>(ret));
    while (v[j].imag() <= p.imag() - d) s.erase(v[j++]);
    auto lo = s.lower_bound(p - d), 
         hi = s.upper_bound(p + d);
    for (auto it = lo; it != hi; ++it) 
      ret = min(ret, {norm(*it - p), *it, p});
    s.insert(p);
  }
  return ret;
}