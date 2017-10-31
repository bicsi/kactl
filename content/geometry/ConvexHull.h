/**
 * Author: Johan Sannemo
 * Date: 2017-04-16
 * License: CC0
 * Source: Basic algorithm knowledge
 * Description:
 \\\begin{minipage}{75mm}Returns a pair (upper\_hull, lower\_hull).
   Points on the edge of the hull between two other points are considered part of the hull.
   To change that, change the signs at (1) and (2) to make them non-strict.
 \end{minipage}
 \begin{minipage}{15mm}
 \vspace{-6mm}
 \includegraphics[width=\textwidth]{../content/geometry/ConvexHull}
 \vspace{-6mm}
 \end{minipage}
 * Status: tested with Kattis problems convexhull
 * Time: O(n \log n)
*/
#pragma once

#include "Point.h"

using Poly = vector<Point>;
pair<Poly, Poly> ConvexHull(Poly P) {
  sort(P.begin(), P.end(), [](Point a, Point b) {
    return make_pair(a.x(), a.y()) < make_pair(b.x(), b.y());
  });
  P.erase(unique(P.begin(), P.end()), P.end());
  
  Poly up, dw;
  for (auto p : P) {
    while (up.size() >= 2 &&
           det(up[up.size() - 2], up.back(), p) > 0) // (1)
      up.pop_back();
    up.push_back(p);
    
    while (dw.size() >= 2 &&
          det(dw[dw.size() - 2], dw.back(), p) < 0) // (2)
      dw.pop_back();
    dw.push_back(p);
  }
  return tie(up, dw);
}
