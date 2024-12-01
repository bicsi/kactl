/**
 * Author: Simon Lindholm
 * Date: 2017-05-11
 * License: CC0
 * Source: folklore
 * Description: Computes sums $a[i,j]$ for all $i<x$, $j<y$, 
 * and increases single elements $a[x,y]$.
 * Requires that the elements to be updated are known in 
 * advance (call FakeUpdate() before Build()).
 * Time: $O(\log^2 N)$. Use persistent segment trees 
 * for $O(\log N)$.
 * Status: stress-tested
 */
#pragma once

struct Fenwick2D {
  vector<vector<int>> ys;
  vector<vector<int>> T;
  Fenwick2D(int n) : ys(n + 1) {}
  
  void FakeUpdate(int x, int y) {
    for (++x; x < (int)ys.size(); x += (x & -x))
      ys[x].push_back(y);
  }
  void Build() {
    for (auto& v : ys) {
      sort(v.begin(), v.end());
      v.erase(unique(v.begin(), v.end()), v.end());
      T.emplace_back(v.size() + 1);
    }
  }
  int ind(int x, int y) {
    auto it = upper_bound(ys[x].begin(), ys[x].end(), y);
    return it - ys[x].begin();
  }
  void Update(int x, int y, int val) {
    for (++x; x < (int)ys.size(); x += (x & -x))
    for (int i = ind(x,y); i < (int)T[x].size(); i += (i & -i))
      T[x][i] = T[x][i] + val;
  }
  int Query(int x, int y) {
    int sum = 0;
    for (; x > 0; x -= (x & -x))
    for (int i = ind(x,y); i > 0; i -= (i & -i))
      sum = sum + T[x][i];
    return sum;
  }
};

