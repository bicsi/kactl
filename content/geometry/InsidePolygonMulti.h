/**
 * Author: Johan Sannemo
 * Date: 2017-03-12
 * License: CC0
 * Source: Wikipedia
 * Description: Given a (possibly non-convex) polygon P and
 * Q query points, computes if the points are inside P or not.
 * Returns -1 for strictly outside, 0 for edge, 1 for strictly
 * inside. If no points are on the polygon, you can remove the
 * events of type 2 completely.
 * Status: Tested.
 * Time: O((N + Q) \log N)
 */
#pragma once

#include <bits/stdc++.h>
#include <bits/extc++.h>

using namespace std;
using namespace __gnu_pbds;

vector<int> PointsInPolygon(vector<Point> P, vector<Point> Q) {
  int n = P.size(), q = Q.size();
  
  // Step 1: add events to sweepline
  vector<tuple<Point, int, int, int>> events;
  auto process = [&](int i, int j) {
    events.emplace_back(P[i], 2, i, i);
    if (P[j] < P[i]) swap(i, j);
    if (P[i].real() == P[j].real()) {
      events.emplace_back(P[i], 2, i, j);
    } else {
      events.emplace_back(P[i], 1, i, j);
      events.emplace_back(P[j], 0, i, j);
    }
  };
  for (int i = 0; i < n; ++i) process(i, (i + 1) % n);
  for (int i = 0; i < q; ++i)
    events.emplace_back(Q[i], 3, i, -1);
  
  // Step 2: Prepare sweepline status
  sort(events.begin(), events.end());
  auto cmp = [](pair<Point, Point> p1, pair<Point, Point> p2) {
    Point a, b, p, q; tie(a, b) = p1; tie(p, q) = p2;
    
    int v = sgn(det(a, b, p)) + sgn(det(a, b, q));
    if (v != 0) return v > 0;
    return sgn(det(p, q, a)) + sgn(det(p, q, b)) < 0;
  };
  
  tree<pair<Point, Point>, null_type, decltype(cmp),
    rb_tree_tag, tree_order_statistics_node_update> s(cmp);
  vector<int> ans(q);
  Point vert{-1, -1};
  vert *= (int)(2e9);
  
  // Step 3: Solve
  for (auto itr : events) {
    int tp, i, j; tie(ignore, tp, i, j) = itr;
    
    if (tp == 0) s.erase({P[i], P[j]});
    if (tp == 1) s.insert({P[i], P[j]});
    if (tp == 2) vert = max(vert, P[j]);
    if (tp == 3) {
      auto q = Q[i];
      auto it = s.lower_bound({q, q});
      int dist = s.order_of_key({q, q});
      ans[i] = (dist % 2 ? 1 : -1);
      
      if ((it != s.end() && det(it->first, it->second, q) == 0)
          || (vert.real() == q.real() && vert.imag() >= q.imag()))
        ans[i] = 0;
    }
  }
  return ans;
}

