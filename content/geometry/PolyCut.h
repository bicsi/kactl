/**
 * Author: Ulf Lundstrom
 * Date: 2009-03-21
 * License: CC0
 * Source:
 * Description:\\
\begin{minipage}{75mm}
 Returns a vector with the vertices of a polygon with everything to the left of the line going from s to e cut away.
\end{minipage}
\begin{minipage}{15mm}
\vspace{-6mm}
\includegraphics[width=\textwidth]{content/geometry/PolygonCut}
\vspace{-6mm}
\end{minipage}
 * Warning: Result might contain degenerations when applied to a concave polygon.
 * Usage:
 * 	vector<Point> p = ...;
 * 	p = PolygonCut(p, Point(0, 0), Point(1, 0));
 */
#pragma once

#include "Point.h"
#include "LineIntersection.h"

vector<Point> PolygonCut(vector<Point>& P, Point s, Point e) {
  int n = P.size(); vector<Point> res;
  for (int i = 0, j = n - 1; i < n; j = i++) {
    int z1 = sgn(det(s, e, P[i])), z2 = sgn(det(s, e, P[j]));
    if (z1 * z2 == -1) 
      res.push_back(LineIntersection(s, e, P[i], P[j]));
    if (z1 <= 0) res.push_back(P[i]);
  }
  return res;
}