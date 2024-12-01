/**
 * Author: Lucian Bicsi
 * Date: 2021-03-10
 * Description: KD-tree (2d, can be trivially extended to kd). 
 * Not sure how it works for duplicate points. 
 * Takes about ~0.7s for $10^6$ \textbf{random} queries.
 * Status: Tested on infoarena nuke, fuzz tested.
 */
#pragma once

using Point = array<int, 2>;

struct KDTree {
  int n;
  vector<Point> P; 
 
  KDTree(vector<Point> P) : n(P.size()), P(P) {
    build(0, n, 0);
  }
  ll sqr(ll x) { return x * x; }
  void build(int b, int e, int spl) {
    if (e <= b) return;
    int m = (b + e) / 2;
    nth_element(P.begin() + b, P.begin() + m, P.begin() + e, 
      [&](auto& p, auto& q) { return p[spl] < q[spl]; });
    build(b, m, !spl); 
    build(m + 1, e, !spl);
  }
  Point Nearest(Point p, bool exclude_me = false) {
    ll best = 5e18; Point ans;
    auto go = [&](auto& self, int b, int e, int spl) {
      if (e <= b) return;
      int m = (b + e) / 2;
      auto& q = P[m]; 
      ll now = sqr(q[0] - p[0]) + sqr(q[1] - p[1]);
      if (now >= exclude_me && now < best) best = now, ans = q;
      if (p[spl] < q[spl]) {
        self(self, b, m, !spl);
        if (q[spl] - p[spl] < 1e-5 + sqrt(best)) 
          self(self, m + 1, e, !spl);
      } else {
        self(self, m + 1, e, !spl);
        if (p[spl] - q[spl] < 1e-5 + sqrt(best)) 
          self(self, b, m, !spl);
      }
    };
    go(go, 0, n, 0); // y-combinator is considerably faster.
    return ans;
  }
};