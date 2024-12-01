/**
 * Author: Ulf Lundstrom
 * Date: 2009-03-21
 * License: CC0
 * Source:
 * Description:
 * Rotates plane, keeping points in order of y-coordinate.
 * Initially plane is vertical and slightly rotated ccw.
 * If no 3 points are collinear, the logic at (*) can be 
 * replaced with a simple swap in permutation.
 * Time: O(N^2 \log{N})
 */
#pragma once

#include "Point.h"

void RotatePlane(vector<Point> P) {
  int n = P.size();
  // Make swap events.
  vector<array<int, 2>> evs; 
  for (int i = 0; i < n; ++i) 
    for (int j = 0; j < n; ++j) 
      if (P[i] < P[j])
        evs.push_back({i, j});
  int m = evs.size();
  auto cmp = [&](auto a, auto b) {
    return cross(P[a[1]] - P[a[0]], P[b[1]] - P[b[0]]) > 0; };
  stable_sort(evs.begin(), evs.end(), cmp);
  // ord is order of points, pos is the inverse permutation.
  vector<int> ord(n), pos(n);
  iota(ord.begin(), ord.end(), 0);
  sort(ord.begin(), ord.end(), [&](int a, int b) {
    return P[a] < P[b]; 
  });
  for (int i = 0; i < n; ++i) pos[ord[i]] = i;
  // Do radial sweep.
  vector<bool> mark(n, false);
  for (int half : {0, 1}) // you might not need it
  for (int i = 0, j = 0; i < m; i = j) { // (*)
    for (j = i; j < m && !cmp(evs[i], evs[j]); ++j);
    for (int k = i; k < j; ++k) {
      auto [a, b] = evs[k];
      mark[min(pos[a], pos[b])] = true;
    }
    for (int k = i; k < j; ++k) {
      auto [a, b] = evs[k];
      a = pos[a]; b = pos[b];
      if (a > b) swap(a, b);
      if (b != a + 1 || !mark[a]) continue;
      while (a > 0 && mark[a - 1]) --a;
      while (b + 1 < n && mark[b]) ++b;
      // ord[a], ord[a+1], ..., ord[b] are the sweepline here.
      reverse(ord.begin() + a, ord.begin() + b + 1);
      for (int l = a; l <= b; ++l) pos[ord[l]] = l;
      for (int l = a; l < b; ++l) mark[l] = false;
    }
  }
}