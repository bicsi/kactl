/**
 * Author: Lucian Bicsi
 * Date: 2021-01-27
 * License: Unlicense
 * Source: own work
 * Description:
 \\\begin{minipage}{75mm}Returns the convex hull of a set of points. 
   Sorts hull in counter-clockwise order.
   Points on the edge of the hull between two other points are considered part of the hull.
   To change that, change the sign under (*) to make it non-strict.
 \end{minipage}
 \begin{minipage}{15mm}
 \vspace{-6mm}
 \includegraphics[width=\textwidth]{../content/geometry/ConvexHull}
 \vspace{-6mm}
 \end{minipage}
 * Status: tested with Kattis problems convexhull
 * Time: O(N \log N)
 * Status: stress-tested, tested with kattis:convexhull
*/
#pragma once

#include "Point.h"

vector<Point> HullHalf(vector<Point>& P, int z) {
  Poly ret; // z = +1 if lower, -1 if upper -^
  for (auto p : P) {
    while ((int)ret.size() >= 2 &&                // (*)
        z * sgn(det(ret.end()[-2], ret.end()[-1], p)) < 0)
      ret.pop_back();
    ret.push_back(p);
  }
  return ret;
}

vector<Point> Hull(vector<Point> P) {
  sort(P.begin(), P.end());
  P.erase(unique(P.begin(), P.end()), P.end());
  if (P.size() <= 1) return P;
  auto l = HullHalf(P, +1), u = HullHalf(P, -1); 
  l.insert(l.end(), u.rbegin() + 1, u.rend() - 1);
  return l;
}
