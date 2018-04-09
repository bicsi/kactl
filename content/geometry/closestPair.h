/**
 * Author: Per Austrin, Max Bennedich, Gunnar Kreitz
 * Date: 2004-03-15
 * Description: Returns the indices to the closest pair of points in the point vector $pts$ after the call. The distance can be easily computed. Might fail when using floating point (distance should be arbitrarily close though).
 * Time: O(n \log n)
 */
#pragma once

#include "Point.h"

using T = long long;
using Point = complex<T>;

pair<int, int> ClosestPair(vector<Point> pts) {
  int n = pts.size();
  
  vector<int> order(n);
  iota(order.begin(), order.end(), 0);
  sort(order.begin(), order.end(), [&](int a, int b) {
    return pts[a].real() < pts[b].real();
  });
  set<pair<T, int>> s;
  
  T best_dist = numeric_limits<T>::max();
  pair<int, int> sol;
  
  int ii = 0, jj = 0;
  while (ii < n) {
    T d = ceil(sqrt(best_dist));
    int i = order[ii], j = order[jj];
    
    if (i != j && pts[i].real() - pts[j].real() >= best_dist) {
      s.erase({pts[j].imag(), j});
      jj += 1;
    } else {
      auto it1 = s.lower_bound({pts[i].imag() - d, -1});
      auto it2 = s.upper_bound({pts[i].imag() + d, n});
      
      for (auto it = it1; it != it2; ++it) {
        T now_dist = norm(pts[i] - pts[it->second]);
        if (best_dist > now_dist) {
          best_dist = now_dist;
          sol = {i, it->second};
        }
      }
      s.insert({pts[i].imag(), i});
      ii += 1;
    }
  }
  return sol;
}

