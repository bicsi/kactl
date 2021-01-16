/**
 * Author: Lucian Bicsi
 * Date: 2017-03-12
 * License: CC0
 * Source: Wikipedia
 * Description: Given a (possibly non-convex) polygon P and
 * Q query points, computes if the points are inside P or not.
 * Returns -1 for strictly outside, 0 for edge, 1 for strictly
 * inside. If no points are on the polygon, you can remove the
 * events of type 2 completely. Products are up to $O(X^2)$.
 * Status: Tested.
 * Time: O((N + Q) \log N)
 */
#pragma once

#include <bits/extc++.h>

using namespace __gnu_pbds;
const int MAXC = 2e9; 

vector<int> PointsInPolygon(vector<Point> P, vector<Point> Q) {
  int n = P.size(), q = Q.size();
  // Make sweepline events.
  vector<tuple<Point, int, int, int>> evs;
  for (int i = 0; i < n; ++i) {
    int a = i, b = (i + 1) % n;
    evs.emplace_back(P[a], 2, a, a);
    if (P[b] < P[a]) swap(a, b);
    if (P[a].real() < P[b].real()) {
      evs.emplace_back(P[a], 1, a, b),
      evs.emplace_back(P[b], 0, a, b);
    } else evs.emplace_back(P[a], 2, a, b);
  }
  for (int i = 0; i < q; ++i)
    evs.emplace_back(Q[i], 3, i, -1);
  sort(evs.begin(), evs.end());
  // Solve.
  auto cmp = [](pair<Point, Point> p1, pair<Point, Point> p2) {
    auto [a, b] = p1; auto [p, q] = p2;
    int v = sgn(det(a, b, p)) + sgn(det(a, b, q));
    if (v != 0) return v > 0;
    return sgn(det(p, q, a)) + sgn(det(p, q, b)) < 0;
  };
  tree<pair<Point, Point>, null_type, decltype(cmp),
      rb_tree_tag, tree_order_statistics_node_update> s(cmp);
  vector<int> ans(q);
  Point vert{-MAXC - 1, 0};
  for (auto [_, tp, i, j] : evs) {
    if (tp == 0) s.erase({P[i], P[j]});
    if (tp == 1) s.insert({P[i], P[j]});
    if (tp == 2) vert = max(vert, P[j]);
    if (tp == 3) {
      auto q = Q[i];
      auto it = s.lower_bound({q, q});
      int cnt = s.order_of_key({q, q});
      ans[i] = (cnt % 2 ? 1 : -1);
      if ((it != s.end() && det(it->first, it->second, q) == 0)
          || (vert.real() == q.real() && 
              vert.imag() >= q.imag()))
        ans[i] = 0;
    }
  }
  return ans;
}

