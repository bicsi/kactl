/**
 * Author: Lucian Bicsi
 * Date: 2017-03-12
 * License: CC0
 * Source: Wikipedia
 * Description: Given a list of points P, a list of segments E,
 * and a list of query points Q, computes for each point the
 * segment that is closest from each query point looking down
 * (towards y = -INF). Returns -1 if no such segment is found,
 * -2 if query point coincides with input point, or the index
 * of the segment otherwise. Products are up to $O(X^2)$.
 * Status: Tested on pointinpolygon.
 * Warning: Segments have to be non-intersecting and non-degenerate.
 * Time: O((N + Q) \log N)
 */
#pragma once

#include "Point.h"

vector<int> PointLocation(vector<Point>& P, 
    vector<array<int, 2>>& E, vector<Point>& Q) {
  int n = P.size(), m = E.size(), q = Q.size();
  // Make sweepline events.
  vector<tuple<Point, int, int>> evs;
  for (int i = 0; i < m; ++i) {
    auto& [a, b] = E[i];
    if (P[b] < P[a]) swap(a, b);
    evs.emplace_back(P[a], 3, i),
    evs.emplace_back(P[b], 0, i);
  }
  for (int i = 0; i < n; ++i) evs.emplace_back(P[i], 1, i);
  for (int i = 0; i < q; ++i) evs.emplace_back(Q[i], 2, i);
  // Solve.
  sort(evs.begin(), evs.end());
  auto cmp = [&](int i, int j) {
    auto a = P[E[i][0]], b = P[E[i][1]], 
         p = P[E[j][0]], q = P[E[j][1]];
    return det(a + a, b + b, p + q) > det(p + p, q + q, a + b);
  };
  set<int, decltype(cmp)> s(cmp);
  int last = -1;
  vector<int> ans(q);
  P.emplace_back(); E.emplace_back();
  for (auto [_, t, i] : evs) {
    if (t == 0) s.erase(i);
    if (t == 1) last = i;
    if (t == 2) {
      if (last != -1 && P[last] == Q[i]) ans[i] = -2;
      else {
        P[n] = Q[i]; E[m] = {n, n};
        auto it = s.lower_bound(m);
        if (it != s.end()) ans[i] = *it;
        else ans[i] = -1;
      }
    }
    if (t == 3) s.insert(i);
  }
  P.pop_back(); E.pop_back();
  return ans;
}
