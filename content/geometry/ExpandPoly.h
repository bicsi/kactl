/**
 * Author: Lucian Bicsi
 * Date: 2021-01-27
 * License: Unlicense
 * Source: own work
 * Description: Expands the edges of a polygon with some delta $d$. 
 * To shrink, call with $d < 0$. 
 * Warning: Resulting polygon might self-intersect for
 * big values of $d$.
 * Status: tested on ICPC 2017 problem A
 * Time: $O(N)$
*/
#pragma once

#include "Point.h"

vector<Point> ExpandPoly(vector<Point> P, double d) {
  int n = P.size();
  vector<Point> ret(n);
  for (int i = 0; i < n; ++i) {
    Point prv = P[i == 0 ? n - 1 : i - 1],
          nxt = P[i == n - 1 ? 0 : i + 1],
          cur = P[i];
    Point d1 = cur - prv, d2 = nxt - cur;
    d1 = perp(d1) / abs(d1), d2 = perp(d2) / abs(d2);
    ret[i] = LineIntersection(
        prv - d1 * d, cur - d1 * d,
        cur - d2 * d, nxt - d2 * d);
  }
  return ret;
}