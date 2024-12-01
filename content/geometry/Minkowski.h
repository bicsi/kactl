/**
 * Author: Lucian Bicsi
 * Date: 2021-06-28
 * License: CC0
 * Source: Own
 * Description: 
 * Computes the set $P + Q = \lbrace p + q \mid p \in P, q \in Q \rbrace$,
 * where $P$, $Q$ are convex sets (described by polygons).
 * Status: Tested on shenyang 2018 regional problem D
 * Time: $O(N + M)$
 */
#pragma once

#include "Point.h"

vector<Point> MinkowskiSum(vector<Point> P, vector<Point> Q) {
  int n = P.size(), m = Q.size();
  vector<Point> R = {P[0] + Q[0]};
  for (int i = 1, j = 1; i < n || j < m; ) {
    if (i < n && (j == m || 
        cross(P[i] - P[i - 1], Q[j] - Q[j - 1]) > 0)) {
      R.push_back(R.back() + P[i] - P[i - 1]);
      ++i;
    } else {
      R.push_back(R.back() + Q[j] - Q[j - 1]);
      ++j;
    }
  }
  return R;
}